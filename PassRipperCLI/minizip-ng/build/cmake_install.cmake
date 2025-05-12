# Install script for directory: C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/minizip-ng")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/Debug/minizip-ng.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/Release/minizip-ng.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/MinSizeRel/minizip-ng.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/RelWithDebInfo/minizip-ng.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/Debug/zlib-ngd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/Release/zlib-ng.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/MinSizeRel/zlib-ng.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/RelWithDebInfo/zlib-ng.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/Debug/zlib-ngd2.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/Release/zlib-ng2.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/MinSizeRel/zlib-ng2.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/_deps/zlib-build/RelWithDebInfo/zlib-ng2.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng/minizip-ng.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng/minizip-ng.cmake"
         "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/CMakeFiles/Export/57c7ef7d0e442d72d1ae2e2d30d9c89b/minizip-ng.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng/minizip-ng-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng/minizip-ng.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng" TYPE FILE FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/CMakeFiles/Export/57c7ef7d0e442d72d1ae2e2d30d9c89b/minizip-ng.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng" TYPE FILE FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/CMakeFiles/Export/57c7ef7d0e442d72d1ae2e2d30d9c89b/minizip-ng-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng" TYPE FILE FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/CMakeFiles/Export/57c7ef7d0e442d72d1ae2e2d30d9c89b/minizip-ng-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng" TYPE FILE FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/CMakeFiles/Export/57c7ef7d0e442d72d1ae2e2d30d9c89b/minizip-ng-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng" TYPE FILE FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/CMakeFiles/Export/57c7ef7d0e442d72d1ae2e2d30d9c89b/minizip-ng-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip-ng" TYPE FILE FILES
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/minizip-ng-config-version.cmake"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/minizip-ng-config.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/minizip-ng" TYPE FILE FILES
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_os.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_crypt.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm_buf.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm_mem.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm_split.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm_os.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_zip.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_zip_rw.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm_zlib.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm_pkcrypt.h"
    "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/mz_strm_wzaes.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/minizip-ng.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/Kamil/Desktop/PRCLI/PassRipperCLI/minizip-ng/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
