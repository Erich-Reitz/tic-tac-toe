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
    USER_WON,
    AI_WON,
    DRAW,
} ;

class TicTacToeBoard {
  public:
    TicTacToeBoard(SharedContext *sharedContext);
    void Render() const;
    void Update() ;

    std::optional<tt::Position> SquareOnBoard(SDL_Point point) const;
    void PerformTurn(const tt::Position &pos, SquareState state );
    bool IsOccupied(const tt::Position &pos) const;
    bool IsOver() const;
    GameState GetGameState() const;

    ~TicTacToeBoard() = default;
  private:
    void renderSquares(SDL_Renderer *renderer) const;
    void renderLines(SDL_Renderer *renderer) const;
    TicTacToeSquare &squareAt(const tt::Position &pos) const;
    TicTacToeSquare &squareAt(int r, int c) const;
    std::vector<std::reference_wrapper<const TicTacToeSquare>> allSquares() const ;
    void evaluateNewState();
    void setWinnerFromSquareState(int i, int j) ;

    std::array<std::array<std::unique_ptr<TicTacToeSquare>, Config::COLS>, Config::ROWS> squares;
    SharedContext *context = nullptr;
    std::vector<SDL_Rect> lines = {};

    GameState gameState;


};