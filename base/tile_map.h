//
//  load_tiles.h
//  ecs
//
//  Created by Nicholas Field on 10/04/2021.
//

#ifndef tile_map_h
#define tile_map_h

#include "world.h"
#include "json.h"

class TileMap
{
public:
    TileMap(World* world);
    ~TileMap() { world = nullptr; }
    void Load(std::string&& tileMapJsonPath, std::string&& tileSetJsonPath);
    void SetTileCollisions(nlohmann::json);
    void SetMapTextures(nlohmann::json);
private:
    int tileSetWidth;
    int tileSetHeight;

    int tileWidth;
    int tileHeight;

    int mapWidth;
    int mapHeight;
    World* world;
};

#endif /* load_tiles_h */
