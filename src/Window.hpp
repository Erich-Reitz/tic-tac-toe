#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "Shared_Context.hpp"

class SharedContext;

class Window {
  public:
    Window();
    Window( std::string w_title, SDL_Point w_size, SharedContext *sharedContext);
    ~Window();
    SDL_Window *GetWindow()  ;
    SDL_Renderer *Renderer() ;
    SDL_Point Center() const;

    void BeginDraw();
    void EndDraw();
    void Update();
    bool Done() const;
  private:
    //The window we'll be rendering to
    SDL_Window *window = nullptr;

    SDL_Renderer *renderer = nullptr;
    SharedContext *context = nullptr;
    bool done = false;
    bool m_down = false;

};