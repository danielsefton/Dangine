//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "Platform/Prerequisites.h"
#include "Scene/Scene.h"

#include "Physics/PhysXActor.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PlayScene : public Scene, public OIS::MouseListener, public OIS::KeyListener
{
public:
	PlayScene(SceneManager& rSceneManager, Input& rInput, PhysXWorld& rPhysXWorld);
	~PlayScene();

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
	PhysXWorld& mPhysXWorld;

	PhysXActor<physx::PxRigidDynamic> mActor;
	Real mAngle;

}; // class PlayScene
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PLAYSCENE_H