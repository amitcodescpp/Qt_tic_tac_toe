#ifndef COMMONUTIL_H
#define COMMONUTIL_H

#include <cstddef>
#include <QString>

enum class XO {
    EMPTY,
    X = 1,
    O = 2
};

enum GameState {
    WinnerX = 0,
    WinnerO = 1,
    Draw    = 2,
    Playing = 3
};

struct Cell {
    Cell (size_t row_, size_t col_)
    : row(row_)
    , col(col_) { }
    std::size_t row;
    std::size_t col;
};


#endif // COMMONUTIL_H
