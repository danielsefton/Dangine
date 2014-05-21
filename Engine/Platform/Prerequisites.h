#ifndef PREREQUISITES_H
#define PREREQUISITES_H

#include "Platform/Platform.h"

namespace Dangine
{
#if DG_DOUBLE_PRECISION == 1
	typedef double Real;
#else
	typedef float Real;
#endif

#if DG_COMPILER == DG_COMPILER_GNUC && DG_COMP_VER >= 310 && !defined(STLPORT)
#   if DG_COMP_VER >= 430
#       define HashMap ::std::tr1::unordered_map
#		define HashSet ::std::tr1::unordered_set
#    else
#       define HashMap ::__gnu_cxx::hash_map
#       define HashSet ::__gnu_cxx::hash_set
#    endif
#else
#   if DG_COMPILER == DG_COMPILER_MSVC
#       if DG_COMP_VER >= 1600 // VC++ 10.0
#			define HashMap ::std::tr1::unordered_map
#           define HashSet ::std::tr1::unordered_set
#		elif DG_COMP_VER > 1300 && !defined(_STLP_MSVC)
#           define HashMap ::stdext::hash_map
#           define HashSet ::stdext::hash_set
#       else
#           define HashMap ::std::hash_map
#           define HashSet ::std::hash_set
#       endif
#   else
#       define HashMap ::std::hash_map
#       define HashSet ::std::hash_set
#   endif
#endif

	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned long ulong;

	class Input;
	class Game;
	class Entity;
	class EntityManager;
	class SystemManager;
	class World;
	class System;
	class Config;

	// Components
	struct Camera;
	struct Light;
	struct Mesh;
	struct Sound;
	struct Transform;

	// Systems
	class CameraSystem;
	class MeshSystem;
	class LightSystem;
	class SoundSystem;

	// Graphics
	class RenderSystem;

	// Network
	class RakClientServer;
	class ReplicaManager;
	class ReplicaConnection;

	// Scene
	class Scene;
	class SceneManager;

	// Physics
	class PhysXWorld;
	class PhysXScene;
	template<class T> class PhysXActor;
	class PhysXMemoryStream;
	class PhysXLogOutputStream;
	class PhysXRenderableBinding;
	class PhysXRenderedActorBinding;
	class PhysXPointRenderable;
	class PhysXEntityRenderable;

#if DANGINE_WCHAR_T_STRINGS
	typedef std::wstring _StringBase;
#else
	typedef std::string _StringBase;
#endif

#if DANGINE_WCHAR_T_STRINGS
	typedef std::basic_stringstream<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _StringStreamBase;
#else
	typedef std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > _StringStreamBase;
#endif

	typedef _StringBase String;
	typedef _StringStreamBase StringStream;
	typedef StringStream stringstream;

	typedef unsigned char ComponentType;
	
	// Component types
	enum ComponentTypeEnum
	{
		COMPONENTTYPE_TRANSFORM = 0x01,
		COMPONENTTYPE_MESH = 0x02,
		COMPONENTTYPE_LIGHT = 0x03,
		COMPONENTTYPE_CAMERA = 0x04,
		COMPONENTTYPE_SOUND = 0x05
	};

	typedef unsigned char ReplicaType;

	// Replica types
	enum ReplicaTypeEnum
	{
		REPLICATYPE_ENTITY = 0x01,
		REPLICATYPE_COMPONENT = 0x02
	};
}

namespace physx
{
	class PxDefaultAllocator;
	class PxFoundation;
	class PxPhysics;
	class PxScene;
	class PxSceneDesc;
	class PxCooking;
	class PxMaterial;
	class PxActor;
	class PxGeometry;
	class PxRigidDynamic;
	class PxTriangleMesh;
	class PxConvexMesh;
	class PxTriangleMeshDesc;
}

#define PHYSX_CANMOVESTATICACTORS 1
#define PX_SUPPORT_VISUAL_DEBUGGER 1

#define DG_UNUSED(x)

#endif // PREREQUISITES_H