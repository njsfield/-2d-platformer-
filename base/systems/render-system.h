//
//  render-system.h
//  ecs
//
//  Created by Nicholas Field on 30/03/2021.
//

#ifndef render_system_h
#define render_system_h

#include "world.h"

class RenderSystem : public System
{
public:
    RenderSystem(
                 std::string&& playerSpritePath,
                 std::string&& tileSpritePath,
                 std::unordered_map<SPRITE_ID, SpriteCoord> playerSpriteMap
                 );

    void onAddedToWorld(World* world) override;

    void tick(World* world) override;

    void handleEvent(SDL_Event& event, World* world) override;

    void onRemovedFromWorld(World* world) override;

    ~RenderSystem() = default;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* playerSprite;
    SDL_Texture* tileSprite;
    std::unordered_map<SPRITE_ID, SpriteCoord> playerSpriteMap;
};

#endif /* render_system_h */
