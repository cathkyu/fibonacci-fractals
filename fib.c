#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    up,
    right,
    down,
    left
} direction;

char *fibstr;
#define BASE_LEN 2

void makefibword(int n){
    
    char *str1 = malloc(BASE_LEN);
    char *str2 = malloc(BASE_LEN);
    strcpy(str1, "1");
    strcpy(str2, "0");

    int i;
    for (i = 2; i < n; i++){
        fibstr = malloc(strlen(str1) + strlen(str2) + 1);
        strcpy(fibstr, str2);
        strcat(fibstr, str1);
        free(str1);
        str1 = str2;
        str2 = fibstr;
    }
}

void draw(int x, int y, direction dir, int step, int w, RGB* im, RGB c)
{
#define I(i, j) im[(i)*w + j]
    int j;
    if (dir == up)
        for (j = 0; j < step; j++)
            I(x + j, y) = c;
    if (dir == down)
        for (j = 0; j < step; j++)
            I(x - j, y) = c;
    if (dir == right)
        for (j = 0; j < step; j++)
            I(x, y + j) = c;
    if (dir == left)
        for (j = 0; j < step; j++)
            I(x, y - j) = c;
#undef I
}

int fib (int n, int x, int y, int step, RGB bc, RGB fc, int w, int h, RGB* image) {
    int i, k;

    makefibword(n);

    direction dir = up;

    if (!fibstr) return 0;
    if (!image) return 0;

    for (i = 0; i < w * h; i++) {
        image[i] = bc;
    }

    int total_steps = 1;

    for (k = 0; k < strlen(fibstr); k++) {

        if (x < 0 || x > h || y < 0 || y > w) return 0;

        draw (x, y, dir, step, w, image, fc);
        total_steps += 1 ;
        
        if (dir == up)
            x += step;
        if (dir == right)
            y += step;
        if (dir == down)
            x -= step;
        if (dir == left)
            y -= step;

        
        if (fibstr[k] == '0') {
            int breakout = 0;
            if ((k+1)%2 == 0) {
                if (dir == up && breakout == 0){
                    dir = left;
                    breakout = 1;
                }
                if (dir == right && breakout == 0) {
                    dir = up;
                    breakout = 1;
                }
                if (dir == down && breakout == 0) {
                    dir = right;
                    breakout = 1;
                }
                if (dir == left && breakout == 0) {
                    dir = down;
                    breakout = 1;
                }
            }
            else {
                if (dir == left && breakout == 0) {
                    dir = up;
                    breakout = 1;
                }
                if (dir == up && breakout == 0) {
                    dir = right;
                    breakout = 1;
                }
                if (dir == right && breakout == 0) {
                    dir = down;
                    breakout = 1;
                }
                if (dir == down && breakout == 0) {
                    dir = left;
                    breakout = 1;
                }
            }
        }
    }
    return total_steps;
}
