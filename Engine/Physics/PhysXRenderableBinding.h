//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXRENDERABLEBINDING_H
#define PHYSXRENDERABLEBINDING_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXRenderableBinding
{
public:
	virtual ~PhysXRenderableBinding() {}

	virtual void sync() = 0;

}; // class PhysXRenderableBinding
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXRENDERABLEBINDING_H