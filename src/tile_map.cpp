//
//  tile_map.cpp
//  ecs
//
//  Created by Nicholas Field on 10/04/2021.
//

#include <stdio.h>
#include <string>
#include <istream>
#include <fstream>
#include "tile_map.h"
#include "json.h"
#include "components.h"

using nlohmann::json;

TileMap::TileMap(World* w)
{
    world = w;
}

void TileMap::Load(std::string &&tileMapJsonPath, std::string &&tileSetJsonPath)
{
    std::ifstream setStream(tileSetJsonPath);
    json setJson;
    setStream >> setJson;
    
    tileSetWidth = setJson["imagewidth"].get<int>();
    tileSetHeight = setJson["imageheight"].get<int>();
    
    std::ifstream mapStream(tileMapJsonPath);
    json mapJson;
    mapStream >> mapJson;
    
    mapWidth = mapJson["width"].get<int>();
    mapHeight = mapJson["height"].get<int>();
    
    tileWidth = mapJson["tilewidth"].get<int>();
    tileHeight = mapJson["tileheight"].get<int>();
    
    world->LEVEL_WIDTH = mapWidth * tileWidth;
    world->LEVEL_HEIGHT = mapHeight * tileHeight;
    
    // Get layers
    for (auto& layer : mapJson["layers"]) {
      if (layer["name"].get<std::string>() == "TileCollisions")
          SetTileCollisions(layer);
        
      if (layer["name"].get<std::string>() == "MapTextures")
          SetMapTextures(layer);
    };
};

void TileMap::SetTileCollisions(json layer)
{
    for (auto& collision : layer["objects"]) {
        int x = (int)collision["x"].get<float>();
        int y = (int)collision["y"].get<float>();
        int w = (int)collision["width"].get<float>();
        int h = (int)collision["height"].get<float>();
        
        int xPos = (int)std::floor(x);
        int yPos = (int)std::floor(y);
        
        Entity* t = world->create();
        t->assign<TileComponent>();
        t->assign<PositionComponent>(xPos, yPos);
        t->assign<TransformComponent>(w, h);
    }
}

const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;

void TileMap::SetMapTextures(json layer)
{    
    auto data = layer["data"];
    
    for (int y = 0; y < mapHeight; y++) {
      for (int x = 0; x < mapWidth; x++) {
          unsigned global_tile_id = data[(y * (mapWidth)) + x];
          if (global_tile_id == 0) continue;
          
          // Read out the flags
          bool flipped_horizontally = (global_tile_id & FLIPPED_HORIZONTALLY_FLAG);
          bool flipped_vertically = (global_tile_id & FLIPPED_VERTICALLY_FLAG);
          bool flipped_diagonally = (global_tile_id & FLIPPED_DIAGONALLY_FLAG);
          
          // Clear flags
          global_tile_id &= ~(FLIPPED_HORIZONTALLY_FLAG |
                              FLIPPED_VERTICALLY_FLAG |
                              FLIPPED_DIAGONALLY_FLAG);
          
          unsigned rotation =
            (flipped_horizontally && flipped_diagonally && !flipped_vertically) ? 90 :
            (flipped_horizontally && !flipped_diagonally && flipped_vertically) ? 180 :
            (!flipped_horizontally && flipped_diagonally && flipped_vertically) ? 270
          : 0;
          
          int tileXLength = (int)(std::floor(tileSetWidth / tileWidth));
          int tileSetX = (global_tile_id - 1) % tileXLength;
          int tileSetY = (int)((global_tile_id - 1) / tileXLength);
          
          Entity* t = world->create();
          t->assign<TileTextureComponent>(tileSetX * tileWidth, tileSetY * tileHeight, tileWidth, tileHeight, rotation);
          t->assign<PositionComponent>(x * tileWidth, y * tileHeight);
          t->assign<TransformComponent>(tileWidth, tileHeight);
      }
    }
}
