//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Systems/LightSystem.h"
#include "Util/Entity/SystemManager.h"
#include "Util/Entity/World.h"
#include "Components/Light.h"
#include "Components/Transform.h"
#include "Graphics/RenderSystem.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
LightSystem::LightSystem(ComponentType type)
	: System(type)
{
}
//------------------------------------------------------------------------------
LightSystem::~LightSystem()
{
	System::destroy();
}
//------------------------------------------------------------------------------
void LightSystem::_initialise(Entity& rEntity)
{
	Light* light = rEntity.getComponent<Light>();
	Transform* transform = rEntity.getComponent<Transform>();
	// TODO: Light shouldn't really be storing the position.
	light->position = transform->position;

	mRenderSystem->setLight(light->num, light);
	setEnabled(rEntity, true);
}
//------------------------------------------------------------------------------
void LightSystem::_destroy(Entity& rEntity)
{
	setEnabled(rEntity, false);
}
//------------------------------------------------------------------------------
void LightSystem::_process(Entity& rEntity)
{
	Light* light = rEntity.getComponent<Light>();
	Transform* transform = rEntity.getComponent<Transform>();
	// TODO: Light shouldn't really be storing the position.
	light->position = transform->position;

	mRenderSystem->setLight(light->num, light);
}
//------------------------------------------------------------------------------
void LightSystem::setEnabled(Entity& rEntity, bool enable)
{
	Light* light = rEntity.getComponent<Light>();
	mRenderSystem->setLightEnabled(light->num, enable);
}
//------------------------------------------------------------------------------
void LightSystem::setType(Entity& rEntity, LightTypes type)
{
	Light* light = rEntity.getComponent<Light>();
	light->lightType = type;
	mRenderSystem->setLight(light->num, light);
}
//------------------------------------------------------------------------------
LightTypes LightSystem::getType(Entity& rEntity)
{
	return rEntity.getComponent<Light>()->lightType;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------