#pragma once

#include <deque>

#include "Window.hpp"
#include "Config.hpp"
#include "ResourceManager.hpp"
#include "SquareState.hpp"

class Window;


struct SharedContext {
    SharedContext():
        window(nullptr), config(nullptr), resMgr(nullptr) {};


    void AddMouseClick(SDL_Point point) {
        mouseClicks.emplace_back(point);
    }


    Window *window;
    Config *config;
    Resource_Manager *resMgr;
    std::deque<SDL_Point> mouseClicks = {};
    /** TODO: Change to square state empty*/
    SquareState userRequestedState = SquareState::X;
    SquareState aiState = SquareState::O;


};