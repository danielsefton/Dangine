//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
typedef std::map<String, Scene*> Scenes;
//------------------------------------------------------------------------------
class SceneManager
{
public:
	SceneManager(World& rWorld, LinearArena& rArena);
	~SceneManager();

	/**
	 * Loads a scene from its template.
	 *
	 * @param rName	Name of the scene to load.
	 */
	void loadScene(const String& rName);
	/**
	 * Updates the active scene.
	 */
	void updateActiveScene();
	/**
	 * Unloads the currently active scene.
	 */
	void unloadActiveScene();
	/**
	 * Gets the currently active scene.
	 */
	Scene& getActiveScene() const;
	/**
	 * Adds a scene with a given name.
	 *
	 * @param rName	Name of the scene to add.
	 */
	Scene& addScene(const String& rName);
	/**
	 * Adds a scene with a given pointer.
	 *
	 * @param pScene	Scene pointer to add.
	 */
	Scene& addScene(Scene* pScene);
	/**
	 * Removes a Scene with a given name.
	 *
	* @param rName	Name of the scene to remove.
	 */
	void removeScene(const String& rName);
	/**
	 * Removes a Scene by reference.
	 *
	 * @param rScene	Reference to the scene to remove.
	 */
	void removeScene(Scene& rScene);
	/**
	 * Gets a named Scene.
	 *
	 * @param rName	Name of the scene to get.
	 */
	Scene& getScene(const String& rName) const;
	/**
	 * Gets the map of scenes.
	 */
	inline const Scenes& getScenes() const { return mScenes; }
	/**
	 * Returns whether a scene with the given name exists.
	 *
	 * @param rName	Name of the scene to find.
	 */
	bool hasScene(const String& rName) const;

	inline World& getWorld() { return mWorld; }

private:
	SceneManager& operator=(const SceneManager&); // Fix for C4512
	World& mWorld;
	LinearArena& mArena;
	Scenes mScenes;
	Scene* mActiveScene;

}; // class SceneManager
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // SCENEMANAGER_H