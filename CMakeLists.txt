cmake_minimum_required(VERSION 3.22)
project(arctrl_ncnn LANGUAGES C CXX)

# This hard fork is one Android arm64 Vulkan runtime for Arctrl's fixed
# ZipDepth graph. Keep platform.h explicit instead of carrying upstream's
# architecture detection and packaging option matrix.
set(NCNN_STDIO 1)
set(NCNN_STRING 1)
set(NCNN_THREADS 1)
set(NCNN_VULKAN 1)
set(NCNN_FORCE_INLINE 1)
set(NCNN_GNU_INLINE_ASM 1)
set(NCNN_VFPV4 1)

foreach(feature
    NCNN_SIMPLEOCV
    NCNN_SIMPLEOMP
    NCNN_SIMPLESTL
    NCNN_SIMPLEMATH
    NCNN_BENCHMARK
    NCNN_C_API
    NCNN_PLATFORM_API
    NCNN_WINXP
    NCNN_PIXEL
    NCNN_PIXEL_ROTATE
    NCNN_PIXEL_AFFINE
    NCNN_PIXEL_DRAWING
    NCNN_SIMPLEVK
    NCNN_SYSTEM_GLSLANG
    NCNN_RUNTIME_CPU
    NCNN_AVX
    NCNN_XOP
    NCNN_FMA
    NCNN_F16C
    NCNN_AVX2
    NCNN_AVXVNNI
    NCNN_AVXVNNIINT8
    NCNN_AVXVNNIINT16
    NCNN_AVXNECONVERT
    NCNN_AVX512
    NCNN_AVX512VNNI
    NCNN_AVX512BF16
    NCNN_AVX512FP16
    NCNN_ARM82
    NCNN_ARM82DOT
    NCNN_ARM82FP16FML
    NCNN_ARM84BF16
    NCNN_ARM84I8MM
    NCNN_ARM86SVE
    NCNN_ARM86SVE2
    NCNN_ARM86SVEBF16
    NCNN_ARM86SVEI8MM
    NCNN_ARM86SVEF32MM
    NCNN_MSA
    NCNN_LSX
    NCNN_LASX
    NCNN_MMI
    NCNN_RVV
    NCNN_ZFH
    NCNN_ZVFH
    NCNN_XTHEADVECTOR
    NCNN_INT8
    NCNN_WEIGHT_QUANT
    NCNN_BF16
)
    set(${feature} 0)
endforeach()

# These capability macros were part of the reviewed arm64 build configuration.
# They are subordinate to NCNN_ARM86SVE=0 and therefore do not enable SVE code.
set(NCNN_ARM86SVE2 1)
set(NCNN_ARM86SVEBF16 1)
set(NCNN_ARM86SVEI8MM 1)
set(NCNN_ARM86SVEF32MM 1)

set(NCNN_VERSION_STRING "1.0.arctrl")
set(NCNN_VERSION_NUMBER 20260730)

add_subdirectory(src)
