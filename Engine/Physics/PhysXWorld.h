//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXWORLD_H
#define PHYSXWORLD_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXWorld
{
public:
	PhysXWorld(LinearArena& rArena);
	~PhysXWorld();

	PhysXScene* addScene(String name, physx::PxSceneDesc& desc);
	PhysXScene* getScene(String name);
	void destroyScene(String name);
	void clearScenes();

	/// Advances the simulation.
	void simulate(Real time);

	/// Synchronises renderables.
	void syncRenderables(); 

	inline physx::PxMaterial& getDefaultMaterial() { return *mDefaultMaterial; }
	inline physx::PxPhysics* getPxPhysics() { return mPxPhysics; }
	inline physx::PxCooking* getCookingInterface() { return mCookingInterface; }

private:
	PhysXWorld& operator=(const PhysXWorld&); // Fix for C4512
	LinearArena& mArena;
	physx::PxDefaultAllocator* mAllocator;

	PhysXLogOutputStream* mErrorOutputStream;

	physx::PxFoundation* mFoundation;
	physx::PxPhysics* mPxPhysics;
	physx::PxCooking* mCookingInterface;

	std::unordered_map<String, PhysXScene*> mScenes;

	bool mSimulating;

	physx::PxMaterial* mDefaultMaterial;

	std::map<String, physx::PxMaterial*> mMaterialBindings;

}; // class PhysXWorld
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXWORLD_H