
#include <SDL2/SDL.h>

#include <algorithm>
#include <iterator>

#include "tictactoe_exceptions.hpp"
#include "Shared_Context.hpp"
#include "TicTacToeBoard.hpp"
#include "SetRenderDrawColor.hpp"
#include "Position.hpp"





typedef std::pair<SDL_Point, SDL_Point> LINE;
SDL_Rect createRectFromLine(SDL_Point start, SDL_Point end, int thickness) {
    SDL_Rect rect;
    if (start.x == end.x) { // If the line is vertical
        rect.x = start.x - thickness / 2;
        rect.y = std::min(start.y, end.y);
        rect.w = thickness;
        rect.h = std::abs(start.y - end.y);
    } else if (start.y == end.y) { // If the line is horizontal
        rect.x = std::min(start.x, end.x);
        rect.y = start.y - thickness / 2;
        rect.w = std::abs(start.x - end.x);
        rect.h = thickness;
    }
    return rect;
}

std::vector<LINE> generateLinesForBoard(SDL_Point center, int squareWidth) {
    const int halfSqrWidth = squareWidth / 2 ;
    const int squareAndHalfWid = static_cast<int>(squareWidth + halfSqrWidth);
    return {
        {{center.x + halfSqrWidth, center.y + squareAndHalfWid}, {center.x + halfSqrWidth, center.y - squareAndHalfWid}},
        {{center.x - halfSqrWidth, center.y + squareAndHalfWid}, {center.x - halfSqrWidth, center.y - squareAndHalfWid}},
        {{center.x - squareAndHalfWid, center.y + halfSqrWidth}, {center.x + squareAndHalfWid, center.y + halfSqrWidth}},
        {{center.x - squareAndHalfWid, center.y - halfSqrWidth}, {center.x + squareAndHalfWid, center.y - halfSqrWidth}}
    };
}

std::vector<SDL_Rect> createLines( SDL_Point center, int squareWidth, int thickness = 3) {
    const auto points = generateLinesForBoard(center, squareWidth);
    std::vector<SDL_Rect> rects;
    for (const auto &pointPair : points) {
        rects.emplace_back(createRectFromLine(pointPair.first, pointPair.second, thickness));
    }
    return rects;
}





TicTacToeBoard::TicTacToeBoard(SharedContext *sharedContext) : context(sharedContext), gameState(GameState::PLAYING) {
    auto center = context->window->Center();
    this->lines = createLines(center, Config::SQUARE_WIDTH, Config::LINE_THICKNESS);
    for (int row = 0; row < Config::ROWS; row++) {
        for (int col = 0; col < Config::COLS; col++) {
            tt::Position pos = {row, col};
            auto squareX = center.x + (col - 1) *Config::SQUARE_WIDTH;
            auto squareY = center.y + (row - 1) *Config::SQUARE_WIDTH;
            const auto centerOfSquare = SDL_Point{squareX, squareY};
            auto const adjustedSqrWidth = static_cast<int> (Config::SQUARE_WIDTH * .98);
            squares[row][col] = std::make_unique<TicTacToeSquare>(pos, centerOfSquare, adjustedSqrWidth, context);
        }
    }
}



GameState TicTacToeBoard::GetGameState() const {
    return gameState;
}

void TicTacToeBoard::Update() {
}

std::optional<tt::Position> TicTacToeBoard::SquareOnBoard(SDL_Point point) const {
    for (const auto &square : allSquares()) {
        if (square.get().WithinBounds(point)) {
            return square.get().Position();
        }
    }
    return std::nullopt;
}

/** Use carefully: this will change turn*/
void TicTacToeBoard::PerformTurn(const tt::Position &pos, SquareState state ) {
    squareAt(pos).SetOccupiedBy(state);
    determineIfGameIsOver();
}

void TicTacToeBoard::determineIfGameIsOver()  {
    for (int r = 0; r < Config::ROWS; r++) {
        if (std::all_of(squares[r].begin(), squares[r].end(), [&](const auto &squarePtr) {
        const auto firstSqrState = squares[r][0]->State();
            return squarePtr->State() == firstSqrState && squarePtr->NotEmpty();
        })) {
            setWinnerFromSquareState(r, 0);
            return;
        }
    }
    for (int c = 0; c < Config::COLS; c++) {
        if (std::all_of(squares.begin(), squares.end(), [&](const auto &row) {
        const auto firstSqrState = squares[0][c]->State();
            return row[c]->State() == firstSqrState && row[c]->NotEmpty();
        })) {
            setWinnerFromSquareState(0, c);
            return;
        }
    }
    bool mainDiagonal = true;
    for (int i = 0; i < Config::ROWS; ++i) {
        if (squares[i][i]->State() != squares[0][0]->State() || squares[i][i]->IsEmpty() ) {
            mainDiagonal = false;
            break;
        }
    }
    if (mainDiagonal) {
        setWinnerFromSquareState(0, 0);
        return;
    }
    bool secondaryDiagonal = true;
    for (int i = 0; i < Config::ROWS; ++i) {
        if (squares[i][Config::COLS - i - 1]->State() != squares[0][Config::COLS - 1]->State() || squares[i][Config::COLS - i - 1]->IsEmpty() ) {
            secondaryDiagonal = false;
            break;
        }
    }
    if (secondaryDiagonal) {
        setWinnerFromSquareState(0, Config::COLS - 1);
        return;
    }
    if (std::all_of(squares.begin(), squares.end(), [&](const auto &row) {
    return std::all_of(row.begin(), row.end(), [](const auto &squarePtr) {
        return squarePtr->NotEmpty();
        });
    })) {
        gameState = GameState::DRAW;
        return;
    }
    gameState = GameState::PLAYING;
}

void TicTacToeBoard::setWinnerFromSquareState(int i, int j) {
    if (squareAt(i, j).State() == context->userRequestedState) {
        gameState = GameState::USER_WON;
    } else {
        gameState = GameState::AI_WON;
    }
}


bool TicTacToeBoard::IsOccupied(const tt::Position &pos) const {
    return squareAt(pos).IsOccupied();
}


TicTacToeSquare &TicTacToeBoard::squareAt(const tt::Position &pos) const {
    return *squares.at(pos.r).at(pos.c);
}

TicTacToeSquare &TicTacToeBoard::squareAt(int r, int c) const {
    return *squares.at(r).at(c);
}


bool TicTacToeBoard::IsOver() const {
    return gameState != GameState::PLAYING;
}

std::vector<tt::Position> TicTacToeBoard::FreeSquares() const {
    std::vector<tt::Position> freeSquares;
    for (const auto &square : allSquares()) {
        if (!square.get().IsOccupied()) {
            freeSquares.push_back(square.get().Position());
        }
    }
    return freeSquares;
}

std::vector<std::reference_wrapper<const TicTacToeSquare>> TicTacToeBoard::allSquares() const {
    std::vector<std::reference_wrapper<const TicTacToeSquare>> flattened;
    flattened.reserve(Config::ROWS * Config::COLS);
    for (const auto &row : this->squares) {
        for (const auto &elem : row) {
            flattened.emplace_back(*elem);
        }
    }
    return flattened;
}

void TicTacToeBoard::Render() const {
    /** TODO: Add some kind of Z-indexing to not have to get the order right **/
    auto renderer = context->window->Renderer();
    renderSquares(renderer);
    renderLines(renderer);
}

void TicTacToeBoard::renderLines(SDL_Renderer *renderer) const {
    tt::SetRenderDrawColor(renderer, context->config->LineColor() );
    for (auto &line : lines) {
        SDL_RenderFillRect(renderer, &line);
    }
}

void TicTacToeBoard::renderSquares(SDL_Renderer *renderer) const {
    for (const auto &square : allSquares()) {
        square.get().Render(renderer);
    }
}
