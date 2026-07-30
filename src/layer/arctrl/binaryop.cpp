// SPDX-License-Identifier: BSD-3-Clause

#include "../binaryop.h"

namespace ncnn {

BinaryOp::BinaryOp()
{
    one_blob_only = false;
    support_inplace = false;
}

int BinaryOp::load_param(const ParamDict& pd)
{
    op_type = pd.get(0, 0);
    with_scalar = pd.get(1, 0);
    b = pd.get(2, 0.f);

    if (with_scalar != 0)
    {
        one_blob_only = true;
        support_inplace = true;
    }

    return 0;
}

// Arctrl only instantiates BinaryOp_vulkan. These virtual methods remain to
// complete the base vtable; CPU inference was deliberately removed.
int BinaryOp::forward(const std::vector<Mat>&, std::vector<Mat>&, const Option&) const
{
    return -1;
}

int BinaryOp::forward_inplace(Mat&, const Option&) const
{
    return -1;
}

} // namespace ncnn
