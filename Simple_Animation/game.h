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

#endif
