#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "Shared_Context.hpp"

struct SharedContext;

class Window {
  public:
    Window();
    Window( const std::string &w_title, SDL_Point w_size, SharedContext *sharedContext);
    ~Window();
    SDL_Renderer *Renderer() ;
    [[nodiscard]] SDL_Point Center() const;

    void BeginDraw();
    void EndDraw();
    void Update();

    void SetDone() ;
    [[nodiscard]] bool Done() const;
  private:
    //The window we'll be rendering to
    SDL_Window *window = nullptr;

    SDL_Renderer *renderer = nullptr;
    SharedContext *context = nullptr;
    bool done = false;
    bool m_down = false;

};