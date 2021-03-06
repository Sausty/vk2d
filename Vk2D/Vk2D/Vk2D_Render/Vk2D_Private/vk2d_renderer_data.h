#ifndef VK2D_RENDERER_DATA
#define VK2D_RENDERER_DATA

#include <vulkan/vulkan.h>
#include <volk.h>

#include <Vk2D/Vk2D_Math/vk2d_mat4.h>

#include <Vk2D/Vk2D_Base/vk2d_base.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_instance_data.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_gpu.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_device.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_swapchain.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_pipeline.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_renderpass.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_command.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_vbuffer.h>
#include <Vk2D/Vk2D_Render/Vk2D_Private/vk2d_ibuffer.h>

typedef struct vk2d_renderer_data vk2d_renderer_data;
struct vk2d_renderer_data
{
    u32 width;
    u32 height;

    vk2d_instance_data instance_data;
    VkSurfaceKHR surface;
    vk2d_gpu* physical_device;
    vk2d_device* logical_device;
    vk2d_swapchain* swap_chain;

    vk2d_pipeline* sprite_pipeline;
    vk2d_renderpass* sprite_renderpass;
    
    vk2d_command* render_command;
    VkSemaphore image_available_semaphore;
    VkSemaphore render_finished_semaphore;
    VkFence fence;
};

typedef struct vk2d_scene_uniforms vk2d_scene_uniforms;
struct vk2d_scene_uniforms
{
    vk2d_mat4 view;
    vk2d_mat4 projection;
};

extern vk2d_renderer_data* _data;

#endif