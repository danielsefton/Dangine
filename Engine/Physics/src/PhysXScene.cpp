//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Physics/PhysXScene.h"

#include "Physics/PhysXWorld.h"
#include "Physics/PhysXRenderedActorBinding.h"

#include <PhysX/extensions/PxDefaultCpuDispatcher.h>
#include <PhysX/PxScene.h>
#include <PhysX/PxMaterial.h>
#include <PhysX/extensions/PxExtensionsAPI.h>
#include <PhysX/common/PxRenderBuffer.h>

using namespace physx;

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
PhysXScene::PhysXScene(PxSceneDesc& rDesc, PxPhysics* pSdk, PhysXWorld& rPhysXWorld)
	: mSDK(pSdk)
	, mPhysXWorld(rPhysXWorld)
	, mTimeAccu(0.0f)
	, mFrameTime(1/80.0f)
	, mSimulationListener(0)
	, mPxScene(0)
	, mCpuDispatcher(0)
{
	if (!rDesc.cpuDispatcher)
	{
		mCpuDispatcher = PxDefaultCpuDispatcherCreate(4);
		if (!mCpuDispatcher)
		{
			LOG(logERROR) << "PxDefaultCpuDispatcherCreate failed!";
			return;
		}
		rDesc.cpuDispatcher	= mCpuDispatcher;
	}

	if (!mSDK)
	{
		LOG(logERROR) << "[PhysX] Error: Cannot create scene because World is not initialised properly.";
		return;
	}

	mPxScene = mSDK->createScene(rDesc);
}
//------------------------------------------------------------------------------
PhysXScene::~PhysXScene()
{
	mPxScene->release();
	mCpuDispatcher->release();
}
//------------------------------------------------------------------------------
PhysXActor<PxRigidDynamic> PhysXScene::createRigidDynamic(PxGeometry& geometry, float density, const PxTransform& shapeOffset, const PxTransform& actorPose)
{
	return createRigidDynamic(geometry, density, mPhysXWorld.getDefaultMaterial(), shapeOffset, actorPose);
}
//------------------------------------------------------------------------------
PhysXActor<PxRigidDynamic> PhysXScene::createRigidDynamic(PxGeometry& geometry, float density, PxMaterial& material, const PxTransform& shapeOffset, const PxTransform& actorPose)
{
	PxRigidDynamic* pxActor = PxCreateDynamic(*mSDK, actorPose, geometry, material, density, shapeOffset);
	mPxScene->addActor(*pxActor);
	PhysXActor<PxRigidDynamic> actor(pxActor);
	return actor;
}
//------------------------------------------------------------------------------
/*PhysXActor<PxRigidDynamic> PhysXScene::createRigidDynamic(Entity* entity, float density, const vmVector3& scale, const PxTransform& actorPose)
{
	return createRigidDynamic(entity, density, mPhysXWorld.getDefaultMaterial(), scale, actorPose);
}
//------------------------------------------------------------------------------
PhysXActor<PxRigidDynamic> PhysXScene::createRigidDynamic(Entity* entity, float density, PxMaterial& material, const vmVector3& scale, const PxTransform& actorPose)
{
	Mesh* mesh = entity->getComponent<Mesh>();

	PxTransform shapeOffset = PxTransform::createIdentity();

	Cooker::Params params;
	params.scale(scale);
	if mesh->getBoundingBox().getSize().x * scale.x > 0.4f &&
		entity->getBoundingBox().getSize().y * scale.y > 0.4f &&
		entity->getBoundingBox().getSize().z * scale.z > 0.4f)
	{
		//return createRigidDynamic(Geometry::convexMeshGeometry(entity->getMesh(), params), density, material, shapeOffset, actorPose);
	}

	//mesh is too small for convex mesh
	PxBoxGeometry boxGeometry = Geometry::boxGeometry(entity, shapeOffset, scale);
	return createRigidDynamic(boxGeometry, density, material, shapeOffset, actorPose); 
}*/
//------------------------------------------------------------------------------
/*PhysXActor<PxRigidStatic> PhysXScene::createRigidStatic(Entity* entity, Cooker::Params& cookerParams, const PxTransform& actorPose)
{
	Cooker::AddedMaterials addedMaterials;
	cookerParams.materials(World::getSingleton().getOgreMaterialNames());
	PxRigidStatic *pxActor = getPxPhysics()->createRigidStatic(actorPose);
	PxTriangleMeshGeometry geometry = PxTriangleMeshGeometry(Cooker::getSingleton().createPxTriangleMesh(entity->getMesh(), cookerParams, &addedMaterials));
		
	if (addedMaterials.materialCount > 0)
		pxActor->createShape(geometry, addedMaterials.materials, addedMaterials.materialCount);
	else
		pxActor->createShape(geometry, mPhysXWorld.getDefaultMaterial());

	mPxScene->addActor(*pxActor);
	Actor<PxRigidStatic> actor(pxActor);
	return actor;
}*/
//------------------------------------------------------------------------------
PhysXActor<PxRigidStatic> PhysXScene::createRigidStatic(PxGeometry& geometry, const PxTransform& shapeOffset, const PxTransform& actorPose)
{
	return createRigidStatic(geometry, mPhysXWorld.getDefaultMaterial(), shapeOffset, actorPose);
}
//------------------------------------------------------------------------------
PhysXActor<PxRigidStatic> PhysXScene::createRigidStatic(PxGeometry& geometry, PxMaterial& material, const PxTransform& shapeOffset, const PxTransform& actorPose)
{
	PxRigidStatic* pxActor = mSDK->createRigidStatic(actorPose);
	pxActor->createShape(geometry, material, shapeOffset);
	mPxScene->addActor(*pxActor);
	PhysXActor<PxRigidStatic> actor(pxActor);
	return actor;
}
//------------------------------------------------------------------------------
void PhysXScene::removeActor(PxActor* actor)
{
	mPxScene->removeActor(*actor);
}
//------------------------------------------------------------------------------
PhysXRenderedActorBinding* PhysXScene::createRenderedActorBinding(PhysXActor<PxRigidDynamic>& actor, PhysXPointRenderable* pointRenderable)
{
	return createRenderedActorBinding(actor.getPxActor(), pointRenderable);
}
//------------------------------------------------------------------------------
PhysXRenderedActorBinding* PhysXScene::createRenderedActorBinding(PxRigidDynamic* actor, PhysXPointRenderable* pointRenderable)
{
	PhysXRenderedActorBinding* renderedActor = new PhysXRenderedActorBinding(actor, pointRenderable);
	mDanginePhysXBindings.push_back(renderedActor);
	return renderedActor;
}
//------------------------------------------------------------------------------
void PhysXScene::destroyRenderableBinding(PhysXRenderableBinding* binding)
{
	for (auto i = mDanginePhysXBindings.begin(); i != mDanginePhysXBindings.end(); i++)
	{
		if ((*i) == binding)
		{
			mDanginePhysXBindings.erase(i);
			break;
		}
	}
	delete binding;
}
//------------------------------------------------------------------------------
void PhysXScene::syncRenderables()
{
	for (auto i = mDanginePhysXBindings.begin(); i != mDanginePhysXBindings.end(); i++)
	{
		(*i)->sync();
	}
}
//------------------------------------------------------------------------------
void PhysXScene::simulate(Real time)
{
	mTimeAccu += time;
	int numSubSteps = 0;
	while (mTimeAccu >= mFrameTime && numSubSteps < 12)
	{
		if (mSimulationListener) mSimulationListener->onBeginSimulate(mFrameTime);
		mPxScene->simulate(mFrameTime);
		if (mSimulationListener) mSimulationListener->onSimulate(mFrameTime);
		mPxScene->fetchResults(true);
		mTimeAccu -= mFrameTime;
		if (mSimulationListener) mSimulationListener->onEndSimulate(mFrameTime);
	}
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------