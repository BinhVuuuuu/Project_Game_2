#ifndef RENDER_H
#define RENDER_H

#include "graphics.h"
#include "game.h"
#include "defs.h"

void render(const Mouse& mouse, const Graphics& graphics) {
    SDL_Rect filled_rect = { mouse.x, mouse.y, PLAYER_SIZE, PLAYER_SIZE };
    SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(graphics.renderer, &filled_rect);
}

#endif
