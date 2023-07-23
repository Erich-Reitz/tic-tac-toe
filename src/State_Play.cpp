#include "State_Play.hpp"
#include "StateManager.hpp"
#include "tictactoe_exceptions.hpp"
#include "TicTacToeBoard.hpp"



State_Play::State_Play(StateManager *p_stateManager)
    : BaseState(p_stateManager), ai(p_stateManager->GetContext()) {}

State_Play::~State_Play() {}

void State_Play::OnCreate() {
    auto context = stateMgr->GetContext();
    if (context->userRequestedState == SquareState::EMPTY) {
        throw NoOptionSelected();
    }
    this->board = std::make_unique<TicTacToeBoard>(context);
}

void State_Play::OnDestroy() {
}

void State_Play::Update() {
    const auto context = stateMgr->GetContext();
    while (context->mouseClicks.size() != 0) {
        auto click = context->mouseClicks.front();
        handleClick(click);
        context->mouseClicks.pop_front();
    }
    const auto state = board->GetGameState();
    switch (state) {
    case GameState::USER_TURN:
        board->Update();
        break;
    case GameState::AI_TURN:
        ai.MakeMove(*board);
        break;
    case GameState::USER_WON:
        context->window->SetDone();
        break;
    case GameState::AI_WON:
        context->window->SetDone();
        break;
    default:
        break;
    }
}

void State_Play::handleClick(SDL_Point point) {
    const auto context = stateMgr->GetContext();
    if (board->GetGameState() != GameState::USER_TURN) {
        return;
    }
    const auto optClickedPosition = board->SquareOnBoard(point);
    if (!optClickedPosition.has_value()) {
        return;
    }
    const auto clickedPosition = optClickedPosition.value();
    if (board->IsOccupied(clickedPosition)) {
        return;
    }
    board->PerformTurn(clickedPosition, context->userRequestedState) ;
}


void State_Play::Render() {
    this->board->Render();
}

void State_Play::Activate() {}

void State_Play::Deactivate() {}

