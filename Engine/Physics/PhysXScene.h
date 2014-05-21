//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXSCENE_H
#define PHYSXSCENE_H

#include "Platform/Prerequisites.h"

#include "Physics/PhysXActor.h"

#include <PhysX/PxPhysicsAPI.h>

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXScene
{
public:
	class SimulationListener
	{
	public:
		/**
		 * Called right before PxScene::simulate.
		 */
		virtual void onBeginSimulate(float time) { (void)time; }

		/**
		 * Called right after PxScene::simulate.
		 * That means that it is executed while the simulation is in progress.
		 */
		virtual void onSimulate(float time) { (void)time; }

		/**
		 * Called right after PxScene::fetchResults.
		 */
		virtual void onEndSimulate(float time) { (void)time; }
	};

	PhysXScene(physx::PxSceneDesc& rDesc, physx::PxPhysics* pSdk, PhysXWorld& rPhysXWorld);
	~PhysXScene();

	/**
	Creates a new rigid dynamic actor with a specified collision shape and a default material and adds it to the scene.
	@return An Actor object wrapping the created PxActor.
	*/
	PhysXActor<physx::PxRigidDynamic> createRigidDynamic(physx::PxGeometry& geometry, float density, const physx::PxTransform& shapeOffset = physx::PxTransform::createIdentity(), const physx::PxTransform& actorPose = physx::PxTransform::createIdentity());

	/**
	Creates a new rigid dynamic actor with a specified collision shape and material and adds it to the scene.
	@return An Actor object wrapping the created PxActor.
	*/
	PhysXActor<physx::PxRigidDynamic> createRigidDynamic(physx::PxGeometry& geometry, float density, physx::PxMaterial& material, const physx::PxTransform& shapeOffset = physx::PxTransform::createIdentity(), const physx::PxTransform& actorPose = physx::PxTransform::createIdentity());

	/**
	Creates a new rigid dynamic actor with a collision shape matching the given entity.
	@return An Actor object wrapping the created PxActor.
	*/
	//PhysXActor<physx::PxRigidDynamic> createRigidDynamic(Entity* entity, float density, const vmVector3& scale = vmVector3(1,1,1), const physx::PxTransform& actorPose = physx::PxTransform::createIdentity());

	/**
	Creates a new rigid dynamic actor with a collision shape matching the given entity.
	@return An Actor object wrapping the created PxActor.
	*/
	//PhysXActor<physx::PxRigidDynamic> createRigidDynamic(Entity* entity, float density, physx::PxMaterial& material, const vmVector3& scale = vmVector3(1,1,1), const physx::PxTransform& actorPose = physx::PxTransform::createIdentity());

	/**
	Creates a new rigid static actor with a triangle mesh collision shape and adds it to the scene.
	The material bindings specified via World::registerMaterialName are used for Ogre -> PhysX material mapping.
	@return An Actor object wrapping the created PxActor.
	*/
	//Actor<PxRigidStatic> createRigidStatic(Ogre::Entity *entity, Cooker::Params &cookerParams = Cooker::Params(), const PxTransform &actorPose = PxTransform::createIdentity());

	/**
	Creates a new rigid static actor with a specified collision shape and a default material and adds it to the scene.		
	@return An Actor object wrapping the created PxActor.
	*/
	PhysXActor<physx::PxRigidStatic> createRigidStatic(physx::PxGeometry& geometry, const physx::PxTransform& shapeOffset = physx::PxTransform::createIdentity(), const physx::PxTransform& actorPose = physx::PxTransform::createIdentity());

	/**
	Creates a new rigid static actor with a specified collision shape and material and adds it to the scene.
	@return An Actor object wrapping the created PxActor.
	*/
	PhysXActor<physx::PxRigidStatic> createRigidStatic(physx::PxGeometry& geometry, physx::PxMaterial& material, const physx::PxTransform& shapeOffset = physx::PxTransform::createIdentity(), const physx::PxTransform& actorPose = physx::PxTransform::createIdentity());

	///Removes an actor from the scene.
	template<class T>
	void removeActor(PhysXActor<T>& actor)
	{
		removeActor(actor.getPxActor());
		actor.setPxActor(0);
	}

	///Removes an from the scene.
	void removeActor(physx::PxActor* actor);

	/**
	Binds a PointRenderable to an actor.
	*/
	PhysXRenderedActorBinding* createRenderedActorBinding(PhysXActor<physx::PxRigidDynamic>& actor, PhysXPointRenderable* pointRenderable);
	PhysXRenderedActorBinding* createRenderedActorBinding(physx::PxRigidDynamic* actor, PhysXPointRenderable* pointRenderable);

	/**
	Destroys ONLY the renderable binding, not the physx actor.
	*/
	void destroyRenderableBinding(PhysXRenderableBinding* binding);

	void syncRenderables();

	void simulate(Real time);

	inline void setSimulationListener(SimulationListener* pListener)
	{
		mSimulationListener = pListener;
	}
	inline physx::PxScene* getPxScene() { return mPxScene; }

private:
	PhysXScene& operator=(const PhysXScene&); // Fix for C4512
	PhysXWorld& mPhysXWorld;
	physx::PxPhysics* mSDK;
	physx::PxScene* mPxScene;
	physx::PxDefaultCpuDispatcher* mCpuDispatcher;
	Real mTimeAccu;
	Real mFrameTime;
	SimulationListener* mSimulationListener;
	std::vector<PhysXRenderableBinding*> mDanginePhysXBindings;

}; // class PhysXScene
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXSCENE_H