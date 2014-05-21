//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXRENDEREDACTORBINDING_H
#define PHYSXRENDEREDACTORBINDING_H

#include "Platform/Prerequisites.h"

#include "Physics/PhysXRenderableBinding.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXRenderedActorBinding : public PhysXRenderableBinding
{
public:
	PhysXRenderedActorBinding(physx::PxRigidDynamic* actor, PhysXPointRenderable* renderable);
	~PhysXRenderedActorBinding();

	void sync();

	physx::PxRigidDynamic* getActor() { return mPxActor; }
	PhysXPointRenderable* getPointRenderable() { return mRenderable; }

private:
	PhysXPointRenderable* mRenderable;
	physx::PxRigidDynamic* mPxActor;

}; // class PhysXRenderedActorBinding
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXRENDEREDACTORBINDING_H