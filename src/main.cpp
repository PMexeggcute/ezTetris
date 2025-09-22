//
// Created by 25619 on 25-9-22.
//
#include "game.h"
#include <curses.h>

int main(){
    // Game game;
    // game.run();
    initscr();          // 初始化 curses 模式
    // printw("Hello, PDCurses!"); // 在虚拟屏幕上打印字符串?
    mvaddch(0,0,'#');
    refresh();          // 将内容刷新到物理屏幕
    getch();            // 等待用户按键
    endwin();
    return 0;
}
