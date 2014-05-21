//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/System.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class CameraSystem : public System
{
public:
	CameraSystem(ComponentType type);
	~CameraSystem();

	void yaw(Entity& rEntity, Real amount);
	void pitch(Entity& rEntity, Real amount);
	void roll(Entity& rEntity, Real amount);

	void moveForward(Entity& rEntity, Real amount);
	void moveRight(Entity& rEntity, Real amount);
	void moveUp(Entity& rEntity, Real amount);

	inline void setRenderSystem(RenderSystem* pRenderSystem)
	{
		mRenderSystem = pRenderSystem;
	}

	static const ComponentType type = COMPONENTTYPE_CAMERA;

private:
	void _initialise(Entity& rEntity);
	void _destroy(Entity& rEntity);
	void _process(Entity& rEntity);
	Real _restrictAngleTo360Range(Real angle) const;

	RenderSystem* mRenderSystem;

}; // class CameraSystem
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // CAMERASYSTEM_H