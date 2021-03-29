#include "game.h"
#include "components.h"
#include "sprite_ids.h"
#include "player-system.h"
#include "physics-system.h"
#include "render-system.h"
#include "animation-system.h"
#include "camera-system.h"
#include "health-system.h"
#include "tile_map.h"

Scene::Scene()
{
    // Init
    world = new World();
    world->LEVEL_WIDTH = 1000;
    world->LEVEL_HEIGHT = 680;
    world->SCREEN_WIDTH = 680;
    world->SCREEN_HEIGHT = 680;
    std::unordered_map<SPRITE_ID, SpriteCoord> spriteMap = {
        { PLAYER_IDLE_1, SpriteCoord{0, 0, 50, 50} },
        { PLAYER_RUNNING_1, SpriteCoord{0, 50, 50, 50} },
        { PLAYER_RUNNING_2, SpriteCoord{50, 50, 50, 50} },
        { PLAYER_RUNNING_3, SpriteCoord{100, 50, 50, 50} },
        { PLAYER_RUNNING_4, SpriteCoord{150, 50, 50, 50} },
        { PLAYER_RUNNING_5, SpriteCoord{200, 50, 50, 50} },
        { PLAYER_RUNNING_6, SpriteCoord{250, 50, 50, 50} },
        { PLAYER_JUMPING_1, SpriteCoord{0, 100, 50, 50} },
    };
    
    // Systems
    world->registerSystem<PlayerSystem>();
    world->registerSystem<PhysicsSystem>();
    world->registerSystem<RenderSystem>("playerSprite.png", "tileSprite.png", spriteMap);
    world->registerSystem<AnimationSystem>();
    world->registerSystem<CameraSystem>();
    world->registerSystem<HealthSystem>([&] { OnPlayerDeath(); });

    InitEntities();
    
    // Exec
    OnExecute();
};

void Scene::InitEntities()
{
    // Player
    Entity* player = world->create();
    player->assign<PlayerComponent>();
    player->assign<PositionComponent>(30, 500);
    player->assign<TransformComponent>(25, 40);
    player->assign<VelocityComponent>(0, 0, 0);
    player->assign<SpriteComponent>(PLAYER_IDLE_1);
    player->assign<HealthComponent>(100);
    
    // Tiles
    TileMap tileMap(world);
    tileMap.Load("tileMap.json", "tileSet.json");
    
    // Camera
    Entity* camera = world->create();
    camera->assign<CameraComponent>(0, 1000, world->SCREEN_WIDTH, world->SCREEN_HEIGHT);
};

void Scene::OnPlayerDeath()
{
    world->destroyEntities();
    InitEntities();
}

Scene::~Scene()
{
    delete world;
}
