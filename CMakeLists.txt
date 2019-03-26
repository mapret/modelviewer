cmake_minimum_required(VERSION 3.0)
project(modelviewer)
include(cmake/qt_functions.cmake)
include(cmake/text2cpp.cmake)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

add_definitions(-DGLEW_STATIC)
add_subdirectory(external/glew)
include_directories(external/glew/include)

include_directories(external/stb/include)

ExternalProject_Add(assimp
    DOWNLOAD_DIR ${CMAKE_CURRENT_LIST_DIR}/external/download
    DOWNLOAD_NAME assimp-4.1.0.zip
    URL https://github.com/assimp/assimp/archive/v4.1.0.zip
    URL_HASH SHA256=407BE74F44F488FCF1AAC3492D962452DDDE89561906E917A208C75E1192BCDC
    CMAKE_ARGS -DASSIMP_BUILD_ASSIMP_TOOLS=0 -DASSIMP_BUILD_TESTS=0 -DCMAKE_BUILD_TYPE=Release -DASSIMP_LIB_INSTALL_DIR=${CMAKE_CURRENT_LIST_DIR}/external/assimp -DASSIMP_BIN_INSTALL_DIR=${CMAKE_BINARY_DIR} -DASSIMP_INCLUDE_INSTALL_DIR=${CMAKE_CURRENT_LIST_DIR}/external/assimp/include
)
include_directories(external/assimp/include)
find_library(libassimp assimp HINTS ${CMAKE_CURRENT_LIST_DIR}/external/assimp)


get_filename_component(PROJECT_DIR "." ABSOLUTE)
set(SOURCE_DIR "${PROJECT_DIR}/src")
set(UI_DIR "${PROJECT_DIR}/ui")
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif ()
if (UNIX)
    set(CMAKE_CXX_FLAGS "-fPIC")
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

add_executable(${PROJECT_NAME} ${cpp_SOURCES} ${hpp_SOURCES} ${moc_output} ${uic_output} ${opengl_shader})
add_dependencies(${PROJECT_NAME} assimp)
include_directories(${include_dirs_INTERNAL})

if (UNIX)
    include_directories(/usr/include/qt) #TODO: Find a better way to do this
endif()

if (libassimp)
    set(LIBS ${libassimp})
else ()
    message(AUTHOR_WARNING "You need to rerun cmake after building assimp (TODO: Fix this)")
endif ()
if (MINGW)
    list(APPEND LIBS stdc++fs)
endif()
if (WIN32)
    list(APPEND LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL glew)
else()
    list(APPEND LIBS Qt5Core Qt5Gui Qt5Widgets Qt5OpenGL GL glew stdc++fs)
endif()
target_link_libraries(${PROJECT_NAME} ${LIBS})
