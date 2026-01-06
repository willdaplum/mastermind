cmake_minimum_required(VERSION 3.23)

project(
  Mastermind
  VERSION 0.0.0
  DESCRIPTION "A starter C++ project for generating a Fibonacci sequence."
  HOMEPAGE_URL https://github.com/threeal/cpp-starter
  LANGUAGES CXX
)

option(MASTERMIND_ENABLE_TESTS "Enable test targets.")
option(MASTERMIND_ENABLE_INSTALL "Enable install targets."
  "${PROJECT_IS_TOP_LEVEL}")

function(cpmaddpackage)
  file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.0/CPM.cmake
    ${CMAKE_BINARY_DIR}/_deps/CPM.cmake
    EXPECTED_MD5 e5facfa5d8d61f058d5a6e3e5391a3b7
  )
  include(${CMAKE_BINARY_DIR}/_deps/CPM.cmake)
  cpmaddpackage(${ARGN})
endfunction()

if(MASTERMIND_ENABLE_TESTS)
  find_package(CheckWarning 3.2.0 QUIET)
  if(NOT CheckWarning_FOUND)
    cpmaddpackage(gh:threeal/CheckWarning.cmake@3.2.0)
  endif()
  add_check_warning(TREAT_WARNINGS_AS_ERRORS)
endif()

find_package(argparse QUIET)
if(NOT argparse_FOUND)
  cpmaddpackage(gh:p-ranav/argparse@3.2)
endif()

add_library(mastermind src/mastermind.cpp)
target_sources(
  mastermind PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES include/mastermind/mastermind.hpp
)
target_compile_features(mastermind PRIVATE cxx_std_11)

add_executable(mastermind_cli src/main.cpp)
target_link_libraries(mastermind_cli PUBLIC argparse::argparse mastermind)

if(MASTERMIND_ENABLE_TESTS)
  enable_testing()

  find_package(ut QUIET)
  if(NOT ut_FOUND)
    cpmaddpackage(
      NAME ut
      GITHUB_REPOSITORY boost-ext/ut
      VERSION 2.3.1
      OPTIONS "BOOST_UT_DISABLE_MODULE ON"
    )
  endif()

  get_target_property(mastermind_SOURCES mastermind SOURCES)
  get_target_property(mastermind_HEADER_DIRS mastermind HEADER_DIRS)

  add_executable(mastermind_test test/mastermind_test.cpp ${mastermind_SOURCES})
  target_include_directories(mastermind_test PRIVATE ${mastermind_HEADER_DIRS})
  target_link_libraries(mastermind_test PRIVATE Boost::ut)

  include(cmake/CheckCoverage.cmake)
  target_check_coverage(mastermind_test)

  add_test(NAME "Mastermind Test" COMMAND mastermind_test)
endif()

if(MASTERMIND_ENABLE_TESTS)
  find_package(FixFormat QUIET)
  if(NOT FixFormat_FOUND)
    cpmaddpackage(gh:threeal/FixFormat.cmake@1.1.1)
    list(APPEND CMAKE_MODULE_PATH ${FixFormat_SOURCE_DIR}/cmake)
  endif()
  include(FixFormat)
  add_fix_format()
endif()

if(MASTERMIND_ENABLE_INSTALL)
  install(
    TARGETS mastermind_cli mastermind
    EXPORT mastermind_targets
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    FILE_SET HEADERS
  )

  install(
    EXPORT mastermind_targets
    FILE MastermindTargets.cmake
    NAMESPACE mastermind::
    DESTINATION lib/cmake/Mastermind
  )

  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    MastermindConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
  )

  install(
    FILES
      cmake/MastermindConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/MastermindConfigVersion.cmake
    DESTINATION lib/cmake/Mastermind
  )
endif()
