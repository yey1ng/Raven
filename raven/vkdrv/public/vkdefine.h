/*
filename:       vkdevice.cpp
author:         Raven
date created:   2023-09-06
description:
*/

#pragma once

#ifdef NDEBUG
#define RAVEN_VK_EXT_debug_utils                                0       // INSTANCE EXTENSION
#else
#define RAVEN_VK_EXT_debug_utils                                1       // INSTANCE EXTENSION
#endif

/*
    THE CORE LAYERS AND EXTENSIONS, WILL BE ADDED AUTOMATICALLY
*/
#define RAVEN_VK_KHR_surface                                    1       // INSTANCE EXTENSION
#define RAVEN_VK_KHR_swapchain                                  1       // DEVICE EXTENSION
#define RAVEN_VK_KHR_win32_surface                              1       // INSTANCE EXTENSION FOR WINDOWS

/*
    THE OPTIONAL LAYERS AND EXTENSIONS
*/
#define RAVEN_VK_LAYER_RENDERDOC_Capture                        1       // INSTANCE LAYER
#define RAVEN_VK_LAYER_KHRONOS_synchronization2                 1       /* Enable this only when your device driver doesn't support VK_KHR_synchronization2 extension */
#define RAVEN_VK_LAYER_KHRONOS_validation                       1       // INSTANCE LAYER
#define RAVEN_VK_KHR_synchronization2                           1       // DEVICE EXTENSION
#define RAVEN_VK_KHR_shader_non_semantic_info                   1       // SHADER DEBUG PRINTF(Need vk1.2 && VK_EXT_debug_utils)
#define RAVEN_VK_KHR_push_descriptor                            1       // DEVICE EXTENSION
#define RAVEN_VK_EXT_descriptor_buffer                          1       // DEVICE EXTENSION

//Ray Tracing Extensions
#define RAVEN_VK_KHR_ray_tracing_pipeline                       1       // DEVICE EXTENSION
#define RAVEN_VK_KHR_acceleration_structure                     1       // DEVICE EXTENSION
#define RAVEN_VK_KHR_buffer_device_address                      1       // This is required when creating AccelerationStructure. DEVICE EXTENSION

// vulkan descriptor limitation
#define RAVEN_VK_MAX_DESCRIPTORSET                              4096
#define RAVEN_VK_MAX_DESCRIPTOR_SAMPLER                         1024
#define RAVEN_VK_MAX_DESCRIPTOR_COMBINED_IMAGE_SAMPLER          1024
#define RAVEN_VK_MAX_DESCRIPTOR_SAMPLED_IMAGE                   4096
#define RAVEN_VK_MAX_DESCRIPTOR_STORAGE_IMAGE                   1024
#define RAVEN_VK_MAX_DESCRIPTOR_UNIFORM_TEXEL_BUFFER            256
#define RAVEN_VK_MAX_DESCRIPTOR_STORAGE_TEXEL_BUFFER            256
#define RAVEN_VK_MAX_DESCRIPTOR_UNIFORM_BUFFER                  4096
#define RAVEN_VK_MAX_DESCRIPTOR_STORAGE_BUFFER                  4096
#define RAVEN_VK_MAX_DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC          4096
//raytracing
#define RAVEN_VK_MAX_DESCRIPTOR_ACCELERATION_STRUCTURES         256

#define RAVEN_VK_MAX_DESCRIPTOR_TYPE                            10