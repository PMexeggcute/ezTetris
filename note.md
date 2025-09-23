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

