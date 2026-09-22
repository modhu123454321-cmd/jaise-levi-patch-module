cmake_minimum_required(VERSION 3.16)
project(CursorIndicator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CursorIndicator SHARED
    src/main.cpp
)

set_target_properties(CursorIndicator PROPERTIES
    OUTPUT_NAME "CursorIndicator"
    PREFIX "lib"
    SUFFIX ".so"
)
