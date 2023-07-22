

#include <SDL2/SDL.h>

#include "Position.hpp"


class TicTacToeSquare {
  public:
    TicTacToeSquare(tt::Position p_pos, SDL_Point center, int squareWidth) : pos(p_pos) {
        area.x = center.x - squareWidth / 2;
        area.y = center.y - squareWidth / 2;
        area.w = squareWidth;
        area.h = squareWidth;
    }
    ~TicTacToeSquare() = default;

    SDL_Rect Area() const {
        return area;
    }

    void render(SDL_Renderer *renderer) const {
        // Draw the square
        SDL_RenderFillRect(renderer, &area);
    }

    bool WithinBounds(SDL_Point point) const {
        return SDL_PointInRect(&point, &area);
    }

    tt::Position Position() const {
        return pos;
    }

  private:
    tt::Position pos;
    SDL_Rect area = {0, 0, 0, 0};


};