#include <SDL2/SDL.h>
#include "SetRenderDrawColor.hpp"

namespace tt {
void SetRenderDrawColor(SDL_Renderer *renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
}