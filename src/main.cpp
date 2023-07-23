
#include <SDL2/SDL.h>
#include <cstdio>

#include "flush_exit_failure.hpp"
#include "Game.hpp"



void SDL_INIT() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        flush_exit_failure();
    }
}

void TTF_INIT() {
    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        flush_exit_failure();
    }
}

int tt_main() {

    SDL_INIT();
    TTF_INIT();
    Game game;
    while(!game.GetWindow()->Done()) {
        game.HandleInput();
        game.Update();
        game.Render();
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}


int main() {
    tt_main();
}