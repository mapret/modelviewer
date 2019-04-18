cmake_minimum_required(VERSION 3.0)


if (out_cpp_initial)
    get_filename_component(out_hpp_rel ${out_hpp_initial} NAME)
    file(WRITE ${out_cpp_initial} "#include \"${out_hpp_rel}\"\n\n")
    file(WRITE ${out_hpp_initial} "namespace binary\n{\n}")
    return()
endif()

if (in_file)
    get_filename_component(var_name ${in_file} NAME)
    string(REGEX REPLACE "\\.glsl" "" var_name ${var_name})
    string(REGEX REPLACE "\\." "_" var_name ${var_name})

    file(READ ${in_file} var_content HEX)
    string(LENGTH "${var_content}" file_size)
    math(EXPR file_size "${file_size} / 2")
    string(REGEX REPLACE "(..)" "0x\\1," var_content "${var_content}")
    file(APPEND ${out_cpp} "const unsigned char binary::${var_name}[] = {${var_content}};\n")
    file(APPEND ${out_cpp} "const unsigned binary::${var_name}_size = ${file_size};\n")

    file(READ ${out_hpp} file_tmp)
    string(REGEX REPLACE "}" "  extern const unsigned char ${var_name}[];\n}" file_tmp "${file_tmp}")
    string(REGEX REPLACE "}" "  extern const unsigned ${var_name}_size;\n}" file_tmp "${file_tmp}")
    file(WRITE ${out_hpp} "${file_tmp}")
    return()
endif()

set(binary2cpp_path ${CMAKE_CURRENT_LIST_FILE})

function (addBinary variable gen_dir)
    SET(cpp_gen_rel "${variable}.gen.cpp")
    SET(hpp_gen_rel "${variable}.gen.hpp")
    get_filename_component(cpp_gen ${gen_dir}/${cpp_gen_rel} ABSOLUTE)
    get_filename_component(hpp_gen ${gen_dir}/${hpp_gen_rel} ABSOLUTE)

    SET(${variable} "${cpp_gen}" PARENT_SCOPE)
    set(command COMMAND ${CMAKE_COMMAND} ARGS -Dout_cpp_initial=${cpp_gen} -Dout_hpp_initial=${hpp_gen} -P ${binary2cpp_path})

    set(binary_sources "")
    foreach (binary_source ${ARGN})
        get_filename_component(binary_source ${binary_source} ABSOLUTE)
        SET(command ${command} COMMAND ${CMAKE_COMMAND} ARGS -Din_file=${binary_source} -Dout_cpp=${cpp_gen} -Dout_hpp=${hpp_gen} ${encrypt} -P ${binary2cpp_path})
        set(binary_sources ${binary_sources} ${binary_source})
    endforeach()

    add_custom_command(
           OUTPUT ${cpp_gen} ${hpp_gen}
           ${command}
           DEPENDS ${binary_sources}
           COMMENT "Generating ${cpp_gen_rel}, ${hpp_gen_rel}"
    )
endfunction()
