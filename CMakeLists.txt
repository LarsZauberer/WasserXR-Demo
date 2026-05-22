cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER clang)
project(WasserXR LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CLANG_TIDY clang-tidy)

option(BUILD_DEBUG "Debug build" OFF)
option(WXR_STATIC "Static Linking for Components and Systems" OFF)

add_compile_options(-std=c99 -Wall -Wextra -Wno-unused-parameter)
add_link_options(-rdynamic)

if (BUILD_DEBUG)
  add_compile_options(-O0 -g -fno-omit-frame-pointer)
  add_compile_options(-fsanitize=address -fsanitize=undefined)
  add_link_options(-fsanitize=address -fsanitize=undefined)
else()
  add_compile_options(-O3)
endif()

if (WXR_STATIC)
  add_compile_definitions(WXR_STATIC)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(WASSERXR REQUIRED wasserxr)
pkg_check_modules(WASSERXR_CORE REQUIRED wasserxr_core)

# Generate main executable
add_executable(demo src/main.c src/glad/gl.c)
target_include_directories(demo PRIVATE ${WASSERXR_INCLUDE_DIRS})
target_link_libraries(demo PRIVATE ${WASSERXR_LIBRARIES})
if(WXR_STATIC)
  target_link_libraries(demo PRIVATE -Wl,--whole-archive 
    ${WASSERXR_CORE_LIBRARIES} 
    -Wl,--no-whole-archive)
endif()

install(TARGETS demo
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
