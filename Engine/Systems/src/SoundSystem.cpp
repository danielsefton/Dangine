//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Systems/SoundSystem.h"
#include "Util/Entity/SystemManager.h"
#include "Util/Entity/World.h"
#include "Components/Sound.h"
#include "Components/Transform.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
SoundSystem::SoundSystem(ComponentType type)
	: System(type)
{
}
//------------------------------------------------------------------------------
SoundSystem::~SoundSystem()
{
	System::destroy();
}
//------------------------------------------------------------------------------
void SoundSystem::_initialise(Entity& rEntity)
{
	Sound* sound = rEntity.getComponent<Sound>();
	Transform* transform = rEntity.getComponent<Transform>();

	// TODO
}
//------------------------------------------------------------------------------
void SoundSystem::_destroy(Entity& rEntity)
{
	Sound* sound = rEntity.getComponent<Sound>();

	// TODO
}
//------------------------------------------------------------------------------
void SoundSystem::_process(Entity& rEntity)
{
	// TODO
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------