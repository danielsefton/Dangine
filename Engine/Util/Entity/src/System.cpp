//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Util/Entity/System.h"
#include "Util/Entity/SystemManager.h"
#include "Util/Entity/World.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
SystemManager* System::systemManager = 0;
//------------------------------------------------------------------------------
System::System(ComponentType type)
	: mComponentType(type)
{
}
//------------------------------------------------------------------------------
System::~System()
{
}
//------------------------------------------------------------------------------
void System::initialise()
{
	// TODO: Add support for updating mEntitiesWithComponent when an entity has 
	// been added/removed.
	systemManager->getWorld().getEntityManager().getEntitiesWithComponent(
		mComponentType, mEntitiesWithComponent);
	_initialiseEntities(mEntitiesWithComponent);
}
//------------------------------------------------------------------------------
void System::destroy()
{
	_destroyEntities(mEntitiesWithComponent);
}
//------------------------------------------------------------------------------
void System::process()
{
	_processEntities(mEntitiesWithComponent);
}
//------------------------------------------------------------------------------
void System::_initialiseEntities(std::vector<Entity*>& rEntities)
{
	for (uint i = 0; i < rEntities.size(); ++i)
	{
		_initialise(*rEntities[i]);
	}
}
//------------------------------------------------------------------------------
void System::_destroyEntities(std::vector<Entity*>& rEntities)
{
	for (uint i = 0; i < rEntities.size(); ++i)
	{
		_destroy(*rEntities[i]);
	}
}
//------------------------------------------------------------------------------
void System::_processEntities(std::vector<Entity*>& rEntities)
{
	for (uint i = 0; i < rEntities.size(); ++i)
	{
		_process(*rEntities[i]);
	}
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------