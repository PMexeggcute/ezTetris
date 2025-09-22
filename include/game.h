//
// Created by 25619 on 25-9-22.
//

#ifndef GAME_H
#define GAME_H
//游戏主要循环
#include "curses.h"

class Game
{
    public:
    bool gameOver = false;
    void init();
    void drawBlock(int x,int y);
    void processInput();
    void run();
    void cleanup();
    void update();
    void render();
};
#endif //GAME_H
