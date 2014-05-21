
#ifndef __VM_INCLUDE_H
#define __VM_INCLUDE_H

//#include "LinearMath/btScalar.h"

#if defined (USE_SYSTEM_VECTORMATH) || defined (__CELLOS_LV2__)
	#include <vectormath_aos.h>
#else //(USE_SYSTEM_VECTORMATH)
	#if defined (DG_USE_SSE) && defined (_WIN32)
		#include "sse/vectormath_aos.h"
	#else //all other platforms
		#include "scalar/vectormath_aos.h"
	#endif //(BT_USE_SSE) && defined (_WIN32)
#endif //(USE_SYSTEM_VECTORMATH)


#if DANGINE_COMPILER == DANGINE_COMPILER_MSVC
// warning C4505: unreferenced local function has been removed
# pragma warning (disable : 4505)
#endif

//------------------------------------------------------------------------------
typedef Vectormath::Aos::Vector3    vmVector3;
typedef Vectormath::Aos::Vector4    vmVector4;
typedef Vectormath::Aos::Quat       vmQuat;
typedef Vectormath::Aos::Matrix3    vmMatrix3;
typedef Vectormath::Aos::Matrix4    vmMatrix4;
typedef Vectormath::Aos::Transform3 vmTransform3;
typedef Vectormath::Aos::Point3     vmPoint3;
//------------------------------------------------------------------------------
#endif //__VM_INCLUDE_H


