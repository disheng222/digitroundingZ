cmake_minimum_required (VERSION 3.10.2)

#disable in-source builds
set (CMAKE_DISABLE_SOURCE_CHANGES ON)
set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

#define the project
project (dround 
  VERSION 0.0.0.0
  DESCRIPTION "Digit_Rounding Error Bounded Lossy Compressor"
  LANGUAGES C CXX
  )
enable_testing()

#correct was to set a default build type
# https://blog.kitware.com/cmake-and-the-default-build-type/
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type was set. Setting build type to ${default_build_type}.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE 
    STRING "Choose the type to build" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

#set the Compiler ID for clang on macOS to AppleClang
if (POLICY CMP0025)
  cmake_policy (SET CMP0025 NEW)
endif()

#compile with C-99 and standard C++14
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#generate tags for the project if tags exist
option(BUILD_CTAGS "enable ctags generation target" OFF)
if(BUILD_CTAGS)
  find_program(TAGS ctags)
  if(TAGS)
    add_custom_target(tags ALL
      COMMAND ${TAGS} --exclude=${CMAKE_BINARY_DIR} -f ${CMAKE_BINARY_DIR}/tags --c++-kinds=+p --fields=+iaS -R
      COMMENT Generating Tag files
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      )
  endif()
endif()

option(BUILD_SHARED_LIBS "build shared libraries over static libraries" ON)

#find dependencies
include(GNUInstallDirs)
find_package(PkgConfig)

#by default pass no 3rd party exports
set(thirdparty_export "")

find_package(ZLIB)
if(ZLIB_FOUND)
  set(ZLIB_dep ZLIB::ZLIB)
else()
  add_subdirectory(zlib)
  set(ZLIB_dep ZLIB)
  list(APPEND thirdparty_export "ZLIB")
endif()

add_subdirectory(libdround)
#add_subdirectory(zlib)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/dr.pc.in
  ${CMAKE_BINARY_DIR}/dr.pc
  @ONLY
)
install(FILES ${CMAKE_BINARY_DIR}/dr.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pkgconfig)

