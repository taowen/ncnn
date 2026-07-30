configure_file(platform.h.in ${CMAKE_CURRENT_BINARY_DIR}/platform.h)

set(ncnn_SRCS
    allocator.cpp
    blob.cpp
    command.cpp
    cpu.cpp
    datareader.cpp
    gpu.cpp
    layer.cpp
    mat.cpp
    modelbin.cpp
    net.cpp
    option.cpp
    paramdict.cpp
    pipeline.cpp
    pipelinecache.cpp
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ncnn_add_shader.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ncnn_add_layer.cmake)

set(NCNN_SHADER_SPV_HEX_FILES)
set(__LAYER_TYPE_ENUM_INDEX 0)
set(__LAYER_SHADER_TYPE_ENUM_INDEX 0)

# ZipDepth fixed graph plus the boundary utilities used by model upload.
# Keep this list in graph order: the immutable portable SPIR-V cache addresses
# generated shaders by registry index.
ncnn_add_layer(BatchNorm)
ncnn_add_layer(Concat)
ncnn_add_layer(Convolution)
ncnn_add_layer(Input)
ncnn_add_layer(MemoryData)
ncnn_add_layer(Pooling)
ncnn_add_layer(ReLU)
ncnn_add_layer(Reshape)
ncnn_add_layer(Sigmoid)
ncnn_add_layer(Split)
ncnn_add_layer(BinaryOp)
ncnn_add_layer(ConvolutionDepthWise)
ncnn_add_layer(Padding)
ncnn_add_layer(Interp)
ncnn_add_layer(Packing)
ncnn_add_layer(Cast)

# These two names are part of the portable cache registry even though Arctrl
# does not compile shaders at runtime.
ncnn_add_shader(${CMAKE_CURRENT_SOURCE_DIR}/convert_ycbcr.comp)
ncnn_add_shader(${CMAKE_CURRENT_SOURCE_DIR}/layer/vulkan/shader/vulkan_activation.comp)

configure_file(layer_declaration.h.in ${CMAKE_CURRENT_BINARY_DIR}/layer_declaration.h)
configure_file(layer_registry.h.in ${CMAKE_CURRENT_BINARY_DIR}/layer_registry.h)
configure_file(layer_type_enum.h.in ${CMAKE_CURRENT_BINARY_DIR}/layer_type_enum.h)
configure_file(layer_shader_registry.h.in ${CMAKE_CURRENT_BINARY_DIR}/layer_shader_registry.h)
configure_file(layer_shader_type_enum.h.in ${CMAKE_CURRENT_BINARY_DIR}/layer_shader_type_enum.h)

add_library(ncnn STATIC ${ncnn_SRCS})
set_target_properties(ncnn PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    INTERFACE_POSITION_INDEPENDENT_CODE ON
)
target_compile_features(ncnn PUBLIC cxx_std_11)
target_compile_definitions(ncnn PRIVATE NCNN_STATIC_DEFINE)
target_compile_options(ncnn PRIVATE
    -Wall
    -Wextra
    -Wno-unused-function
    -fvisibility=hidden
    -fvisibility-inlines-hidden
    $<$<CONFIG:Release>:-ffast-math>
)

include(GenerateExportHeader)
generate_export_header(ncnn)

target_include_directories(ncnn
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/layer
)

find_package(Vulkan REQUIRED)
find_package(Threads REQUIRED)
target_link_libraries(ncnn PUBLIC Vulkan::Vulkan Threads::Threads)
