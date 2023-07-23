#pragma once

#include <SDL2/SDL.h>


#include <memory>

#include "Shared_Context.hpp"

class Object {
  public:
    Object() = default;
    Object(SDL_Point center, int height, int width, SharedContext *p_context ) : context(p_context) {
        area.x = center.x - width / 2;
        area.y = center.y - height / 2;
        area.w = width;
        area.h = height;
    }

    ~Object() = default;

    virtual void Render(SDL_Renderer *renderer) const = 0;

    bool WithinBounds(SDL_Point point) const {
        return SDL_PointInRect(&point, &area);
    }
  protected:
    SharedContext *context;
    SDL_Rect area = {0, 0, 0, 0};
};