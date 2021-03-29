#ifndef player_h
#define player_h

#include "world.h"

class PlayerSystem : public System
{
public:
    PlayerSystem();

    void onAddedToWorld(World* world) override;

    void tick(World* world) override;

    void handleEvent(SDL_Event& event, World* world) override;

    void onRemovedFromWorld(World* world) override;

    ~PlayerSystem() = default;
};

#endif /* player_h */
