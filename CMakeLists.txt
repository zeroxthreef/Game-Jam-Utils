cmake_minimum_required(VERSION 2.8)
project(GJ_utils)

set(GJ_SRC src/scene.c src/state.c src/util.c)
include_directories(include)

add_library(GJ_utils STATIC ${GJ_SRC})
