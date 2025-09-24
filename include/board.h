//
// Created by 25619 on 25-9-22.
//

#ifndef BOARD_H
#define BOARD_H
//棋盘
class Board
{
    public:
    static constexpr int BOARD_WIDTH = 10;
    static constexpr int BOARD_HEIGHT = 20;
    static int board[Board::BOARD_WIDTH+2][Board::BOARD_HEIGHT+2];//棋盘矩阵,0,1,2对应三种状态
    //0代表无方块
    //1代表运动的方块
    //2代表不动的方块
    //3代表边界
    void init();
};
#endif //BOARD_H
