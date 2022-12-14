#include "state_menu.h"

#include <raylib.h>
#include <math.h>

#include "../constants.h"
#include "../global_resources.h"
#include "../player.h"
#include "state.h"
#include "state_main.h"
#include "../core/sprite.h"
#include "../core/tween.h"

static const char* text1s = "CHOOSE YOUR CHARACTER";
static Vector2 text1p;

static const char* text2s = "(pick with arrow key)";
static Vector2 text2p;

static Player* char0;
static Player* char1;

static Tween* fade_tween;
static float fade_alpha_progress = 1;

static Music bgm;

static bool selected = false;

static void _on_fade_tween_finished(void);

void state_menu_enter()
{
    selected = false;

    Vector2 text1m = MeasureTextEx(gr_medium_font, text1s, gr_medium_font.baseSize, 0);
    text1p = (Vector2) { floorf((INIT_VIEWPORT_WIDTH - text1m.x) * 0.5), floorf((INIT_VIEWPORT_HEIGHT - text1m.y) * 0.5) - 5 };

    Vector2 text2m = MeasureTextEx(gr_small_font, text2s, gr_medium_font.baseSize, 0);
    text2p = (Vector2) { floorf((INIT_VIEWPORT_WIDTH - text2m.x) * 0.5), floorf((INIT_VIEWPORT_HEIGHT - text2m.y) * 0.5)+ 5 };

    char0 = player_new(PLAYERCHAR_0);
    char0->sprite->position.x = 50;
    char0->sprite->position.y = text2p.y + 9;

    char1 = player_new(PLAYERCHAR_1);
    char1->sprite->position.x = INIT_VIEWPORT_WIDTH - 50;
    char1->sprite->position.y = text2p.y + 9;

    fade_tween = tween_new(&fade_alpha_progress, 1, 0, 2, EASE_LINEAR);
    fade_tween->on_tween_finished_ptr = &_on_fade_tween_finished;
    tween_start(fade_tween);

    bgm = LoadMusicStream("./resources/bgm/i_have_a_vision.xm");
    PlayMusicStream(bgm);
    SetMusicVolume(bgm, 0.0);
}

void state_menu_update()
{
    UpdateMusicStream(bgm);
    SetMusicVolume(bgm, 1.0 - fade_alpha_progress);

    if (!selected)
    {
        bool left_sel = IsKeyPressed(KEY_LEFT);
        bool right_sel = IsKeyPressed(KEY_RIGHT);

        if (left_sel)
            chosen_character = 0;
        else if (right_sel)
            chosen_character = 1;

        if (left_sel || right_sel)
        {
            //state_switchto(STATE_MAIN);
            selected = true;

            fade_tween->from = 0;
            fade_tween->to = 1;
            tween_start(fade_tween);
        }
    }

    tween_update(fade_tween);
}

void state_menu_draw()
{
    ClearBackground(BLACK);
    DrawTextEx(gr_medium_font, text1s, text1p, gr_medium_font.baseSize, 0, WHITE);
    DrawTextEx(gr_small_font, text2s, text2p, gr_medium_font.baseSize, 0, WHITE);
    DrawTextEx(gr_small_font, "<-", (Vector2) { char0->sprite->position.x - 3, char0->sprite->position.y }, gr_medium_font.baseSize, 0, WHITE);
    DrawTextEx(gr_small_font, "->", (Vector2) { char1->sprite->position.x - 3, char1->sprite->position.y }, gr_medium_font.baseSize, 0, WHITE);
    player_draw(char0);
    player_draw(char1);
    if (fade_alpha_progress != 0)
        DrawRectangle(0, 0, INIT_VIEWPORT_WIDTH, INIT_VIEWPORT_HEIGHT, (Color) { 0, 0, 0, (unsigned char)(fade_alpha_progress * 255) });
}

void state_menu_exit()
{
    player_destroy(char1);
    player_destroy(char0);
    UnloadMusicStream(bgm);
    tween_destroy(fade_tween);
    fade_tween = NULL;
    fade_alpha_progress = 0.0;
}

static void _on_fade_tween_finished(void)
{
    if (selected)
        state_switchto(STATE_MAIN);
}
