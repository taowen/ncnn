// SPDX-License-Identifier: BSD-3-Clause
#include "../convolutiondepthwise.h"

namespace ncnn {
ConvolutionDepthWise::ConvolutionDepthWise() { one_blob_only = true; support_inplace = false; }
int ConvolutionDepthWise::load_param(const ParamDict& pd)
{
    num_output = pd.get(0, 0); kernel_w = pd.get(1, 0); kernel_h = pd.get(11, kernel_w);
    dilation_w = pd.get(2, 1); dilation_h = pd.get(12, dilation_w);
    stride_w = pd.get(3, 1); stride_h = pd.get(13, stride_w);
    pad_left = pd.get(4, 0); pad_right = pd.get(15, pad_left);
    pad_top = pd.get(14, pad_left); pad_bottom = pd.get(16, pad_top); pad_value = pd.get(18, 0.f);
    bias_term = pd.get(5, 0); weight_data_size = pd.get(6, 0); group = pd.get(7, 1);
    int8_scale_term = pd.get(8, 0); activation_type = pd.get(9, 0);
    activation_params = pd.get(10, Mat()); dynamic_weight = pd.get(19, 0);
    if (dynamic_weight) one_blob_only = false;
    if (group <= 0 || num_output % group != 0 || int8_scale_term) return -1;
    return 0;
}
int ConvolutionDepthWise::load_model(const ModelBin& mb)
{
    if (dynamic_weight) return 0;
    weight_data = mb.load(weight_data_size, 0);
    if (weight_data.empty()) return -100;
    if (bias_term) { bias_data = mb.load(num_output, 1); if (bias_data.empty()) return -100; }
    return 0;
}
int ConvolutionDepthWise::forward(const Mat&, Mat&, const Option&) const { return -1; }
int ConvolutionDepthWise::forward(const std::vector<Mat>&, std::vector<Mat>&, const Option&) const { return -1; }
void ConvolutionDepthWise::make_padding(const Mat&, Mat&, const Option&) const {}
void ConvolutionDepthWise::make_padding(const Mat&, Mat&, int, int, const Option&) const {}
} // namespace ncnn
