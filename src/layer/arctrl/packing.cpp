// SPDX-License-Identifier: BSD-3-Clause
#include "../packing.h"

namespace ncnn {

Packing::Packing()
{
    one_blob_only = true;
    support_inplace = false;
}

int Packing::load_param(const ParamDict& pd)
{
    out_elempack = pd.get(0, 1);
    use_padding = pd.get(1, 0);
    cast_type_from = pd.get(2, 0);
    cast_type_to = pd.get(3, 0);
    return 0;
}

int Packing::forward(const Mat& bottom_blob, Mat& top_blob, const Option& opt) const
{
    const int elempack = bottom_blob.elempack;
    if (elempack == out_elempack)
    {
        top_blob = bottom_blob;
        return 0;
    }

    const int w = bottom_blob.w;
    const int h = bottom_blob.h;
    const int d = bottom_blob.d;
    const int channels = bottom_blob.c;
    const int dims = bottom_blob.dims;
    const size_t elemsize = bottom_blob.elemsize;

    if (!use_padding)
    {
        if ((dims == 1 && w * elempack % out_elempack != 0) ||
            (dims == 2 && h * elempack % out_elempack != 0) ||
            ((dims == 3 || dims == 4) && channels * elempack % out_elempack != 0))
        {
            top_blob = bottom_blob;
            return 0;
        }
    }

    if (dims == 1)
    {
        if (out_elempack == 1)
        {
            top_blob = bottom_blob;
            top_blob.w = w * elempack;
            top_blob.cstep = bottom_blob.cstep * elempack;
            top_blob.elemsize = elemsize / elempack;
            top_blob.elempack = 1;
            return 0;
        }

        const int outw = (w * elempack + out_elempack - 1) / out_elempack;
        const size_t out_elemsize = elemsize / elempack * out_elempack;
        top_blob.create(outw, out_elemsize, out_elempack, opt.blob_allocator);
        if (top_blob.empty()) return -100;
        memcpy(top_blob.data, bottom_blob.data, w * elemsize);
        return 0;
    }

    const size_t lane_size = elemsize / elempack;
    const size_t out_elemsize = lane_size * out_elempack;
    if (dims == 2)
    {
        const int outh = (h * elempack + out_elempack - 1) / out_elempack;
        top_blob.create(w, outh, out_elemsize, out_elempack, opt.blob_allocator);
        if (top_blob.empty()) return -100;
        for (int i = 0; i < outh; i++)
        {
            unsigned char* outptr = top_blob.row<unsigned char>(i);
            for (int j = 0; j < w; j++)
            {
                for (int k = 0; k < out_elempack; k++)
                {
                    const int source_lane = i * out_elempack + k;
                    const int srcy = source_lane / elempack;
                    if (srcy >= h) break;
                    const int srck = source_lane % elempack;
                    const unsigned char* src = bottom_blob.row<const unsigned char>(srcy) + j * elemsize;
                    memcpy(outptr + j * out_elemsize + k * lane_size,
                           src + srck * lane_size, lane_size);
                }
            }
        }
        return 0;
    }

    if (dims != 3 && dims != 4) return -1;
    const int outc = (channels * elempack + out_elempack - 1) / out_elempack;
    if (dims == 3)
        top_blob.create(w, h, outc, out_elemsize, out_elempack, opt.blob_allocator);
    else
        top_blob.create(w, h, d, outc, out_elemsize, out_elempack, opt.blob_allocator);
    if (top_blob.empty()) return -100;

    for (int q = 0; q < outc; q++)
    {
        Mat out = top_blob.channel(q);
        for (int z = 0; z < d; z++)
        {
            for (int i = 0; i < h; i++)
            {
                unsigned char* outptr = out.row<unsigned char>(z * h + i);
                for (int j = 0; j < w; j++)
                {
                    for (int k = 0; k < out_elempack; k++)
                    {
                        const int source_lane = q * out_elempack + k;
                        const int srcq = source_lane / elempack;
                        if (srcq >= channels) break;
                        const int srck = source_lane % elempack;
                        const unsigned char* src = bottom_blob.channel(srcq).row<const unsigned char>(z * h + i) + j * elemsize;
                        memcpy(outptr + j * out_elemsize + k * lane_size,
                               src + srck * lane_size, lane_size);
                    }
                }
            }
        }
    }
    return 0;
}

} // namespace ncnn
