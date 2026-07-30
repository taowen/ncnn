// SPDX-License-Identifier: BSD-3-Clause
#include "../memorydata.h"

namespace ncnn {
MemoryData::MemoryData() { one_blob_only = false; support_inplace = false; }
int MemoryData::load_param(const ParamDict& pd)
{
    w = pd.get(0, 0); h = pd.get(1, 0); d = pd.get(11, 0);
    c = pd.get(2, 0); load_type = pd.get(21, 1); return 0;
}
int MemoryData::load_model(const ModelBin& mb)
{
    if (d != 0) data = mb.load(w, h, d, c, load_type);
    else if (c != 0) data = mb.load(w, h, c, load_type);
    else if (h != 0) data = mb.load(w, h, load_type);
    else if (w != 0) data = mb.load(w, load_type);
    else data.create(1);
    return data.empty() ? -100 : 0;
}
int MemoryData::forward(const std::vector<Mat>&, std::vector<Mat>&, const Option&) const { return -1; }
} // namespace ncnn
