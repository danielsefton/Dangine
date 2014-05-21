//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXGEOMETRY_H
#define PHYSXGEOMETRY_H

#include "Platform/Prerequisites.h"

#include "Physics/PhysXMappings.h"
#include "Physics/PhysXCooker.h"
#include "Systems/MeshSystem.h"

#include <PhysX/geometry/PxPlaneGeometry.h>
#include <PhysX/geometry/PxSphereGeometry.h>
#include <PhysX/geometry/PxBoxGeometry.h>
#include <PhysX/geometry/PxCapsuleGeometry.h>
#include <PhysX/geometry/PxConvexMeshGeometry.h>
#include <PhysX/geometry/PxTriangleMeshGeometry.h>

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXGeometry
{
public:
	static physx::PxSphereGeometry sphereGeometry(Entity& entity, MeshSystem& meshSystem, Real scale = 1.0f)
	{
		Real sphereShapeRadius = meshSystem.getBoundingRadius(entity) * scale;
		return physx::PxSphereGeometry(sphereShapeRadius);
	}

	static physx::PxSphereGeometry sphereGeometry(Entity& entity, MeshSystem& meshSystem, physx::PxTransform& outShapeOffset, Real scale = 1.0f)
	{
		outShapeOffset.p = PhysXMappings::toPx(meshSystem.getBoundingBox(entity).getCenter());
		Real sphereShapeRadius = meshSystem.getBoundingRadius(entity) * scale;
		return physx::PxSphereGeometry(sphereShapeRadius);
	}

	static physx::PxBoxGeometry boxGeometry(Entity& entity, MeshSystem& meshSystem, const vmVector3& scale = vmVector3(1,1,1))
	{
		vmVector3 size = meshSystem.getBoundingBox(entity).getHalfSize();
		size.setX(size.getX() * scale.getX());
		size.setY(size.getY() * scale.getY());
		size.setZ(size.getZ() * scale.getZ());
		return physx::PxBoxGeometry(PhysXMappings::toPx(size));
	}

	static physx::PxBoxGeometry boxGeometry(Entity& entity, MeshSystem& meshSystem, physx::PxTransform& outShapeOffset, const vmVector3& scale = vmVector3(1,1,1))
	{
		outShapeOffset.p = PhysXMappings::toPx(meshSystem.getBoundingBox(entity).getCenter());
		vmVector3 size = meshSystem.getBoundingBox(entity).getHalfSize();
		size.setX(size.getX() * scale.getX());
		size.setY(size.getY() * scale.getY());
		size.setZ(size.getZ() * scale.getZ());
		return physx::PxBoxGeometry(PhysXMappings::toPx(size));
	}

	static physx::PxBoxGeometry boxGeometry(const vmVector3& dimensions)
	{
		return physx::PxBoxGeometry(PhysXMappings::toPx(dimensions));
	}

	/// A plane geometry has no properties in PhysX 3, the normal is always (1, 0, 0).
	static physx::PxPlaneGeometry planeGeometry()
	{
		return physx::PxPlaneGeometry();
	}

	/*static physx::PxConvexMeshGeometry convexMeshGeometry(Ogre::MeshPtr mesh, Cooker::Params params = Cooker::Params())
	{
		return physx::PxConvexMeshGeometry(Cooker::getSingleton().createPxConvexMesh(mesh, params));
	}*/

	/*static physx::PxTriangleMeshGeometry triangleMeshGeometry(Ogre::MeshPtr mesh, Cooker::Params params = Cooker::Params())
	{
		return physx::PxTriangleMeshGeometry(PhysXCooker::createPxTriangleMesh(mesh, params));
	}*/

}; // class PhysXGeometry
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXGEOMETRY_H