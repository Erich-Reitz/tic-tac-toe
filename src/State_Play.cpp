#include "State_Play.hpp"
#include "StateManager.hpp"
#include "tictactoe_exceptions.hpp"
#include "TicTacToeBoard.hpp"



State_Play::State_Play(StateManager *p_stateManager)
    : BaseState(p_stateManager) {
    ai = std::make_unique<AI_Player>(p_stateManager->GetContext());
}

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


void State_Play::HandleInput() {
    const auto context = stateMgr->GetContext();
    while (context->mouseClicks.size() != 0) {
        auto click = context->mouseClicks.front();
        handleClick(click);
        context->mouseClicks.pop_front();
    }
}


void State_Play::Update() {
    auto state = board->GetGameState();
    auto context = stateMgr->GetContext();
    switch (state) {
    case GameState::USER_WON:
        context->window->SetDone();
        break;
    case GameState::AI_WON:
        context->window->SetDone();
        break;
    case GameState::DRAW:
        context->window->SetDone();
        break;
    case GameState::PLAYING: {
        if (!usersTurn) {
            ai->MakeMove(*board);
            this->usersTurn = true;
        }
    }
    break;
    default:
        break;
    }
    board->Update();
}

void State_Play::handleClick(SDL_Point point) {
    const auto context = stateMgr->GetContext();
    const auto optClickedPosition = board->SquareOnBoard(point);
    if (!optClickedPosition.has_value()) {
        return;
    }
    const auto clickedPosition = optClickedPosition.value();
    if (board->IsOccupied(clickedPosition)) {
        return;
    }
    board->PerformTurn(clickedPosition, context->userRequestedState) ;
    this->usersTurn = false;
}


void State_Play::Render() {
    this->board->Render();
}

void State_Play::Activate() {}

void State_Play::Deactivate() {}

