//------------------------------------------------------------------------------
// Created by Daniel Sefton
// Timing code based on OGRE's implementation
/*
Copyright (c) 2000-2012 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
*/
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Game.h"

#include "Input/Input.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Light.h"
#include "Components/Camera.h"
#include "Util/Entity/World.h"
#include "Util/Entity/System.h"
#include "Util/Entity/SystemManager.h"
#include "Systems/CameraSystem.h"
#include "Systems/MeshSystem.h"
#include "Systems/LightSystem.h"
#include "Systems/SoundSystem.h"
#include "Graphics/RenderSystem.h"
#include "Network/RakClientServer.h"
#include "Scene/SceneManager.h"
#include "Scenes/MenuScene.h"
#include "Scenes/PlayScene.h"
#include "Physics/PhysXWorld.h"
#include "Physics/PhysXScene.h"
#include "Util/Helper/ConfigFile.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
Game::Game(Config& rConfig)
	: mConfig(rConfig)
	, mInitialised(false)
	, mWorld(0)
	, mInput(0)
	, mHeapArea(64 * 1024 * 1024)
	, mLinearArena(mHeapArea)
	, mCameraSystem(0)
	, mMeshSystem(0)
	, mLightSystem(0)
	, mSoundSystem(0)
	, mRenderSystem(0)
	, mRakClientServer(0)
	, mSceneManager(0)
	, mPhysXWorld(0)
	, mPhysXScene(0)
	, mFrameSmoothingTime(5.0f)
{
}
//------------------------------------------------------------------------------
Game::~Game()
{
	shutdown();
}
//------------------------------------------------------------------------------
bool Game::initialiseClient(void* pHandle)
{
	mRenderSystem = DG_NEW(RenderSystem, mLinearArena)();
	mRenderSystem->initialise(pHandle);

	mRenderSystem->setLightingEnabled(true);
	mRenderSystem->setDepthEnabled(true);
	mRenderSystem->setAmbientLight(0.2, 0.2, 0.2);
	mRenderSystem->setCullingMode(CULL_ANTICLOCKWISE);
	mRenderSystem->setAlpha(CMPF_GREATER, 0);
	mRenderSystem->setBlending(SBF_SOURCE_ALPHA, SBF_ONE_MINUS_SOURCE_ALPHA, SBO_ADD);

	// Non-abstracted settings
	IDirect3DDevice9* d3dDevice = mRenderSystem->getD3D9Device();
	d3dDevice->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	d3dDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	d3dDevice->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);
	d3dDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 14);

	// Create world
	mWorld = DG_NEW(World, mLinearArena)(mLinearArena, 50);

	SystemManager& systemManager = mWorld->getSystemManager();

	// Create systems
	mCameraSystem = systemManager.addSystem<CameraSystem>();
	mCameraSystem->cast<CameraSystem>()->setRenderSystem(mRenderSystem);

	mMeshSystem = systemManager.addSystem<MeshSystem>();
	mMeshSystem->cast<MeshSystem>()->setRenderSystem(mRenderSystem);

	mLightSystem = systemManager.addSystem<LightSystem>();
	mLightSystem->cast<LightSystem>()->setRenderSystem(mRenderSystem);

	mSoundSystem = systemManager.addSystem<SoundSystem>();

	// Create input
	mInput = DG_NEW(Input, mLinearArena)((unsigned long)pHandle);

	// Create physics
	mPhysXWorld = DG_NEW(PhysXWorld, mLinearArena)(mLinearArena);
	physx::PxSceneDesc desc(mPhysXWorld->getPxPhysics()->getTolerancesScale());
	//desc.gravity = physx::PxVec3(0, -9.81f, 0);
	desc.gravity = physx::PxVec3(0, -2.0f, 0);
	desc.filterShader = &physx::PxDefaultSimulationFilterShader;
	mPhysXScene = mPhysXWorld->addScene("Main", desc);

	// Create network
	mRakClientServer = DG_NEW(RakClientServer, mLinearArena)();
	mRakClientServer->connect(mConfig.read<String>("server_address"), 
		mConfig.read<int>("server_port"));

	// Create scene manager
	mSceneManager = DG_NEW(SceneManager, mLinearArena)(*mWorld, mLinearArena);
	mSceneManager->addScene(new MenuScene(*mSceneManager, *mInput));
	mSceneManager->addScene(new PlayScene(*mSceneManager, *mInput, *mPhysXWorld));
	mSceneManager->loadScene("Play");

	mTimer = DG_NEW(Timer, mLinearArena)();
	mTimer->reset();

	resetStatistics();

	mInitialised = true;
	return true;
}
//------------------------------------------------------------------------------
bool Game::initialiseServer()
{
	LOG(logINFO) << "Initialising server...";

	// Create network
	mRakClientServer = DG_NEW(RakClientServer, mLinearArena)();
	mRakClientServer->initialiseServer(mConfig.read<int>("max_connections"), 
		mConfig.read<int>("listen_port"));

	mInitialised = true;
	return true;
}
//------------------------------------------------------------------------------
void Game::shutdown()
{
	if (!mInitialised)
		return;
	mInitialised = false;

	if (mTimer != 0)
		DG_DELETE(mTimer, mLinearArena);
	mTimer = 0;

	if (mSceneManager != 0)
		DG_DELETE(mSceneManager, mLinearArena);
	mSceneManager = 0;

	if (mRakClientServer != 0)
		DG_DELETE(mRakClientServer, mLinearArena);
	mRakClientServer = 0;

	mPhysXScene = 0;
	if (mPhysXWorld != 0)
		DG_DELETE(mPhysXWorld, mLinearArena);
	mPhysXWorld = 0;

	if (mInput != 0)
		DG_DELETE(mInput, mLinearArena);
	mInput = 0;

	if (mSoundSystem != 0)
		DG_DELETE(mSoundSystem, mLinearArena);
	mSoundSystem = 0;

	if (mLightSystem != 0)
		DG_DELETE(mLightSystem, mLinearArena);
	mLightSystem = 0;

	if (mMeshSystem != 0)
		DG_DELETE(mMeshSystem, mLinearArena);
	mMeshSystem = 0;

	if (mCameraSystem != 0)
		DG_DELETE(mCameraSystem, mLinearArena);
	mCameraSystem = 0;

	if (mWorld != 0)
		DG_DELETE(mWorld, mLinearArena);
	mWorld = 0;

	if (mRenderSystem != 0)
		DG_DELETE(mRenderSystem, mLinearArena);
	mRenderSystem = 0;
}
//------------------------------------------------------------------------------
void Game::updateClient()
{
	FrameEvent evt;
	populateFrameEvent(FETT_STARTED, evt);

	mPhysXWorld->simulate(0.01);//evt.timeSinceLastFrame);
	updateLogic(0);
	updateGraphics();
	mInput->update();
	mSoundSystem->process();
	mRakClientServer->update();

	updateStats();

	populateFrameEvent(FETT_ENDED, evt);
}
//------------------------------------------------------------------------------
void Game::updateServer()
{
	mRakClientServer->update();
}
//------------------------------------------------------------------------------
void Game::updateLogic(const Real& elapsed)
{
	mWorld->setElapsed(elapsed);
	mSceneManager->updateActiveScene();
}
//------------------------------------------------------------------------------
void Game::updateGraphics()
{
	if (mRenderSystem->beginScene(FBT_COLOUR | FBT_DEPTH))
	{
		mPhysXWorld->syncRenderables();
		mCameraSystem->process();
		mMeshSystem->process();
		mLightSystem->process();

		mRenderSystem->endScene();
	}

	mRenderSystem->present();
}
//------------------------------------------------------------------------------
void Game::updateStats()
{
	++mFrameCount;
	unsigned long thisTime = mTimer->getMilliseconds();

	// check frame time
	unsigned long frameTime = thisTime - mLastTime ;
	mLastTime = thisTime ;

	mStats.bestFrameTime = std::min(mStats.bestFrameTime, frameTime);
	mStats.worstFrameTime = std::max(mStats.worstFrameTime, frameTime);

	// check if new second (update only once per second)
	if (thisTime - mLastSecond > 1000) 
	{ 
		// new second - not 100% precise
		mStats.lastFPS = (float)mFrameCount / (float)(thisTime - mLastSecond) * 1000.0f;

		if (mStats.avgFPS == 0)
			mStats.avgFPS = mStats.lastFPS;
		else
			mStats.avgFPS = (mStats.avgFPS + mStats.lastFPS) / 2; // not strictly correct, but good enough

		mStats.bestFPS = std::max(mStats.bestFPS, mStats.lastFPS);
		mStats.worstFPS = std::min(mStats.worstFPS, mStats.lastFPS);

		mLastSecond = thisTime;
		mFrameCount  = 0;
	}
}
//------------------------------------------------------------------------------
void Game::resetStatistics()
{
	mStats.avgFPS = 0.0;
	mStats.bestFPS = 0.0;
	mStats.lastFPS = 0.0;
	mStats.worstFPS = 999.0;
	mStats.triangleCount = 0;
	mStats.batchCount = 0;
	mStats.bestFrameTime = 999999;
	mStats.worstFrameTime = 0;

	mLastTime = mTimer->getMilliseconds();
	mLastSecond = mLastTime;
	mFrameCount = 0;
}
//------------------------------------------------------------------------------
void Game::populateFrameEvent(FrameEventTimeType type, FrameEvent& evtToUpdate)
{
	unsigned long now = mTimer->getMilliseconds();
	evtToUpdate.timeSinceLastEvent = calculateEventTime(now, FETT_ANY);
	evtToUpdate.timeSinceLastFrame = calculateEventTime(now, type);
}
//------------------------------------------------------------------------------
Real Game::calculateEventTime(unsigned long now, FrameEventTimeType type)
{
	// Calculate the average time passed between events of the given type
	// during the last mFrameSmoothingTime seconds.

	EventTimesQueue& times = mEventTimes[type];
	times.push_back(now);

	if (times.size() == 1)
		return 0;

	// Times up to mFrameSmoothingTime seconds old should be kept
	unsigned long discardThreshold =
		static_cast<unsigned long>(mFrameSmoothingTime * 1000.0f);

		// Find the oldest time to keep
	EventTimesQueue::iterator it = times.begin(),
		end = times.end()-2; // We need at least two times
	while (it != end)
	{
		if (now - *it > discardThreshold)
			++it;
		else
			break;
	}

	// Remove old times
	times.erase(times.begin(), it);

	return Real(times.back() - times.front()) / ((times.size()-1) * 1000);
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------