#pragma once
#include <array>

#include <SDL2/SDL.h>

#include <memory>
#include <iostream>
#include <vector>
#include <optional>

#include "TicTacToeSquare.hpp"
#include "Shared_Context.hpp"
#include "Config.hpp"
#include "Position.hpp"

enum GameState {
    USER_TURN,
    AI_TURN,
    OVER
} ;

class TicTacToeBoard {
  public:
    TicTacToeBoard(SharedContext *sharedContext);
    void Render() const;
    void Update() ;

    std::optional<tt::Position> SquareOnBoard(SDL_Point point) const;
    void PerformTurn(const tt::Position &pos, SquareState state );
    bool IsOccupied(const tt::Position &pos) const;
    GameState GetGameState() const;

    ~TicTacToeBoard() = default;
  private:
    void renderSquares(SDL_Renderer *renderer) const;
    void renderLines(SDL_Renderer *renderer) const;
    TicTacToeSquare &squareAt(const tt::Position &pos) const;
    std::vector<std::reference_wrapper<const TicTacToeSquare>> allSquares() const ;

    std::array<std::array<std::unique_ptr<TicTacToeSquare>, Config::COLS>, Config::ROWS> squares;
    SharedContext *context = nullptr;
    std::vector<SDL_Rect> lines = {};
    bool currentPlayerIsX = true;
    GameState gameState;


};