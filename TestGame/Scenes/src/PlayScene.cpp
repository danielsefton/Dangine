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
	transCamera->position = vmVector3(0.0f, 3.4f, 0.0f);

	Camera* camera = DG_NEW(Camera, world.getLinearArena());
	camera->fov = 0.9f;

	world.getEntity(0).addComponent(transCamera);
	world.getEntity(0).addComponent(camera);

	// Light
	Transform* transLight = DG_NEW(Transform,  world.getLinearArena());
	transLight->position = vmVector3(0, 10, 0);

	Light* light = DG_NEW(Light, world.getLinearArena())(0);
	light->lightType = LT_DIRECTIONAL;
	light->direction = vmVector3(0.0f, 0.9f, 1.0f);

	//Material matCube;
	//matCube.ambient = vmVector4(0.7f, 0.7f, 0.7f, 1.f);
	//matCube.diffuse = vmVector4(0.7f, 0.7f, 0.7f, 1.f);
	//matCube.textureFiles.push_back("tiles.png");

	//Mesh* meshCube = DG_NEW(Mesh, world.getLinearArena());
	//meshCube->file = "../media/cube.x";
	//meshCube->materials.push_back(matCube);

	world.getEntity(1).addComponent(transLight);
	world.getEntity(1).addComponent(light);
	//world.getEntity(1).addComponent(meshCube);

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
	
	// Terrain
	Transform* transTerrain = DG_NEW(Transform,  world.getLinearArena());
	transTerrain->position = vmVector3(0, 0, 0);

	Material matTerrain;
	matTerrain.ambient = vmVector4(0.2f, 0.2f, 0.2f, 1.f);
	matTerrain.diffuse = vmVector4(0.7f, 0.7f, 0.7f, 1.f);
	matTerrain.textureFiles.push_back("grass.jpg");

	Mesh* meshTerrain = DG_NEW(Mesh, world.getLinearArena());
	meshTerrain->file = "../media/TerrainTextured.x";
	meshTerrain->effectFile = "../media/terrain.cg";
	meshTerrain->materials.push_back(matTerrain);

	world.getEntity(3).addComponent(transTerrain);
	world.getEntity(3).addComponent(meshTerrain);

	// Water
	Transform* transWater = DG_NEW(Transform, world.getLinearArena());
	transWater->position = vmVector3(0, -2, 0);
	transWater->scale = vmVector3(130, 1, 130);

	Material matWater;
	matWater.ambient = vmVector4(0.0f, 0.5459f, 0.8496f, 1.f);
	matWater.diffuse = vmVector4(0.0f, 0.5459f, 0.8496f, 0.5f);

	Mesh* meshWater = DG_NEW(Mesh,  world.getLinearArena());
	meshWater->file = "../media/quad.x";
	meshWater->effectFile = "../media/water.cg";
	meshWater->materials.push_back(matWater);

	world.getEntity(4).addComponent(transWater);
	world.getEntity(4).addComponent(meshWater);

	// Copter
	Transform* transCopter = DG_NEW(Transform, world.getLinearArena());
	transCopter->position = vmVector3(0, 0, 0);

	Material matCopter;
	Material matCopter2;
	matCopter2.ambient = vmVector4(0.2f, 0.2f, 0.2f, 1.f);
	matCopter2.diffuse = vmVector4(0.7f, 0.7f, 0.7f, 1.f);
	matCopter2.textureFiles.push_back("copter_diffuse.png");
	matCopter2.textureFiles.push_back("copter_normal.png");
	//matCopter2.textureFiles.push_back("tiles.png");
	//matCopter2.textureFiles.push_back("tiles_normal.png");

	Mesh* meshCopter = DG_NEW(Mesh,  world.getLinearArena());
	meshCopter->file = "../media/copter.x";
	meshCopter->effectFile = "../media/copter.cg";
	meshCopter->materials.push_back(matCopter);
	meshCopter->materials.push_back(matCopter2);

	world.getEntity(5).addComponent(transCopter);
	world.getEntity(5).addComponent(meshCopter);

	// Initialise all systems
	world.getSystemManager().initialiseAll();

	// Test physics
	PxMaterial* material = &mPhysXWorld.getDefaultMaterial();
	material->setRestitution(0.5f);
	material->setStaticFriction(1.0f);
	material->setDynamicFriction(1.0f);

	//mActor = mPhysXWorld.getScene("Main")->createRigidDynamic(
		//physx::PxConvexMeshGeometry(PhysXCooker::createPxConvexMesh(*mPhysXWorld.getPxPhysics(), *mPhysXWorld.getCookingInterface(), 
		//world.getSystemManager().getSystem<MeshSystem>()->getVertices(world.getEntity(3)))), 20.0f, *material);
	/*mActor = mPhysXWorld.getScene("Main")->createRigidDynamic(
		PhysXGeometry::boxGeometry(world.getEntity(2), *world.getSystemManager().getSystem<MeshSystem>()), 10.0f, *material);
	mPhysXWorld.getScene("Main")->createRenderedActorBinding(mActor, 
		DG_NEW(PhysXEntityRenderable, world.getLinearArena())(&world.getEntity(2)));
	mActor.setGlobalPosition(vmVector3(0.0f, 20.0, 0.0f));*/

	//PhysXActor<PxRigidDynamic> actor1 = mPhysXWorld.getScene("Main")->createRigidDynamic(
		//physx::PxConvexMeshGeometry(PhysXCooker::createPxConvexMesh(*mPhysXWorld.getPxPhysics(), *mPhysXWorld.getCookingInterface(), 
		//world.getSystemManager().getSystem<MeshSystem>()->getVertices(world.getEntity(4)))), 20.0f, *material);
	mActor = mPhysXWorld.getScene("Main")->createRigidDynamic(
		PhysXGeometry::boxGeometry(world.getEntity(5), *world.getSystemManager().getSystem<MeshSystem>()), 1.f, *material);
	mPhysXWorld.getScene("Main")->createRenderedActorBinding(mActor, 
		DG_NEW(PhysXEntityRenderable, world.getLinearArena())(&world.getEntity(5)));
	mActor.setGlobalPosition(vmVector3(-3.0f, 0.0f, 0.0f));
	mActor.getPxActor()->setLinearDamping(0.8f);
	mActor.getPxActor()->setAngularDamping(1.0f);

	PhysXActor<PxRigidStatic> actor2 = mPhysXWorld.getScene("Main")->createRigidStatic(
		physx::PxTriangleMeshGeometry(PhysXCooker::createPxTriangleMesh(*mPhysXWorld.getPxPhysics(), *mPhysXWorld.getCookingInterface(), 
		world.getSystemManager().getSystem<MeshSystem>()->getIndices(world.getEntity(3)),
		world.getSystemManager().getSystem<MeshSystem>()->getVertices(world.getEntity(3)))), *material);

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

	Real speed = 2000.0f;

	// Lock orientation
	mActor.setGlobalOrientation(vmQuat(0.0f, 0.0f, 0.0f, 1.0f));

	if (mInput.getKeyboard()->isKeyDown(OIS::KC_UP))
	{
		mActor.getPxActor()->addForce(PxVec3(0.0f, 0.0f , speed));
	}
	else if (mInput.getKeyboard()->isKeyDown(OIS::KC_DOWN))
	{
		mActor.getPxActor()->addForce(PxVec3(0.0f, 0.0f , -speed));
	}
	if (mInput.getKeyboard()->isKeyDown(OIS::KC_LEFT))
	{
		mActor.getPxActor()->addForce(PxVec3(-speed, 0.0f , 0.0f));
	}
	else if (mInput.getKeyboard()->isKeyDown(OIS::KC_RIGHT))
	{
		mActor.getPxActor()->addForce(PxVec3(speed, 0.0f , 0.0f));
	}
	if (mInput.getKeyboard()->isKeyDown(OIS::KC_SPACE))
	{
		mActor.getPxActor()->addForce(PxVec3(0.0f, speed / 2, 0.0f));
	}
	if (mInput.getKeyboard()->isKeyDown(OIS::KC_H))
	{
		mActor.setGlobalPosition(vmVector3(-3.0f, 0.0, 0.0f));
		mActor.getPxActor()->setLinearVelocity(PxVec3(0));
	}

	// TODO: Day/night cycle
	vmVector3 centre = vmVector3(0.0f, 0.0f, 0.0f);
	vmVector3 point = vmVector3(10.0f, 0.0f, 0.0f);
	vmVector3 axis = vmVector3(0.0f, 1.0f, 0.0f);
	//mAngle += 0.1f;
	Real mAngle = 45.0f;

	vmVector3 pos = centre - point;
	Real cosTheta = cos(mAngle * D3DX_PI / Real(180.0));
	Real sinTheta = sin(mAngle * D3DX_PI / Real(180.0));
	
	vmVector3 newPos;
	// Find the new x position for the new rotated point.
	newPos.setX((cosTheta + (1 - cosTheta) * axis.getX() * axis.getX()) * pos.getX());
	newPos.setX(newPos.getX() + ((1 - cosTheta) * axis.getX() * axis.getY() - axis.getZ() * sinTheta) * pos.getY());
	newPos.setX(newPos.getX() + ((1 - cosTheta) * axis.getX() * axis.getZ() + axis.getY() * sinTheta) * pos.getZ());
	
	// Find the new y position for the new rotated point.
	newPos.setY(((1 - cosTheta) * axis.getX() * axis.getY() + axis.getZ() * sinTheta) * pos.getX());
	newPos.setY(newPos.getY() + (cosTheta + (1 - cosTheta) * axis.getY() * axis.getY()) * pos.getY());
	newPos.setY(newPos.getY() + ((1 - cosTheta) * axis.getY() * axis.getZ() - axis.getX() * sinTheta) * pos.getZ());
	
	// Find the new z position for the new rotated point.
	newPos.setZ(((1 - cosTheta) * axis.getZ() * axis.getZ() - axis.getY() * sinTheta) * pos.getX());
	newPos.setZ(newPos.getZ() + ((1 - cosTheta) * axis.getY() * axis.getZ() + axis.getX() * sinTheta) * pos.getY());
	newPos.setZ(newPos.getZ() + (cosTheta + (1 - cosTheta) * axis.getZ() * axis.getZ()) * pos.getZ());
	
	//world.getEntity(1).getComponent<Transform>()->position = newPos + point;
	//world.getEntity(1).getComponent<Light>()->direction = normalize(centre - world.getEntity(1).getComponent<Transform>()->position);
	
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
	float rotateSpeed = 0.005f;

	World& world = getSceneManager().getWorld();
	Transform* cameraPos = world.getEntity(0).getComponent<Transform>();

	// Camera rotation
	world.getSystemManager().getSystem<CameraSystem>()->pitch(world.getEntity(0), rEvent.state.Y.rel * rotateSpeed);
	world.getSystemManager().getSystem<CameraSystem>()->yaw(world.getEntity(0), rEvent.state.X.rel * rotateSpeed);

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