#pragma once

#include <SDL2/SDL_ttf.h>

#include <string>
#include <unordered_map>

class Resource_Manager {
  public:
    Resource_Manager();
    ~Resource_Manager();

    [[nodiscard]] std::unordered_map< std::string, TTF_Font * > get_fonts();
    [[nodiscard]] TTF_Font *get_font(std::string fontName);

  private:
    void load_fonts();

    std::unordered_map<std::string, TTF_Font * > fonts;
};