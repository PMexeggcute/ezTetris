//
// Created by 25619 on 25-9-22.
//

#ifndef BOARD_H
#define BOARD_H
//棋盘
class Board
{
    public:
    const int BOARD_WIDTH = 10;
    const int BOARD_HEIGHT = 15;
    int board[10][15];
    void init();
};
#endif //BOARD_H
