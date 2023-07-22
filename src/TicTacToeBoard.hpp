#include <array>

#include <SDL2/SDL.h>

#include <memory>
#include <iostream>
#include <vector>

#include "TicTacToeSquare.hpp"
#include "Shared_Context.hpp"
#include "Config.hpp"


class TicTacToeBoard {
  public:

    TicTacToeBoard(SharedContext *sharedContext);
    void Render(SDL_Renderer *renderer) ;

    ~TicTacToeBoard() = default;
  private:
    void renderSquares(SDL_Renderer *renderer) ;
    void renderLines(SDL_Renderer *renderer) ;

    std::array<std::array<std::unique_ptr<TicTacToeSquare>, tt::Config::COLS>, tt::Config::ROWS> squares;
    SharedContext *context = nullptr;
    std::vector<SDL_Rect> lines;

};