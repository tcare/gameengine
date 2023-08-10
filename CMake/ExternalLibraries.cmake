#
# External libraries
#

# We have no control over deprecation warnings in external libraries.
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
add_compile_options(-Wno-deprecated-declarations)

set(GAME_EXTERNAL_LIBRARIES)

# SFML - Rendering Library
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)
set(GAME_EXTERNAL_LIBRARIES
    ${GAME_EXTERNAL_LIBRARIES}
    sfml-graphics
    sfml-audio
)

# spdlog - Logging Library
set(SPDLOG_NO_EXCEPTIONS ON) # Disable exceptions so we can log in places like destructors
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)
set(GAME_EXTERNAL_LIBRARIES
    ${GAME_EXTERNAL_LIBRARIES}
    spdlog::spdlog_header_only
)

# libassert - Assertion Library
FetchContent_Declare(
    assert
    GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert.git
    GIT_TAG v1.2
)
FetchContent_MakeAvailable(assert)
set(GAME_EXTERNAL_LIBRARIES
    ${GAME_EXTERNAL_LIBRARIES}
    assert
)

# tmxlite - Tiled Map Loader
#set(USE_EXTLIBS TRUE)
set(TMXLITE_STATIC_LIB TRUE)
FetchContent_Declare(
    tmxlite
    GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    GIT_TAG v1.4.4
)
FetchContent_MakeAvailable(tmxlite)
add_subdirectory(${tmxlite_SOURCE_DIR}/tmxlite)
set(GAME_EXTERNAL_LIBRARIES
    ${GAME_EXTERNAL_LIBRARIES}
    ${TMXLITE_LIBRARIES}
)

# Turn back on deprecation warnings for our code
set(CMAKE_WARN_DEPRECATED ON CACHE BOOL "" FORCE)
