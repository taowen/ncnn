// SPDX-License-Identifier: BSD-3-Clause
#include "../relu.h"

namespace ncnn {
ReLU::ReLU() { one_blob_only = true; support_inplace = true; }
int ReLU::load_param(const ParamDict& pd) { slope = pd.get(0, 0.f); return 0; }
int ReLU::forward_inplace(Mat&, const Option&) const { return -1; }
} // namespace ncnn
