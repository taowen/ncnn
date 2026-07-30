// SPDX-License-Identifier: BSD-3-Clause
#include "../vulkan/reshape_vulkan.h"

namespace ncnn {

Reshape_vulkan::Reshape_vulkan()
    : pipeline_reshape(0),
      pipeline_reshape_pack4(0),
      pipeline_reshape_pack1to4(0),
      pipeline_reshape_pack4to1(0)
#if NCNN_BATCH
    , pipeline_reshape_batch_reorder(0),
      pipeline_reshape_batch_reorder_pack4(0),
      pipeline_reshape_batch_reorder_pack1to4(0),
      pipeline_reshape_batch_reorder_pack4to1(0)
#endif
{
    support_vulkan = true;
    support_vulkan_packing = true;
}

int Reshape_vulkan::create_pipeline(const Option&) { return -1; }
int Reshape_vulkan::destroy_pipeline(const Option&) { return 0; }
int Reshape_vulkan::forward(const VkMat&, VkMat&, VkCompute&, const Option&) const { return -1; }
int Reshape_vulkan::forward(const std::vector<VkMat>&, std::vector<VkMat>&, VkCompute&, const Option&) const { return -1; }

} // namespace ncnn
