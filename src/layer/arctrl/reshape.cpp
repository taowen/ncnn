// SPDX-License-Identifier: BSD-3-Clause
#include "../reshape.h"

namespace ncnn {

Reshape::Reshape()
{
    one_blob_only = true;
    support_inplace = false;
}

int Reshape::load_param(const ParamDict& pd)
{
    w = pd.get(0, -233);
    h = pd.get(1, -233);
    d = pd.get(11, -233);
    c = pd.get(2, -233);
    ndim = d == -233 ? 3 : 4;
    if (c == -233) ndim = 2;
    if (h == -233) ndim = 1;
    if (w == -233) ndim = 0;
    shape_expr = pd.get(6, "");
    return shape_expr.empty() ? 0 : -1;
}

int Reshape::forward(const Mat&, Mat&, const Option&) const { return -1; }
int Reshape::forward(const std::vector<Mat>&, std::vector<Mat>&, const Option&) const { return -1; }
int Reshape::eval_shape_expr(const std::vector<Mat>&, int&, int&, int&, int&) const { return -1; }


} // namespace ncnn
