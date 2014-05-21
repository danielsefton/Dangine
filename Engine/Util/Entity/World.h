//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef WORLD_H
#define WORLD_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class World
{
public:
	World(LinearArena& rArena, uint maxEntities);
	~World();

	inline void setElapsed(const Real& elapsed) { mElapsed = elapsed; }
	inline Real getElapsed() { return mElapsed; }

	inline Entity& getEntity(uint id) { return mEntityManager->getEntity(id); }

	template<typename T> inline T* getSystem()
	{
		return mSystemManager->getSystem<T>();
	}

	inline EntityManager& getEntityManager() { return *mEntityManager; }
	inline SystemManager& getSystemManager() { return *mSystemManager; }
	inline LinearArena& getLinearArena() { return mArena; }

private:
	World& operator=(const World&); // Fix for C4512
	LinearArena& mArena;
	EntityManager* mEntityManager;
	SystemManager* mSystemManager;
	Real mElapsed;

}; // class World
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // WORLD_H