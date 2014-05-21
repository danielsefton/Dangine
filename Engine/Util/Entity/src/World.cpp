//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Util/Entity/World.h"
#include "Util/Entity/EntityManager.h"
#include "Util/Entity/SystemManager.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
World::World(LinearArena& rArena, uint maxEntities)
	: mArena(rArena)
{
	mEntityManager = DG_NEW(EntityManager, mArena)(*this, mArena, maxEntities);
	mSystemManager = DG_NEW(SystemManager, mArena)(*this, mArena);
}
//------------------------------------------------------------------------------
World::~World()
{
	DG_DELETE(mSystemManager, mArena);
	DG_DELETE(mEntityManager, mArena);
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------