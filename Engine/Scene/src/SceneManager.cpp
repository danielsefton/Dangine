//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
SceneManager::SceneManager(World& rWorld, LinearArena& rArena)
	: mWorld(rWorld)
	, mArena(rArena)
	, mActiveScene(0)
{
}
//------------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	unloadActiveScene();

	for (Scenes::iterator i = mScenes.begin(); i != mScenes.end(); ++i)
	{
		delete i->second;
	}
	mScenes.clear();
}
//------------------------------------------------------------------------------
void SceneManager::loadScene(const String& rName)
{
	if (hasScene(rName))
	{
		unloadActiveScene();
		
		mActiveScene = &getScene(rName);
		mActiveScene->create();
	}
	else
	{
		LOG(logERROR) << "[SceneManager::loadScene] Scene '" << rName << "' does not exist.";
	}
}
//------------------------------------------------------------------------------
void SceneManager::updateActiveScene()
{
	if (mActiveScene)
		mActiveScene->update();
}
//------------------------------------------------------------------------------
void SceneManager::unloadActiveScene()
{
	if (mActiveScene)
	{
		mActiveScene->destroy();
		mActiveScene = 0;
	}
}
//------------------------------------------------------------------------------
Scene& SceneManager::getActiveScene() const
{
	if (mActiveScene)
	{
		return *mActiveScene;
	}
	else
	{
		LOG(logERROR) << "[SceneManager::getActiveScene] No active scene has been defined.";
	}
}
//------------------------------------------------------------------------------
Scene& SceneManager::addScene(const String& rName)
{
	if (!hasScene(rName))
	{
		Scene* scene = new Scene(rName, *this);
		mScenes[scene->getName()] = scene;
		return *scene;
	}
	else
	{
		LOG(logERROR) << "[SceneManager::addScene] Scene with the name '" << rName + "' already exists.";
	}
}
//------------------------------------------------------------------------------
Scene& SceneManager::addScene(Scene* pScene)
{
	if (!hasScene(pScene->getName()))
	{
		mScenes[pScene->getName()] = pScene;
		return *pScene;
	}
	else
	{
		LOG(logERROR) << "[SceneManager::addScene] Scene with the name '" << pScene->getName() + "' already exists.";
	}
}
//------------------------------------------------------------------------------
void SceneManager::removeScene(const String& rName)
{
	Scenes::iterator i = mScenes.find(rName);
	if (i != mScenes.end())
	{
		delete i->second;
		mScenes.erase(i);
	}
	else
	{
		LOG(logERROR) << "[SceneManager::removeScene] Scene '" << rName << "' does not exist.";
	}
}
//------------------------------------------------------------------------------
void SceneManager::removeScene(Scene& rScene)
{
	removeScene(rScene.getName());
}
//------------------------------------------------------------------------------
Scene& SceneManager::getScene(const String& rName) const
{
	Scenes::const_iterator i = mScenes.find(rName);
	if (i != mScenes.end())
	{
		return *i->second;
	}
	else
	{
		LOG(logERROR) << "[SceneManager::getScene] Scene '" << rName << "' does not exist.";
	}
}
//------------------------------------------------------------------------------
bool SceneManager::hasScene(const String& rName) const
{
	return (mScenes.find(rName) != mScenes.end());
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------