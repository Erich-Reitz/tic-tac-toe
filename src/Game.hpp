#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Window.hpp"
#include "TicTacToeBoard.hpp"
#include "Shared_Context.hpp"


class Game {
  public:
    Game();
    ~Game() = default;
    void HandleInput();
    void Update();
    void Render();
    Window *GetWindow();


  private:
    std::unique_ptr<TicTacToeBoard> board;
    std::unique_ptr<Window> window;
    SharedContext sharedContext;


};