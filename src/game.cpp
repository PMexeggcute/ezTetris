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
Game game;
int board[10][15];
void Game::init()
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

/*void Game::drawBlock(Graph &g,int x, int y)//显示图形
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
}*/

void Game::drawBoard()
{
    for (int i = 0;i < 15;i++)//y
    {
        for (int j = 0;j < 10;j++)//x
        {
            if (board[i][j])
                mvaddch(i,j,'#');
        }
    }
}

/*
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
*/

void Game::eraseBoard()
{
    for (int i = 0;i < 15;i++)
    {
        for (int j = 0;j < 10;j++)
        {
            if (board[i][j] == 1)
                mvaddch(i,j,' ');
        }
    }
}

void Game::processInput()//键盘操作
{
    int ch = getch();//左
    if(ch == 260)
    {
        if (true)//未出界
            x--;
    }
    else if(ch == 261)//右
    {
        if (true)//未出界
            x++;
    }
}

void Game::update()//方块下落逻辑
{
    /*
     先检查
     erase
     下落
     然后refresh
     */
    if (isBottom())//触底了
    {//1全变2

    }
    else
    {
        game.eraseBoard();
        //为1的块集体向下移一格

        refresh();
    }
}

void Game::render()//方块刷新逻辑 只有在触底时刷新方块
{
    Square square;
    if (true)
    {
        game.drawBoard();
        refresh();
        //game.eraseBoard();
    }
}

void Game::run()
{
    // Game game;
    while (!gameOver)
    {   /*展示棋盘
        erase draw移动
        到底时不再erase
        然后循环,每次都循环展示棋盘而不是方块对象
        */
        render();//刷新屏幕
        processInput();
        update();//方块下落
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}