// SPDX-License-Identifier: BSD-3-Clause
#include "../split.h"

namespace ncnn {
Split::Split()
{
    one_blob_only = false;
    support_inplace = false;
    support_packing = true;
    support_fp16_storage = true;
    support_bf16_storage = false;
}
int Split::forward(const std::vector<Mat>&, std::vector<Mat>&, const Option&) const { return -1; }
} // namespace ncnn
