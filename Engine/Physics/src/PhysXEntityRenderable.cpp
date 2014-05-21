//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Physics/PhysXEntityRenderable.h"

#include "Util/Entity/Entity.h"
#include "Components/Transform.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
PhysXEntityRenderable::PhysXEntityRenderable(Entity* entity)
{
	mEntity = entity;
}
//------------------------------------------------------------------------------
PhysXEntityRenderable::~PhysXEntityRenderable()
{
}
//------------------------------------------------------------------------------
void PhysXEntityRenderable::setTransform(const vmVector3& position, const vmQuat& orientation)
{
	Transform* transform = mEntity->getComponent<Transform>();
	transform->position = position;
	transform->orientation = orientation;
}
//------------------------------------------------------------------------------
void PhysXEntityRenderable::setMatrixTransform(const D3DXMATRIX& mat)
{
	Transform* transform = mEntity->getComponent<Transform>();
	transform->useMatrixTransform = true;
	transform->d3dMat = mat;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------