//
// Created by 25619 on 25-9-22.
//
#include "tetromino.h"
#include <random>
#include <memory>
BlockType randomBlock()
{
    static std::random_device rd;//C++11 提供的 硬件真随机数生成器（如果平台支持）
    static std::mt19937 gen(rd());//梅森旋转伪随机数生成器
    static std::uniform_int_distribution<> distrib(0, 1);//用于生成 均匀分布的整数随机数

    int value = distrib(gen);
    return static_cast<BlockType>(value);//类型转换
}

std::unique_ptr<Graph> createBlock(BlockType type)
{
    switch (type)
    {
    case BlockType::Square: return std::make_unique<Square>();
    case BlockType::Hero: return std::make_unique<Hero>();
    default : return nullptr;
    }
}