
#include <SDL2/SDL.h>

#include "Shared_Context.hpp"
#include "TicTacToeBoard.hpp"
#include "SetRenderDrawColor.hpp"
#include "Position.hpp"


namespace tt {

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


}


TicTacToeBoard::TicTacToeBoard(SharedContext *sharedContext) : context(sharedContext) {
    auto center = context->window->Center();
    this->lines = tt::createLines(center, tt::Config::SQUARE_WIDTH, tt::Config::LINE_THICKNESS);
    for (int row = 0; row < tt::Config::ROWS; row++) {
        for (int col = 0; col < tt::Config::COLS; col++) {
            tt::Position pos = {row, col};
            auto squareX = center.x + (col - 1) *tt::Config::SQUARE_WIDTH;
            auto squareY = center.y + (row - 1) *tt::Config::SQUARE_WIDTH;
            const auto centerOfSquare = SDL_Point{squareX, squareY};
            squares[row][col] = std::make_unique<TicTacToeSquare>(pos, centerOfSquare, tt::Config::SQUARE_WIDTH);
        }
    }
}



void TicTacToeBoard::Update() {
    while (context->mouseClicks.size() != 0) {
        auto click = context->mouseClicks.front();
        HandleClick(click);
        context->mouseClicks.pop_front();
    }
}

void TicTacToeBoard::HandleClick(SDL_Point point) {
    for (const auto &square : Squares()) {
        if (square.get().WithinBounds(point)) {
            // this->handleClickOnSquare(square.get().Position());
        }
    }
}

std::vector<std::reference_wrapper<const TicTacToeSquare>> TicTacToeBoard::Squares() const {
    std::vector<std::reference_wrapper<const TicTacToeSquare>> flattened;
    flattened.reserve(tt::Config::ROWS * tt::Config::COLS);
    for (const auto &row : this->squares) {
        for (const auto &elem : row) {
            flattened.emplace_back(*elem);
        }
    }
    return flattened;
}

void TicTacToeBoard::Render(SDL_Renderer *renderer) const {
    /** TODO: Add some kind of Z-indexing to not have to get the order right **/
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
    tt::SetRenderDrawColor(renderer, context->config->SquareColor() );
    for (const auto &square : Squares()) {
        square.get().render(renderer);
    }
}
