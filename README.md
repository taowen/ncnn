# Arctrl ncnn Vulkan runtime

This directory is a hard fork of Tencent ncnn for Arctrl's fixed ZipDepth
graph. It is not a general ncnn distribution.

The runtime is statically linked into `arctrl_depth` and supports only:

- Android arm64 Vulkan execution;
- the operators listed in `src/CMakeLists.txt`;
- CPU `Input`, `Packing`, and `Cast` at graph/model-upload boundaries;
- immutable portable SPIR-V cache loading from Arctrl's model Blob;
- a Vulkan device supplied by Arctrl's shared Vulkan runtime.

It intentionally has no runtime GLSL compiler, general CPU inference fallback,
architecture-specific CPU kernels, C API, pixel utilities, tools, examples,
Python bindings, tests, or standalone package/install workflow. Do not restore
those upstream subsystems. Add code only when the fixed graph or a verified
target device requires it.

Upstream project: <https://github.com/Tencent/ncnn>

The retained source remains under the BSD 3-Clause license in `LICENSE.txt`.
