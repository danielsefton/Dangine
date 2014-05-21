//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based on: http://entity-systems.wikidot.com/test-for-parallel-processing-of-components
//------------------------------------------------------------------------------

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/Entity.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
typedef std::multimap<ComponentType, Entity*> EntitiesByComponent;
//------------------------------------------------------------------------------
class EntityManager
{
public:
	EntityManager(World& rWorld, LinearArena& rArena, const uint maxEntities);
	~EntityManager();

	/**
	 * Gets the entity at the specified id.
	 *
	 * @param id	The entity id.
	 */
	inline Entity& getEntity(uint id) { return mEntities[id]; }

	/**
	 * Gets the entities array.
	 */
	inline Entity* getEntities() { return mEntities; }

	/**
	 * Gets the number of entities.
	 */
	inline uint getNumEntities() { return mNumEntities; }

	/**
	 * Adds a component to the given entity.
	 *
	 * @param pEntity		The entity to add the component to.
	 * @param pComponent	The component to add.
	 */
	template<typename T> inline void addComponent(Entity* pEntity, T* pComponent)
	{
		mEntitiesByComponent.insert(std::pair<ComponentType, Entity*>(T::type, pEntity));
		pEntity->mComponents.insert(std::pair<ComponentType, Component*>(T::type, pComponent));
	}

	/**
	 * Gets a component for the given entity using the component's C++ type 
	 * as a template parameter.
	 *
	 * @param pEntity	The entity to find the component in.
     */
	template<typename T> inline T* getComponent(Entity* pEntity)
	{
		return (T*)pEntity->mComponents[T::type];
	}
	
	/**
	 * Removes a component from the given entity using the component's C++ type 
	 * as a template parameter.
	 *
	 * @param pEntity		The entity to remove the component from.
	 * @param pComponent	The component to remove.
	 */
	template<typename T> inline void removeComponent(Entity* pEntity, T* pComponent)
	{
		removeComponent(pEntity, T::type);
	}

	/**
	 * Removes a component from the given entity.
	 *
	 * @param pEntity	The entity to remove the component from.
	 * @param type		The component to remove.
	 */
	void removeComponent(Entity* pEntity, ComponentType type);

	/**
	 * Gets multiple entities using the component's C++ type as template 
	 * parameter and returns a vector result.
	 *
	 * @param rResult	The vector of returned entities.
	 */
	template<typename T> inline void getEntitiesWithComponent(std::vector<Entity*>& rResult)
	{
		auto iPair = mEntitiesByComponent.equal_range(T::type);
		for (auto i = iPair.first; i != iPair.second; ++i)
		{
			rResult.push_back(i->second);
		}
	}

	/**
	 * Gets multiple entities using the component's type and returns a vector result.
	 *
	 * @param rResult	The vector of returned entities.
	 */
	inline void getEntitiesWithComponent(ComponentType type, std::vector<Entity*>& rResult)
	{
		auto iPair = mEntitiesByComponent.equal_range(type);
		for (auto i = iPair.first; i != iPair.second; ++i)
		{
			rResult.push_back(i->second);
		}
	}

	/**
	 * Gets multiple entities using the component's C++ type as a template parameter.
	 *
	 * @return A beginning and end iterator to transverse the returned entities.
	 */
	template<class T> inline std::pair<EntitiesByComponent::iterator, 
		EntitiesByComponent::iterator> getEntitiesWithComponent()
	{
		return mEntitiesByComponent.equal_range(T::type);
	}

	/**
	 * Gets multiple components using the component's type.
	 *
	 * @param type	The type of the component.
	 * @return A beginning and end iterator to transverse the returned entities.
	 */
	inline std::pair<EntitiesByComponent::iterator, EntitiesByComponent::iterator> 
		getEntitiesWithComponent(ComponentType type)
	{
		return mEntitiesByComponent.equal_range(type);
	}

	/**
	 * Removes the components of the given entity.
	 *
	 * @param pEntity	The entity to remove the components from.
	 */
	void removeComponentsOfEntity(Entity* pEntity);

	inline World& getWorld() { return mWorld; }

private:
	World& mWorld;
	LinearArena& mArena;
	Entity* mEntities;
	EntitiesByComponent mEntitiesByComponent;
	uint mNumEntities;

}; // class EntityManager
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // ENTITYMANAGER_H