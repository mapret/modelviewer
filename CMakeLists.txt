cmake_minimum_required(VERSION 3.0)
project(modelviewer)

if (POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
endif()

get_filename_component(PROJECT_DIR "." ABSOLUTE)
set(SOURCE_DIR   "${PROJECT_DIR}/src")
set(UI_DIR       "${PROJECT_DIR}/ui")
set(EXTERNAL_DIR "${PROJECT_DIR}/external")
set(LPREFIX ${CMAKE_SHARED_LIBRARY_PREFIX})
set(LSUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
set(CMAKE_CXX_STANDARD 17)
if (${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    set(STATIC_BUILD 1)
    if (MINGW)
        list(APPEND LIBS -static) #Statically link MinGW dependencies (winpthread-1, gcc_s_seh-1)
    endif ()
    list(APPEND LIBS -static-libstdc++)
    #LTO does not seem to work with MinGW (because of libstdc++fs ?)
    #set(CMAKE_INTERPROCEDURAL_OPTIMIZATION 1)
    set(rc_src ${UI_DIR}/main.rc)
endif ()

include(cmake/qt_functions.cmake)
include(cmake/text2cpp.cmake)
include(cmake/dependencies.cmake)
include(cmake/licenses.cmake)

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

add_executable(${PROJECT_NAME} ${cpp_SOURCES} ${hpp_SOURCES} ${moc_output} ${uic_output} ${opengl_shader} ${rc_src} ${rcc_src} ${license_sources})
add_dependencies(${PROJECT_NAME} assimp)
include_directories(${include_dirs_INTERNAL})

list(APPEND LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)
list(APPEND LIBS glew)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")  # gcc and MinGW
    list(APPEND LIBS stdc++fs)
endif()
target_link_libraries(${PROJECT_NAME} ${LIBS})
