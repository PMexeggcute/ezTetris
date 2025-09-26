//
// Created by 25619 on 25-9-22.
//

#ifndef TETROMINO_H
#define TETROMINO_H
#include <cstring>
#include <memory>
#include <conio.h>

class Graph;

enum class BlockType
{
    Square,
    Hero,
    Snake,
    Kenas,
    Jacob,
    Bojac,
    Tank,
};

BlockType randomBlock();
std::unique_ptr<Graph> createBlock(BlockType type);
//方块
class Graph//O I S Z L J T
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
        {0,1,0,0,},
        {0,1,0,0,},
        {0,1,0,0,},
        {0,1,0,0,},
        };
        std::memcpy(matrix, hero, sizeof(matrix));
    }
};

class Snake : public Graph
{
    public:
    Snake()
    {
        int snake[4][4] = {
            {0,1,1,0,},
            {1,1,0,0,},
            {0,0,0,0,},
            {0,0,0,0,},
        };
        std::memcpy(matrix, snake, sizeof(matrix));
    }
};

class Kenas : public Graph
{
    public:
    Kenas()
    {
        int kenas[4][4] =
        {
            {1,1,0,0,},
            {0,1,1,0,},
            {0,0,0,0,},
            {0,0,0,0,},
        };
        std::memcpy(matrix, kenas, sizeof(matrix));
    }
};

class Jacob : public Graph
{
    public:
    Jacob()
    {
        int jacob[4][4] = {
            {0,1,0,0,},
            {0,1,0,0,},
            {1,1,0,0,},
            {0,0,0,0,},
        };
        std::memcpy(matrix, jacob, sizeof(matrix));
    }
};

class Bojac : public Graph
{
    public:
    Bojac()
    {
        int bojac[4][4] = {
            {0,1,0,0,},
            {0,1,0,0,},
            {0,1,1,0,},
            {0,0,0,0,},
        };
        std::memcpy(matrix, bojac, sizeof(matrix));
    }
};

class Tank : public Graph
{
    public:
    Tank()
    {
        int tank[4][4] = {
            {1,1,1,0,},
            {0,1,0,0,},
            {0,0,0,0,},
            {0,0,0,0,},
        };
        std::memcpy(matrix, tank, sizeof(matrix));
    }
};
#endif //TETROMINO_H
