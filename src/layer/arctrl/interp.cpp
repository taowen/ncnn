// SPDX-License-Identifier: BSD-3-Clause
#include "../interp.h"

namespace ncnn {
Interp::Interp() { one_blob_only = true; support_inplace = false; }
int Interp::load_param(const ParamDict& pd)
{
    resize_type = pd.get(0, 0); height_scale = pd.get(1, 1.f); width_scale = pd.get(2, 1.f);
    output_height = pd.get(3, 0); output_width = pd.get(4, 0);
    dynamic_target_size = pd.get(5, 0); align_corner = pd.get(6, 0);
    size_expr = pd.get(9, "");
    if (resize_type < 0 || resize_type > 3 || !size_expr.empty()) return -1;
    if (dynamic_target_size == 1) one_blob_only = false;
    return 0;
}
int Interp::forward(const Mat&, Mat&, const Option&) const { return -1; }
int Interp::forward(const std::vector<Mat>&, std::vector<Mat>&, const Option&) const { return -1; }
int Interp::eval_size_expr(const std::vector<Mat>&, int&, int&) const { return -1; }
} // namespace ncnn
