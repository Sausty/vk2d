#include "vk2d_shader.h"
#include <Vk2D/Vk2D_Base/vk2d_file.h>
#include <Vk2D/Vk2D_Base/vk2d_log.h>

#include <stdlib.h>
#include <string.h>

vk2d_shader* vk2d_create_shader(const char* vertexPath, const char* fragmentPath)
{
    vk2d_new(vk2d_shader* result, sizeof(vk2d_shader));

    u32 vertexSize;
    u32* vertexSource = vk2d_read_spirv(vertexPath, &vertexSize);

    u32 fragmentSize;
    u32* fragmentSource = vk2d_read_spirv(fragmentPath, &fragmentSize);

    VkDevice device = volkGetLoadedDevice();

    // Vertex shader module
    {
        VkShaderModuleCreateInfo createInfo;
        vk2d_zero_memory(createInfo, sizeof(VkShaderModuleCreateInfo));

        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = vertexSize;
        createInfo.pCode = vertexSource;

        VkResult res = vkCreateShaderModule(device, &createInfo, NULL, &result->vertex_shader);
        vk2d_assert(res == VK_SUCCESS);
    }

    // Fragment shader module
    {
        VkShaderModuleCreateInfo createInfo;
        vk2d_zero_memory(createInfo, sizeof(VkShaderModuleCreateInfo));

        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = fragmentSize;
        createInfo.pCode = fragmentSource;

        VkResult res = vkCreateShaderModule(device, &createInfo, NULL, &result->fragment_shader);
        vk2d_assert(res == VK_SUCCESS);
    }

    result->geometry_shader = VK_NULL_HANDLE;
    result->compute_shader = VK_NULL_HANDLE;
    result->tessellation_control_shader = VK_NULL_HANDLE;
    result->tessellation_evaluation_shader = VK_NULL_HANDLE;

    vk2d_free(vertexSource);
    vk2d_free(fragmentSource);

    return result;
}

void vk2d_build_shader_module(vk2d_shader* shader, const char* path)
{
    char* source = vk2d_read_file(path);

    VkDevice device = volkGetLoadedDevice();

    VkShaderModuleCreateInfo createInfo;
    vk2d_zero_memory(createInfo, sizeof(VkShaderModuleCreateInfo));

    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = sizeof(source) / sizeof(char);
    createInfo.pCode = (const uint32_t*)source;

    VkResult res = vkCreateShaderModule(device, &createInfo, NULL, &shader->geometry_shader);
    vk2d_assert(res == VK_SUCCESS);
}

void vk2d_free_shader(vk2d_shader* shader)
{
    VkDevice device = volkGetLoadedDevice();

    if (shader->vertex_shader != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, shader->vertex_shader, NULL);
    if (shader->fragment_shader != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, shader->fragment_shader, NULL);
    if (shader->geometry_shader != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, shader->geometry_shader, NULL);
    if (shader->compute_shader != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, shader->compute_shader, NULL);
    if (shader->tessellation_control_shader != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, shader->tessellation_control_shader, NULL);
    if (shader->tessellation_evaluation_shader != VK_NULL_HANDLE)
        vkDestroyShaderModule(device, shader->tessellation_evaluation_shader, NULL);

    vk2d_free(shader);
}