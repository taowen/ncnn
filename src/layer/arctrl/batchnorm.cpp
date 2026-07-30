// SPDX-License-Identifier: BSD-3-Clause
#include "../batchnorm.h"

namespace ncnn {
BatchNorm::BatchNorm() { one_blob_only = true; support_inplace = true; }
int BatchNorm::load_param(const ParamDict& pd)
{
    channels = pd.get(0, 0); eps = pd.get(1, 0.f); return 0;
}
int BatchNorm::load_model(const ModelBin& mb)
{
    slope_data = mb.load(channels, 1);
    mean_data = mb.load(channels, 1);
    var_data = mb.load(channels, 1);
    bias_data = mb.load(channels, 1);
    if (slope_data.empty() || mean_data.empty() || var_data.empty() || bias_data.empty()) return -100;
    a_data.create(channels); b_data.create(channels);
    if (a_data.empty() || b_data.empty()) return -100;
    for (int i = 0; i < channels; i++)
    {
        float sqrt_var = sqrtf(var_data[i] + eps);
        if (sqrt_var == 0.f) sqrt_var = 0.0001f;
        a_data[i] = bias_data[i] - slope_data[i] * mean_data[i] / sqrt_var;
        b_data[i] = slope_data[i] / sqrt_var;
    }
    return 0;
}
int BatchNorm::forward_inplace(Mat&, const Option&) const { return -1; }
} // namespace ncnn
