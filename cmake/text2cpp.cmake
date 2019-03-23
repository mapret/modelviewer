cmake_minimum_required(VERSION 3.0)


if (out_cpp_initial)
    get_filename_component(out_hpp_rel ${out_hpp_initial} NAME)
    file(WRITE ${out_cpp_initial} "#include \"${out_hpp_rel}\"\n\n")
    file(WRITE ${out_hpp_initial} "namespace plaintext\n{\n}")
    return()
endif()

if (in_file)
    get_filename_component(var_name ${in_file} NAME)
    string(REGEX REPLACE "\\.glsl" "" var_name ${var_name})
    string(REGEX REPLACE "\\." "_" var_name ${var_name})

    file(READ ${out_hpp} file_tmp)
    string(REGEX REPLACE "}" "  extern const char* ${var_name};\n}" file_tmp "${file_tmp}")
    file(WRITE ${out_hpp} "${file_tmp}")

    file(READ ${in_file} var_content)
    file(APPEND ${out_cpp} "const char* plaintext::${var_name} = R\"\"\"(${var_content})\"\"\";\n")
    return()
endif()

set(glsl2cpp_path ${CMAKE_CURRENT_LIST_FILE})

function (addPlaintext shader_var gen_dir)
    SET(cpp_gen_rel "${shader_var}.gen.cpp")
    SET(hpp_gen_rel "${shader_var}.gen.hpp")
    get_filename_component(cpp_gen ${gen_dir}/${cpp_gen_rel} ABSOLUTE)
    get_filename_component(hpp_gen ${gen_dir}/${hpp_gen_rel} ABSOLUTE)

    SET(${shader_var} "${cpp_gen}" PARENT_SCOPE)
    set(command COMMAND ${CMAKE_COMMAND} ARGS -Dout_cpp_initial=${cpp_gen} -Dout_hpp_initial=${hpp_gen} -P ${glsl2cpp_path})

    set(shader_sources "")
    foreach (shader_source ${ARGN})
        get_filename_component(shader_source ${shader_source} ABSOLUTE)
        SET(command ${command} COMMAND ${CMAKE_COMMAND} ARGS -Din_file=${shader_source} -Dout_cpp=${cpp_gen} -Dout_hpp=${hpp_gen} ${encrypt} -P ${glsl2cpp_path})
        set(shader_sources ${shader_sources} ${shader_source})
    endforeach()

    add_custom_command(
           OUTPUT ${cpp_gen} ${hpp_gen}
           ${command}
           DEPENDS ${shader_sources}
           COMMENT "Generating ${cpp_gen_rel}, ${hpp_gen_rel}"
    )
endfunction()
