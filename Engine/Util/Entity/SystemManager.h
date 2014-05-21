//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/System.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
typedef std::map<ComponentType, System*> Systems;
//------------------------------------------------------------------------------
class SystemManager
{
public:
	SystemManager(World& rWorld, LinearArena& rArena);
	~SystemManager();

	System* addSystem(ComponentType type, System* pSystem);

	template<typename T> inline System* addSystem()
	{
		return addSystem(T::type, DG_NEW(T, mArena)(T::type));
	}

	template<typename T> inline T* getSystem()
	{
		return (T*)mSystems[T::type];
	}

	void initialiseAll();
	void destroyAll();

	inline const Systems& getSystems() const { return mSystems; }
	inline World& getWorld() { return mWorld; }

private:
	SystemManager& operator=(const SystemManager&); // Fix for C4512
	World& mWorld;
	LinearArena& mArena;
	Systems mSystems;

}; // class SystemManager
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // SYSTEMMANAGER_H