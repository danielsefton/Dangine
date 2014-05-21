//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef PHYSXCOOKER_H
#define PHYSXCOOKER_H

#include "Platform/Prerequisites.h"

#include "Physics/PhysXMappings.h"

#include <PhysX/cooking/PxConvexMeshDesc.h>

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXCooker
{
public:
	PhysXCooker();
	~PhysXCooker();

	static physx::PxTriangleMesh* createPxTriangleMesh(physx::PxPhysics& physics, 
		physx::PxCooking& cooking, std::vector<short> indices, std::vector<Real> vertices);
	static physx::PxConvexMesh* createPxConvexMesh(physx::PxPhysics& physics, 
		physx::PxCooking& cooking, std::vector<Real> vertices);

	static physx::PxTriangleMesh* createTriangleMesh32(physx::PxPhysics& physics, physx::PxCooking& cooking, const physx::PxVec3* verts, physx::PxU32 vertCount, const physx::PxU32* indices32, physx::PxU32 triCount);
	static physx::PxTriangleMesh* createTriangleMesh16(physx::PxPhysics& physics, physx::PxCooking& cooking, const physx::PxVec3* verts, physx::PxU16 vertCount, const physx::PxU16* indices16, physx::PxU16 triCount);
	static physx::PxTriangleMesh* createTriangleMesh32(physx::PxPhysics& physics, physx::PxCooking& cooking, physx::PxTriangleMeshDesc* meshDesc);
	static physx::PxConvexMesh* createConvexMesh(physx::PxPhysics& physics, physx::PxCooking& cooking, const physx::PxVec3* verts, physx::PxU32 vertCount, physx::PxConvexFlags flags);

}; // class PhysXCooker
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXCOOKER_H