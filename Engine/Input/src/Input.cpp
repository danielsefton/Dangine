//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Input/Input.h"
#include "Util/Helper/Assert.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
Input::Input(unsigned long windowHandle)
	: mInputManager(0)
	, mKeyboard(0)
	, mMouse(0)
{
	std::ostringstream windowHndStr;
	OIS::ParamList pl;

	// Use OS mouse.
	windowHndStr << windowHandle;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

//#if DANGINE_PLATFORM == DANGINE_PLATFORM_WIN32
	pl.insert(std::make_pair(
		std::string("w32_mouse"),
		std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(
		std::string("w32_mouse"),
		std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(
		std::string("w32_keyboard"),
		std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(
		std::string("w32_keyboard"),
		std::string("DISCL_NONEXCLUSIVE")));
/*#elif DANGINE_PLATFORM == DANGINE_PLATFORM_LINUX
	pl.insert(std::make_pair(
		std::string("x11_mouse_grab"),
		std::string("false")));
	pl.insert(std::make_pair(
		std::string("x11_mouse_hide"),
		std::string("false")));
	pl.insert(std::make_pair(
		std::string("x11_keyboard_grab"),
		std::string("false")));
	pl.insert(std::make_pair(
		std::string("XAutoRepeatOn"),
		std::string("true")));
#elif DANGINE_PLATFORM == DANGINE_PLATFORM_APPLE
	pl.insert(std::make_pair(
		std::string("osx_mouse_grab"),
		std::string("false")));
	pl.insert(std::make_pair(
		std::string("osx_mouse_hide"),
		std::string("false")));
#endif*/

	mInputManager = OIS::InputManager::createInputSystem(pl);
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(
		OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(
		OIS::OISMouse, true));

	mKeyboard->setEventCallback(this);
	mMouse->setEventCallback(this);
}
//------------------------------------------------------------------------------
Input::~Input()
{
	mInputManager->destroyInputObject(mKeyboard);
	mInputManager->destroyInputObject(mMouse);
	OIS::InputManager::destroyInputSystem(mInputManager);
}
//------------------------------------------------------------------------------
void Input::update()
{
	mKeyboard->capture();
	mMouse->capture();
}
//------------------------------------------------------------------------------
void Input::subscribeMouse(OIS::MouseListener& rMouseListener)
{
	mMouseListeners.push_back(&rMouseListener);
}
//------------------------------------------------------------------------------
void Input::unsubscribeMouse(OIS::MouseListener& rMouseListener)
{
	for (uint i = 0; i < mMouseListeners.size(); ++i)
    {
		if (mMouseListeners[i] == &rMouseListener)
		{
			mMouseListeners.erase(mMouseListeners.begin() + i);
			break;
		}
	}
}
//------------------------------------------------------------------------------
void Input::subscribeKeyboard(OIS::KeyListener& rKeyboardListener)
{
	mKeyboardListeners.push_back(&rKeyboardListener);
}
//------------------------------------------------------------------------------
void Input::unsubscribeKeyboard(OIS::KeyListener& rKeyboardListener)
{
	for (uint i = 0; i < mKeyboardListeners.size(); ++i)
    {
		if (mKeyboardListeners[i] == &rKeyboardListener)
		{
			mKeyboardListeners.erase(mKeyboardListeners.begin() + i);
			break;
		}
	}
}
//------------------------------------------------------------------------------
bool Input::mouseMoved(const OIS::MouseEvent& rEvent)
{
	for (uint i = 0; i < mMouseListeners.size(); ++i)
    {
		OIS::MouseListener* listener = mMouseListeners[i];
		listener->mouseMoved(rEvent);
	}

	return true;
}
//------------------------------------------------------------------------------
bool Input::mousePressed(const OIS::MouseEvent& rEvent, OIS::MouseButtonID id)
{
	for (uint i = 0; i < mMouseListeners.size(); ++i)
    {
		OIS::MouseListener* listener = mMouseListeners[i];
		listener->mousePressed(rEvent, id);
	}

	return true;
}
//------------------------------------------------------------------------------
bool Input::mouseReleased(const OIS::MouseEvent& rEvent, OIS::MouseButtonID id)
{
	for (uint i = 0; i < mMouseListeners.size(); ++i)
    {
		OIS::MouseListener* listener = mMouseListeners[i];
		listener->mouseReleased(rEvent, id);
	}

	return true;
}
//------------------------------------------------------------------------------
bool Input::keyPressed(const OIS::KeyEvent& rEvent)
{
	for (uint i = 0; i < mKeyboardListeners.size(); ++i)
    {
		OIS::KeyListener* listener = mKeyboardListeners[i];
		listener->keyPressed(rEvent);
	}

	return true;
}
//------------------------------------------------------------------------------
bool Input::keyReleased(const OIS::KeyEvent& rEvent)
{
	for (uint i = 0; i < mKeyboardListeners.size(); ++i)
    {
		OIS::KeyListener* listener = mKeyboardListeners[i];
		listener->keyReleased(rEvent);
	}

	return true;
}
//------------------------------------------------------------------------------
void Input::windowResized(unsigned int width, unsigned int height)
{
	const OIS::MouseState& mouseState = mMouse->getMouseState();
	mouseState.width = width;
	mouseState.height = height;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------