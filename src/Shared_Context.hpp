#pragma once
#include "Window.hpp"
#include "Config.hpp"

class Window;
class Config;

struct SharedContext {
    SharedContext():
        window(nullptr), config(nullptr) {};

    SDL_Color BackgroundColor() {
        return config->BackgroundColor();
    }



    Window *window;
    tt::Config *config;
};