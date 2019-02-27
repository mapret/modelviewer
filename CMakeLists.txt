cmake_minimum_required(VERSION 3.0)
project(modelviewer)
include(qt_functions.cmake)
include(text2cpp.cmake)

get_filename_component(PROJECT_DIR "." ABSOLUTE)
set(SOURCE_DIR "${PROJECT_DIR}/src")
set(UI_DIR "${PROJECT_DIR}/ui")
set(LIBRARY_DIR "${PROJECT_DIR}/include")
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
include_directories(${LIB_ROOT}/../include/qt)
qt_add_moc_files(moc_output ${moc_files})
qt_add_uic_files(uic_output ${ui_files})
addPlaintext(opengl_shader ${CMAKE_CURRENT_BINARY_DIR}/include/plaintext ${glsl_SOURCES})

add_executable(${PROJECT_NAME} ${cpp_SOURCES} ${hpp_SOURCES} ${moc_output} ${uic_output} ${opengl_shader})
include_directories(${include_dirs_INTERNAL})
include_directories(SYSTEM ${LIBRARY_DIR})

target_link_libraries(${PROJECT_NAME} assimp)
if (MSVC)
    target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Xml Qt5::OpenGL)
else()
    target_link_libraries(${PROJECT_NAME} Qt5Core Qt5Gui Qt5Widgets Qt5Xml Qt5OpenGL GL GLEW stdc++fs)
endif()
