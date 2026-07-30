// SPDX-License-Identifier: BSD-3-Clause
#include "../cast.h"

namespace ncnn {

Cast::Cast()
{
    one_blob_only = true;
    support_inplace = false;
    support_packing = true;
}

int Cast::load_param(const ParamDict& pd)
{
    type_from = pd.get(0, 0);
    type_to = pd.get(1, 0);
    return (type_from == type_to ||
            (type_from == 1 && type_to == 2) ||
            (type_from == 2 && type_to == 1)) ? 0 : -1;
}

int Cast::forward(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const
{
    if (type_from == type_to)
    {
        top_blob = bottom_blob;
        return 0;
    }
    if (!((type_from == 1 && type_to == 2) ||
          (type_from == 2 && type_to == 1)))
        return -1;

    const int w = bottom_blob.w;
    const int h = bottom_blob.h;
    const int d = bottom_blob.d;
    const int channels = bottom_blob.c;
    const int dims = bottom_blob.dims;
    const int elempack = bottom_blob.elempack;
    const size_t out_elemsize = (type_to == 1 ? 4u : 2u) * elempack;

    if (dims == 1)
        top_blob.create(w, out_elemsize, elempack, opt.blob_allocator);
    else if (dims == 2)
        top_blob.create(w, h, out_elemsize, elempack, opt.blob_allocator);
    else if (dims == 3)
        top_blob.create(w, h, channels, out_elemsize, elempack, opt.blob_allocator);
    else if (dims == 4)
        top_blob.create(w, h, d, channels, out_elemsize, elempack, opt.blob_allocator);
    else
        return -1;
    if (top_blob.empty())
        return -100;

    const int size = w * h * d * elempack;
    if (type_from == 1)
    {
        for (int q = 0; q < channels; q++)
        {
            const float* ptr = bottom_blob.channel(q);
            unsigned short* outptr = top_blob.channel(q);
            for (int i = 0; i < size; i++)
                outptr[i] = float32_to_float16(ptr[i]);
        }
    }
    else
    {
        for (int q = 0; q < channels; q++)
        {
            const unsigned short* ptr = bottom_blob.channel(q);
            float* outptr = top_blob.channel(q);
            for (int i = 0; i < size; i++)
                outptr[i] = float16_to_float32(ptr[i]);
        }
    }
    return 0;
}

} // namespace ncnn
