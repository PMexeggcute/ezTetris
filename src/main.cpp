//
// Created by 25619 on 25-9-22.
//
#include "game.h"
#include <curses.h>
#include <thread>

#include "board.h"

int main(){
    // initscr();
    // noecho();
    // cbreak();
    // // nodelay(stdscr, TRUE);
    // keypad(stdscr, TRUE);
    // int test = 0;
    // mvprintw(1,1,"Hello World! %d",test);
    // test++;
    // refresh();
    // clear();
    // mvprintw(2,1,"Hello World! %d",test);
    // refresh();

    Game game;
    Board board;
    game.init();
    board.init();

    std::thread t(Game::inputThread, &game);
    game.run();
    t.join();
    _getch();            // 等待用户按键
    endwin();
    return 0;
}
