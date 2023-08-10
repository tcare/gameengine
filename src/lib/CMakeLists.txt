add_library(libgame STATIC
    Animation.cpp
    AssetManager.cpp
    EntityManager.cpp
    EntityMemoryPool.cpp
    GameEngine.cpp
    Scene.cpp
    TiledMap.cpp

    Scenes/TestScene.cpp
    Scenes/TiledScene.cpp
)

# Enable PCH for expensive headers
target_precompile_headers(libgame
  PRIVATE
    pch.h
)

target_link_libraries(libgame
    ${GAME_EXTERNAL_LIBRARIES}
    tmxlite
)
