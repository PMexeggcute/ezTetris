//
// Created by 25619 on 25-9-22.
//
#include "game.h"
#include <curses.h>

#include "board.h"

int main(){
    Game game;
    Board board;
    game.init();
    board.init();
    game.run();
    // refresh();          // 将内容刷新到物理屏幕
    getch();            // 等待用户按键
    endwin();
    return 0;
}
