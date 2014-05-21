//---------------------------//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Physics/PhysXRenderedActorBinding.h"

#include "Physics/PhysXMappings.h"
#include "Physics/PhysXPointRenderable.h"

#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

void getColumnMajor(PxMat33 m, PxVec3 t, float* mat) {
	mat[0] = m.column0[0];
	mat[1] = m.column0[1];
	mat[2] = m.column0[2];
	mat[3] = 0;

	mat[4] = m.column1[0];
	mat[5] = m.column1[1];
	mat[6] = m.column1[2];
	mat[7] = 0;

	mat[8] = m.column2[0];
	mat[9] = m.column2[1];
	mat[10] = m.column2[2];
	mat[11] = 0;

	mat[12] = t[0];
	mat[13] = t[1];
	mat[14] = t[2];
	mat[15] = 1;
}

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
PhysXRenderedActorBinding::PhysXRenderedActorBinding(PxRigidDynamic* actor, 
	PhysXPointRenderable* renderable)
	: mPxActor(actor)
	, mRenderable(renderable)
{
}
//------------------------------------------------------------------------------
PhysXRenderedActorBinding::~PhysXRenderedActorBinding()
{
}
//------------------------------------------------------------------------------
void PhysXRenderedActorBinding::sync()
{
	//PxTransform pose = mPxActor->getGlobalPose();
	//mRenderable->setTransform(PhysXMappings::toVm(pose.p), PhysXMappings::toVm(pose.q));

	PxMat44 mat(mPxActor->getGlobalPose());
	D3DXMATRIX d3dMat(
		mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	mRenderable->setMatrixTransform(d3dMat);

	/*PxTransform pose = mPxActor->getGlobalPose();
	PxMat33 m = PxMat33(pose.q);
	D3DXMATRIX d3dMat;
	getColumnMajor(m, pose.p, d3dMat);
	mRenderable->setMatrixTransform(d3dMat);*/
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------