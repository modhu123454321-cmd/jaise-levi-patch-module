cmake_minimum_required(VERSION 3.22)

project(aim_cursor_mod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(MOD_ID "aim_cursor" CACHE STRING "LeviLauncher mod package directory name")
set(MOD_NAME "Aim Cursor Mob Indicator" CACHE STRING "LeviLauncher mod display name")
set(MOD_AUTHOR "modhu123454321-cmd" CACHE STRING "LeviLauncher mod author")
set(MOD_VERSION "1.0.0" CACHE STRING "LeviLauncher mod version")
set(MOD_LIBRARY_NAME "aim_cursor" CACHE STRING "Native library name")
set(MOD_MINECRAFT_VERSIONS "[\"1.26.45*\"]" CACHE STRING "Minecraft versions")

include(FetchContent)

FetchContent_Declare(
    preloader_android
    GIT_REPOSITORY https://github.com/LiteLDev/preloader-android.git
    GIT_TAG 0.2.2
    SOURCE_SUBDIR cmake/preloader-sdk
)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_Declare(
    boost_pfr
    GIT_REPOSITORY https://github.com/boostorg/pfr.git
    GIT_TAG boost-1.88.0
)

FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG v0.9.7
)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.2.0
)

set(FMT_DOC OFF CACHE BOOL "" FORCE)
set(FMT_TEST OFF CACHE BOOL "" FORCE)
set(FMT_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(
    preloader_android
    nlohmann_json
    boost_pfr
    magic_enum
    fmt
)

FetchContent_GetProperties(preloader_android)
set(LEVI_PRELOADER_INCLUDE_DIR
    "${preloader_android_SOURCE_DIR}/include"
)

if(NOT ANDROID)
    set(LEVI_GENERATED_CONFIG_DIR
        "${CMAKE_CURRENT_BINARY_DIR}/generated-config"
    )

    add_executable(
        levi_config_generator
        src/config_generator.cpp
        src/mod/Config.cpp
    )

    target_include_directories(
        levi_config_generator
        PRIVATE
        src
        "${LEVI_PRELOADER_INCLUDE_DIR}"
    )

    target_compile_definitions(
        levi_config_generator
        PRIVATE
        PL_CONFIG_NO_RUNTIME
    )

    target_link_libraries(
        levi_config_generator
        PRIVATE
        nlohmann_json::nlohmann_json
        Boost::pfr
        magic_enum::magic_enum
    )

    add_custom_target(
        levi_generate_config
        COMMAND levi_config_generator
                "${LEVI_GENERATED_CONFIG_DIR}"
        DEPENDS levi_config_generator
    )

    return()
endif()

if(NOT DEFINED LEVI_PACKAGE_CONFIG_DIR)
    set(
        LEVI_PACKAGE_CONFIG_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/config"
        CACHE PATH "Config directory"
    )
endif()

if(NOT EXISTS "${LEVI_PACKAGE_CONFIG_DIR}/config.json")
    message(FATAL_ERROR "config/config.json is missing")
endif()

if(NOT EXISTS "${LEVI_PACKAGE_CONFIG_DIR}/config.schema.json")
    message(FATAL_ERROR "config/config.schema.json is missing")
endif()

if(NOT CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
    message(FATAL_ERROR "Only arm64-v8a is supported")
endif()

if(NOT TARGET preloader)
    add_subdirectory(
        "${preloader_android_SOURCE_DIR}"
        "${CMAKE_BINARY_DIR}/_preloader_android"
    )
endif()

add_library(
    ${MOD_LIBRARY_NAME}
    SHARED
    src/main.cpp
    src/mod/Config.cpp
    src/mod/MyMod.cpp
)

target_include_directories(
    ${MOD_LIBRARY_NAME}
    PRIVATE
    src
    "${LEVI_PRELOADER_INCLUDE_DIR}"
)

target_link_options(
    ${MOD_LIBRARY_NAME}
    PRIVATE
    "-Wl,-z,max-page-size=16384"
)

find_library(log-lib log REQUIRED)

target_link_libraries(
    ${MOD_LIBRARY_NAME}
    PRIVATE
    ${log-lib}
    nlohmann_json::nlohmann_json
    Boost::pfr
    magic_enum::magic_enum
    fmt::fmt
    preloader
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/manifest.json.in"
    "${CMAKE_CURRENT_BINARY_DIR}/manifest.json"
    @ONLY
)

set(PACKAGE_ROOT
    "${CMAKE_CURRENT_BINARY_DIR}/package"
)

set(PACKAGE_MOD_DIR
    "${PACKAGE_ROOT}/${MOD_ID}"
)

set(PACKAGE_FILE
    "${CMAKE_CURRENT_BINARY_DIR}/${MOD_ID}-${MOD_VERSION}-${CMAKE_ANDROID_ARCH_ABI}.levipack"
)

add_custom_target(
    levi_package

    COMMAND ${CMAKE_COMMAND} -E rm -rf
            "${PACKAGE_ROOT}"

    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${PACKAGE_MOD_DIR}"

    COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE:${MOD_LIBRARY_NAME}>"
            "${PACKAGE_MOD_DIR}/lib${MOD_LIBRARY_NAME}.so"

    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_BINARY_DIR}/manifest.json"
            "${PACKAGE_MOD_DIR}/manifest.json"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${LEVI_PACKAGE_CONFIG_DIR}"
            "${PACKAGE_MOD_DIR}/config"

    COMMAND ${CMAKE_COMMAND} -E chdir
            "${PACKAGE_ROOT}"
            ${CMAKE_COMMAND} -E tar cf
            "${PACKAGE_FILE}"
            --format=zip
            "${MOD_ID}"

    DEPENDS ${MOD_LIBRARY_NAME}
)
