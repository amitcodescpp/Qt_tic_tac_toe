#include "tictactoedatamodel.h"

TicTacToeDataModel::TicTacToeDataModel()
{
    reset();
}


XO
TicTacToeDataModel::getValue(Cell cell) const
{
    return board[cell.row][cell.col];
}

bool
TicTacToeDataModel::setValue(Cell cell, XO value, bool isDryRunMode)
{
    if (isDryRunMode) {
        board[cell.row][cell.col] = value;
        return true;
    }

    // TODO check if game is not over
    if (getGameState() != GameState::Playing) {
        return false;
    }

    if (board[cell.row][cell.col] == XO::EMPTY) {
        board[cell.row][cell.col] = value;
        return true;
    }

    return false;
}

GameState
TicTacToeDataModel::getGameState()
{
    XO refVal = board[0][0];
    bool gameWon = false;

    // Check if the current player has won any row
    for (size_t row = 0; (!gameWon && row < 3); row++) {
        refVal = board[row][0];
        if (XO::EMPTY != refVal &&
            board[row][0] == refVal &&
            board[row][1] == refVal &&
            board[row][2] == refVal) {
            gameWon = true;
        }
    }

    // Check if the current player has won any row
    for (size_t col = 0; (!gameWon && col < 3); col++) {
        refVal = board[0][col];
        if (XO::EMPTY != refVal &&
            board[0][col] == refVal &&
            board[1][col] == refVal &&
            board[2][col] == refVal) {
            gameWon = true;
        }
    }

    // Check if the current player has won any diagonal
    if (!gameWon) {
        refVal = board[0][0];
        if (XO::EMPTY != refVal &&
            board[0][0] == refVal &&
            board[1][1] == refVal &&
            board[2][2] == refVal) {
            gameWon = true;
        }
    }

     if (!gameWon) {
        refVal = board[0][2];
        if (XO::EMPTY != refVal &&
            board[0][2] == refVal &&
            board[1][1] == refVal &&
            board[2][0] == refVal) {
            gameWon = true;
        }
    }

    if (gameWon) {
        if (refVal == XO::X) {
            return GameState::WinnerX;
        } else {
            return GameState::WinnerO;
        }
    }

    // Check if the game is a draw i.e. no winner and no empty cells left
    for (size_t row = 0; row < 3; ++row)
        for (size_t col = 0; col < 3; ++col)
            if (XO::EMPTY == board[row][col])
                return GameState::Playing;

    return GameState::Draw;
}

void TicTacToeDataModel::reset()
{
    for (size_t row = 0; row < 3; row++) {
        for (size_t col = 0; col < 3; col++) {
            board[row][col] = XO::EMPTY;
        }
    }
}
