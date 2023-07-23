#pragma once

#include <SDL2/SDL.h>

#define M_WHITE 255, 255, 255, 255
#define M_BLUE 173, 216, 230, 255
#define M_LIGHT_PINK 255, 182, 193, 255
#define M_LIGHT_YELLOW 255, 255, 224, 255



class Config {
  public:
    Config() = default;
    static constexpr int ROWS = 3;
    static constexpr int COLS = 3;
    static constexpr int SQUARE_WIDTH = 100;
    static constexpr int LINE_THICKNESS = 3;

    const SDL_Color WHITE = {M_WHITE};
    const SDL_Color BLUE = {M_BLUE};
    const SDL_Color LIGHT_PINK = {M_LIGHT_PINK};
    const SDL_Color LIGHT_YELLOW = {M_LIGHT_YELLOW};


    SDL_Color BackgroundColor() {
        return BLUE;
    }

    SDL_Color LineColor() {
        return WHITE;
    }

    SDL_Color XColor() {
        return LIGHT_PINK;
    }

    SDL_Color OColor() {
        return LIGHT_YELLOW;
    }


};


