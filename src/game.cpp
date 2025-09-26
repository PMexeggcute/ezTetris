//
// Created by 25619 on 25-9-22.
//

#include "game.h"

#include <chrono>
#include <random>
#include <thread>
#include <vector>
#include <bits/ctype_base.h>

#include "board.h"
#include "tetromino.h"
// TETROMINO tetromino;
int x = 1;
int y = 0;
bool gameOver = false;
Game game;
int board[Board::BOARD_WIDTH+1][Board::BOARD_HEIGHT];

static std::random_device rd;//C++11 提供的 硬件真随机数生成器（如果平台支持）
static std::mt19937 gen(rd());//梅森旋转伪随机数生成器
static std::uniform_int_distribution<> distrib(1,8);

void Game::init()
{
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void Game::blockGenerate(Graph &block)
{
    int randomX = distrib(gen);
    for (int x = 0;x < 4;x++)
    {
        for (int y = 0;y < 4;y++)
        {
            if (block.matrix[y][x] == 1)//初始化时与图形定义视觉上一致
            {
                board[x+randomX][y] = 1;
            }
        }
    }
}
/*void Game::drawBlock(Graph &g,int x, int y)//显示图形
{
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if (g.matrix[i][j])
                mvaddch(y+i,x+j,'#');
        }
    }
    refresh();
}*/

void Game::drawBoard()
{
    Board::init();
    showData();
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)//y
    {
        for (int x = 1;x < Board::BOARD_WIDTH+1;x++)//x
        {
            if (board[x][y])
                mvaddch(y,x,'#');
        }
    }
    refresh();
}

/*
void Game::eraseBlock(Graph &g,int x, int y)
{
    for (int i = 0;i < 3;i++)
    {
        for (int j = 0;j < 3;j++)
        {
            if (g.matrix[i][j])
                mvaddch(y+i,x+j,' ');//显示以后立马清除
        }
    }
}
*/

void Game::eraseBoard()
{
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)
    {
        for (int x = 0;x < Board::BOARD_WIDTH + 1;x++)
        {
            if (board[x][y] == 1)
                mvaddch(y,x,' ');
        }
    }
    // refresh();
}

void Game::processInput(char ch)//键盘操作逻辑
{
    // int ch = getch();
    // game.eraseBoard();
    //后续增加下操作
    if (!isBottom())
    {
        if(ch == 97)//L
        {
            if (!game.isBorderL()) //未出界 靠近左边或右边一列的数据不能为1
            //左移逻辑
            {
                for (int y = 0; y < Board::BOARD_HEIGHT; y++)
                {
                    for (int x = 0; x < Board::BOARD_WIDTH + 1; x++)
                    {
                        if (board[x][y] == 1)
                        {
                            board[x][y] = 0;
                            board[x - 1][y] = 1;
                        }
                    }
                }
            }
        }
        else if (ch == 100) //右
        {
            if (!game.isBorderR()) //未出界
            //右移逻辑
            {
                for (int y = 0; y < Board::BOARD_HEIGHT; y++)
                {
                    for (int x = Board::BOARD_WIDTH; x >= 0; x--)
                    {
                        if (board[x][y] == 1)
                        //go in this way the program dead
                        {
                            board[x][y] = 0;
                            board[x + 1][y] = 1;
                        }
                    }
                }
            }
        }
        else if (ch == 115)//s
        {
            for (int y = Board::BOARD_HEIGHT - 1;y >= 0;y--)//下落
            {
                for (int x = Board::BOARD_WIDTH;x >= 0;x--)
                {
                    if (board[x][y] == 1)
                    {
                        board[x][y] = 0;
                        board[x][y+1] = 1;
                    }
                }
            }
        }
        else if (ch == 32)//空格
        {
            rotate();
            // drawBoard();
        }
    }
}
void Game::update()//方块下落逻辑
{
    /*
     先检查
     erase
     下落
     然后refresh
     */
    if (isBottom())//触底了
    {//1全变2
        for (int y = 0;y < Board::BOARD_HEIGHT;y++)
        {
            for (int x = 0;x < Board::BOARD_WIDTH + 1;x++)
            {
                if (board[x][y] == 1)
                    board[x][y] = 2;
            }
        }
        bottomFlag = 1;
        //这里对计时器处理逻辑存疑
        return;
    }

    fallCounter++;
    if (fallCounter == 60)
    {
        fallCounter = 0;
        for (int y = Board::BOARD_HEIGHT - 1;y >= 0;y--)//下落
        {
            for (int x = Board::BOARD_WIDTH;x >= 0;x--)
            {
                if (board[x][y] == 1)
                {
                    board[x][y] = 0;
                    board[x][y+1] = 1;
                }
            }
        }
    }
}

// void Game::render()//方块刷新逻辑 只有在触底时刷新方块
// {
//     // Square square;
//     if (game.isBottom())//触底?
//     {
//         game.drawBoard();
//         //-----------------------------warning----------------------------------
//         // refresh();//这里是否需要刷新?一个循环两次刷新是否不妥??
//         //------------------------------warning---------------------------------
//         //game.eraseBoard();
//     }
// }
//底部/堆叠判断逻辑
bool Game::isBottom()
{
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)
    {
        for (int x = 0;x < Board::BOARD_WIDTH + 1;x++)
        {
            if (board[x][y] == 1)//找到正在运动的块
            {
                if (board[x][y+1] == 2||y == Board::BOARD_HEIGHT - 1)//正在运动的块的下面是不动的块或边界
                    return true;
            }
        }
    }
    return false;
}

//边界判断逻辑
bool Game::isBorderL()
{
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)
    {
        if (board[1][y] == 1)//判断方块位置上到边缘
            return true;
    }
    //还需考虑旁边是静止块
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)
    {
        for (int x = 0;x < Board::BOARD_WIDTH + 1;x++)
        {
            if (board[x][y] == 1)
            {
                if (board[x-1][y] == 2)
                    return true;
            }
        }
    }
    return false;
}
bool Game::isBorderR()
{
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)
    {
        if (board[Board::BOARD_WIDTH][y] == 1)//判断方块位置上到边缘
            return true;
    }
    //还需考虑旁边是静止块
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)
    {
        for (int x = 0;x < Board::BOARD_WIDTH + 1;x++)
        {
            if (board[x][y] == 1)
            {
                if (board[x+1][y] == 2)
                    return true;
            }
        }
    }
    return false;
}

bool Game::isFull(int y)
{
    //不一定是最下面一层是满的
    //判断该行是否是满的,即需要消行的
    for (int x = 1;x < Board::BOARD_WIDTH+1;x++)
    {
        if (board[x][y] != 2)
            return false;
    }
    return true;
}
//
// void Game::clearLine(int y)
// {
//     //是否需要全部mvaddch(' ')? 还是说run的最后将整个屏幕clear
// }

void Game::downfall(int y)
{//y即以上层均需要操作
    for (;y >= 1;y--)
    {
        for (int x = 1;x < Board::BOARD_WIDTH + 1;x++)
        {
            board[x][y] = board[x][y-1];
        }
    }
    for (int x = 0;x < Board::BOARD_WIDTH + 1;x++)
        board[x][0] = 0;
    clear();
    drawBoard();  //待定
}


void Game::clearLines(int y)
{
    if (isFull(y))
    {
        rate++;
        score += Score(rate,y);
        // clearLine(y);
        downfall(y);
        clearLines(y);
    }
}

double Game::Score(int rate,int y)//分数和什么有关? 待定
{
    return (100/(static_cast<double>(y)+1))*rate;
}

void Game::clearLinesAndScore()
{
    //如果棋盘最底部均为2,消行
    //注意连续消行处理及其得分规则
    rate = 0;//每次都归零
    for (int y = Board::BOARD_HEIGHT-1;y >= 0;y--)
    {
        //if (isFull(y))//如果该行(y)已满,执行消除逻辑
          //  int tmp = y;
        clearLines(y);

        //     //消行并且rate++,得分通过rate的值相关 满足单调递增曲线
        //     //如何消行 1自下而上判断 2如果是就2变0然后其他块向下移
        //     //递归处理

        //score();
    }
    // score += Score(rate,y);
}

void Game::showData()
{
    mvprintw(0,15,"Score: %lf",score);
    // for (int x = 0;x < 4;x++)
    // {
    //     for (int y = 0;y < 4;y++)
    //     {
    //         if (block->matrix[y][x] == 1)
    //             mvaddch(3+y,15+x,'#');
    //     }
    // }
    mvprintw(2,15,"next block:");
    preview();
    mvprintw(10,15,"type 'a' to shift the block left; 'd' to right; 's' to move down; 'space' to rotate");
}

void Game::preview()
{
    for (int x = 0;x < 4;x++)//preview
    {
        for (int y = 0;y < 4;y++)
        {
            if (block->matrix[y][x] == 1)
                mvaddch(4+y,20+x,'#');
        }
    }
}

void Game::rotate()//提取到临时矩阵 做变换后写回
{
    if (type == BlockType::Square)
        return;
    std::vector<std::pair<int,int>> blockCoords;
    for (int y = 0;y < Board::BOARD_HEIGHT;y++)
    {
        for (int x = 1;x < Board::BOARD_WIDTH + 1;x++)
        {
            if (board[x][y] == 1)
            blockCoords.emplace_back(x,y);
        }
    }//遍历棋盘 找到所有1

    int minX = Board::BOARD_WIDTH,maxX = 0;
    int minY = Board::BOARD_HEIGHT,maxY = 0;
    for (auto [x,y] : blockCoords)
    {
        minX = std::min(minX,x);
        maxX = std::max(maxX,x);
        minY = std::min(minY,y);
        maxY = std::max(maxY,y);
    }
    int w = maxX - minX + 1;
    int h = maxY - minY + 1;
    //找到方块边界
    std::vector<std::vector<int>> block(h,std::vector<int>(w,0));//STL vector方式创建二维数组
    //创建一个h * w的矩阵
    for (auto [x,y] : blockCoords)
    {
        block[y - minY][x - minX] = 1;
    }//拷贝到临时数组里去

    //旋转逻辑
    std::vector<std::vector<int>> rotatedBlock(w,std::vector<int>(h,0));//变成 h * w
    for (int x = 0;x < h;x++)
    {
        for (int y = 0;y < w;y++)
        {//snake横不变 kenas竖不变 均为逆时针
            //旋转逻辑?
            // if (type == BlockType::Square || type == BlockType::Tank)
            //     pass;//这个逻辑得重写
            // else if (type == BlockType::Jacob || type == BlockType::Bojac ||
            //     type == BlockType::Snake || type == BlockType::Kenas)
            // else rotatedBlock[x][h - 1 - y] = block[y][x];//除square (已经在前面判断)和hero
            rotatedBlock[w - 1 -y][x] = block[x][y];
        }
    }

    //检测是否冲突
    bool canRotate = true;
    for (int y = 0;y < rotatedBlock.size();y++)
    {
        for (int x = 0;x < rotatedBlock[0].size();x++)
        {
            if (rotatedBlock[y][x] == 1)//判断原棋盘上对应位置是否可写回
            {
                int newX = x + minX;
                int newY = y + minY;
                if (newX < 0 || newX >= Board::BOARD_WIDTH ||
                    newY < 0 || newY >= Board::BOARD_HEIGHT ||
                    board[newX][newY] == 2)
                {
                    canRotate = false;
                    break;
                }
            }
        }
        if (!canRotate)
            return;
    }

    //写回
    //先清除
    for (auto [x,y] : blockCoords)
        board[x][y] = 0;

    //将旋转后的对象写回
    for (int y = 0;y < rotatedBlock.size();y++)
    {
        for (int x = 0;x < rotatedBlock[0].size();x++)
        {
            if (rotatedBlock[y][x] == 1)
                board[x + minX][y + minY] = 1;
        }
    }
}

void Game::inputThread()//实现异步输入
{
    while (!gameOver)
    {
        if (_kbhit())
        {
            char c = _getch();
            std::lock_guard<std::mutex> lock(queuemutex);
            inputQueue.push(c);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}


void Game::run()
{
    //先生成第一个
    type = randomBlock();
    block = createBlock(type);
    if (block == nullptr)
        return;//异常处理
    blockGenerate(*block);//随即生成
    block = createBlock(type);
    // Game game;
    // for (int x = 1;x < Board::BOARD_WIDTH - 1;x++)//test
    // {
    //     board[x][19] = 2;
    // }
    const auto frameDuration = std::chrono::milliseconds(1000 / fps);



    while (!gameOver)
    {
        /*展示棋盘
        erase draw移动
        到底时不再erase
        然后循环,每次都循环展示棋盘而不是方块对象
        */

        auto frameStart = std::chrono::steady_clock::now();

        if (bottomFlag)
        {   auto type = randomBlock();
            blockGenerate(*block);
            block = createBlock(type);
            bottomFlag = 0;
        }
        clear();//这样前文只需关注棋盘逻辑,不用手动清除
        drawBoard();//refresh()在这里
        // render();//渲染
        // processInput();
        {
            //处理输入
            std::lock_guard<std::mutex> lock(queuemutex);
            while (!inputQueue.empty())
            {
                char key = inputQueue.front();
                inputQueue.pop();
                processInput(key);
            }
        }
        update();//方块下落 每循环60次执行一次下落逻辑 后续添加下键操作 isBottom()分支不受循环次数影响?
        //消行计分逻辑
        //先变为2(静止块),然后判断是否可消除,再判断是否over 注意最上面一层的边界逻辑
        clearLinesAndScore();//blockGenerate逻辑应该在清除之后
        //游戏结束判断
        for (int x = 1;x < Board::BOARD_WIDTH + 1;x++)
        {
            if (board[x][0] == 2)
                gameOver = true;
        }

        auto frameEnd = std::chrono::steady_clock::now();
        std::this_thread::sleep_until(frameStart+frameDuration);
        //60帧
    }
}