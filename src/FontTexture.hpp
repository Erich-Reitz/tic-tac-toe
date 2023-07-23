#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <memory>

#include "flush_exit_failure.hpp"


class FontTexture {
  public:

    FontTexture(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color textColor) {
        this->loadFromFont(renderer, font, text, textColor);
    }


    ~FontTexture() {
        if( mTexture != NULL ) {
            SDL_DestroyTexture( mTexture );
            mTexture = NULL;
        }
    }


    void loadFromFont(SDL_Renderer *renderer, TTF_Font *font, std::string textureText, SDL_Color textColor ) {
        SDL_Surface *textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
        if (!textSurface) {
            printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( !mTexture  ) {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            flush_exit_failure();
        }
        SDL_FreeSurface( textSurface );
    }


    /** TODO: Not sure if I want this. Would I rather just render a reference to SDL_Texture? */
    void Render( SDL_Renderer *renderer, const SDL_Rect &renderQuad ) const {
        SDL_RenderCopy( renderer, mTexture, NULL, &renderQuad );
    }


  private:
    SDL_Texture *mTexture;
};