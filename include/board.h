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
    static int board[10][15];//棋盘矩阵,0,1,2对应三种状态
    //0代表无方块
    //1代表运动的方块
    //2代表不动的方块
    void init();
};
#endif //BOARD_H
