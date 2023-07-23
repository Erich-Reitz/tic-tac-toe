#pragma once

#include <SDL2/SDL.h>

#include "Position.hpp"
#include "SquareState.hpp"
#include "Config.hpp"
#include "SetRenderDrawColor.hpp"
#include "Shared_Context.hpp"
#include "Object.hpp"

class TicTacToeSquare : public Object {
  public:
    TicTacToeSquare(tt::Position p_pos, SDL_Point center, int squareWidth, SharedContext *p_context) : Object(center, squareWidth, squareWidth,
                p_context),
        pos(p_pos) {
    }
    ~TicTacToeSquare() = default;

    void Render(SDL_Renderer *renderer) const {
        switch (state) {
        case SquareState::X:
            tt::SetRenderDrawColor(renderer, context->config->XColor());
            SDL_RenderFillRect(renderer, &area);
            break;
        case SquareState::O:
            tt::SetRenderDrawColor(renderer, context->config->OColor());
            SDL_RenderFillRect(renderer, &area);
            break;
        default:
            break;
        }
    }

    tt::Position Position() const {
        return pos;
    }

    bool IsOccupied() const {
        return state != SquareState::EMPTY;
    }

    void SetOccupiedBy(SquareState newState) {
        state = newState;
    }

    bool IsEmpty() const {
        return state == SquareState::EMPTY;
    }

    bool NotEmpty() const {
        return !IsEmpty();
    }

    SquareState State() const {
        return state;
    }

  private:
    tt::Position pos = {0, 0};
    SquareState state = SquareState::EMPTY;



};