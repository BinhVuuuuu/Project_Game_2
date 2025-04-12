
#ifndef ENTITY_H
#define ENTITY_H

#include "defs.h"
#include <SDL.h>
#include <cstdlib>

struct Entity {
    int x, y;
    float dx, dy;
    float speed;
    double size = ENTITY_SIZE;

    Entity(int startX, int startY, float directionX, float directionY, float startSpeed)
        : x(startX), y(startY), dx(directionX), dy(directionY), speed(startSpeed) {}

    void move() {
        x += dx * speed;
        y += dy * speed;
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect rect = {x, y, size, size};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

     bool checkCollision(int playerX, int playerY, int playerSize) {
        return (x < playerX + playerSize && x + size > playerX &&
                y < playerY + playerSize && y + size > playerY);
    }
};

struct Enemy : public Entity {
    Enemy(int startX, int startY, int targetX, int targetY, float startSpeed)
        : Entity(startX, startY, 0, 0, startSpeed) {

        float deltaX = targetX - startX;
        float deltaY = targetY - startY;
        float length = sqrt(deltaX * deltaX + deltaY * deltaY);

        if (length != 0) {
            dx = deltaX / length * startSpeed;
            dy = deltaY / length * startSpeed;
        }
    }
};

#endif
