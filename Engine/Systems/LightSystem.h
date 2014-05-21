//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/System.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class LightSystem : public System
{
public:
	LightSystem(ComponentType type);
	~LightSystem();

	inline void setRenderSystem(RenderSystem* pRenderSystem)
	{
		mRenderSystem = pRenderSystem;
	}

	void setEnabled(Entity& rEntity, bool enable);
	void setType(Entity& rEntity, LightTypes type);
	LightTypes getType(Entity& rEntity);

	static const ComponentType type = COMPONENTTYPE_LIGHT;
	
private:
	void _initialise(Entity& rEntity);
	void _destroy(Entity& rEntity);
	void _process(Entity& rEntity);

	RenderSystem* mRenderSystem;

}; // class LightSystem
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // LIGHTSYSTEM_H