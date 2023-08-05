cmake_minimum_required(VERSION 3.26)
project(game VERSION 1.0)
include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

set(LIBCXX_HARDENING_MODE debug)

#
# External libraries
#

# We have no control over deprecation warnings in external libraries.
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
add_compile_options(-Wno-deprecated-declarations)

# SFML - Rendering Library
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# spdlog - Logging Library
set(SPDLOG_NO_EXCEPTIONS ON) # Disable exceptions so we can log in places like destructors
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

# libassert - Assertion Library
FetchContent_Declare(
    assert
    GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert.git
    GIT_TAG v1.2
)
FetchContent_MakeAvailable(assert)

# nlohmann/json - JSON Library for Tiled maps
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

# Turn back on deprecation warnings for our code
set(CMAKE_WARN_DEPRECATED ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)

#add_compile_options(-Werror)

add_compile_options(
    -Wall
    -Wextra
    -pedantic
)

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

#set(CMAKE_CXX_CLANG_TIDY /opt/homebrew/opt/llvm/bin/clang-tidy
#    --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
#)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION true)

add_executable(game
    Animation.cpp
    AssetManager.cpp
    EntityManager.cpp
    EntityMemoryPool.cpp
    GameEngine.cpp
    Scene.cpp

    main.cpp

    Scenes/TestScene.cpp
)
target_link_libraries(game
    sfml-graphics
    sfml-audio
    spdlog::spdlog_header_only
    assert
    nlohmann_json::nlohmann_json
)

# Enable PCH for expensive headers
target_precompile_headers(game
  PRIVATE
    pch.h
)