//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/System.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class SoundSystem : public System
{
public:
	SoundSystem(ComponentType type);
	~SoundSystem();
	
	static const ComponentType type = COMPONENTTYPE_SOUND;

private:
	void _initialise(Entity& rEntity);
	void _destroy(Entity& rEntity);
	void _process(Entity& rEntity);

}; // class SoundSystem
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // SOUNDSYSTEM_H