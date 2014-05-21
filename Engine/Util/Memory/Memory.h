//------------------------------------------------------------------------------
// Created by Daniel Sefton
//
// Based on: http://molecularmusings.wordpress.com/2011/07/05/memory-system-part-1/
//------------------------------------------------------------------------------

#ifndef MEMORY_H
#define MEMORY_H

#include "Platform/Prerequisites.h"

#include <malloc.h>
#include <assert.h>

#define ALLOCATOR_ALIGNMENT    16
#define ALIGNED_SIZE(size, alignment) ((size + (alignment - 1)) & ~(alignment - 1))

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
// Helper functions
//------------------------------------------------------------------------------
/**
 * Type-based dispatching.
 */
template <int I>
struct IntToType
{
	enum { Value = I };
	typedef int ValueType;
	typedef IntToType<I> Type;
	typedef IntToType<I+1> Next;
	typedef IntToType<I-1> Previous;
};

typedef IntToType<0> NonPODType;
typedef IntToType<1> PODType;
//------------------------------------------------------------------------------
/**
 * Helper function which is able to deduce both the type and count from a single argument.
 * A partial template specialization is provided for types taking the form T[N].
 */
template <class T>
struct TypeAndCount
{
};

template <class T, size_t N>
struct TypeAndCount<T[N]>
{
  typedef T Type;
  static const size_t Count = N;
};
//------------------------------------------------------------------------------
/**
 * Determines whether the given data is a Plain Old Data format.
 */
template <typename T>
struct IsPOD
{
	static const bool Value = std::is_pod<T>::value;
};
//------------------------------------------------------------------------------
/**
 * Holds the source file and line number.
 */
struct SourceInfo
{
	SourceInfo(const char* file, int line)
		: File(file), Line(line)
	{
	}
	const char* File;
	int Line;
};
//------------------------------------------------------------------------------
// Specialisations
//------------------------------------------------------------------------------
template <typename T, class ARENA>
void Delete(T* object, ARENA& arena)
{
	object->~T();
	arena.Free(object);
}
//------------------------------------------------------------------------------
template <typename T, class ARENA>
T* NewArray(ARENA& arena, size_t N, size_t alignment, const SourceInfo& sourceInfo, NonPODType)
{
	union
	{
		void* as_void;
		size_t* as_size_t;
		T* as_T;
	};

	as_void = arena.Allocate(sizeof(T) * N + sizeof(size_t), alignment, sourceInfo);

	// store number of instances in first size_t bytes
	*as_size_t++ = N;

	// construct instances using placement new
	const T* const onePastLast = as_T + N;
	while (as_T < onePastLast)
		new (as_T++) T;

	// hand user the pointer to the first instance
	return (as_T - N);
}

template <typename T, class ARENA>
T* NewArray(ARENA& arena, size_t N, size_t alignment, const SourceInfo& sourceInfo, PODType)
{
	return (T*)arena.Allocate(sizeof(T) * N, alignment, sourceInfo);
}

template <typename T, class ARENA>
T* NewNullArray(ARENA& arena, size_t N, size_t alignment, const SourceInfo& sourceInfo)
{
	return (T*)arena.Allocate(sizeof(T) * N, alignment, sourceInfo);
}
//------------------------------------------------------------------------------
template <typename T, class ARENA>
void DeleteArray(T* ptr, ARENA& arena, NonPODType)
{
	union
	{
		size_t* as_size_t;
		T* as_T;
	};

	// user pointer points to first instance...
	as_T = ptr;

	// ...so go back size_t bytes and grab number of instances
	const size_t N = as_size_t[-1];

	// call instances' destructor in reverse order
	for (size_t i = N; i > 0; --i)
		as_T[i-1].~T();

	arena.Free(as_size_t - 1);
}

template <typename T, class ARENA>
void DeleteArray(T* ptr, ARENA& arena, PODType)
{
	arena.Free(ptr);
}

template <typename T, class ARENA>
void DeleteArray(T* ptr, ARENA& arena)
{
	DeleteArray(ptr, arena, IntToType<IsPOD<T>::Value>());
}
//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define DG_NEW(type, arena)						new (arena.Allocate(sizeof(type), ALLOCATOR_ALIGNMENT, SourceInfo(__FILE__, __LINE__))) type
#define DG_DELETE(object, arena)				Delete(object, arena)
#define DG_NEW_ARRAY(type, arena)				NewArray<TypeAndCount<type>::Type>(arena, TypeAndCount<type>::Count, ALLOCATOR_ALIGNMENT, SourceInfo(__FILE__, __LINE__), IntToType<IsPOD<TypeAndCount<type>::Type>::Value>())
#define DG_NEW_ARRAY2(type, count, arena)		NewArray<type>(arena, count, ALLOCATOR_ALIGNMENT, SourceInfo(__FILE__, __LINE__), IntToType<IsPOD<type>::Value>())
#define DG_NEW_NULL_ARRAY(type, count, arena)	NewNullArray<type>(arena, count, ALLOCATOR_ALIGNMENT, SourceInfo(__FILE__, __LINE__))
#define DG_DELETE_ARRAY(object, arena)			DeleteArray(object, arena)
//------------------------------------------------------------------------------
// Memory Arena
//------------------------------------------------------------------------------
template <class AllocationPolicy, class ThreadPolicy, class BoundsCheckingPolicy, class MemoryTrackingPolicy, class MemoryTaggingPolicy>
class MemoryArena
{
public:
	template <class AreaPolicy>
	explicit MemoryArena(AreaPolicy& area)
		: mAllocator(area.GetStart(), area.GetEnd())
	{
	}

	void* Allocate(size_t size, size_t alignment, const SourceInfo& sourceInfo)
	{
		mThreadGuard.Enter();

		const size_t originalSize = size;
		const size_t newSize = size + BoundsCheckingPolicy::SIZE_FRONT + BoundsCheckingPolicy::SIZE_BACK;

		char* plainMemory = static_cast<char*>(mAllocator.Allocate(newSize, alignment, BoundsCheckingPolicy::SIZE_FRONT));

		mBoundsChecker.GuardFront(plainMemory);
		mMemoryTagger.TagAllocation(plainMemory + BoundsCheckingPolicy::SIZE_FRONT, originalSize);
		mBoundsChecker.GuardBack(plainMemory + BoundsCheckingPolicy::SIZE_FRONT + originalSize);

		mMemoryTracker.OnAllocation(plainMemory, newSize, alignment, sourceInfo);

		mThreadGuard.Leave();

		return (plainMemory + BoundsCheckingPolicy::SIZE_FRONT);
	}

	void Free(void* ptr)
	{
		mThreadGuard.Enter();

		char* originalMemory = static_cast<char*>(ptr) - BoundsCheckingPolicy::SIZE_FRONT;
		const size_t allocationSize = mAllocator.GetAllocationSize(originalMemory);

		mBoundsChecker.CheckFront(originalMemory);
		mBoundsChecker.CheckBack(originalMemory + BoundsCheckingPolicy::SIZE_FRONT + allocationSize);

		mMemoryTracker.OnDeallocation(originalMemory);

		mMemoryTagger.TagDeallocation(originalMemory, allocationSize);

		mAllocator.Free(originalMemory);

		mThreadGuard.Leave();
	}

private:
	AllocationPolicy mAllocator;
	ThreadPolicy mThreadGuard;
	BoundsCheckingPolicy mBoundsChecker;
	MemoryTrackingPolicy mMemoryTracker;
	MemoryTaggingPolicy mMemoryTagger;
};
//------------------------------------------------------------------------------
// Policies
//------------------------------------------------------------------------------
class SingleThreadPolicy
{
public:
	inline void Enter(void) const {}
	inline void Leave(void) const {}
};

class NoBoundsChecking
{
public:
	static const size_t SIZE_FRONT = 0;
	static const size_t SIZE_BACK = 0;

	inline void GuardFront(void*) const {}
	inline void GuardBack(void*) const {}

	inline void CheckFront(const void*) const {}
	inline void CheckBack(const void*) const {}
};

class NoMemoryTracking
{
public:
	inline void OnAllocation(void*, size_t, size_t, const SourceInfo&) const {}
	inline void OnDeallocation(void*) const {}
};

class NoMemoryTagging
{
public:
	inline void TagAllocation(void*, size_t) const {}
	inline void TagDeallocation(void*, size_t) const {}
};
//------------------------------------------------------------------------------
// Allocators
//------------------------------------------------------------------------------
/**
 * Persistant allocation - allocated once at startup/creation of a system.
 */
class LinearAllocator
{
public:
	LinearAllocator(char* start, char* end)
		: mCursor(start)
		, mEnd(end)
	{
	}

	void* Allocate(size_t size, size_t alignment, size_t boundsChecking)
	{
		size = ALIGNED_SIZE(size, alignment);
		char* result = mCursor;
		assert(mCursor + size <= mEnd);
		mCursor = mCursor + size;
		return result;
	}

	void Free(void* ptr)
	{
	}

	void Rewind(void* ptr)
	{
		mCursor = (char*)ptr;
	}

	void* GetCursor() const
	{
		return mCursor;
	}

	size_t GetAllocationSize(void* ptr)
	{
		return sizeof(ptr);
	}

private:
	char* mCursor;
	char* mEnd;
};
//------------------------------------------------------------------------------
class StackAllocator
{
public:
	StackAllocator(uchar* start, uchar* end)
	{
	}

	void* Allocate(size_t size, size_t alignment, size_t boundsChecking)
	{
		// TODO

		return 0;
	}

	void Free(void* ptr)
	{
		// TODO
	}

	size_t GetAllocationSize(void* ptr)
	{
		return sizeof(ptr);
	}
};
//------------------------------------------------------------------------------
class PoolAllocator
{
public:
	PoolAllocator(uchar* start, uchar* end)
	{
	}

	void* Allocate(size_t size, size_t alignment, size_t boundsChecking)
	{
		// TODO

		return 0;
	}

	void Free(void* ptr)
	{
		// TODO
	}

	size_t GetAllocationSize(void* ptr)
	{
		return sizeof(ptr);
	}
};
//------------------------------------------------------------------------------
typedef MemoryArena<LinearAllocator, SingleThreadPolicy, NoBoundsChecking, NoMemoryTracking, NoMemoryTagging> LinearArena;
typedef MemoryArena<StackAllocator, SingleThreadPolicy, NoBoundsChecking, NoMemoryTracking, NoMemoryTagging> StackArena;
typedef MemoryArena<PoolAllocator, SingleThreadPolicy, NoBoundsChecking, NoMemoryTracking, NoMemoryTagging> PoolArena;
//------------------------------------------------------------------------------
// Memory areas
//------------------------------------------------------------------------------
class HeapArea
{
public:
	HeapArea(size_t size)
	{
		mStart = (char*)VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		mEnd = mStart + size;
		mMemory = size;
	}
	~HeapArea()
	{
		VirtualFree(mStart, 0, MEM_RELEASE); 
	}

	char* GetStart() { return mStart; }
	char* GetEnd() { return mEnd; }
	size_t GetMemory() { return mMemory; }

private:
	char* mStart;
	char* mEnd;
	size_t mMemory;
};
//------------------------------------------------------------------------------
class StackArea
{
public:
	StackArea(size_t size)
	{
		mStart = (char*)alloca(size * sizeof(char));
		mEnd = mStart + size;
		mMemory = size;
	}
	~StackArea() {}

	char* GetStart() { return mStart; }
	char* GetEnd() { return mEnd; }
	size_t GetMemory() { return mMemory; }

private:
	char* mStart;
	char* mEnd;
	size_t mMemory;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // MEMORY_H