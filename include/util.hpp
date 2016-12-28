#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <mutex>
#include <vector>

#include <vulkan/vulkan.h>

#define VT_BAD_DATA -1

#define BYTE_SIZE    8

bool supported_surface_present_mode(VkPresentModeKHR mode,
				    const std::vector<VkPresentModeKHR>& modes);

bool supported_surface_format(VkFormat format,
			      const std::vector<VkSurfaceFormatKHR>& surf_fmts);

void print_mem(VkDevice device, VkDeviceMemory memory,
	       std::mutex& mutex, VkDeviceSize offset,
	       VkDeviceSize size);

bool supports_mem_reqs(unsigned int memory_type_idx,
		       const std::vector<VkMemoryRequirements>& mem_reqs);

uint32_t make_data(const char*);

#endif
