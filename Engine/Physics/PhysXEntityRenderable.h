//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXENTITYRENDERABLE_H
#define PHYSXENTITYRENDERABLE_H

#include "Platform/Prerequisites.h"

#include "Physics/PhysXPointRenderable.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXEntityRenderable : public PhysXPointRenderable
{
public:
	PhysXEntityRenderable(Entity* entity);
	~PhysXEntityRenderable();

	Entity* getEntity() { return mEntity; }

	void setTransform(const vmVector3& position, const vmQuat& orientation);
	void setMatrixTransform(const D3DXMATRIX& mat);

private:
	Entity* mEntity;

}; // class PhysXEntityRenderable
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXENTITYRENDERABLE_H