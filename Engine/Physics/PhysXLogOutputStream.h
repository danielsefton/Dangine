//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based loosely on OgrePhysX http://www.ogre3d.org/forums/viewtopic.php?f=5&t=54763
//------------------------------------------------------------------------------

#ifndef PHYSXLOGOUTPUTSTREAM_H
#define PHYSXLOGOUTPUTSTREAM_H

#include <PhysX/foundation/PxErrorCallback.h>
#include <PhysX/PxPhysicsAPI.h>

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class PhysXLogOutputStream : public physx::PxErrorCallback
{
	void reportError(physx::PxErrorCode::Enum e, const char* message, const char* file, int line)
	{
		(void)e;
		String msg = "[PhysX] Error in " + String(file) + "line " + StringUtil::toString(line) + ": " + String(message);
#if	PHYSX_CANMOVESTATICACTORS
		if (msg.find("Static actor moved") == String::npos)
			LOG(logINFO) << msg;
#else
		LOG(logINFO) << msg;
#endif
	}
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // PHYSXLOGOUTPUTSTREAM_H