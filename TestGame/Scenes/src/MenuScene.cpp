//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Scenes/MenuScene.h"

#include "Scene/SceneManager.h"
#include "Input/Input.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
MenuScene::MenuScene(SceneManager& rSceneManager, Input& rInput)
	: Scene("Menu", rSceneManager)
	, mInput(rInput)
{
}
//------------------------------------------------------------------------------
MenuScene::~MenuScene()
{
}
//------------------------------------------------------------------------------
void MenuScene::create()
{
	mInput.subscribeKeyboard(*this);
	mInput.subscribeMouse(*this);
}
//------------------------------------------------------------------------------
void MenuScene::destroy()
{
	mInput.unsubscribeKeyboard(*this);
	mInput.unsubscribeMouse(*this);
}
//------------------------------------------------------------------------------
void MenuScene::update()
{
}
//------------------------------------------------------------------------------
bool MenuScene::mouseMoved(const OIS::MouseEvent& rEvent)
{
	return true;
}
//------------------------------------------------------------------------------
bool MenuScene::mousePressed(const OIS::MouseEvent& DG_UNUSED(rEvent), OIS::MouseButtonID DG_UNUSED(id))
{
	return true;
}
//------------------------------------------------------------------------------
bool MenuScene::mouseReleased(const OIS::MouseEvent& DG_UNUSED(rEvent), OIS::MouseButtonID DG_UNUSED(id))
{
	return true;
}
//------------------------------------------------------------------------------
bool MenuScene::keyPressed(const OIS::KeyEvent& rEvent)
{
	if (rEvent.key == OIS::KC_SPACE)
	{
		getSceneManager().loadScene("Play");
	}
	return true;
}
//------------------------------------------------------------------------------
bool MenuScene::keyReleased(const OIS::KeyEvent& DG_UNUSED(rEvent))
{
	return true;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------