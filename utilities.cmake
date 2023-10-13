function(RAVENCM_USE_Vulkan)
    message("Add Vulkan in windows OS")
    set(RAVENCM_MOD_LIBRARIES ${RAVENCM_MOD_LIBRARIES} ${Vulkan_LIBRARY} PARENT_SCOPE)
endfunction()

function(RAVENCM_USE_Assimp)
    message("Add Assimp in windows OS")
    set(RAVENCM_MOD_LIBRARIES ${RAVENCM_MOD_LIBRARIES} "assimp" PARENT_SCOPE)
endfunction()

function(RAVENCM_USE_MiMalloc)
    message("Add MiMalloc in windows OS")
    set(RAVENCM_MOD_LIBRARIES ${RAVENCM_MOD_LIBRARIES} "mimalloc" PARENT_SCOPE)
endfunction()