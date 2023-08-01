cmake_minimum_required(VERSION 3.26)
project(game VERSION 1.0)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

#
# External libraries
#

# SFML - Rendering Library
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# spdlog - Logging Library
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(game
    main.cpp
    GameEngine.cpp
    Scene.cpp
    Scenes/TestScene.cpp
)
target_link_libraries(game
    sfml-graphics
    sfml-audio
    spdlog::spdlog_header_only
)

# Enable PCH for expensive headers
target_precompile_headers(game
  PRIVATE
    pch.h
)