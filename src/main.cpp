
#include <SDL2/SDL.h>
#include <stdio.h>
#include "iostream"


#include "flush_exit_failure.hpp"
#include "Game.hpp"


namespace tic_tac_toe {

void SDL_INIT() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        flush_exit_failure();
    }
}

int main() {
    //Initialize SDL
    SDL_INIT();
    Game game;
    while(!game.GetWindow()->Done()) {
        game.HandleInput();
        game.Update();
        game.Render();
    }
    //Quit SDL subsystems
    SDL_Quit();
    return EXIT_SUCCESS;
}
}

int main() {
    tic_tac_toe::main();
}