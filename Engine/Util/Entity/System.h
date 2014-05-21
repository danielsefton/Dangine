//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class System
{
public:
	static SystemManager* systemManager;

	System(ComponentType type);
	virtual ~System();

	void initialise();
	void destroy();
	void process();

	template<class T> inline T* cast() { return static_cast<T*>(this); }

protected:
	virtual void _initialise(Entity& rEntity) = 0;
	virtual void _destroy(Entity& rEntity) = 0;
	virtual void _process(Entity& rEntity) = 0;

private:
	void _initialiseEntities(std::vector<Entity*>& rEntities);
	void _destroyEntities(std::vector<Entity*>& rEntities);
	void _processEntities(std::vector<Entity*>& rEntities);

	ComponentType mComponentType;
	std::vector<Entity*> mEntitiesWithComponent;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // SYSTEM_H