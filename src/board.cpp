#include "board.h"

#include "curses.h"
//
// Created by 25619 on 25-9-22.
//
void Board::init()
{
//左右边框
    Board board;
    int i = 0;
    for (i = 0; i< board.BOARD_HEIGHT;i++)
    {
        mvaddch(i,0,'|');
        mvaddch(i,board.BOARD_WIDTH+1,'|');
    }
    //下边界
    for (i = 0; i< board.BOARD_WIDTH+2;i++)
    {
        mvaddch(board.BOARD_HEIGHT,i,'-');
    }
    refresh();
}