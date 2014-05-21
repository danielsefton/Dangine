//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/Component.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
struct Camera : public Component
{
	static const ComponentType type = COMPONENTTYPE_CAMERA;

	Camera()
		: viewMatrix(0)
		, projectionMatrix(0)
		, right(vmVector3(1.0f, 0.0f, 0.0f))
		, up(vmVector3(0.0f, 1.0f, 0.0f))
		, look(vmVector3(0.0f, 0.0f, 1.0f))
		, position(vmVector3(0.0f, 0.0f, 0.0f))
		, yaw(0.0f)
		, pitch(0.0f)
		, roll(0.0f)
		, nearRange(0.1f)
		, farRange(10000.0f)
		, aspectRatio(1024 / 768)
		, fov(D3DX_PI / 4.0f)
	{
	}

	vmMatrix4 viewMatrix;
	vmMatrix4 projectionMatrix;
	vmVector3 right;
	vmVector3 up;
	vmVector3 look;
	vmVector3 position;
	Real yaw;
	Real pitch;
	Real roll;
	Real nearRange;
	Real farRange;
	Real aspectRatio;
	Real fov;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // CAMERA_H