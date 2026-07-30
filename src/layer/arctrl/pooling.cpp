// SPDX-License-Identifier: BSD-3-Clause
#include "../pooling.h"

namespace ncnn {
Pooling::Pooling() { one_blob_only = true; support_inplace = false; }
int Pooling::load_param(const ParamDict& pd)
{
    pooling_type = pd.get(0, 0); kernel_w = pd.get(1, 0); kernel_h = pd.get(11, kernel_w);
    stride_w = pd.get(2, 1); stride_h = pd.get(12, stride_w);
    pad_left = pd.get(3, 0); pad_right = pd.get(14, pad_left);
    pad_top = pd.get(13, pad_left); pad_bottom = pd.get(15, pad_top);
    global_pooling = pd.get(4, 0); pad_mode = pd.get(5, 0);
    avgpool_count_include_pad = pd.get(6, 0); adaptive_pooling = pd.get(7, 0);
    out_w = pd.get(8, 0); out_h = pd.get(18, out_w); return 0;
}
int Pooling::forward(const Mat&, Mat&, const Option&) const { return -1; }
void Pooling::make_padding(const Mat&, Mat&, const Option&) const {}
} // namespace ncnn
