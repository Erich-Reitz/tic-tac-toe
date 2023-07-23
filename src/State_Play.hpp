#pragma once


#include "BaseState.hpp"
#include "TicTacToeBoard.hpp"
#include "AI_Player.hpp"

class State_Play : public BaseState {
  public:
    State_Play(StateManager *p_stateManager);
    ~State_Play();

    void OnCreate();
    void OnDestroy();

    void Activate();
    void Deactivate();

    void Update() ;
    void Render() ;

  private:
    void handleClick(SDL_Point point);
    AI_Player ai;
    std::unique_ptr<TicTacToeBoard> board;
};