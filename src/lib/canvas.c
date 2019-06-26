#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CIRCLES 100

struct Circle {
    int x;
    int y;
    int radius;

    int cr;
    int cg;
    int cb;
};

struct CircleAnimation {
    int x;
    int y;
    int radius;

    int xVelocity;
    int yVelocity;
    int xDirection; // 1 = forward, 0 backwards
    int yDirection; // 1 = forward, 0 backwards
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimation circleAnimations[NUM_CIRCLES];

int getRand(int max) {
    return (rand()%max);
}

int main() {
    srand(time(NULL));

    int circleStructSize = sizeof (struct Circle) / sizeof (int);

    for (int i = 0; i < NUM_CIRCLES; i++) {
        int radius = getRand(100);

        int x = getRand(1000) + radius;
        int y = getRand(1000) + radius;


        circleAnimations[i].x = x;
        circleAnimations[i].y = y;
        circleAnimations[i].radius = radius;

        circleAnimations[i].xVelocity = 2 + getRand(10);
        circleAnimations[i].yVelocity = 2 + getRand(10);
        circleAnimations[i].xDirection = getRand(2);
        circleAnimations[i].yDirection = getRand(2);

        circles[i].x = x;
        circles[i].y = y;
        circles[i].radius = radius;

        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
    }

    EM_ASM({ render($0, $1); }, NUM_CIRCLES*circleStructSize, circleStructSize);

    return 0;
}

struct Circle * getCircles(int canvasWidth, int canvasHeight) {
    for (int i = 0; i < NUM_CIRCLES; i++) {
        if(circleAnimations[i].x + circleAnimations[i].radius >= canvasWidth) {
            circleAnimations[i].xDirection = 0;
        }
        if(circleAnimations[i].x - circleAnimations[i].radius <= 0) {
            circleAnimations[i].xDirection = 1;
        }
        if(circleAnimations[i].y + circleAnimations[i].radius >= canvasHeight) {
            circleAnimations[i].yDirection = 0;
        }
        if(circleAnimations[i].y - circleAnimations[i].radius <= 0) {
            circleAnimations[i].yDirection = 1;
        }

        if(circleAnimations[i].xDirection == 1) {
            circleAnimations[i].x += circleAnimations[i].xVelocity;
        } else {
            circleAnimations[i].x -= circleAnimations[i].xVelocity;
        }

        if(circleAnimations[i].yDirection == 1) {
            circleAnimations[i].y += circleAnimations[i].yVelocity;
        } else {
            circleAnimations[i].y -= circleAnimations[i].yVelocity;
        }

        circles[i].x = circleAnimations[i].x;
        circles[i].y = circleAnimations[i].y;
    }

    return circles;
}
