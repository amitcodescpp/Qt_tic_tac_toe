#ifndef TICTACTOEDATAMODEL_H
#define TICTACTOEDATAMODEL_H

#include "commonUtil.h"

class TicTacToeDataModel
{
private:
    XO board[3][3];
public:
    TicTacToeDataModel();
    TicTacToeDataModel(TicTacToeDataModel &model);
    TicTacToeDataModel(TicTacToeDataModel &&model);
    void operator=(TicTacToeDataModel &model);


    XO getValue(Cell cell) const;
    bool setValue(Cell cell, XO value, bool isDryRunMode = false);
    void reset();

    GameState getGameState();
};

#endif // TICTACTOEDATAMODEL_H
