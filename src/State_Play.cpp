#include "State_Play.hpp"
#include "StateManager.hpp"

#include <iostream>

State_Play::State_Play(StateManager *p_stateManager)
    : BaseState(p_stateManager) {}

State_Play::~State_Play() {}

void State_Play::OnCreate() {
    auto context = stateMgr->GetContext();
    this->board = std::make_unique<TicTacToeBoard>(context);
}

void State_Play::OnDestroy() {
}

void State_Play::Update() {
    this->board->Update();
}


void State_Play::Render() {
    this->board->Render();
}

void State_Play::MainMenu() {
    stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Play::Activate() {}

void State_Play::Deactivate() {}

