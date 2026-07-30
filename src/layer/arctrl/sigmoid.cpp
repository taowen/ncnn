// SPDX-License-Identifier: BSD-3-Clause
#include "../sigmoid.h"

namespace ncnn {
Sigmoid::Sigmoid() { one_blob_only = true; support_inplace = true; }
int Sigmoid::forward_inplace(Mat&, const Option&) const { return -1; }
} // namespace ncnn
