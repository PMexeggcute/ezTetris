//
// Created by 25619 on 25-9-22.
//

#ifndef GAME_H
#define GAME_H
//游戏主要循环
#include "curses.h"
#include "tetromino.h"
extern int x;//作为偏移
extern int y;
extern bool gameOver;

class Game
{
    public:
    void init();
    void drawBlock(Graph &g,int x, int y);
    void eraseBlock(Graph &g,int x, int y);
    void processInput();
    void run();
    void cleanup();
    void update();
    void render();
};
#endif //GAME_H
