//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

// This code contains NVIDIA Confidential Information and is disclosed to you 
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and 
// any modifications thereto. Any use, reproduction, disclosure, or 
// distribution of this software and related documentation without an express 
// license agreement from NVIDIA Corporation is strictly prohibited.
// 
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2012 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef PHYSXSTREAM_H
#define PHYSXSTREAM_H

#include "Platform/Prerequisites.h"

#include <PhysX/common/PxIO.h>

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXMemoryOutputStream : public physx::PxOutputStream
{
public:
	PhysXMemoryOutputStream();
	virtual ~PhysXMemoryOutputStream();

	physx::PxU32 write(const void* src, physx::PxU32 count);

	physx::PxU32 getSize() const { return mSize; }
	physx::PxU8* getData() const { return mData; }

private:
	physx::PxU8* mData;
	physx::PxU32 mSize;
	physx::PxU32 mCapacity;
};
//------------------------------------------------------------------------------
class PhysXFileOutputStream : public physx::PxOutputStream
{
public:
	PhysXFileOutputStream(const char* name);
	virtual ~PhysXFileOutputStream();

	physx::PxU32 write(const void* src, physx::PxU32 count);

	bool isValid();

private:
	FILE* mFile;
};
//------------------------------------------------------------------------------
class PhysXMemoryInputData : public physx::PxInputData
{
public:
	PhysXMemoryInputData(physx::PxU8* data, physx::PxU32 length);

	physx::PxU32 read(void* dest, physx::PxU32 count);
	physx::PxU32 getLength() const;
	void seek(physx::PxU32 pos);
	physx::PxU32 tell() const;

private:
	physx::PxU32 mSize;
	const physx::PxU8* mData;
	physx::PxU32 mPos;
};
//------------------------------------------------------------------------------
class PhysXFileInputData : public physx::PxInputData
{
public:
	PhysXFileInputData(const char* name);
	virtual ~PhysXFileInputData();

	physx::PxU32 read(void* dest, physx::PxU32 count);
	void seek(physx::PxU32 pos);
	physx::PxU32 tell() const;
	physx::PxU32 getLength() const;
			
	bool isValid() const;

private:
	FILE* mFile;
	physx::PxU32 mLength;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXSTREAM_H