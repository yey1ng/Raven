/*
filename:       memory.h
author:         Raven
date created:   2023-09-27
description:
*/

#pragma once

#include "defines.h"
#include "typedefs.h"
#include <boost/preprocessor.hpp>

RAVEN_NAMESPACE_BEGIN

// the memory allocator should be thread safe
class RAVEN_CORE_API IMemoryAllocator_MT
{
public:
	static const struct placementnew_t {} placementnew;

	virtual ~IMemoryAllocator_MT() noexcept {}

	// FAST MEMORY ALLOCATION
	virtual void* alloc(Uint i_Size, Uint i_AlignMode) noexcept = 0;
	virtual void        free(void* i_Ptr) noexcept = 0;

	// MEMORY ALLOCATION WITH META DATA
	virtual void* allocMD(Uint i_Size, Uint i_AlignMode, U16 i_MDSize) noexcept = 0;
	virtual void* allocMD(Uint i_Size, Uint i_AlignMode, U16 i_MDSize, const WChar* i_pFileName, Uint i_LineNo, const Char* i_pTag) noexcept = 0;
	virtual void        freeMD(void* i_Ptr) noexcept = 0;

	virtual void* getMetaData(const void* i_Ptr, U16* o_pSize) const noexcept = 0;
	virtual Uint        getSizeMD(const void* i_Ptr) const noexcept = 0;
	virtual const WChar* getFileNameMD(const void* i_Ptr) const noexcept = 0;
	virtual Uint        getLineNumMD(const void* i_Ptr) const noexcept = 0;
	virtual const Char* getTagMD(const void* i_Ptr) const noexcept = 0;
	virtual const Uint  getAllocCountMD() const noexcept = 0;
	virtual const void* getFirstAllocMD() const noexcept = 0;
	virtual const void* getNextAllocMD(const void* i_Ptr) const noexcept = 0;

	// VERIFY FUNCTIONS
	virtual Int         getTotalAllocCount() const noexcept = 0;
	virtual Int         getTotalMemoryUsed() const noexcept = 0;
};

RAVEN_NAMESPACE_END

// FAST NEW
RAVEN_CORE_API void* operator new(size_t i_Size, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator) noexcept;
RAVEN_CORE_API void  operator delete(void* p, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator) noexcept;

// META DATA NEW
RAVEN_CORE_API void* operator new(size_t i_Size, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize) noexcept;
RAVEN_CORE_API void  operator delete(void* p, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize) noexcept;

// DEBUG NEW
RAVEN_CORE_API void* operator new(size_t i_Size, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize, const RAVEN_NS::WChar* i_pFileName, RAVEN_NS::Uint i_LineNum, const RAVEN_NS::Char* i_Tag) noexcept;
RAVEN_CORE_API void  operator delete(void* p, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize, const RAVEN_NS::WChar* i_pFileName, RAVEN_NS::Uint i_LineNum, const RAVEN_NS::Char* i_Tag) noexcept;

// PLACEMENT NEW
RAVEN_CORE_API void* operator new(size_t i_Size, void* i_Ptr, RAVEN_NS::IMemoryAllocator_MT::placementnew_t) noexcept;
RAVEN_CORE_API void  operator delete(void* p, void* i_Ptr, RAVEN_NS::IMemoryAllocator_MT::placementnew_t) noexcept;

#define RAVEN_PlacementNew(TYPE, ptr)									::new(ptr, RAVEN_NS::IMemoryAllocator_MT::placementnew) TYPE
#define RAVEN_PlacementDel(TYPE, ptr)									ptr->~TYPE();

RAVEN_NAMESPACE_BEGIN

template<class T>
void DeleteHelper(T* i_Ptr, IMemoryAllocator_MT* i_pAllocator) noexcept
{
	RAVEN_PlacementDel(T, i_Ptr);
	i_pAllocator->free(i_Ptr);
}

template<class T>
void DeleteHelperMD(T* i_Ptr, IMemoryAllocator_MT* i_pAllocator) noexcept
{
	RAVEN_PlacementDel(T, i_Ptr);
	i_pAllocator->freeMD(i_Ptr);
}

template<class T>
T* NewArrayHelper(Uint i_Count, Uint i_AlignMode, IMemoryAllocator_MT* i_pAllocator, U16 i_MDSize) noexcept
{
	Uint l_TotalSize = sizeof(T) * i_Count;
	T* l_pObjectArray = (T*)i_pAllocator->allocMD(l_TotalSize, i_AlignMode, i_MDSize);
	for (Int i = 0; i < i_Count; ++i)
	{
		RAVEN_PlacementNew(T, l_pObjectArray + i);
	}
	return l_pObjectArray;
}

template<class T>
T* NewArrayHelper(Uint i_Count, Uint i_AlignMode, IMemoryAllocator_MT* i_pAllocator, U16 i_MDSize, const WChar* i_pFileName, Uint i_LineNo, const Char* i_pTag) noexcept
{
	Uint l_TotalSize = sizeof(T) * i_Count;
	T* l_pObjectArray = (T*)i_pAllocator->allocMD(l_TotalSize, i_AlignMode, i_MDSize, i_pFileName, i_LineNo, i_pTag);
	for (Int i = 0; i < i_Count; ++i)
	{
		RAVEN_PlacementNew(T, l_pObjectArray + i);
	}
	return l_pObjectArray;
}

template<class T>
void DeleteArrayHelper(T* i_Ptr, IMemoryAllocator_MT* i_pAllocator) noexcept
{
	Uint l_TotalSize = i_pAllocator->getSizeMD(i_Ptr);
	R_LOG_FATAL(l_TotalSize > 0, "Invalid pointer");
	Uint l_ArraySize = l_TotalSize / sizeof(T);
	R_LOG_FATAL(l_ArraySize * sizeof(T) == l_TotalSize, "Invalid pointer");
	for (Uint i = 0; i < l_ArraySize; ++i)
	{
		RAVEN_PlacementDel(T, (((T*)i_Ptr) + i));
	}

	i_pAllocator->freeMD(i_Ptr);
}

RAVEN_CORE_API IMemoryAllocator_MT* RAVEN_GetDefaultMemoryAllocator() noexcept;
RAVEN_CORE_API void RAVEN_Memory_Init() noexcept;
RAVEN_CORE_API void RAVEN_Memory_Uninit() noexcept;

RAVEN_NAMESPACE_END

#define RAVEN_DEFAULTMEMORYALLOCATOR									RAVEN_NS::RAVEN_GetDefaultMemoryAllocator()

#define RAVEN_ALIGNDEFAULT												alignof(std::max_align_t);

#ifdef NDEBUG
#define RAVEN_Alloc1(size)												RAVEN_DEFAULTMEMORYALLOCATOR->alloc(size, RAVEN_ALIGNDEFAULT)
#define RAVEN_Alloc2(size, align)										RAVEN_DEFAULTMEMORYALLOCATOR->alloc(size, align)
#define RAVEN_Alloc3(size, align, pAllocator)							pAllocator->alloc(size, align)
#define RAVEN_Free1(ptr)                                                RAVEN_DEFAULTMEMORYALLOCATOR->freeMD(ptr)
#define RAVEN_Free2(ptr, pAllocator)                                    pAllocator->freeMD(ptr)
#define RAVEN_New1(TYPE)											    ::new(alignof(TYPE), RAVEN_DEFAULTMEMORYALLOCATOR) TYPE
#define RAVEN_New2(TYPE, align)											::new(align, RAVEN_DEFAULTMEMORYALLOCATOR) TYPE
#define RAVEN_New3(TYPE, align, pAllocator)								::new(align, pAllocator) TYPE
#define RAVEN_Del1(ptr)                                                 RAVEN_NS::DeleteHelper(ptr, RAVEN_DEFAULTMEMORYALLOCATOR)
#define RAVEN_Del2(ptr, pAllocator)                                     RAVEN_NS::DeleteHelper(ptr, pAllocator)
#else
#define RAVEN_Alloc1(size)												RAVEN_DEFAULTMEMORYALLOCATOR->allocMD(size, RAVEN_ALIGNDEFAULT, 0, RAVEN_WFILENAME, __LINE__, "unknown")
#define RAVEN_Alloc2(size, align)										RAVEN_DEFAULTMEMORYALLOCATOR->allocMD(size, align, 0, RAVEN_WFILENAME, __LINE__, "unknown")
#define RAVEN_Alloc3(size, align, pAllocator)							pAllocator->allocMD(size, align, 0, RAVEN_WFILENAME, __LINE__, "unknown")
#define RAVEN_Free1(ptr)                                                RAVEN_DEFAULTMEMORYALLOCATOR->freeMD(ptr)
#define RAVEN_Free2(ptr, pAllocator)                                    pAllocator->freeMD(ptr)
#define RAVEN_New1(TYPE)											    ::new(alignof(TYPE), RAVEN_DEFAULTMEMORYALLOCATOR, 0, RAVEN_WFILENAME, __LINE__, "unknown") TYPE
#define RAVEN_New2(TYPE, align)											::new(align, RAVEN_DEFAULTMEMORYALLOCATOR, 0, RAVEN_WFILENAME, __LINE__, "unknown") TYPE
#define RAVEN_New3(TYPE, align, pAllocator)								::new(align, pAllocator, 0, RAVEN_WFILENAME, __LINE__, "unknown") TYPE
#define RAVEN_Del1(ptr)                                                 RAVEN_NS::DeleteHelperMD(ptr, RAVEN_DEFAULTMEMORYALLOCATOR)
#define RAVEN_Del2(ptr, pAllocator)                                     RAVEN_NS::DeleteHelperMD(ptr, pAllocator)
#endif
#define RAVEN_Alloc(...)                                                RAVEN_PP_OVERLOAD(RAVEN_Alloc, __VA_ARGS__)
#define RAVEN_Free(...)                                                 RAVEN_PP_OVERLOAD(RAVEN_Free, __VA_ARGS__)
#define RAVEN_New(...)                                                  RAVEN_PP_OVERLOAD(RAVEN_New, __VA_ARGS__)
#define RAVEN_Del(...)                                                  RAVEN_PP_OVERLOAD(RAVEN_Del, __VA_ARGS__)