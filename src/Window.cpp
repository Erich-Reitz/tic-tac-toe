
#include <SDL2/SDL.h>

#include <string>
#include <iostream>
#include "Window.hpp"
#include "flush_exit_failure.hpp"

#define EXIT_GRACEFUL this->done = true;

#define BLACK 255, 255, 255, 255
#define WHITE 255, 255, 255, 255
#define BLUE 173, 216, 230, 255


Window::Window() {}
Window::Window( std::string w_title, SDL_Point w_size, SharedContext *sharedContext) : context(sharedContext) {
    int width = w_size.x;
    int height = w_size.y;
    this->window = SDL_CreateWindow( w_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                     SDL_WINDOW_SHOWN );
    if( !this->window ) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        flush_exit_failure();
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Window *Window::GetWindow()  {
    return window;
}

SDL_Renderer *Window::Renderer() {
    return renderer;
}

void Window::BeginDraw() {
    SDL_SetRenderDrawColor( renderer, BLUE );
    SDL_RenderClear(renderer);
}

void Window::EndDraw() {
    SDL_RenderPresent(renderer);
}

SDL_Point Window::Center() const {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight) ;
    return {windowWidth / 2, windowHeight / 2 }  ;
}

void Window::Update() {
    SDL_Event e;
    while( SDL_PollEvent( &e ) ) {
        switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            this->m_down = true;
            break;
        case SDL_MOUSEBUTTONUP:
            this->m_down = false;
            break;
        case SDL_QUIT:
            EXIT_GRACEFUL;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                EXIT_GRACEFUL;
                break;
            }
        default:
            break;
        }
    }
}

bool Window::Done() const {
    return this->done;
}

Window::~Window()  {
    if (window) {
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}