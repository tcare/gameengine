add_executable(gamebin
    game.cpp
)

target_include_directories(gamebin
    PRIVATE
    ../lib
)

target_link_libraries(gamebin
    libgame
)

add_executable(maptest
    maptest.cpp
)

target_include_directories(maptest
    PRIVATE
    ../lib
)

target_link_libraries(maptest
    libgame
)
