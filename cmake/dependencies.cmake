cmake_minimum_required(VERSION 3.0)

if (patch_assimp)
  set(filename ${EXTERNAL_DIR}/assimp/CMakeLists.txt)
  file(READ ${filename} data)
  # Force build minizip sources
  string(REPLACE "use_pkgconfig(UNZIP minizip)" "" data "${data}")
  # Reduces library size by a factor of 12
  string(REPLACE "CMAKE_CXX_FLAGS \"-g " "CMAKE_CXX_FLAGS \"" data "${data}") #
  file(WRITE ${filename} "${data}")
  return()
endif ()

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

add_definitions(-DGLEW_STATIC)
add_definitions(-DGLEW_NO_GLU)
add_subdirectory(external/glew)
include_directories(${EXTERNAL_DIR}/glew/include)

include_directories(${EXTERNAL_DIR}/stb/include)

if (STATIC_BUILD)
  set(LPREFIX ${CMAKE_STATIC_LIBRARY_PREFIX})
  set(LSUFFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(assimp_static -DBUILD_SHARED_LIBS=0 -DCMAKE_CXX_FLAGS=-w -DCMAKE_C_FLAGS=-w)
else()
  #LTO does not work with mingw and static build (because of libstdc++fs ?), assimp dll works though
  set(assimp_static -DCMAKE_CXX_FLAGS=-flto\ -w -DCMAKE_C_FLAGS=-flto\ -w)
endif()
ExternalProject_Add(
    assimp
    DOWNLOAD_DIR ${EXTERNAL_DIR}/download
    DOWNLOAD_NAME assimp-5.0.0.zip
    SOURCE_DIR ${EXTERNAL_DIR}/assimp
    URL https://github.com/assimp/assimp/archive/v5.0.0.zip
    URL_HASH SHA256=0c81f2d6c2b18272c98727e21846a9a8a203b15e8957c2ff7a6e76a1c52af2d3
    PATCH_COMMAND ${CMAKE_COMMAND} -Dpatch_assimp=1 -DEXTERNAL_DIR=${EXTERNAL_DIR} -P ${CMAKE_CURRENT_LIST_FILE}
    CMAKE_ARGS ${assimp_static} -DASSIMP_BUILD_IFC_IMPORTER=0 -DASSIMP_NO_EXPORT=1 -DASSIMP_BUILD_ASSIMP_TOOLS=0 -DASSIMP_BUILD_TESTS=0 -DASSIMP_BUILD_ZLIB=1 -DCMAKE_BUILD_TYPE=Release
    INSTALL_COMMAND ""
)
set(assimp_name assimp)
if (MSVC)
  set(assimp_name $<CONFIGURATION>/assimp-vc140-mt)
  set(LSUFFIX .lib) #TODO: Better way to do this?
endif ()
list(APPEND LIBS ${CMAKE_BINARY_DIR}/assimp-prefix/src/assimp-build/code/${LPREFIX}${assimp_name}${LSUFFIX})
if (STATIC_BUILD)
  list(APPEND LIBS ${CMAKE_BINARY_DIR}/assimp-prefix/src/assimp-build/contrib/zlib/${LPREFIX}zlibstatic${LSUFFIX})
  list(APPEND LIBS ${CMAKE_BINARY_DIR}/assimp-prefix/src/assimp-build/contrib/irrXML/${LPREFIX}IrrXML${LSUFFIX})
endif()
include_directories(${EXTERNAL_DIR}/assimp/include)
include_directories(${CMAKE_BINARY_DIR}/assimp-prefix/src/assimp-build/include)

ExternalProject_Add(
    qdarkstyle
    DOWNLOAD_DIR ${EXTERNAL_DIR}/download
    DOWNLOAD_NAME QDarkStyleSheet-2.7.zip
    SOURCE_DIR ${EXTERNAL_DIR}/qdarkstyle
    URL https://github.com/ColinDuquesnoy/QDarkStyleSheet/archive/2.7.zip
    URL_HASH SHA256=21e9724623d8bbccf7959767040c71ff0a6365ed3d05934bee64180f9ea8d83f
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
list(APPEND styles qdarkstyle)
list(APPEND qrcfiles ${EXTERNAL_DIR}/qdarkstyle/qdarkstyle/style.qrc)

ExternalProject_Add(
    breeze
    DOWNLOAD_DIR ${EXTERNAL_DIR}/download
    DOWNLOAD_NAME BreezeStyleSheets-2d595a956f8a5f493aa51139a470b768a6d82cce.zip
    SOURCE_DIR ${EXTERNAL_DIR}/breeze
    URL https://github.com/Alexhuszagh/BreezeStyleSheets/archive/2d595a956f8a5f493aa51139a470b768a6d82cce.zip
    URL_HASH SHA256=ec0e460115ea30635e18bcac7288bb1e98b427518cb07239755c4ba8cb986f91
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
list(APPEND styles breeze)
list(APPEND qrcfiles ${EXTERNAL_DIR}/breeze/breeze.qrc)

qt_add_rcc_file(rcc_src "${qrcfiles}" "${styles}")
