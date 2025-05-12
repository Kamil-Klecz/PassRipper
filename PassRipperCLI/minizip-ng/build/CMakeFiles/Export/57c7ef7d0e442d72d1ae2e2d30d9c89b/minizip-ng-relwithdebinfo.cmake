#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MINIZIP::minizip-ng" for configuration "RelWithDebInfo"
set_property(TARGET MINIZIP::minizip-ng APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(MINIZIP::minizip-ng PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/minizip-ng.lib"
  )

list(APPEND _cmake_import_check_targets MINIZIP::minizip-ng )
list(APPEND _cmake_import_check_files_for_MINIZIP::minizip-ng "${_IMPORT_PREFIX}/lib/minizip-ng.lib" )

# Import target "MINIZIP::zlib" for configuration "RelWithDebInfo"
set_property(TARGET MINIZIP::zlib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(MINIZIP::zlib PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/zlib-ng.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/zlib-ng2.dll"
  )

list(APPEND _cmake_import_check_targets MINIZIP::zlib )
list(APPEND _cmake_import_check_files_for_MINIZIP::zlib "${_IMPORT_PREFIX}/lib/zlib-ng.lib" "${_IMPORT_PREFIX}/bin/zlib-ng2.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
