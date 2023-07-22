#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "Window.hpp"
#include "TicTacToeBoard.hpp"
#include "Shared_Context.hpp"
#include "StateManager.hpp"


class Game {
  public:
    Game();
    ~Game() = default;
    void HandleInput();
    void Update();
    void Render();
    Window *GetWindow();


  private:
    void UpdateAndPrintFPS();
    void UpdateWindowAndState();


    std::unique_ptr<Window> window;
    SharedContext sharedContext;
    std::unique_ptr<StateManager> stateMgr;
    int fps = 0;
    int frameCount = 0;
    Uint32 lastFPSTime = 0;


};