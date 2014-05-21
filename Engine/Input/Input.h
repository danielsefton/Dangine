//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef INPUT_H
#define INPUT_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
typedef std::vector<OIS::MouseListener*> MouseListeners;
typedef std::vector<OIS::KeyListener*> KeyboardListeners;
//------------------------------------------------------------------------------
class Input : public OIS::MouseListener, public OIS::KeyListener
{
public:
	/**
	 * Default constructor.
	 */
	Input(unsigned long windowHandle);
	/**
	 * Destructor.
	 */
	~Input();

	void update();

	/**
	 * Subscribe for mouse events.
	 * 
	 * @param [in,out] rMouseListener  The mouse listener. 
	 */
	void subscribeMouse(OIS::MouseListener& rMouseListener);
	/**
	 * Unsubscribe for mouse events.
	 * 
	 * @param [in,out] rMouseListener  The mouse listener. 
	 */
	void unsubscribeMouse(OIS::MouseListener& rMouseListener);
	/**
	 * Subscribe for keyboard events.
	 * 
	 * @param [in,out] rKeyboardListener   The keyboard listener. 
	 */
	void subscribeKeyboard(OIS::KeyListener& rKeyboardListener);
	/**
	 * Unsubscribe for keyboard events.
	 * 
	 * @param [in,out] rKeyboardListener   The keyboard listener. 
	 */
	void unsubscribeKeyboard(OIS::KeyListener& rKeyboardListener);

	inline OIS::InputManager* getInput() const { return mInputManager; }
	inline OIS::Mouse* getMouse() const { return mMouse; }
	inline OIS::Keyboard* getKeyboard() const { return mKeyboard; }

private:
	bool mouseMoved(const OIS::MouseEvent& rEvent);
	bool mousePressed(const OIS::MouseEvent& rEvent, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& rEvent, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent& rEvent);
	bool keyReleased(const OIS::KeyEvent& rEvent);

	void windowResized(unsigned int width, unsigned int height);

	OIS::InputManager* mInputManager;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;

	MouseListeners mMouseListeners;
	KeyboardListeners mKeyboardListeners;

}; // class Input
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // INPUTMANAGER_H