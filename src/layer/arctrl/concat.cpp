// SPDX-License-Identifier: BSD-3-Clause
#include "../concat.h"

namespace ncnn {
Concat::Concat() { one_blob_only = false; support_inplace = false; }
int Concat::load_param(const ParamDict& pd) { axis = pd.get(0, 0); return 0; }
int Concat::forward(const std::vector<Mat>&, std::vector<Mat>&, const Option&) const { return -1; }
} // namespace ncnn
