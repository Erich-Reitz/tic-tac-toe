#pragma once

#include "BaseState.hpp"
#include "TextObject.hpp"
class State_Menu : public BaseState {
  public:
    explicit State_Menu(StateManager *p_stateManager);
    ~State_Menu();

    void OnCreate();
    void OnDestroy();

    void Activate();
    void Deactivate();

    void Update() ;
    void Render() ;
    void HandleInput() ;

    void Play();
  private:

    void handleClick(SDL_Point point) ;
    TextObject *helloMessage = nullptr;

    TextObject *startMessage  = nullptr;
    TextObject *quitMessage = nullptr;



};