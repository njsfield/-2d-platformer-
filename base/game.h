#ifndef game_h
#define game_h

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "world.h"

class Game
{
public:
    World* world;
    bool Running = true;
    const int SCREEN_FPS = 60;
    const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
    int countedFrames = 0;
    
    Game() {};

    int OnExecute();

    bool OnInit();

    void OnEvent(SDL_Event& Event);

    void OnTick();

    void OnCleanup();
};

class Scene : public Game
{
public:
    Scene();
    void InitEntities();
    void OnPlayerDeath();
    void ResetWorld();
    ~Scene();
};

#endif /* game_h */
