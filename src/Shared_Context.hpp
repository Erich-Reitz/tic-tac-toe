#pragma once
#include "Window.hpp"

class Window;

struct SharedContext {
    SharedContext():
        window(nullptr) {};

    Window *window;
};