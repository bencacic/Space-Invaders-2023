#include "music.h"

int note_playing = 0;
int duration;

const tones imperial_march[] = {
   /* bar 1 and 2 good*/
    {0,  0.1},
    {79.75, 7.5},
    {0,  0.1},
    {79.75, 7.5},
    {0,  0.1},
    {79.75, 7.5},
    {100.5, 5.625},
    {67, 1.875},
    {79.75, 7.5},
    {100.5, 5.625},
    {67, 1.875},
    {79.75, 15},
    
    /*bar 3 and 4 good*/
    {53.25, 7.5},
    {0,  0.1},
    {53.25, 7.5},
    {0,  0.1},
    {53.25, 7.5},
    {50.25, 5.625},
    {67, 1.875},
    {84.5, 7.5},
    {100.5, 5.625},
    {67, 1.875},
    {79.75, 15},
    
    /*bar 5  good */
    {39.875, 7.5},
    {79.75, 5.625},
    {0,  0.1},
    {79.75, 1.875},
    {39.875, 7.5},
    {42.25, 5.625},
    {44.75, 1.875},
    
    /*bar 6 good*/
    {47.375, 1.875},
    {50.25, 1.875}, 
    {47.375, 3.75}, 
    {0, 3.75}, 
    {75.25, 3.75},
    {56.375, 7.5},
    {59.75, 5.625},
    {63.25, 1.875},
    
    /* bar 7 good*/
    {67, 1.875},
    {71, 1.875},
    {67, 3.75},
    {0,  3.75},
    {100.5, 3.75},
    {84.5, 7.5},
    {100.5, 5.625},
    {84.5, 1.875},
    
    /* bar 8 good*/
    {67, 7.5},
    {79.75, 5.625},
    {67, 1.875},
    {53.25, 15},
    
    /*bar 9 good*/
    {39.875, 7.5},
    {79.75, 5.625},
    {0,  0.1},
    {79.75, 1.875},
    {39.875, 7.5},
    {42.25, 5.625},
    {44.75, 1.875},
    
    /*bar 10 good*/
    {47.375, 1.875},
    {50.25, 1.875},
    {47.375, 3.75},
    {0, 3.75},
    {75.25, 3.75},
    {56.375 ,7.5},
    {59.75 ,5.625},
    {63.25, 1.875},
    
    /*bar 11 good*/
    {67, 1.875},
    {71, 1.875},
    {67, 3.75},
    {0, 3.75},
    {100.5, 3.75},
    {84.5, 7.5},
    {100.5, 5.625},
    {67, 1.875},
    
    /*bar 12 good*/
    {79.75, 7.5},
    {100.5, 5.625},
    {67, 1.875},
    {79.75, 15},
    {0, 2.5}
};

void start_music(){
    
    int volume = 10;

    set_tone(CHANNEL_C, imperial_march[note_playing].period);
    enable_channel(CHANNEL_C, 1, 0);
    set_volume(CHANNEL_C, volume);
    duration = imperial_march[note_playing].duration;
    note_playing++;
}

void update_music(UINT32 time_elapsed){

    duration--; 
    
    if(duration <= 0){
        
        set_tone(CHANNEL_C, imperial_march[note_playing].period);
        duration = imperial_march[note_playing].duration;
        note_playing++;

        if(note_playing == 77){
             note_playing = 0;
        
        } 
            
    }
    
}
