/*
filename:       memory.cpp
author:         Raven
date created:   2023-10-09
description:
*/

#include <core/public/memory_mi.h>
#include <core/public/module.h>

RAVEN_NAMESPACE_BEGIN

const IMemoryAllocator_MT::placementnew_t IMemoryAllocator_MT::placementnew;
IMemoryAllocator_MT* g_pDefaultMemoryAllocator = R_NULL;

RAVEN_CORE_API IMemoryAllocator_MT* RAVEN_GetDefaultMemoryAllocator() noexcept 
{
	return g_pDefaultMemoryAllocator;
}

RAVEN_CORE_API void RAVEN_Memory_Init() noexcept
{
	R_LOG_FATAL(g_pDefaultMemoryAllocator == R_NULL, "MemoryAllocator Is Created");
	g_pDefaultMemoryAllocator = new RMemoryAllocator_MI;
}

RAVEN_CORE_API void RAVEN_Memory_Uninit() noexcept 
{
	delete g_pDefaultMemoryAllocator;
	g_pDefaultMemoryAllocator = R_NULL;
}

RAVEN_NAMESPACE_END

// FAST NEW
RAVEN_CORE_API void* operator new(size_t i_Size, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator) noexcept
{
	R_LOG_FATAL(i_pAllocator == R_NULL, "Memory allocator is NULL");
	return i_pAllocator->alloc(i_Size, i_AlignMode);
}

RAVEN_CORE_API void  operator delete(void* p, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator) noexcept
{
	R_LOG_FATAL(i_pAllocator == R_NULL, "Memory allocator is NULL");
	return i_pAllocator->free(p);
}

// META DATA NEW
RAVEN_CORE_API void* operator new(size_t i_Size, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize) noexcept
{
	R_LOG_FATAL(i_pAllocator == R_NULL, "Memory allocator is NULL");
	return i_pAllocator->allocMD(i_Size, i_AlignMode, i_MDSize);
}

RAVEN_CORE_API void  operator delete(void* p, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize) noexcept
{
	R_LOG_FATAL(i_pAllocator == R_NULL, "Memory allocator is NULL");
	return i_pAllocator->freeMD(p);
}

// DEBUG NEW
RAVEN_CORE_API void* operator new(size_t i_Size, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize, const RAVEN_NS::WChar* i_pFileName, RAVEN_NS::Uint i_LineNum, const RAVEN_NS::Char* i_Tag) noexcept
{
	R_LOG_FATAL(i_pAllocator == R_NULL, "Memory allocator is NULL");
	return i_pAllocator->allocMD(i_Size, i_AlignMode, i_MDSize, i_pFileName, i_LineNum, i_Tag);
}

RAVEN_CORE_API void  operator delete(void* p, RAVEN_NS::Uint i_AlignMode, RAVEN_NS::IMemoryAllocator_MT* i_pAllocator, RAVEN_NS::U16 i_MDSize, const RAVEN_NS::WChar* i_pFileName, RAVEN_NS::Uint i_LineNum, const RAVEN_NS::Char* i_Tag) noexcept
{
	R_LOG_FATAL(i_pAllocator == R_NULL, "Memory allocator is NULL");
	return i_pAllocator->freeMD(p);
}

// PLACEMENT NEW
RAVEN_CORE_API void* operator new(size_t i_Size, void* i_Ptr, RAVEN_NS::IMemoryAllocator_MT::placementnew_t) noexcept
{
	return i_Ptr;
}

RAVEN_CORE_API void  operator delete(void* p, void* i_Ptr, RAVEN_NS::IMemoryAllocator_MT::placementnew_t) noexcept
{
	
}
