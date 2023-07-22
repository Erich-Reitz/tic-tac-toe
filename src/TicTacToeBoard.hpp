#include <array>

#include <SDL2/SDL.h>

#include <memory>
#include <iostream>
#include <vector>

#include "TicTacToeSquare.hpp"
#include "Shared_Context.hpp"
#include "Config.hpp"
#include "Position.hpp"


class TicTacToeBoard {
  public:

    TicTacToeBoard(SharedContext *sharedContext);
    void Render(SDL_Renderer *renderer) const;
    void Update() ;

    ~TicTacToeBoard() = default;
  private:
    void renderSquares(SDL_Renderer *renderer) const;
    void renderLines(SDL_Renderer *renderer) const;
    void handleClick(SDL_Point point) ;
    void handleClickOnSquare(const tt::Position &pos);
    std::vector<std::reference_wrapper<const TicTacToeSquare>> allSquares() const ;

    std::array<std::array<std::unique_ptr<TicTacToeSquare>, tt::Config::COLS>, tt::Config::ROWS> squares;
    SharedContext *context = nullptr;
    std::vector<SDL_Rect> lines;
    bool currentPlayerIsX = true;

};