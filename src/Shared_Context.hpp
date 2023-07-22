#pragma once

#include <deque>

#include "Window.hpp"
#include "Config.hpp"

class Window;
class Config;

enum class GameState {
    PLAYING
};

struct SharedContext {
    SharedContext():
        window(nullptr), config(nullptr) {};

    SDL_Color BackgroundColor() {
        return config->BackgroundColor();
    }

    void AddMouseClick(SDL_Point point) {
        mouseClicks.emplace_back(point);
    }


    Window *window;
    tt::Config *config;
    GameState gameState = GameState::PLAYING;

    std::deque<SDL_Point> mouseClicks = {};

};