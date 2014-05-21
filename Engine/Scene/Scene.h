//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef SCENE_H
#define SCENE_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class Scene
{
public:
	Scene(const String& rName, SceneManager& rSceneManager)
		: mName(rName)
		, mSceneManager(rSceneManager)
	{
	}
	~Scene() {}

	virtual void create() {}
	virtual void destroy() {}
	virtual void update() {}

	inline void setName(const String& value) { mName = value; }
	inline const String& getName() const { return mName; }
	inline SceneManager& getSceneManager() const { return mSceneManager; }

private:
	Scene& operator=(const Scene&); // Fix for C4512
	String mName;
	SceneManager& mSceneManager;

}; // class Scene
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // SCENE_H