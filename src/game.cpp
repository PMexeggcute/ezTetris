//
// Created by 25619 on 25-9-22.
//

#include "game.h"

#include <chrono>
#include <thread>


void Game::init()
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void Game::drawBlock(int x,int y)
{
    mvaddch(y,x,'#');
    refresh();
}

void Game::processInput()
{
    int ch = getch();
    if(ch == KEY_LEFT)
    {

    }
    else if(ch == KEY_RIGHT)
    {

    }
}

void Game::update()
{

}

void Game::render()
{

}

void Game::run()
{
    Game game;
    while (!game.gameOver)
    {
        processInput();
        update();//方块下落
        render();//刷新屏幕
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}