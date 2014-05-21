//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Platform/Prerequisites.h"
#include "Scene/Scene.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class MenuScene : public Scene, public OIS::MouseListener, public OIS::KeyListener
{
public:
	MenuScene(SceneManager& rSceneManager, Input& rInput);
	~MenuScene();

	void create();
	void destroy();
	void update();

private:
	bool mouseMoved(const OIS::MouseEvent& rEvent);
	bool mousePressed(const OIS::MouseEvent& rEvent, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& rEvent, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent& rEvent);
	bool keyReleased(const OIS::KeyEvent& rEvent);

	Input& mInput;

}; // class MenuScene
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // MENUSCENE_H