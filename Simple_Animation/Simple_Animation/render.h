#ifndef RENDER_H
#define RENDER_H

#include "graphics.h"
#include "game.h"
#include "defs.h"

void render(const Mouse& mouse, SDL_Texture* texture, const Graphics& graphics) {
    SDL_Rect dest = { mouse.x, mouse.y, PLAYER_SIZE, PLAYER_SIZE };
    SDL_RenderCopy(graphics.renderer, texture, nullptr, &dest);
}

#endif
