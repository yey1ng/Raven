/*
filename:       memory_mi.h
author:         Raven
date created:   2023-10-10
description:
*/

#include "memory.h"
#include <atomic>

RAVEN_NAMESPACE_BEGIN

class RMemoryAllocator_MI : public IMemoryAllocator_MT
{
public:
	RMemoryAllocator_MI() noexcept;
	virtual ~RMemoryAllocator_MI() noexcept override;

	// FAST MEMORY ALLOCATION
	virtual void*		alloc(Uint i_Size, Uint i_AlignMode) noexcept override;
	virtual void        free(void* i_Ptr) noexcept override;

	// MEMORY ALLOCATION WITH META DATA
	virtual void*		allocMD(Uint i_Size, Uint i_AlignMode, U16 i_MDSize) noexcept override;
	virtual void*		allocMD(Uint i_Size, Uint i_AlignMode, U16 i_MDSize, const WChar* i_pFileName, Uint i_LineNo, const Char* i_pTag) noexcept override;
	virtual void        freeMD(void* i_Ptr) noexcept override;

	virtual void*		getMetaData(const void* i_Ptr, U16* o_pSize) const noexcept override;
	virtual Uint        getSizeMD(const void* i_Ptr) const noexcept override;
	virtual const WChar* getFileNameMD(const void* i_Ptr) const noexcept override;
	virtual Uint        getLineNumMD(const void* i_Ptr) const noexcept override;
	virtual const Char* getTagMD(const void* i_Ptr) const noexcept override;
	virtual const Uint  getAllocCountMD() const noexcept override;
	virtual const void* getFirstAllocMD() const noexcept override;
	virtual const void* getNextAllocMD(const void* i_Ptr) const noexcept override;

	// VERIFY FUNCTIONS
	virtual Int         getTotalAllocCount() const noexcept override;
	virtual Int         getTotalMemoryUsed() const noexcept override;

private:
	struct _TailInfo 
	{
		U64				m_AllocSize : 48;
		U64				m_MDSize : 16;
#if RAVENCFG_MALLOC_FORCEDEBUG
		const WChar*	m_pFileName;
		Uint			m_LineNo;
#endif // RAVENCFG_MALLOC_FORCEDEBUG
	};

	std::atomic<Int>	m_AllocCount;
	std::atomic<Int>    m_MemoryUsed;
};

RAVEN_NAMESPACE_END