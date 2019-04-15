cmake_minimum_required(VERSION 3.0)
project(modelviewer)
include(cmake/qt_functions.cmake)
include(cmake/text2cpp.cmake)
include(cmake/licenses.cmake)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

get_filename_component(PROJECT_DIR "." ABSOLUTE)
set(SOURCE_DIR   "${PROJECT_DIR}/src")
set(UI_DIR       "${PROJECT_DIR}/ui")
set(EXTERNAL_DIR "${PROJECT_DIR}/external")
set(LPREFIX ${CMAKE_SHARED_LIBRARY_PREFIX})
set(LSUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DGLEW_STATIC)
add_subdirectory(external/glew)
include_directories(${EXTERNAL_DIR}/glew/include)

include_directories(${EXTERNAL_DIR}/stb/include)

ExternalProject_Add(
    assimp
    DOWNLOAD_DIR ${EXTERNAL_DIR}/download
    DOWNLOAD_NAME assimp-4.1.0.zip
    SOURCE_DIR ${EXTERNAL_DIR}/assimp
    URL https://github.com/assimp/assimp/archive/v4.1.0.zip
    URL_HASH SHA256=407BE74F44F488FCF1AAC3492D962452DDDE89561906E917A208C75E1192BCDC
    CMAKE_ARGS ${ASSIMP_STATIC} -DASSIMP_BUILD_ASSIMP_TOOLS=0 -DASSIMP_BUILD_TESTS=0 -DASSIMP_BUILD_ZLIB=1 -DCMAKE_BUILD_TYPE=Release
    INSTALL_COMMAND ""
)
list(APPEND LIBS ${CMAKE_BINARY_DIR}/assimp-prefix/src/assimp-build/code/${LPREFIX}assimp${LSUFFIX})
include_directories(${EXTERNAL_DIR}/assimp/include)
include_directories(${CMAKE_BINARY_DIR}/assimp-prefix/src/assimp-build/include)

if (MSVC)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif ()

file(GLOB_RECURSE ui_files RELATIVE "${UI_DIR}" "${UI_DIR}/*.ui")
file(GLOB_RECURSE moc_files RELATIVE "${SOURCE_DIR}" "${SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE hpp_SOURCES "${SOURCE_DIR}/*.hpp")
file(GLOB_RECURSE cpp_SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB glsl_SOURCES "${SOURCE_DIR}/glsl/*.glsl")

set(include_dirs_INTERNAL
    ${SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/include
    )

get_filename_component(LIB_ROOT ${QT_UIC_PATH} DIRECTORY)
qt_add_moc_files(moc_output ${moc_files})
qt_add_uic_files(uic_output ${ui_files})
addPlaintext(opengl_shader ${CMAKE_CURRENT_BINARY_DIR}/include/plaintext ${glsl_SOURCES})

add_executable(${PROJECT_NAME} ${cpp_SOURCES} ${hpp_SOURCES} ${moc_output} ${uic_output} ${opengl_shader} ${license_sources})
add_dependencies(${PROJECT_NAME} assimp)
include_directories(${include_dirs_INTERNAL})

list(APPEND LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)
list(APPEND LIBS glew)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")  # gcc and MinGW
    list(APPEND LIBS stdc++fs)
endif()
target_link_libraries(${PROJECT_NAME} ${LIBS})
