
macro(ncnn_add_shader NCNN_SHADER_SRC)
    get_filename_component(NCNN_SHADER_SRC_NAME_WE ${NCNN_SHADER_SRC} NAME_WE)
    string(APPEND layer_shader_registry "{\"${NCNN_SHADER_SRC_NAME_WE}\"},\n")

    # generate layer_shader_type_enum file
    set(layer_shader_type_enum "${layer_shader_type_enum}${NCNN_SHADER_SRC_NAME_WE} = ${__LAYER_SHADER_TYPE_ENUM_INDEX},\n")
    math(EXPR __LAYER_SHADER_TYPE_ENUM_INDEX "${__LAYER_SHADER_TYPE_ENUM_INDEX}+1")
endmacro()
