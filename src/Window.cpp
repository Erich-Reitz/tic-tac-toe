
#include <SDL2/SDL.h>

#include <string>
#include "Window.hpp"
#include "flush_exit_failure.hpp"
#include "SetRenderDrawColor.hpp"

#define EXIT_GRACEFUL this->done = true;



Window::Window() = default;
Window::Window( const std::string &w_title, SDL_Point w_size, SharedContext *sharedContext) : context(sharedContext) {
    int width = w_size.x;
    int height = w_size.y;
    this->window = SDL_CreateWindow( w_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                     SDL_WINDOW_SHOWN );
    if( !this->window ) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        flush_exit_failure();
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED );
}

SDL_Renderer *Window::Renderer() {
    return renderer;
}

void Window::BeginDraw() {
    tt::SetRenderDrawColor(renderer, context->config->BackgroundColor()) ;
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
    auto lastMouseState = this->m_down;
    SDL_Event e;
    while( SDL_PollEvent( &e ) ) {
        switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            this->m_down = true;
            break;
        case SDL_MOUSEBUTTONUP:
            this->m_down = false;
            /** TODO: Bad. Delta function needed? lastMouseState could be struct with previous bound info */
            if (lastMouseState != this->m_down) {
                this->context->AddMouseClick(SDL_Point{e.button.x, e.button.y});
            }
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