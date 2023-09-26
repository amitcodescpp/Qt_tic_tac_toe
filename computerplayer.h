#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "tictactoedatamodel.h"

class ComputerPlayer
{

public:
    ComputerPlayer();
    Cell playMove(TicTacToeDataModel &model, XO sign);
    int minimax(TicTacToeDataModel &model, size_t depth, bool isMaximizing, XO sign);

private:
    int m_scoresX[3];
    int m_scoresO[3];
};

#endif // COMPUTERPLAYER_H
