#pragma once

#include <memory>


#include "BaseState.hpp"
#include "TicTacToeBoard.hpp"

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

    void MainMenu();


  private:
    std::unique_ptr<TicTacToeBoard> board;
    int player;
};