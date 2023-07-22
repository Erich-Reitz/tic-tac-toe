

#include <SDL2/SDL.h>

#define BLACK 0, 0, 0, 0
#define WHITE 255, 255, 255, 255
#define BLUE 173, 216, 230, 255


class TicTacToeSquare {
  public:
    TicTacToeSquare(SDL_Point center, int squareWidth) {
        area.x = center.x - squareWidth / 2;
        area.y = center.y - squareWidth / 2;
        area.w = squareWidth;
        area.h = squareWidth;
    }
    ~TicTacToeSquare() = default;

    SDL_Rect Area() const {
        return area;
    }

    void render(SDL_Renderer *renderer) {
        // Draw the square
        SDL_RenderFillRect(renderer, &area);
    }

  private:

    SDL_Rect area = {0, 0, 0, 0};


};