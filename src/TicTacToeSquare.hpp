

#include <SDL2/SDL.h>

#include "Position.hpp"
#include "SquareState.hpp"
#include "Config.hpp"
#include "SetRenderDrawColor.hpp"

class TicTacToeSquare {
  public:
    TicTacToeSquare(tt::Position p_pos, SDL_Point center, int squareWidth, SharedContext *p_context) : pos(p_pos), context(p_context) {
        area.x = center.x - squareWidth / 2;
        area.y = center.y - squareWidth / 2;
        area.w = squareWidth;
        area.h = squareWidth;
    }
    ~TicTacToeSquare() = default;

    SDL_Rect Area() const {
        return area;
    }

    void Render(SDL_Renderer *renderer) const {
        switch (state) {
        case tt::SquareState::X:
            tt::SetRenderDrawColor(renderer, context->config->XColor());
            break;
        case tt::SquareState::O:
            tt::SetRenderDrawColor(renderer, context->config->OColor());
            break;
        case tt::SquareState::EMPTY:
            tt::SetRenderDrawColor(renderer, context->config->SquareColor());
            break;
        }
        SDL_RenderFillRect(renderer, &area);
    }

    bool WithinBounds(SDL_Point point) const {
        return SDL_PointInRect(&point, &area);
    }

    tt::Position Position() const {
        return pos;
    }

    bool IsOccupied() const {
        return state != tt::SquareState::EMPTY;
    }

    void SetOccupiedBy(tt::SquareState newState) {
        state = newState;
    }

  private:
    tt::Position pos;
    SDL_Rect area = {0, 0, 0, 0};
    tt::SquareState state = tt::SquareState::EMPTY;
    SharedContext *context = nullptr;


};