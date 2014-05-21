//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXPOINTRENDERABLE_H
#define PHYSXPOINTRENDERABLE_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXPointRenderable
{
public:
	virtual ~PhysXPointRenderable() {}

	virtual void setTransform(const vmVector3& position, const vmQuat& orientation) = 0;
	virtual void setMatrixTransform(const D3DXMATRIX& mat) = 0;

}; // class PhysXPointRenderable
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXPOINTRENDERABLE_H