#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "graphics.h"
#include "defs.h"
#include "game.h"
#include "render.h"
#include "entity.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    Graphics graphics;
    graphics.init();

    SDL_Texture* backgroundTexture = graphics.loadTexture("space.png");
    SDL_Texture* mouseTexture = graphics.loadTexture("planet03.png");
    SDL_Texture* enemyTexture = graphics.loadTexture("planet02.png");

    Mouse mouse;
    mouse.x = SCREEN_WIDTH / 2;
    mouse.y = SCREEN_HEIGHT / 2;

    std::vector <Enemy> enemies;

    int spawnTimer = 0;
    const int spawnDelay = 50;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        graphics.prepareScene();
        SDL_RenderCopy(graphics.renderer, backgroundTexture, nullptr, nullptr);
        render(mouse, mouseTexture, graphics);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        bool up = currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_UP];
        bool down = currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_DOWN];
        bool left = currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_LEFT];
        bool right = currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_RIGHT];

        if (up) mouse.turnNorth();
        if (down) mouse.turnSouth();
        if (left) mouse.turnWest();
        if (right) mouse.turnEast();

        mouse.setDirection(up, down, left, right);
        mouse.move();

        spawnTimer++;
        if (spawnTimer >= spawnDelay) {
            spawnTimer = 0;

            int edge = rand() % 4;
            int ex, ey;

            if (edge == 0) { ex = rand() % SCREEN_WIDTH; ey = 0; }
            else if (edge == 1) { ex = rand() % SCREEN_WIDTH; ey = SCREEN_HEIGHT; }
            else if (edge == 2) { ex = 0; ey = rand() % SCREEN_HEIGHT; }
            else { ex = SCREEN_WIDTH; ey = rand() % SCREEN_HEIGHT; }

            float enemySpeed = 2.0f + static_cast<float>(rand() % 2) / 2.0f;

            enemies.push_back(Enemy(ex, ey, mouse.x, mouse.y, enemySpeed));;
        }


        for (auto& enemy : enemies) {
            enemy.move();
            if (enemy.checkCollision(mouse.getX(), mouse.getY(), PLAYER_SIZE)) {
                std::cout << "Game Over!";
                quit = true;
            }
        }

        for (auto& enemy : enemies) {
            enemy.render(enemyTexture, graphics);
        }

         enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) {
            return e.x < -e.size || e.x > SCREEN_WIDTH + e.size ||
                   e.y < -e.size || e.y > SCREEN_HEIGHT + e.size;
        }), enemies.end());

        graphics.presentScene();
        SDL_Delay(16);
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(mouseTexture);
    SDL_DestroyTexture(enemyTexture);

    graphics.quit();
    return 0;
}
