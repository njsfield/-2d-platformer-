#include "game.h"
#include "components.h"
#include "render-system.h"
#include "constants.h"

RenderSystem::RenderSystem(
                           std::string&& playerSpritePath,
                           std::string&& tileSpritePath,
                           std::unordered_map<SPRITE_ID, SpriteCoord> ps
                           ) {
    playerSpriteMap = ps;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");
    // Load Window
    window = SDL_CreateWindow("Game Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    
    // Load Renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Init Image
    int imgFlags = IMG_INIT_PNG;
    IMG_Init( imgFlags );
    
    // Load player sprite
    SDL_Surface* loadedPlayerSurface = IMG_Load( playerSpritePath.c_str() );
    playerSprite = SDL_CreateTextureFromSurface( renderer, loadedPlayerSurface );
    
    // Load tile sprite
    SDL_Surface* loadedTileSurface = IMG_Load( tileSpritePath.c_str() );
    tileSprite = SDL_CreateTextureFromSurface( renderer, loadedTileSurface );
}

void RenderSystem::onAddedToWorld(World* world)
{
    
}

void RenderSystem::tick(World* world)
{
    SDL_RenderClear(renderer);
    
    Entity* camera = world->find<CameraComponent>();
    CameraComponent* cam = camera->get<CameraComponent>();

    world->findAll<PlayerComponent>([&](Entity* e) {
        PlayerComponent* p = e->get<PlayerComponent>();
        PositionComponent* pos = e->get<PositionComponent>();
        TransformComponent* trans = e->get<TransformComponent>();
        SpriteComponent* s = e->get<SpriteComponent>();
        
        SDL_RendererFlip flipped = p->forwardFacing ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        
        SpriteCoord spriteCoord = playerSpriteMap.at(s->spriteId);
        
        SDL_Rect clip;
        clip.x = spriteCoord.x + 12; // define x position in sprite
        clip.y = spriteCoord.y; // define y position in sprite
        clip.w = spriteCoord.w - 25; // width of the clipped area
        clip.h = spriteCoord.h - 10; // width of the clipped area
        
        SDL_Rect renderQuad;
        renderQuad.x = pos->x - cam->x; // define x position on viewport
        renderQuad.y = pos->y - cam->y; // define y position on viewport (flip y coords)
        renderQuad.w = trans->w; // scaled width
        renderQuad.h = trans->h; // scaled height
        
        SDL_RenderCopyEx(renderer, playerSprite, &clip, &renderQuad, (double)0, NULL, flipped);
    });
    
    world->findAll<TileTextureComponent>([&](Entity* e) {
        TileTextureComponent* tile = e->get<TileTextureComponent>();
        PositionComponent* pos = e->get<PositionComponent>();
        TransformComponent* trans = e->get<TransformComponent>();
        
        SDL_Rect clip;
        clip.x = tile->x; // define x position in sprite
        clip.y = tile->y; // define y position in sprite
        clip.w = tile->w; // width of the clipped area
        clip.h = tile->h; // width of the clipped area
        
        SDL_Rect renderQuad;
        renderQuad.x = pos->x - cam->x; // define x position on viewport
        renderQuad.y = pos->y - cam->y; // define y position on viewport (flip y coords)
        renderQuad.w = trans->w; // scaled width
        renderQuad.h = trans->h; // scaled height
        
        SDL_RenderCopyEx(renderer, tileSprite, &clip, &renderQuad, tile->rotation, NULL, SDL_FLIP_NONE);
    });
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}

void RenderSystem::handleEvent(SDL_Event& event, World* world)
{
};

void RenderSystem::onRemovedFromWorld(World* world)
{
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(playerSprite);

    window = nullptr;
    renderer = nullptr;
    playerSprite = nullptr;
    tileSprite = nullptr;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


