#pragma once

#include <deque>

#include "Window.hpp"
#include "Config.hpp"

class Window;

struct SharedContext {
    SharedContext():
        window(nullptr), config(nullptr) {};


    void AddMouseClick(SDL_Point point) {
        mouseClicks.emplace_back(point);
    }


    Window *window;
    tt::Config *config;

    std::deque<SDL_Point> mouseClicks = {};

};