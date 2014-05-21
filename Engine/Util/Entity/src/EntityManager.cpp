//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Util/Entity/EntityManager.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
EntityManager::EntityManager(World& rWorld, LinearArena& rArena, const uint maxEntities)
	: mWorld(rWorld)
	, mArena(rArena)
	, mNumEntities(maxEntities)
{
	Entity::entityManager = this;
	mEntities = DG_NEW_ARRAY2(Entity, maxEntities, mArena);
}
//------------------------------------------------------------------------------
EntityManager::~EntityManager()
{
	DG_DELETE_ARRAY(mEntities, mArena);
}
//------------------------------------------------------------------------------
void EntityManager::removeComponent(Entity* pEntity, ComponentType type)
{
	Components::iterator i = pEntity->mComponents.find(type);
	if (i != pEntity->mComponents.end())
	{
		DG_DELETE(i->second, mArena);
		pEntity->mComponents.erase(i);
	}

	std::pair<EntitiesByComponent::iterator, EntitiesByComponent::iterator> get =
		getEntitiesWithComponent(type);

	for (EntitiesByComponent::iterator j = get.first; j != get.second; ++j)
	{
		if (j->second == pEntity)
		{
			mEntitiesByComponent.erase(j);
			break;
		}
	}
}
//------------------------------------------------------------------------------
void EntityManager::removeComponentsOfEntity(Entity* pEntity)
{
	for (Components::iterator i = pEntity->mComponents.begin(); i != pEntity->mComponents.end(); ++i)
	{
		DG_DELETE(i->second, mArena);
	}
	pEntity->mComponents.clear();

	for (EntitiesByComponent::iterator j = mEntitiesByComponent.begin(); j != mEntitiesByComponent.end(); ++j)
	{
		if (j->second == pEntity)
		{
			mEntitiesByComponent.erase(j);
			break;
		}
	}
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------