//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/Component.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
struct Transform : public Component
{
	static const ComponentType type = COMPONENTTYPE_TRANSFORM;

	Transform()
		: position(vmVector3(0, 0, 0))
		, orientation(vmQuat(0, 0, 0, 1))
		, scale(vmVector3(1, 1, 1))
		, useMatrixTransform(false)
	{
		D3DXMatrixIdentity(&d3dMat);
	}

	vmVector3 position;
	vmQuat orientation;
	vmVector3 scale;
	D3DXMATRIX d3dMat;
	bool useMatrixTransform;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // TRANSFORM_H