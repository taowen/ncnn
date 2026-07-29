# Vulkan-only hard fork: architecture-specific CPU layer generators were removed.

macro(ncnn_add_layer class)
    string(TOLOWER ${class} name)

    # WITH_LAYER_xxx option
    if(${ARGC} EQUAL 2)
        option(WITH_LAYER_${name} "build with layer ${name}" ${ARGV1})
    else()
        option(WITH_LAYER_${name} "build with layer ${name}" ON)
    endif()

    if(NCNN_CMAKE_VERBOSE)
        message(STATUS "WITH_LAYER_${name} = ${WITH_LAYER_${name}}")
    endif()

    if(WITH_LAYER_${name})
        list(APPEND ncnn_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/layer/${name}.cpp)

        set(LAYER_VULKAN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/layer/vulkan/${name}_vulkan.cpp)
        if(NCNN_VULKAN AND EXISTS ${LAYER_VULKAN_SRC})
            set(WITH_LAYER_${name}_vulkan 1)
            list(APPEND ncnn_SRCS ${LAYER_VULKAN_SRC})
        endif()
    endif()

    # generate layer_declaration and layer_registry file
    if(WITH_LAYER_${name})
        set(layer_declaration "${layer_declaration}#include \"layer/${name}.h\"\n")
        # Input describes the graph boundary. Packing and Cast are the two
        # CPU-side utilities Vulkan model upload needs to arrange and convert
        # immutable constants before recording their transfer. None is an
        # inference fallback.
        if(name STREQUAL "input" OR name STREQUAL "packing" OR name STREQUAL "cast")
            set(layer_declaration "${layer_declaration}namespace ncnn { DEFINE_LAYER_CREATOR(${class}) }\n")
        endif()

        source_group ("sources\\\\layers" FILES "${CMAKE_CURRENT_SOURCE_DIR}/layer/${name}.cpp")
    endif()

    if(WITH_LAYER_${name}_vulkan)
        set(layer_declaration "${layer_declaration}#include \"layer/vulkan/${name}_vulkan.h\"\n")
        set(layer_declaration "${layer_declaration}namespace ncnn { DEFINE_LAYER_CREATOR(${class}_vulkan) }\n")

        file(GLOB NCNN_SHADER_SRCS "layer/vulkan/shader/${name}.comp")
        file(GLOB NCNN_SHADER_SUBSRCS "layer/vulkan/shader/${name}_*.comp")
        list(APPEND NCNN_SHADER_SRCS ${NCNN_SHADER_SUBSRCS})
        if(NOT NCNN_BATCH AND name STREQUAL "reshape")
            list(REMOVE_ITEM NCNN_SHADER_SRCS
                ${CMAKE_CURRENT_SOURCE_DIR}/layer/vulkan/shader/reshape_batch_reorder.comp
                ${CMAKE_CURRENT_SOURCE_DIR}/layer/vulkan/shader/reshape_batch_reorder_pack1to4.comp
                ${CMAKE_CURRENT_SOURCE_DIR}/layer/vulkan/shader/reshape_batch_reorder_pack4.comp
                ${CMAKE_CURRENT_SOURCE_DIR}/layer/vulkan/shader/reshape_batch_reorder_pack4to1.comp)
        endif()
        foreach(NCNN_SHADER_SRC ${NCNN_SHADER_SRCS})
            ncnn_add_shader(${NCNN_SHADER_SRC})
        endforeach()

        source_group ("sources\\\\layers\\\\vulkan" FILES "${CMAKE_CURRENT_SOURCE_DIR}/layer/vulkan/${name}_vulkan.cpp")
    endif()

    if(WITH_LAYER_${name} AND (name STREQUAL "input" OR name STREQUAL "packing" OR name STREQUAL "cast"))
        set(layer_registry "${layer_registry}#if NCNN_STRING\n{\"${class}\", ${class}_layer_creator},\n#else\n{${class}_layer_creator},\n#endif\n")
    else()
        set(layer_registry "${layer_registry}#if NCNN_STRING\n{\"${class}\", 0},\n#else\n{0},\n#endif\n")
    endif()

    if(WITH_LAYER_${name}_vulkan)
        set(layer_registry_vulkan "${layer_registry_vulkan}#if NCNN_STRING\n{\"${class}\", ${class}_vulkan_layer_creator},\n#else\n{${class}_vulkan_layer_creator},\n#endif\n")
    else()
        set(layer_registry_vulkan "${layer_registry_vulkan}#if NCNN_STRING\n{\"${class}\", 0},\n#else\n{0},\n#endif\n")
    endif()

    # generate layer_type_enum file
    set(layer_type_enum "${layer_type_enum}${class} = ${__LAYER_TYPE_ENUM_INDEX},\n")
    math(EXPR __LAYER_TYPE_ENUM_INDEX "${__LAYER_TYPE_ENUM_INDEX}+1")
endmacro()
