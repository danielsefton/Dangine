//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef ENTITY_H
#define ENTITY_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/Component.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
typedef std::map<ComponentType, Component*> Components;
//------------------------------------------------------------------------------
struct Entity
{
	static EntityManager* entityManager;

	Entity();
	~Entity();

	template<typename T> inline void addComponent(T* pComponent)
	{
		entityManager->addComponent(this, pComponent);
	}

	template<typename Type> inline Type* getComponent()
	{
		return entityManager->getComponent<Type>(this);
	}

	template<typename T> inline void removeComponent(T* pComponent)
	{
		entityManager->removeComponent(this, T::type);
	}

	void removeComponent(Entity* pEntity, ComponentType type);

	Components mComponents;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // ENTITY_H