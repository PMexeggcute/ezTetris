//
// Created by 25619 on 25-9-22.
//

#include "game.h"

#include <chrono>
#include <thread>
#include <bits/ctype_base.h>

#include "tetromino.h"
// TETROMINO tetromino;
int x = 1;
int y = 0;
bool gameOver = false;
void Game::init()
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void Game::drawBlock(Graph &g,int x, int y)//显示图形
{
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if (g.matrix[i][j])
                mvaddch(y+i,x+j,'#');
        }
    }
    refresh();
}

void Game::eraseBlock(Graph &g,int x, int y)
{
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if (g.matrix[i][j])
                mvaddch(y+i,x+j,' ');//显示以后立马清除
        }
    }
}

void Game::processInput()//键盘操作
{
    int ch = getch();
    if(ch == 260)
    {
        x--;
    }
    else if(ch == 261)
    {
        x++;
    }
}

void Game::update()//方块下落逻辑
{
    if (y<12)//方块是否与棋盘中其他方块y轴相邻
        y++;//测试逻辑
    else
    {
        y = 0;//重置y轴并且保持不变 同时生成新方块
        //同时触发计分逻辑
    }
}

void Game::render()//方块刷新逻辑 只有在触底时刷新方块
{
    Game game;
    Square square;
    if (true)
    {
        game.drawBlock(square,x,y);
        refresh();
        game.eraseBlock(square,x,y);
    }
}

void Game::run()
{
    // Game game;
    while (!gameOver)
    {
        processInput();
        update();//方块下落
        render();//刷新屏幕
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}