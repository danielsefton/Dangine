//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Physics/PhysXWorld.h"

#include "Physics/PhysXScene.h"
#include "Physics/PhysXLogOutputStream.h"

#include <PhysX/PxPhysicsAPI.h>
#include <PhysX/extensions/PxDefaultAllocator.h>
#include <PhysX/extensions/PxExtensionsAPI.h>

using namespace physx;

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
PhysXWorld::PhysXWorld(LinearArena& rArena)
	: mArena(rArena)
	, mFoundation(0)
	, mPxPhysics(0)
	, mSimulating(false)
{
	if (!mPxPhysics)
	{
		mAllocator = DG_NEW(PxDefaultAllocator, mArena)();
		mErrorOutputStream = DG_NEW(PhysXLogOutputStream, mArena)();

		mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *mAllocator, *mErrorOutputStream);
		if (!mFoundation)
		{
			LOG(logERROR) << "[PhysX] SDK initialisation failed at PxCreateFoundation.";
			return;
		}

		mPxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale());
		if (!mPxPhysics)
		{
			LOG(logERROR) << "[PhysX] SDK initialisation failed at PxCreatePhysics.";
			return;
		}

		PxCookingParams params;
		mCookingInterface = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, params);
		if (!mCookingInterface)
		{
			LOG(logERROR) << "[PhysX] Cooking initialisation failed.";
			return;
		}

		if (!PxInitExtensions(*mPxPhysics))
		{
			LOG(logERROR) << "[PhysX] Extension initialisation failed.";
			return;
		}

		if (mPxPhysics->getPvdConnectionManager())
		{
			PxVisualDebuggerConnectionFlags theConnectionFlags(PxVisualDebuggerExt::getAllConnectionFlags());
			PVD::PvdConnection* theConnection = PxVisualDebuggerExt::createConnection(mPxPhysics->getPvdConnectionManager(), "localhost", 5425, 500, theConnectionFlags);
			if (theConnection)
				theConnection->release();
		}

		// Create default material
		mDefaultMaterial = mPxPhysics->createMaterial(1.0f, 1.0f, 0.1f);
	}
}
//------------------------------------------------------------------------------
PhysXWorld::~PhysXWorld()
{
	if (mPxPhysics)
	{
		clearScenes();
		mCookingInterface->release();
		mCookingInterface = 0;
		PxCloseExtensions();
		mPxPhysics->release();
		mPxPhysics = 0;
		mFoundation->release();
		mFoundation = 0;
		DG_DELETE(mAllocator, mArena);
		mAllocator = 0;
		DG_DELETE(mErrorOutputStream, mArena);
		mErrorOutputStream = 0;
	}
}
//------------------------------------------------------------------------------
PhysXScene* PhysXWorld::addScene(String name, PxSceneDesc& desc)
{
	PhysXScene* scene = DG_NEW(PhysXScene, mArena)(desc, mPxPhysics, *this);
	mScenes.insert(std::make_pair<String, PhysXScene*>(name, scene));
	return scene;
}
//------------------------------------------------------------------------------
PhysXScene* PhysXWorld::getScene(String name)
{
	auto i = mScenes.find(name);
	if (i != mScenes.end()) return i->second;
	else
	{
		LOG(logERROR) << "[PhysX] Could not find Scene \"" << name << "\".";
		return 0;
	}
}
//------------------------------------------------------------------------------
void PhysXWorld::destroyScene(String name)
{
	auto i = mScenes.find(name);
	if (i != mScenes.end())
	{
		DG_DELETE(i->second, mArena);
		mScenes.erase(i);
	}
	else
	{
		LOG(logERROR) << "[PhysX] Could not find Scene \"" << name << "\".";
	}
}
//------------------------------------------------------------------------------
void PhysXWorld::clearScenes()
{
	for (auto i = mScenes.begin(); i != mScenes.end(); i++)
	{
		DG_DELETE(i->second, mArena);
	}
	mScenes.clear();
}
//------------------------------------------------------------------------------
void PhysXWorld::simulate(Real time)
{
	if (mSimulating)
		LOG(logWARNING) << "[PhysX] startSimulate called while simulation is in progress!";

	mSimulating = true;
	for (auto i = mScenes.begin(); i != mScenes.end(); i++)
	{
		i->second->simulate(time);
	}
	mSimulating = false;
}
//------------------------------------------------------------------------------
void PhysXWorld::syncRenderables()
{
	for (auto i = mScenes.begin(); i != mScenes.end(); i++)
	{
		i->second->syncRenderables();
	}
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------