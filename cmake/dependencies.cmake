cmake_minimum_required(VERSION 3.0)

if (patch_assimp)
  set(filename ${EXTERNAL_DIR}/assimp/CMakeLists.txt)
  file(READ ${filename} data)
  # Force build minizip sources
  string(REPLACE "use_pkgconfig(UNZIP minizip)" "" data "${data}")
  # Reduces library size by a factor of 12
  string(REPLACE "\${CMAKE_CXX_FLAGS} -g" "\${CMAKE_CXX_FLAGS}" data "${data}") #
  file(WRITE ${filename} "${data}")
  return()
endif ()

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

add_definitions(-DGLEW_STATIC)
add_subdirectory(external/glew)
include_directories(${EXTERNAL_DIR}/glew/include)

include_directories(${EXTERNAL_DIR}/stb/include)

if (STATIC_BUILD)
  set(LPREFIX ${CMAKE_STATIC_LIBRARY_PREFIX})
  set(LSUFFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(assimp_static -DBUILD_SHARED_LIBS=0)
endif()
ExternalProject_Add(
    assimp
    DOWNLOAD_DIR ${EXTERNAL_DIR}/download
    DOWNLOAD_NAME assimp-4.1.0.zip
    SOURCE_DIR ${EXTERNAL_DIR}/assimp
    URL https://github.com/assimp/assimp/archive/v4.1.0.zip
    URL_HASH SHA256=407BE74F44F488FCF1AAC3492D962452DDDE89561906E917A208C75E1192BCDC
    PATCH_COMMAND ${CMAKE_COMMAND} -Dpatch_assimp=1 -DEXTERNAL_DIR=${EXTERNAL_DIR} -P ${CMAKE_CURRENT_LIST_FILE}
    CMAKE_ARGS ${assimp_static} -DCMAKE_CXX_FLAGS=-flto\ -w -DCMAKE_C_FLAGS=-flto\ -w -DASSIMP_BUILD_IFC_IMPORTER=0 -DASSIMP_BUILD_ASSIMP_TOOLS=0 -DASSIMP_BUILD_TESTS=0 -DASSIMP_BUILD_ZLIB=1 -DCMAKE_BUILD_TYPE=Release
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
    DOWNLOAD_NAME QDarkStyleSheet-2.6.5.zip
    SOURCE_DIR ${EXTERNAL_DIR}/qdarkstyle
    URL https://github.com/ColinDuquesnoy/QDarkStyleSheet/archive/2.6.5.zip
    URL_HASH SHA256=795414d972a6cc3291a1b5faf34550a1bb11c5fe368fe5a2ade81c90ae043364
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
qt_add_rcc_file(qdarkstyle_src ${EXTERNAL_DIR}/qdarkstyle/qdarkstyle/style.qrc qdarkstyle)
