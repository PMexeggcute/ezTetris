### PDCurses 函数部分

| 功能                                                  | 函数                                   |
| ----------------------------------------------------- | -------------------------------------- |
| 初始化屏幕                                            | `initscr()`                            |
| 结束程序                                              | `endwin()`                             |
| 移动光标                                              | `move(y,x)`                            |
| 打印字符                                              | `addch()`, `mvaddch(y,x,ch)`           |
| 刷新屏幕                                              | `refresh()`                            |
| 捕获键盘                                              | `getch()`, `nodelay(stdscr, TRUE)`     |
| 不回显输入                                            | noecho() \|\|相反echo()                |
| 零缓冲                                                | cbreak() \|\|nocbreak() 行缓冲         |
| 非阻塞模式                                            | nodelay(WINDOW *win, bool bf)          |
| 键盘模式                                              | keypad(WINDOW *win, bool bf)           |
| 将光标移动到指定的 (y, x) 位置，并将 ch 添加到 stdscr | mvaddch(int y, int x, const chtype ch) |
|                                                       | refresh()                              |

随机数
```cpp
    static std::random_device rd;//C++11 提供的 硬件真随机数生成器（如果平台支持）
    static std::mt19937 gen(rd());//梅森旋转伪随机数生成器
    static std::uniform_int_distribution<> distrib(0, 6);//用于生成 均匀分布的整数随机数

    int value = distrib(gen);
    return static_cast<BlockType>(value);//类型转换
```

```cpp
std::vector<std::vector<int>> block(x,std::vector<int>(y,0));//STL vector方式创建二维数组
```