
#include <SDL2/SDL.h>

#include "Shared_Context.hpp"
#include "TicTacToeBoard.hpp"

#define SQUARE_WIDTH 100

namespace tic_tac {

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
    this->lines = tic_tac::createLines(center, SQUARE_WIDTH);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            const auto centerOfSquare = SDL_Point{center.x + (j - 1) *SQUARE_WIDTH, center.y + (i - 1) *SQUARE_WIDTH};
            squares[i][j] = std::make_unique<TicTacToeSquare>(centerOfSquare, SQUARE_WIDTH);
        }
    }
}

void TicTacToeBoard::Render(SDL_Renderer *renderer) {
    /** TODO: Add some kind of Z-indexing to not have to get the order right **/

    renderSquares(renderer);
    renderLines(renderer);

}

void TicTacToeBoard::renderLines(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, WHITE);
    for (auto &line : lines) {
        SDL_RenderFillRect(renderer, &line);
    }
}

void TicTacToeBoard::renderSquares(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, BLACK);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            const auto &square = squares.at(i).at(j);
            square->render(renderer);
        }
    }
}
