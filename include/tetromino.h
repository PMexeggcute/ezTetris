//
// Created by 25619 on 25-9-22.
//

#ifndef TETROMINO_H
#define TETROMINO_H
#include <cstring>
#include <memory>

class Graph;

enum class BlockType
{
    Square,
    Hero,
};

BlockType randomBlock();
std::unique_ptr<Graph> createBlock(BlockType type);
//方块
class Graph
{
public:
    int matrix[4][4]{};
    virtual ~Graph() = default;
};

class Square : public Graph
{
    public:
    Square()
    {
        int square[4][4] = {
            {1,1,0,0,},
            {1,1,0,0,},
            {0,0,0,0,},
            {0,0,0,0,},
        };
        std::memcpy(matrix, square, sizeof(matrix));//数组不能在类成员初始化列表里直接赋值（C++ 不允许数组直接用 = 赋值初始化）
    }
};
class Hero : public Graph
{
    public:
    Hero()
    {
        int hero[4][4] = {
        {1,0,0,0,},
        {1,0,0,0,},
        {1,0,0,0,},
        {1,0,0,0,},
        };
        std::memcpy(matrix, hero, sizeof(matrix));
    }
};
#endif //TETROMINO_H
