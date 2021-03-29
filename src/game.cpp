#include "game.h"
#include "world.h"
#include "timer.h"

int Game::OnExecute()
{
    if (OnInit() == false) return -1;
    
    //The frames per second timer
    Timer fpsTimer;

    //The frames per second cap timer
    Timer capTimer;
    
    fpsTimer.start();
 
    SDL_Event Event;
 
    while(Running) {
        capTimer.start();
        
        while(SDL_PollEvent(&Event)) {
            OnEvent(Event);
        }
        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        {
            avgFPS = 0;
        }
        if (countedFrames > 200000)
        {
            countedFrames = 0;
            fpsTimer.stop();
            fpsTimer.start();
        }

        OnTick();
        
        ++countedFrames;
        int frameTicks = capTimer.getTicks();
        if( frameTicks < SCREEN_TICK_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
        }
    }
    
    printf("true");
 
    OnCleanup();
    return 0;
};

bool Game::OnInit() {
    return true;
};

void Game::OnEvent(SDL_Event& event)
{
    if( event.type == SDL_QUIT) {
        printf("Quitting...");
        Running = false;
    };
    world->handleEvent(event);
}

void Game::OnTick()
{
    world->countedFrames = countedFrames;
    world->tick();
}

void Game::OnCleanup()
{
}

