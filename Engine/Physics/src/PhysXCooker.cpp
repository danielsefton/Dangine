//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Physics/PhysXCooker.h"

#include "Physics/PhysXStream.h"

#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
PhysXCooker::PhysXCooker()
{
}
//------------------------------------------------------------------------------
PhysXCooker::~PhysXCooker()
{
}
//------------------------------------------------------------------------------
PxTriangleMesh* PhysXCooker::createPxTriangleMesh(PxPhysics& physics, PxCooking& cooking, 
	std::vector<short> indices, std::vector<Real> vertices)
{
	PxU32 numVertices = vertices.size() / 3;
	PxU32 numTris = indices.size() / 3;

	// Create pointer for vertices
	PxVec3* verts = new PxVec3[numVertices];

	int ii = numVertices * 3;
	for (int i = numVertices - 1; i >= 0; i--)
	{
		--ii;
		verts[i].x = vertices[ii];
		verts[i].y = vertices[--ii];
		verts[i].z = vertices[--ii];
	}

	// Create pointer for indices
	PxU16* tris = new PxU16[indices.size()];

	ii = 0;
	for (int numInd = 0; numInd < numTris * 3; ++numInd)
	{
		tris[numInd] = indices[ii];
		numInd++;
		tris[numInd] = indices[++ii];
		numInd++;
		tris[numInd] = indices[++ii];
		++ii;
	}

	PxTriangleMesh* triangleMesh = PhysXCooker::createTriangleMesh16(
		physics, cooking, verts, numVertices, tris, numTris);

	delete[] verts;
	delete[] tris;

	return triangleMesh;
}
//------------------------------------------------------------------------------
physx::PxConvexMesh* PhysXCooker::createPxConvexMesh(PxPhysics& physics, 
	PxCooking& cooking, std::vector<Real> vertices)
{
	PxU32 numVertices = vertices.size() / 3;

	// Create pointer for vertices
	PxVec3* verts = new PxVec3[numVertices];

	int ii = numVertices * 3;
	for (int i = numVertices - 1; i >= 0; i--)
	{
		--ii;
		verts[i].x = vertices[ii];
		verts[i].y = vertices[--ii];
		verts[i].z = vertices[--ii];
	}

	PxConvexFlags flags;
	flags |= PxConvexFlag::eCOMPUTE_CONVEX;
	PxConvexMesh* convexMesh = PhysXCooker::createConvexMesh(
		physics, cooking, verts, numVertices, flags);

	delete[] verts;

	return convexMesh;
}
//------------------------------------------------------------------------------
PxTriangleMesh* PhysXCooker::createTriangleMesh32(PxPhysics& physics, PxCooking& cooking, 
	const PxVec3* verts, PxU32 vertCount, const PxU32* indices32, PxU32 triCount)
{
	PxTriangleMeshDesc meshDesc;
	meshDesc.points.count			= vertCount;
	meshDesc.points.stride			= sizeof(PxVec3);
	meshDesc.points.data			= verts;

	meshDesc.triangles.count		= triCount;
	meshDesc.triangles.stride		= 3 * sizeof(PxU32);
	meshDesc.triangles.data			= indices32;

	PhysXMemoryOutputStream writeBuffer;
	bool status = cooking.cookTriangleMesh(meshDesc, writeBuffer);
	if (!status)
		return NULL;

	PhysXMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	return physics.createTriangleMesh(readBuffer);
}
//------------------------------------------------------------------------------
PxTriangleMesh* PhysXCooker::createTriangleMesh16(PxPhysics& physics, PxCooking& cooking, 
	const PxVec3* verts, PxU16 vertCount, const PxU16* indices16, PxU16 triCount)
{
	PxTriangleMeshDesc meshDesc;
	meshDesc.points.count			= vertCount;
	meshDesc.points.stride			= sizeof(PxVec3);
	meshDesc.points.data			= verts;

	meshDesc.triangles.count		= triCount;
	meshDesc.triangles.stride		= 3 * sizeof(PxU16);
	meshDesc.triangles.data			= indices16;
	meshDesc.flags |= PxMeshFlag::e16_BIT_INDICES | PxMeshFlag::eFLIPNORMALS;

	PhysXMemoryOutputStream writeBuffer;
	bool status = cooking.cookTriangleMesh(meshDesc, writeBuffer);
	if (!status)
		return NULL;

	PhysXMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	return physics.createTriangleMesh(readBuffer);
}
//------------------------------------------------------------------------------
PxTriangleMesh* PhysXCooker::createTriangleMesh32(PxPhysics& physics, PxCooking& cooking, 
	PxTriangleMeshDesc* meshDesc)
{
	PhysXMemoryOutputStream writeBuffer;
	bool status = cooking.cookTriangleMesh(*meshDesc, writeBuffer);
	if (!status)
		return NULL;

	PhysXMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	return physics.createTriangleMesh(readBuffer);
}
//------------------------------------------------------------------------------
PxConvexMesh* PhysXCooker::createConvexMesh(PxPhysics& physics, PxCooking& cooking, 
	const PxVec3* verts, PxU32 vertCount, PxConvexFlags flags)
{
	PxConvexMeshDesc convexDesc;
	convexDesc.points.count			= vertCount;
	convexDesc.points.stride		= sizeof(PxVec3);
	convexDesc.points.data			= verts;
	convexDesc.flags				= flags;

	PhysXMemoryOutputStream buf;
	if (!cooking.cookConvexMesh(convexDesc, buf))
		return NULL;

	PhysXMemoryInputData input(buf.getData(), buf.getSize());
	return physics.createConvexMesh(input);
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------