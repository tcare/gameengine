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
