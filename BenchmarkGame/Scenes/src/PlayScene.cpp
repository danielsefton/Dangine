//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Scenes/PlayScene.h"

#include "Scene/SceneManager.h"
#include "Util/Entity/World.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Light.h"
#include "Components/Camera.h"
#include "Util/Entity/System.h"
#include "Util/Entity/SystemManager.h"
#include "Systems/CameraSystem.h"
#include "Systems/LightSystem.h"
#include "Input/Input.h"
#include "Physics/PhysXWorld.h"
#include "Physics/PhysXScene.h"
#include "Physics/PhysXEntityRenderable.h"
#include "Physics/PhysXMappings.h"
#include "Physics/PhysXGeometry.h"
#include "Physics/PhysXCooker.h"

using namespace physx;

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
PlayScene::PlayScene(SceneManager& rSceneManager, Input& rInput, PhysXWorld& rPhysXWorld)
	: Scene("Play", rSceneManager)
	, mInput(rInput)
	, mPhysXWorld(rPhysXWorld)
	//, mAngle(0)
{
}
//------------------------------------------------------------------------------
PlayScene::~PlayScene()
{
}
//------------------------------------------------------------------------------
void PlayScene::create()
{
	World& world = getSceneManager().getWorld();

	// Camera
	Transform* transCamera = DG_NEW(Transform, world.getLinearArena());
	transCamera->position = vmVector3(-23.0f, 8.0f, 43.0f);

	Camera* camera = DG_NEW(Camera, world.getLinearArena());
	camera->fov = 0.9f;
	camera->yaw = 2.43f;

	world.getEntity(0).addComponent(transCamera);
	world.getEntity(0).addComponent(camera);

	// Light
	Transform* transLight = DG_NEW(Transform,  world.getLinearArena());
	transLight->position = vmVector3(0, 10, 0);

	Light* light = DG_NEW(Light, world.getLinearArena())(0);
	light->lightType = LT_DIRECTIONAL;
	light->direction = vmVector3(0.0f, 0.9f, 1.0f);

	world.getEntity(1).addComponent(transLight);
	world.getEntity(1).addComponent(light);

	// Set active camera and light
	world.getSystemManager().getSystem<MeshSystem>()->setCamera(camera);
	world.getSystemManager().getSystem<MeshSystem>()->setLight(light);

	// Sky
	Transform* transSky = DG_NEW(Transform,  world.getLinearArena());
	transSky->position = vmVector3(0, 0, 0);

	Material matSky;
	matSky.textureFiles.push_back("NoiseVolume.dds");

	Mesh* meshSky = DG_NEW(Mesh, world.getLinearArena());
	meshSky->file = "../media/sphere_inverted.x";
	meshSky->effectFile = "../media/sky.cg";
	meshSky->materials.push_back(matSky);

	world.getEntity(2).addComponent(transSky);
	world.getEntity(2).addComponent(meshSky);

	// Copter
	int amount = 3;
	int spacing = 8;
	int entityNum = 3;
	for (int x = 0; x < amount; ++x)
	{
		for (int y = 0; y < amount; ++y)
		{
			for (int z = 0; z < amount; ++z)
			{
				Transform* transCopter = DG_NEW(Transform, world.getLinearArena());
				transCopter->position = vmVector3(x * spacing, y * spacing, z * spacing);

				Material matCopter;
				Material matCopter2;
				matCopter2.ambient = vmVector4(0.2f, 0.2f, 0.2f, 1.f);
				matCopter2.diffuse = vmVector4(0.7f, 0.7f, 0.7f, 1.f);
				matCopter2.textureFiles.push_back("copter_diffuse.png");
				matCopter2.textureFiles.push_back("copter_normal.png");

				Mesh* meshCopter = DG_NEW(Mesh,  world.getLinearArena());
				meshCopter->file = "../media/copter.x";
				meshCopter->effectFile = "../media/copter.cg";
				meshCopter->materials.push_back(matCopter);
				meshCopter->materials.push_back(matCopter2);

				world.getEntity(entityNum).addComponent(transCopter);
				world.getEntity(entityNum).addComponent(meshCopter);
				++entityNum;
			}
		}
	}

	// Initialise all systems
	world.getSystemManager().initialiseAll();

	mInput.subscribeKeyboard(*this);
	mInput.subscribeMouse(*this);
}
//------------------------------------------------------------------------------
void PlayScene::destroy()
{
	World& world = getSceneManager().getWorld();
	world.getSystemManager().destroyAll();

	mInput.unsubscribeKeyboard(*this);
	mInput.unsubscribeMouse(*this);
}
//------------------------------------------------------------------------------
void PlayScene::update()
{
	World& world = getSceneManager().getWorld();

	// Camera translation
	float moveSpeed = 0.1f;
	if (mInput.getKeyboard()->isKeyDown(OIS::KC_A))
	{
		world.getSystemManager().getSystem<CameraSystem>()->moveRight(world.getEntity(0), -(moveSpeed / 2));
	}
	else if (mInput.getKeyboard()->isKeyDown(OIS::KC_D))
	{
		world.getSystemManager().getSystem<CameraSystem>()->moveRight(world.getEntity(0), (moveSpeed / 2));
	}
	if (mInput.getKeyboard()->isKeyDown(OIS::KC_S))
	{
		world.getSystemManager().getSystem<CameraSystem>()->moveForward(world.getEntity(0), -moveSpeed);
	}
	else if (mInput.getKeyboard()->isKeyDown(OIS::KC_W))
	{
		world.getSystemManager().getSystem<CameraSystem>()->moveForward(world.getEntity(0), moveSpeed);
	}
	else if (mInput.getKeyboard()->isKeyDown(OIS::KC_R))
	{
		world.getEntity(1).getComponent<Light>()->direction += vmVector3(0.0f, 0.001f, 0.0f);
	}
	else if (mInput.getKeyboard()->isKeyDown(OIS::KC_E))
	{
		world.getEntity(1).getComponent<Light>()->direction += vmVector3(0.0f, -0.001f, 0.0f);
	}
}
//------------------------------------------------------------------------------
bool PlayScene::mouseMoved(const OIS::MouseEvent& rEvent)
{
	//float rotateSpeed = 0.005f;

	//World& world = getSceneManager().getWorld();
	//Transform* cameraPos = world.getEntity(0).getComponent<Transform>();

	// Camera rotation
	//world.getSystemManager().getSystem<CameraSystem>()->pitch(world.getEntity(0), rEvent.state.Y.rel * rotateSpeed);
	//world.getSystemManager().getSystem<CameraSystem>()->yaw(world.getEntity(0), rEvent.state.X.rel * rotateSpeed);

	return true;
}
//------------------------------------------------------------------------------
bool PlayScene::mousePressed(const OIS::MouseEvent& DG_UNUSED(rEvent), OIS::MouseButtonID DG_UNUSED(id))
{
	return true;
}
//------------------------------------------------------------------------------
bool PlayScene::mouseReleased(const OIS::MouseEvent& DG_UNUSED(rEvent), OIS::MouseButtonID DG_UNUSED(id))
{
	return true;
}
//------------------------------------------------------------------------------
bool PlayScene::keyPressed(const OIS::KeyEvent& rEvent)
{
	World& world = getSceneManager().getWorld();

	if (rEvent.key == OIS::KC_1)
	{
		world.getSystemManager().getSystem<LightSystem>()->setEnabled(world.getEntity(1), true);
	}
	else if (rEvent.key == OIS::KC_2)
	{
		world.getSystemManager().getSystem<LightSystem>()->setEnabled(world.getEntity(1), false);
	}
	return true;
}
//------------------------------------------------------------------------------
bool PlayScene::keyReleased(const OIS::KeyEvent& DG_UNUSED(rEvent))
{
	return true;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------