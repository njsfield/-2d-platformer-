//
//  components.h
//  ecs
//
//  Created by Nicholas Field on 28/03/2021.
//

#ifndef components_h
#define components_h

#include <unordered_map>
#include "world.h"

struct PlayerComponent : public Component
{
    bool LEFT;
    bool RIGHT;
    bool UP;
    bool DOWN;
    bool forwardFacing = true;
};

struct TileComponent : public Component {};

struct TileTextureComponent : public Component {
    TileTextureComponent(int x, int y, int w, int h, int rotation): x(x), y(y), w(w), h(h), rotation(rotation) {};
    int x, y, w, h, rotation;
};

struct GroundedComponent : public Component {};

struct PositionComponent : public Component
{
    PositionComponent(int x, int y): x(x), y(y) {};
    int x, y;
};

inline std::ostream& operator<< (std::ostream &out, const PositionComponent &position)
{
    out << "Pos: X " << position.x << ", Y " << position.y;
    return out;
}

struct SpriteComponent : public Component
{
    SPRITE_ID spriteId;
    SpriteComponent(SPRITE_ID s): spriteId(s) {};
};

struct VelocityComponent : public Component
{
    VelocityComponent(int velX, int velY, int speed): velX(velX), velY(velY), speed(speed) {};
    int velX, velY, speed;
};

struct TransformComponent : public Component
{
    TransformComponent(int w, int h): w(w), h(h) {};
    int w, h;
};

enum CharacterState {
    Idle,
    Jumping,
    Airborne,
    Running
};
enum CharacterFacing
{
    Left,
    Right
};

struct CharacterComponent : public Component
{
    CharacterState state;
    CharacterFacing facing;
    bool moving;
    CharacterComponent(CharacterState s, CharacterFacing f, bool m)
        : state(s), facing(f), moving(m) {};
};

inline std::ostream& operator<< (std::ostream &out, const CharacterComponent &character)
{
    std::string state;
    std::string facing;
    
    switch(character.state) {
        case Idle: { state = "Idle"; break; }
        case Jumping: { state = "Jumping"; break; }
        case Airborne: { state = "Airborne"; break; }
        case Running: { state = "Running"; break; }
    };
    
    switch(character.facing) {
        case Left: { facing = "Facing Left"; break; }
        case Right: { facing = "Facing Right"; break; }
    };
    
    out << "Char: " << state << ", " << facing << ", " << (character.moving ? "Moving" : "Not Moving");
    return out;
}

struct AnimationComponent : public Component
{
    AnimationComponent(int durationTicks): durationTicks(durationTicks){};
    int durationTicks;
};

struct CameraComponent : public Component
{
    CameraComponent(int x, int y, int w, int h): x(x), y(y), w(w), h(h) {};
    int x, y, w, h;
};

struct HealthComponent : public Component
{
    HealthComponent(int health) : health(health) {}
    int health;
};

#endif /* components_h */
