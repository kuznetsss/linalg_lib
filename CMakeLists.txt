cmake_minimum_required(VERSION 3.10)

project(linalg_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_EXE_LINKER_FLAGS -fuse-ld=lld)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE-LTO "-O3 -flto=full -march=native -DNDEBUG")
set(CMAKE_CXX_FLAGS_MSAN "-O1 -g -fsanitize=memory -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_CXX_FLAGS_ASAN "-O1 -g -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")

add_compile_options(-Werror -Wall -Wextra)

add_library(linalg INTERFACE)
target_include_directories(linalg INTERFACE include)


add_subdirectory(tests)

execute_process(COMMAND ln -sf build/compile_commands.json)
