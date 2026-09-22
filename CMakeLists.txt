cmake_minimum_required(VERSION 3.16)
project(CursorIndicator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CursorIndicator SHARED
    src/main.cpp
    src/logger.cpp
    src/config.cpp
    src/paths.cpp
)

find_library(log-lib log)

target_link_libraries(CursorIndicator
    ${log-lib}
)

set_target_properties(CursorIndicator PROPERTIES
    OUTPUT_NAME "CursorIndicator"
    PREFIX "lib"
    SUFFIX ".so"
)
