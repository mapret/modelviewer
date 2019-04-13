cmake_minimum_required(VERSION 3.0)
include(cmake/text2cpp.cmake)


set(EXTERNAL_DIR ${CMAKE_CURRENT_LIST_DIR}/../external)

set(licenses
    Assimp ${EXTERNAL_DIR}/assimp/LICENSE
    Glew   ${EXTERNAL_DIR}/glew/LICENSE.txt
)

list(LENGTH licenses num_licenses)
math(EXPR num_licenses "${num_licenses} / 2 - 1")

foreach (val RANGE ${num_licenses})
  math(EXPR index1 "${val} * 2")
  math(EXPR index2 "${val} * 2 + 1")
  list(GET licenses ${index1} name)
  list(GET licenses ${index2} path)
  set(output_name ${CMAKE_BINARY_DIR}/licenses/${name})
  if (EXISTS ${path})
    list(APPEND copy_command COMMAND ${CMAKE_COMMAND} ARGS -E copy ${path} ${output_name})
    list(APPEND license_sources ${path})
    list(APPEND license_list ${output_name})
  endif ()
endforeach()
add_custom_command(
    OUTPUT ${license_list}
    ${copy_command}
    DEPENDS ${license_sources}
    COMMENT "Copying licenses"
)

addPlaintext(license_sources ${CMAKE_CURRENT_BINARY_DIR}/include/plaintext ${license_list})
