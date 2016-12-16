#include "util.hpp"

#include <iostream>
#include <cstring>

bool supports_mem_reqs(unsigned int memory_type_idx,
		       const std::vector<VkMemoryRequirements>& mem_reqs) {
  unsigned long mem_type_bit = 1 << memory_type_idx;
  for (auto& mem_requirement : mem_reqs)
    if ((mem_requirement.memoryTypeBits & mem_type_bit) == 0)
      return false;
  return true;
}

void print_mem(VkDevice device,
	       VkDeviceMemory memory,
	       std::mutex& mem_mutex,
	       VkDeviceSize offset,
	       VkDeviceSize size) {
  std::lock_guard<std::mutex> lock(mem_mutex);
  void* data;
  VkResult res = vkMapMemory(device,
			     memory,
			     offset,
			     size+1,
			     0,
			     &data);
  if (res != VK_SUCCESS)
    std::cout << "Failed to print memory (Offset=" << offset
	      << ",Size=" << size << ")..." << std::endl;
  char* str = static_cast<char*>(data);
  str[size] = '\0';
  std::cout << str << std::endl;
  vkUnmapMemory(device, memory);
}

uint32_t make_data(const char* str)
{
  if (strlen(str) != 4) {
    std::cout << "Failed make_data(const char*): string must be size 4!" << std::endl;
    return VT_BAD_DATA;
  }
  return (str[3] << 3*BYTE_SIZE)
    + (str[2] << 2*BYTE_SIZE)
    + (str[1] << BYTE_SIZE)
    + str[0];
}
