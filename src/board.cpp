#include "board.h"

#include "curses.h"
//
// Created by 25619 on 25-9-22.
//
void Board::init()
{
//左右边框
    int i = 0;
    for (i = 0; i< Board::BOARD_HEIGHT;i++)
    {
        mvaddch(i,0,'|');
        mvaddch(i,Board::BOARD_WIDTH+1,'|');
    }//下标1-10为可操作的
    //下边界
    for (i = 0; i< Board::BOARD_WIDTH+2;i++)
    {
        mvaddch(Board::BOARD_HEIGHT,i,'-');
    }//下标0-19为可操作
    // refresh();
}