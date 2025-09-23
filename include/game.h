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
    // void drawBlock(Graph &g,int x, int y);
    // void eraseBlock(Graph &g,int x, int y);
    void processInput();
    void run();
    void cleanup();
    void update();
    void render();
    bool isBottom();//检查是否触底了检查棋盘上对应currentY+1的值 触底时所有1都变为2
    bool isBorderL();
    bool isBorderR();
    void drawBoard();
    void eraseBoard();//清除所有为1的块,触底时在被清除前就需要置零
    void blockGenerate(Graph &g);
};
#endif //GAME_H
