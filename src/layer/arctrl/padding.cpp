// SPDX-License-Identifier: BSD-3-Clause
#include "../padding.h"

namespace ncnn {
Padding::Padding() { one_blob_only = true; support_inplace = false; }
int Padding::load_param(const ParamDict& pd)
{
    top = pd.get(0, 0); bottom = pd.get(1, 0); left = pd.get(2, 0); right = pd.get(3, 0);
    type = pd.get(4, 0); value = pd.get(5, 0.f); per_channel_pad_data_size = pd.get(6, 0);
    front = pd.get(7, 0); behind = pd.get(8, 0); return 0;
}
int Padding::load_model(const ModelBin& mb)
{
    if (per_channel_pad_data_size) per_channel_pad_data = mb.load(per_channel_pad_data_size, 1);
    return per_channel_pad_data_size && per_channel_pad_data.empty() ? -100 : 0;
}
int Padding::forward(const Mat&, Mat&, const Option&) const { return -1; }
} // namespace ncnn
