cmake_minimum_required(VERSION 3.10)
project(libntr)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_FOR_DS "Compile for NDS" OFF)

if(NOT CMAKE_TOOLCHAIN_FILE MATCHES "devkitARM.cmake")
  set(BUILD_FOR_TESTS)
  add_definitions(-DTEST_MODE)
else()
  set(BUILD_FOR_TESTS OFF)
  add_definitions(-DARM9 -D__NDS__)
endif()

if(BUILD_FOR_TESTS)
  # <Compile for PC>
  add_definitions(-DTEST_MODE)

  find_package(cmocka CONFIG REQUIRED)

  add_executable(runner_test
    src/core.c
    test/test_main.c
  )

  target_link_libraries(runner_test PRIVATE cmocka::cmocka)
  target_include_directories(runner_test PRIVATE include)

  else()
    include_directories($ENV{DEVKITPRO}/libnds/include)
    link_directories($ENV{DEVKITPRO}/libnds/lib)

    add_library(libntr STATIC
      source/main.c
      source/fmt/NCLR.c)
    target_include_directories(libntr PUBLIC
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
      "${CMAKE_CURRENT_SOURCE_DIR}/include/libntr")
    target_link_libraries(libntr fat nds9)

  endif()
