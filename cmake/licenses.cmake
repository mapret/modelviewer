cmake_minimum_required(VERSION 3.0)
include(cmake/binary2cpp.cmake)


set(EXTERNAL_DIR ${CMAKE_CURRENT_LIST_DIR}/../external)

set(licenses
#display name | dependency name | path
    Assimp           assimp       ${EXTERNAL_DIR}/assimp/LICENSE
    Glew             glew         ${EXTERNAL_DIR}/glew/LICENSE.txt
    QDarkStyleSheet  qdarkstyle   ${EXTERNAL_DIR}/qdarkstyle/LICENSE.md
    Breeze           breeze       ${EXTERNAL_DIR}/breeze/LICENSE.md
)

list(LENGTH licenses num_licenses)
math(EXPR num_licenses "${num_licenses} / 3 - 1")

foreach (val RANGE ${num_licenses})
  math(EXPR index1 "${val} * 3")
  math(EXPR index2 "${val} * 3 + 1")
  math(EXPR index3 "${val} * 3 + 2")
  list(GET licenses ${index1} name)
  list(GET licenses ${index2} dependency)
  list(GET licenses ${index3} path)
  set(output_name ${CMAKE_BINARY_DIR}/licenses/${name})
  list(APPEND copy_command COMMAND ${CMAKE_COMMAND} ARGS -E copy ${path} ${output_name})
  list(APPEND license_list ${output_name})
  list(APPEND dependencies ${dependency})
  list(APPEND license_sources ${path})
endforeach()
add_custom_command(
    OUTPUT ${license_list}
    ${copy_command}
    DEPENDS ${license_sources} ${dependencies}
    COMMENT "Copying licenses"
)

# MSVC only allows strings up to 16KB, use addBinary instead of addPlaintext (some licenses are larger than 16KB)
addBinary(license_sources ${CMAKE_CURRENT_BINARY_DIR}/include/plaintext ${license_list})
