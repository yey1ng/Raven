/*
filename:       memory_mi.cpp
author:         RAVEN
date created:   2023-10-10
description:
*/

#include <core/public/memory_mi.h>
#include <core/public/module.h>
#include <mimalloc.h>

RAVEN_NAMESPACE_BEGIN

RMemoryAllocator_MI::RMemoryAllocator_MI() noexcept
{
	m_AllocCount = 0;
	m_MemoryUsed = 0;
}

RMemoryAllocator_MI::~RMemoryAllocator_MI() noexcept
{
	R_LOG_FATAL((m_AllocCount == 0), "Memory Leak!!!");
	R_LOG_FATAL((m_MemoryUsed == 0), "Memory Leak!!!");
}

// FAST MEMORY ALLOCATION
void* RMemoryAllocator_MI::alloc(Uint i_Size, Uint i_AlignMode) noexcept
{
	void* l_Ptr = mi_malloc_aligned(i_Size, i_AlignMode);
	m_AllocCount++;
	m_MemoryUsed += mi_malloc_usable_size(l_Ptr);
	return l_Ptr;
}

void RMemoryAllocator_MI::free(void* i_Ptr) noexcept
{
	R_LOG_FATAL(i_Ptr, "Null Ptr");
	m_AllocCount--;
	m_MemoryUsed -= mi_malloc_usable_size(i_Ptr);
	mi_free(i_Ptr);
}

// MEMORY ALLOCATION WITH META DATA
void* RMemoryAllocator_MI::allocMD(Uint i_Size, Uint i_AlignMode, U16 i_MDSize) noexcept
{
	Int l_MemSize = i_Size + i_MDSize + sizeof(_TailInfo);
	void* l_Ptr = mi_malloc_aligned(i_Size, i_AlignMode);
	Int l_MemoryUsed = mi_malloc_usable_size(l_Ptr);
	m_AllocCount++;
	m_MemoryUsed += l_MemoryUsed;

	_TailInfo* l_pInfo = (_TailInfo*)((Char*)l_Ptr + l_MemoryUsed - sizeof(_TailInfo));
	l_pInfo->m_AllocSize = i_Size;
	l_pInfo->m_MDSize = i_MDSize;

#if RAVENCFG_MALLOC_FORCEDEBUG
	l_pInfo->m_pFileName = R_NULL;
	l_pInfo->m_LineNo = R_UINT_MAX;
#endif
	return l_Ptr;
}

void* RMemoryAllocator_MI::allocMD(Uint i_Size, Uint i_AlignMode, U16 i_MDSize, const WChar* i_pFileName, Uint i_LineNo, const Char* i_pTag) noexcept
{
	Int l_MemSize = i_Size + i_MDSize + sizeof(_TailInfo);
	void* l_Ptr = mi_malloc_aligned(i_Size, i_AlignMode);
	Int l_MemoryUsed = mi_malloc_usable_size(l_Ptr);
	m_AllocCount++;
	m_MemoryUsed += l_MemoryUsed;

	_TailInfo* l_pInfo = (_TailInfo*)((Char*)l_Ptr + l_MemoryUsed - sizeof(_TailInfo));
	l_pInfo->m_AllocSize = i_Size;
	l_pInfo->m_MDSize = i_MDSize;

#if RAVENCFG_MALLOC_FORCEDEBUG
	l_pInfo->m_pFileName = i_pFileName;
	l_pInfo->m_LineNo = i_LineNo;
#endif
	return l_Ptr;
}

void RMemoryAllocator_MI::freeMD(void* i_Ptr) noexcept
{
	free(i_Ptr);
}

void* RMemoryAllocator_MI::getMetaData(const void* i_Ptr, U16* o_pSize) const noexcept
{
	Int l_MemoryUsed = mi_malloc_usable_size(i_Ptr);
	_TailInfo* l_pInfo = (_TailInfo*)((Char*)i_Ptr + l_MemoryUsed - sizeof(_TailInfo));
	*o_pSize = l_pInfo->m_MDSize;
	return (Char*)i_Ptr + l_MemoryUsed - sizeof(_TailInfo) - l_pInfo->m_MDSize;
}

Uint RMemoryAllocator_MI::getSizeMD(const void* i_Ptr) const noexcept
{
	Int l_MemoryUsed = mi_malloc_usable_size(i_Ptr);
	_TailInfo* l_pInfo = (_TailInfo*)((Char*)i_Ptr + l_MemoryUsed - sizeof(_TailInfo));
	return l_pInfo->m_AllocSize;
}

const WChar* RMemoryAllocator_MI::getFileNameMD(const void* i_Ptr) const noexcept
{
#if RAVENCFG_MALLOC_FORCEDEBUG
	Int l_MemoryUsed = mi_malloc_usable_size(i_Ptr);
	_TailInfo* l_pInfo = (_TailInfo*)((Char*)i_Ptr + l_MemoryUsed - sizeof(_TailInfo));
	return l_pInfo->m_pFileName;
#else
	return R_NULL;
#endif
}

Uint RMemoryAllocator_MI::getLineNumMD(const void* i_Ptr) const noexcept
{
#if RAVENCFG_MALLOC_FORCEDEBUG
	Int l_MemoryUsed = mi_malloc_usable_size(i_Ptr);
	_TailInfo* l_pInfo = (_TailInfo*)((Char*)i_Ptr + l_MemoryUsed - sizeof(_TailInfo));
	return l_pInfo->m_LineNo;
#else
	return R_UINT_MAX;
#endif
}

const Char* RMemoryAllocator_MI::getTagMD(const void* i_Ptr) const noexcept
{
	return R_NULL;
}

const Uint RMemoryAllocator_MI::getAllocCountMD() const noexcept
{
	return 0;
}

const void* RMemoryAllocator_MI::getFirstAllocMD() const noexcept 
{
	return R_NULL;
}

const void* RMemoryAllocator_MI::getNextAllocMD(const void* i_Ptr) const noexcept 
{
	return R_NULL;
}	

// VERIFY FUNCTIONS
Int RMemoryAllocator_MI::getTotalAllocCount() const noexcept
{
	return m_AllocCount;
}

Int RMemoryAllocator_MI::getTotalMemoryUsed() const noexcept
{
	return m_MemoryUsed;
}

RAVEN_NAMESPACE_END