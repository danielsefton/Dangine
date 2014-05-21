//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXMAPPINGS_H
#define PHYSXMAPPINGS_H

#include "Platform/Prerequisites.h"

#include <PhysX/foundation/PxQuat.h>
#include <PhysX/foundation/PxMat44.h>
#include <PhysX/foundation/PxVec3.h>
#include <PhysX/foundation/PxBounds3.h>
#include "Util/Math/vmInclude.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXMappings
{
public:
	static vmVector3 toVm(const physx::PxVec3& vec3)
	{
		return vmVector3(vec3.x, vec3.y, vec3.z);
	}
	static vmQuat toVm(const physx::PxQuat& q)
	{
		return vmQuat(q.x, q.y, q.z, q.w);
	}
	static AxisAlignedBox toVm(const physx::PxBounds3 &b)
	{
		return AxisAlignedBox(toVm(b.minimum), toVm(b.maximum));
	}

	static physx::PxVec3 toPx(const vmVector3& vec3)
	{
		return physx::PxVec3(vec3.getX(), vec3.getY(), vec3.getZ());
	}
	static physx::PxQuat toPx(const vmQuat& q)
	{
		physx::PxQuat pxq;
		pxq.w = q.getW();
		pxq.x = q.getX();
		pxq.y = q.getY();
		pxq.z = q.getZ();
		return pxq;
	}
	static physx::PxBounds3 toPx(const AxisAlignedBox &b)
	{
		physx::PxBounds3 Pxb;
		Pxb.minimum = toPx(b.getMinimum());
		Pxb.maximum = toPx(b.getMaximum());
		return Pxb;
	}
	static physx::PxMat44 toPx(const vmVector3& pos, const vmQuat& rot)
	{
		return physx::PxMat44(physx::PxMat33(toPx(rot)), toPx(pos));
	}

}; // class PhysXMappings
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXMAPPINGS_H