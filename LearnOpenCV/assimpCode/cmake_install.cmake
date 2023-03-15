# Install script for directory: ./code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.5-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "./lib/Debug/assimp-vc143-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "./lib/Release/assimp-vc143-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "./lib/MinSizeRel/assimp-vc143-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "./lib/RelWithDebInfo/assimp-vc143-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.5x" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "./bin/Debug/assimp-vc143-mtd.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "./bin/Release/assimp-vc143-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "./bin/MinSizeRel/assimp-vc143-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "./bin/RelWithDebInfo/assimp-vc143-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "./code/../include/assimp/anim.h"
    "./code/../include/assimp/aabb.h"
    "./code/../include/assimp/ai_assert.h"
    "./code/../include/assimp/camera.h"
    "./code/../include/assimp/color4.h"
    "./code/../include/assimp/color4.inl"
    "./code/../include/assimp/config.h"
    "./code/../include/assimp/ColladaMetaData.h"
    "./code/../include/assimp/commonMetaData.h"
    "./code/../include/assimp/defs.h"
    "./code/../include/assimp/cfileio.h"
    "./code/../include/assimp/light.h"
    "./code/../include/assimp/material.h"
    "./code/../include/assimp/material.inl"
    "./code/../include/assimp/matrix3x3.h"
    "./code/../include/assimp/matrix3x3.inl"
    "./code/../include/assimp/matrix4x4.h"
    "./code/../include/assimp/matrix4x4.inl"
    "./code/../include/assimp/mesh.h"
    "./code/../include/assimp/ObjMaterial.h"
    "./code/../include/assimp/pbrmaterial.h"
    "./code/../include/assimp/GltfMaterial.h"
    "./code/../include/assimp/postprocess.h"
    "./code/../include/assimp/quaternion.h"
    "./code/../include/assimp/quaternion.inl"
    "./code/../include/assimp/scene.h"
    "./code/../include/assimp/metadata.h"
    "./code/../include/assimp/texture.h"
    "./code/../include/assimp/types.h"
    "./code/../include/assimp/vector2.h"
    "./code/../include/assimp/vector2.inl"
    "./code/../include/assimp/vector3.h"
    "./code/../include/assimp/vector3.inl"
    "./code/../include/assimp/version.h"
    "./code/../include/assimp/cimport.h"
    "./code/../include/assimp/AssertHandler.h"
    "./code/../include/assimp/importerdesc.h"
    "./code/../include/assimp/Importer.hpp"
    "./code/../include/assimp/DefaultLogger.hpp"
    "./code/../include/assimp/ProgressHandler.hpp"
    "./code/../include/assimp/IOStream.hpp"
    "./code/../include/assimp/IOSystem.hpp"
    "./code/../include/assimp/Logger.hpp"
    "./code/../include/assimp/LogStream.hpp"
    "./code/../include/assimp/NullLogger.hpp"
    "./code/../include/assimp/cexport.h"
    "./code/../include/assimp/Exporter.hpp"
    "./code/../include/assimp/DefaultIOStream.h"
    "./code/../include/assimp/DefaultIOSystem.h"
    "./code/../include/assimp/ZipArchiveIOSystem.h"
    "./code/../include/assimp/SceneCombiner.h"
    "./code/../include/assimp/fast_atof.h"
    "./code/../include/assimp/qnan.h"
    "./code/../include/assimp/BaseImporter.h"
    "./code/../include/assimp/Hash.h"
    "./code/../include/assimp/MemoryIOWrapper.h"
    "./code/../include/assimp/ParsingUtils.h"
    "./code/../include/assimp/StreamReader.h"
    "./code/../include/assimp/StreamWriter.h"
    "./code/../include/assimp/StringComparison.h"
    "./code/../include/assimp/StringUtils.h"
    "./code/../include/assimp/SGSpatialSort.h"
    "./code/../include/assimp/GenericProperty.h"
    "./code/../include/assimp/SpatialSort.h"
    "./code/../include/assimp/SkeletonMeshBuilder.h"
    "./code/../include/assimp/SmallVector.h"
    "./code/../include/assimp/SmoothingGroups.h"
    "./code/../include/assimp/SmoothingGroups.inl"
    "./code/../include/assimp/StandardShapes.h"
    "./code/../include/assimp/RemoveComments.h"
    "./code/../include/assimp/Subdivision.h"
    "./code/../include/assimp/Vertex.h"
    "./code/../include/assimp/LineSplitter.h"
    "./code/../include/assimp/TinyFormatter.h"
    "./code/../include/assimp/Profiler.h"
    "./code/../include/assimp/LogAux.h"
    "./code/../include/assimp/Bitmap.h"
    "./code/../include/assimp/XMLTools.h"
    "./code/../include/assimp/IOStreamBuffer.h"
    "./code/../include/assimp/CreateAnimMesh.h"
    "./code/../include/assimp/XmlParser.h"
    "./code/../include/assimp/BlobIOSystem.h"
    "./code/../include/assimp/MathFunctions.h"
    "./code/../include/assimp/Exceptional.h"
    "./code/../include/assimp/ByteSwapper.h"
    "./code/../include/assimp/Base64.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "./code/../include/assimp/Compiler/pushpack1.h"
    "./code/../include/assimp/Compiler/poppack1.h"
    "./code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "./code/Debug/assimp-vc143-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "./code/RelWithDebInfo/assimp-vc143-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

