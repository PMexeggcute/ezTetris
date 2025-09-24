cmake_minimum_required(VERSION 3.20)
project(Tetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 你的项目头文件
include_directories(include)

add_executable(Tetris
        src/main.cpp
        src/game.cpp
        src/board.cpp
        src/tetromino.cpp
        include/constants.h
)

if (WIN32)
    # --- 如果你自己已经用 mingw32-make 编译过 pdcurses.a ---
    # 1. 告诉编译器头文件在哪
    target_include_directories(Tetris PRIVATE
            ${CMAKE_SOURCE_DIR}/third_party/pdcurses
    )

    # 2. 直接链接静态库文件
    target_link_libraries(Tetris PRIVATE
            ${CMAKE_SOURCE_DIR}/third_party/pdcurses/wincon/pdcurses.a
    )

else()
    # Linux / macOS：使用系统自带 ncurses
    find_package(Curses REQUIRED)
    target_link_libraries(Tetris PRIVATE ${CURSES_LIBRARIES})
    target_include_directories(Tetris PRIVATE ${CURSES_INCLUDE_DIR})
endif()
