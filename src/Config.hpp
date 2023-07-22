#pragma once

#include <SDL2/SDL.h>

#define M_BLACK 0, 0, 0, 0
#define M_WHITE 255, 255, 255, 255
#define M_BLUE 173, 216, 230, 255


namespace tt {
class Config {
  public:
    Config() : WHITE{M_WHITE}, BLUE{M_BLUE}, BLACK{M_BLACK} {};
    static constexpr int ROWS = 3;
    static constexpr int COLS = 3;
    static constexpr int SQUARE_WIDTH = 100;
    static constexpr int LINE_THICKNESS = 3;

    const SDL_Color WHITE;
    const SDL_Color BLUE;
    const SDL_Color BLACK ;

    SDL_Color BackgroundColor() {
        return BLUE;
    }

    SDL_Color LineColor() {
        return WHITE;
    }

    SDL_Color SquareColor() {
        return BLACK;
    }
};


}