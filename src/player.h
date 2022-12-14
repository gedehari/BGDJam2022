#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <raylib.h>

#include "core/sprite.h"
#include "crate.h"
#include "chest.h"
#include "cLDtk.h"

#define PLAYER_ACCEL_SPEED 0.08
#define PLAYER_DEACCEL_SPEED 0.1
#define PLAYER_MAX_SPEED 1.35
#define PLAYER_TERMINAL_VELOCITY 4

typedef enum
{
    PLAYERCHAR_0,
    PLAYERCHAR_1
} PlayerCharacter;

typedef struct Player
{
    Vector2 position;
    Vector2 respawn_position;
    Vector2 velocity;

    Sprite* sprite;

    PlayerCharacter character;

    enum { PLAYER_IDLE, PLAYER_MOVING } state;

    Vector2 level_size;
    Rectangle door_rect;

    int current_frame;
    int frames_counter;
    int frame_speed;

    bool hurt_anim;
    int hurt_timer;

    bool dashing;
    Vector2 dash_direction;
    int dash_frames;

    unsigned int max_hp;
    unsigned int hp;

    bool touching_ground;
    bool jump_used;
    bool dash_used;

    int keys_collected;
    int keys_target;
} Player;

Player* player_new(PlayerCharacter player_character);
void player_update(Player* player,
    struct layerInstances* map_col_layer, struct layerInstances* map_spikes,
    Crate** crates_ptr, int crate_size, Chest** chest_ptr, int chest_size);
void player_draw(Player* player);
void player_destroy(Player* player);

#endif
