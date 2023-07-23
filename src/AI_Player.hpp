#pragma once

#include "TicTacToeBoard.hpp"

class AI_Player {
  public:
    AI_Player(SharedContext *p_context) : context(p_context), selectedState(p_context->aiState) {};

    void MakeMove(TicTacToeBoard &board) {
        const auto rows = context->config->ROWS;
        const auto cols = context->config->COLS;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                const  auto pos = tt::Position{i, j} ;
                if (!board.IsOccupied(pos )) {
                    board.PerformTurn(pos, selectedState);
                    return;
                }
            }
        }
    }
  private:
    SharedContext *context = nullptr;
    const SquareState selectedState;
} ;