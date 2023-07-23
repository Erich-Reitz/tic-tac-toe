#pragma once

#include <SDL2/SDL.h>

#include <memory>

#include "FontTexture.hpp"
#include "Object.hpp"
#include "Shared_Context.hpp"
#include "SetRenderDrawColor.hpp"



class TextObject : public Object {
  public:
    TextObject( SDL_Point center, int height, int width, SharedContext *p_context, std::string text, TTF_Font *font,
                SDL_Color textColor) :  Object(center, height, width, p_context) {
        auto renderer = p_context->window->Renderer();
        fontTexture = std::make_unique<FontTexture>(renderer, text, font, textColor);
    }
    ~TextObject() = default;

    void Render(SDL_Renderer *renderer) const {
        // tt::SetRenderDrawColor(renderer, context->config->LIGHT_PINK);
        // SDL_RenderDrawRect(renderer, &area);
        this->fontTexture->Render(renderer, area) ;
    }

  private:
    std::unique_ptr<FontTexture> fontTexture;
};