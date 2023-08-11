#include "EntityManager.h"
#include "TiledMap.h"

int main() {
    EntityManager entityMgr;
    TiledMap map("assets/maps/map.tmx", entityMgr);
    return 0;
}