//
// Created by 25619 on 25-9-22.
//

#ifndef TETROMINO_H
#define TETROMINO_H
#include <cstring>

//方块
class Graph
{
public:
    int matrix[3][3]{};
    virtual ~Graph() = default;
};

class Square : public Graph
{
    public:
        Square()
        {
            int tmp[3][3] = {
                {1,1,1,},
                {1,1,1,},
                {1,1,1,},
            };
            std::memcpy(matrix, tmp, sizeof(matrix));
        }
};
#endif //TETROMINO_H
