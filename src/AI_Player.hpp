#pragma once

#include <utility>
#include "TicTacToeBoard.hpp"

class AI_Player {
  public:
    AI_Player(SharedContext *p_context) : context(p_context), selectedState(p_context->aiState) {};


    void MakeMove(TicTacToeBoard &board) {
        const auto bestMovePos = findBestMove(board);
        board.PerformTurn(bestMovePos, selectedState);
    }
  private:
    int minimax(TicTacToeBoard &board, int depth,  bool isMaximizingPlayer) {
        const auto gameState = board.GetGameState();
        if (gameState == GameState::AI_WON) {
            return 100 - depth;
        } else if (gameState == GameState::USER_WON) {
            return -100 + depth;
        } else if (gameState == GameState::DRAW) {
            return 0;
        }
        if (isMaximizingPlayer) {
            int value = -10000;
            for (const auto pos : board.FreeSquares()) {
                board.PerformTurn(pos, selectedState);
                value = std::max(value, minimax(board, depth + 1, false));
                board.PerformTurn(pos, SquareState::EMPTY);
            }
            return value;
        } else {
            int value = 10000;
            for (const auto pos : board.FreeSquares()) {
                board.PerformTurn(pos, context->userRequestedState);
                value = std::min(value, minimax(board, depth + 1, false));
                board.PerformTurn(pos, SquareState::EMPTY);
            }
            return value;
        }
    }
    tt::Position findBestMove(TicTacToeBoard &board) {
        std::pair<tt::Position, int> currentBest = std::make_pair(tt::Position {-1, -1}, -10000) ;
        for (const auto pos : board.FreeSquares()) {
            board.PerformTurn(pos, selectedState);
            int eval = minimax(board, 0, false);
            board.PerformTurn(pos, SquareState::EMPTY);
            if (eval > currentBest.second) {
                currentBest = std::make_pair(pos, eval);
            }
        }
        return currentBest.first;
    }


    SharedContext *context = nullptr;
    const SquareState selectedState;
} ;