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
    // nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void Game::blockGenerate(Graph &g)
{
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if (g.matrix[j][i] == 1)
            {
                board[j+4][i] = 1;
            }
        }
    }
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
            if (board[j][i])
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
            if (board[j][i] == 1)
                mvaddch(i,j,' ');
        }
    }
    // refresh();
}

void Game::processInput()//键盘操作逻辑
{
    int ch = getch();//左
    if(ch == 260)
    {
        if (!game.isBorderL())//未出界 靠近左边或右边一列的数据不能为1
            x--;
    }
    else if(ch == 261)//右
    {
        if (!game.isBorderR())//未出界
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
        for (int i = 0;i < 15;i++)
        {
            for (int j = 0;j < 10;j++)
            {
                if (board[i][j] == 1)
                    board[i][j] = 2;
            }
        }
    }
    else
    {
        game.eraseBoard();
        //为1的块集体向下移一格
        for (int i = 14;i >= 0;i--)
        {
            for (int j = 9;j >= 0;j--)
            {
                if (board[j][i] == 1)
                {
                    board[j][i] = 0;
                    board[j][i+1] = 1;
                }
            }
        }
        refresh();
    }
}

void Game::render()//方块刷新逻辑 只有在触底时刷新方块
{
    // Square square;
    if (game.isBottom())//触底?
    {
        game.drawBoard();
        //-----------------------------warning----------------------------------
        refresh();//这里是否需要刷新?一个循环两次刷新是否不妥??
        //------------------------------warning---------------------------------
        //game.eraseBoard();
    }
}
//底部/堆叠判断逻辑
bool Game::isBottom()
{
    for (int i = 0;i < 15;i++)
    {
        for (int j = 0;j < 10;j++)
        {
            if (board[j][i] == 1)//找到正在运动的块
            {
                if (board[j][i+1] == 2||board[j][i+1] == '-')//正在运动的块的下面是不动的块或边界
                    return true;
            }
        }
    }
    return false;
}

//边界判断逻辑
bool Game::isBorderL()
{
    for (int i = 0;i < 15;i++)
    {
        if (board[1][i] == 1)//判断方块位置上到边缘
            return true;
    }
    //还需考虑旁边是静止块
    for (int i = 0;i < 15;i++)
    {
        for (int j = 0;j < 10;j++)
        {
            if (board[j][i] == 1)
            {
                if (board[j][i-1] == 2)
                    return true;
            }
        }
    }
    return false;
}
bool Game::isBorderR()
{
    for (int i = 0;i < 15;i++)
    {
        if (board[10][i] == 1)//判断方块位置上到边缘
            return true;
    }
    //还需考虑旁边是静止块
    for (int i = 0;i < 15;i++)
    {
        for (int j = 0;j < 10;j++)
        {
            if (board[j][i] == 1)
            {
                if (board[j][i+1] == 2)
                    return true;
            }
        }
    }
    return false;
}
void Game::run()
{
    //先生成第一个
    Square square;
    blockGenerate(square);
    // Game game;
    while (!gameOver)
    {   /*展示棋盘
        erase draw移动
        到底时不再erase
        然后循环,每次都循环展示棋盘而不是方块对象
        */

        drawBoard();
        refresh();
        render();//刷新屏幕
        processInput();
        update();//方块下落
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}