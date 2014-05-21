//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Util/Entity/SystemManager.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
SystemManager::SystemManager(World& rWorld, LinearArena& rArena)
	: mWorld(rWorld)
	, mArena(rArena)
{
	System::systemManager = this;
}
//------------------------------------------------------------------------------
SystemManager::~SystemManager()
{
	destroyAll();
}
//------------------------------------------------------------------------------
System* SystemManager::addSystem(ComponentType type, System* pSystem)
{
	mSystems.insert(std::make_pair(type, pSystem));
	return pSystem;
}
//------------------------------------------------------------------------------
void SystemManager::initialiseAll()
{
	for (Systems::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
	{
		i->second->initialise();
	}
}
//------------------------------------------------------------------------------
void SystemManager::destroyAll()
{
	for (Systems::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
	{
		DG_DELETE(i->second, mArena);
	}
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------