#ifndef _STATE_MAIN_H_
#define _STATE_MAIN_H_

void state_main_enter();
void state_main_update();
void state_main_draw();
void state_main_exit();

void state_main_next_level();
void state_main_game_over();

extern int chosen_character;

#endif
