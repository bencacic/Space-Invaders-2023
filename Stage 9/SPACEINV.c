#include "SPACEINV.h"

UINT8 buffer[32256];
extern int vbl_music_timer;


int main () {

    
    void *base = Physbase(); 

    /*
    UINT16 *base = get_video_base();
    */
    
    void *second_base = align_base(buffer);

    disable_cursor();

    clear();
    install_vbl_vector();
    while (1) {
        menu((UINT32* )base);
        game_start(base, second_base); 
    }
    uninstall_vbl_vector();
    return 0;
}
    
void game_start(UINT16 *base, UINT16 *second_base) {

    UINT32 curr_clock;
    UINT32 old_clock = 0;
    UINT32 time;
    UINT32 musictime = 0;

    UINT8 input;
    BOOL move = TRUE;
    UINT16 buffer_num = 1;

    Laser laser;
    Laser_Cannon laser_cannon;
    Invader invader;
    Score score;
    Game game;

    init_laser_cannon(&laser_cannon);
    init_armada(&invader);
    init_score(&score);
    init_laser(&laser);
    init_game(&game);

    render_master(base, &laser_cannon, &laser, &invader, &score);
    start_music();
    
    while(game.game_over == FALSE) {
        if(Cconis()) {
            input = (char)Cnecin();
            async_ev(&laser_cannon, &laser, input);
        }   

        curr_clock = game_clock();
        time = curr_clock - old_clock; 

        if (update_music(vbl_music_timer))
            vbl_music_timer = 0;
        
           

        if (time > 0)
        {      
            

            sync_ev(&invader, &laser, &score, &laser_cannon, &game);
                if (buffer_num == 1) {

                    clear_screen(base);

                    render_master(base, &laser_cannon, &laser, &invader, &score);

                    Setscreen(-1, base, -1);
                    Vsync();

                    buffer_num = 0;
                } 
                else if (buffer_num == 0) {

                    clear_screen(second_base);

                    render_master(second_base, &laser_cannon, &laser, &invader, &score);

                    Setscreen(-1, second_base, -1);
                    Vsync();

                     
 
                    buffer_num = 1;
                }
            
            }
        } 
    old_clock = curr_clock; 
    render_master(base, &laser_cannon, &laser, &invader, &score); /*Render very last updated frame because if the player is hit 3 times, it updates first in the model and
    then terminates the game while still displaying 1 life left because render_master() isn't called until next iteration of the loop.*/

    clear_screen(base);

    Setscreen(-1, base, -1);
    Vsync();
    stop_sound();
    return;
    }

void sync_ev (Invader *invader, Laser *laser, Score *score , Laser_Cannon *laser_cannon, Game *game ) {

    move_laser(laser);
    hit_det_on_armada(invader, laser, score, game);
    hit_det_on_player(laser_cannon, laser, game);
    boundary_checker(invader);
    
    if (invader->x == laser_cannon->x) {
        Alien_fires_laser(invader, laser);
    }

    if (invader->move == TRUE ) { 
        switch (invader->dir)
        {
            case 0:
                if((invader->x + invader->left) > MIN_X) {
                    invader->delta_x = -1;
                    invader->delta_y = 0;
                    move_invaders(invader);
                    if ((invader->x + invader->left) == MIN_X) {
                        invader->dir = 1;
                        invader->delta_y = 3;
                        move_invaders_down(invader);
                    }
                }
                break;

            case 1:
                if((invader->x + invader->right) < MAX_X) {
                    invader->delta_x = 1;
                    invader->delta_y = 0;
                    move_invaders(invader);
                    if ((invader->x + invader->right) == MAX_X) { 
                        invader->dir = 0;
                        invader->delta_y = 3;
                        move_invaders_down(invader);
                    }
                }
                break; 
        } 
        invader->move = FALSE;
    }
    else 
    {
        invader->move = TRUE;
    }

    if (invader->delta_y > 0) {
        find_bottom_of_armada(invader);
        if((invader->y + (invader->bottom * ALIEN_HEIGHT)) >= CANNON_Y) {
            game->game_over = TRUE;
        }
    }
}

void async_ev ( Laser_Cannon *laser_cannon, Laser *laser, char input ) {

    if( input == 'a') 
    {  
        laser_cannon->delta_x = -1; 
        Laser_cannon_input(laser_cannon);
    }
    if ( input == 'd') 
    {
        laser_cannon->delta_x = 1;
        Laser_cannon_input(laser_cannon);
    }
    if (input == ' ') {

        Player_laser_input(laser_cannon, laser);
    }
    
    return;

}

void menu(UINT32 *base) {

    while (Cconis() == 0) {
        render_splash((UINT32*) base);
    }

}

UINT32 game_clock() {

    UINT32 curr_clock;
    UINT32 old_ssp;

    old_ssp = Super(0);
    curr_clock = *((UINT32 *)0x462);
    Super(old_ssp);

    return curr_clock;

}

UINT8 *align_base(UINT8 *buffer) {

    UINT8 *base;
    UINT16 offset;
    base = buffer;
    offset = (UINT16)base;
    offset %= BYTE_BOUNDARY;
    offset = BYTE_BOUNDARY - offset;
    
    return base + offset;

}