//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXACTOR_H
#define PHYSXACTOR_H

#include "Platform/Prerequisites.h"

#include "Physics/PhysXMappings.h"

#include <PhysX/PxPhysics.h>

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
/**
 * Helper class that wraps an PxRigidActor to keep code clean.
 * Provides set/get position/orientation methods that accept VM math types.
 */
template<class T>		//T extends PxRigidActor
class PhysXActor
{
public:
	PhysXActor() : mActor(0) {}
	PhysXActor(T* actor) : mActor(actor) {}
	virtual ~PhysXActor() {}

	inline void setPxActor(T* actor) { mActor = actor; }
	inline T* getPxActor() const { return mActor; }

	/// Retrieves the first shape of the actor.
	physx::PxShape* getFirstShape()
	{
		physx::PxShape* shapes[1];
		mActor->getShapes(shapes, 1);
		return shapes[0];
	}

	inline void setGlobalPosition(const vmVector3& position)
	{
		mActor->setGlobalPose(PxTransform(PhysXMappings::toPx(position), mActor->getGlobalPose().q));
	}

	inline vmVector3 getGlobalPosition()
	{
		return PhysXMappings::toVm(mActor->getGlobalPose().p);
	}

	inline void setGlobalOrientation(const vmQuat& q)
	{
		mActor->setGlobalPose(PxTransform(mActor->getGlobalPose().p, PhysXMappings::toPx(q)));
	}

	inline vmQuat getGlobalOrientation()
	{
		return PhysXMappings::toVm(mActor->getGlobalPose().q);
	}

	inline void setGlobalTransform(const vmVector3& position, const vmQuat& q)
	{
		mActor->setGlobalPose(PxTransform(PhysXMappings::toPx(position), PhysXMappings::toPx(q)));
	}

	/// Freezed / unfreezes the actor.
	void setFreezed(bool freezed)
	{
		unsigned int numShapes = mActor->getNbShapes();
		PxShape** shapes = new PxShape*[numShapes];
		mActor->getShapes(shapes, numShapes);
		for (unsigned int i = 0; i < numShapes; i++)
			shapes[i]->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !freezed);

		delete[] shapes;

		mActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, freezed);

		// clear all forces
		mActor->clearForce(PxForceMode::eFORCE);
		mActor->clearForce(PxForceMode::eIMPULSE);
		mActor->clearForce(PxForceMode::eVELOCITY_CHANGE);
		mActor->clearForce(PxForceMode::eACCELERATION);
	}

protected:
	T* mActor;

}; // class PhysXActor
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXACTOR_H