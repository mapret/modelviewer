cmake_minimum_required(VERSION 3.0)
include(cmake/text2cpp.cmake)


set(EXTERNAL_DIR ${CMAKE_CURRENT_LIST_DIR}/../external)

set(licenses
    Assimp ${CMAKE_BINARY_DIR}/assimp-prefix/src/assimp/LICENSE
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
    file(READ ${path} license)
    file(WRITE ${output_name} "${name}\n")
    file(APPEND ${output_name} "${license}")
  endif ()
endforeach()

file(GLOB licenses "${CMAKE_BINARY_DIR}/licenses/*")
addPlaintext(license_sources ${CMAKE_CURRENT_BINARY_DIR}/include/plaintext ${licenses})
