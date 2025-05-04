
#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include <cmath>

struct Mouse {
    int x, y;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;

    Mouse(int startX = SCREEN_WIDTH / 2, int startY = SCREEN_HEIGHT / 2)
        : x(startX), y(startY) {}

    void move() {
        if (dx != 0 && dy != 0) {
            x += (int)(dx * DIAG_SPEED);
            y += (int)(dy * DIAG_SPEED);
        } else {
            x += (int)(dx * speed);
            y += (int)(dy * speed);
        }

        if (x < 0) x = 0;
        if (x > SCREEN_WIDTH - 10) x = SCREEN_WIDTH - 10;
        if (y < 0) y = 0;
        if (y > SCREEN_HEIGHT - 10) y = SCREEN_HEIGHT - 10;
    }
    void turnNorth() {
        dy = -speed;
        dx = 0;
    }
    void turnSouth() {
        dy = speed;
        dx = 0;
    }
    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }
    void stop() {
        dx = 0; dy = 0;
    }

    void setDirection(bool up, bool down, bool left, bool right) {
        dx = dy = 0;
        if (up)    dy = -1;
        if (down)  dy = 1;
        if (left)  dx = -1;
        if (right) dx = 1;
    }

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
};

bool showMenu(Graphics& graphics) {
    SDL_Texture* menuBackground = graphics.loadTexture("menu_background.png");
    SDL_Texture* startNormal = graphics.loadTexture("start_normal.png");
    SDL_Texture* startSelected = graphics.loadTexture("start_selected.png");
    SDL_Texture* quitNormal = graphics.loadTexture("quit_normal.png");
    SDL_Texture* quitSelected = graphics.loadTexture("quit_selected.png");

    int selected = 0;
    bool inMenu = true;
    SDL_Event e;

    while (inMenu) {
        graphics.prepareScene();
        SDL_RenderCopy(graphics.renderer, menuBackground, NULL, NULL);

        SDL_Rect startRect = { SCREEN_WIDTH/2 - 100, 200, 200, 50 };
        SDL_Rect quitRect = { SCREEN_WIDTH/2 - 100, 300, 200, 50 };

        if (selected == 0) {
            SDL_RenderCopy(graphics.renderer, startSelected, NULL, &startRect);
            SDL_RenderCopy(graphics.renderer, quitNormal, NULL, &quitRect);
        } else {
            SDL_RenderCopy(graphics.renderer, startNormal, NULL, &startRect);
            SDL_RenderCopy(graphics.renderer, quitSelected, NULL, &quitRect);
        }

        graphics.presentScene();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                selected = 1;
                inMenu = false;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        selected = (selected - 1 + 2) % 2;
                        break;
                    case SDLK_DOWN:
                        selected = (selected + 1) % 2;
                        break;
                    case SDLK_RETURN:
                        inMenu = false;
                        break;
                }
            }
        }

        SDL_Delay(16);
    }

    SDL_DestroyTexture(menuBackground);
    SDL_DestroyTexture(startNormal);
    SDL_DestroyTexture(startSelected);
    SDL_DestroyTexture(quitNormal);
    SDL_DestroyTexture(quitSelected);

    return selected == 0;
}


#endif
