#include "computerplayer.h"
#include <limits>

ComputerPlayer::ComputerPlayer()
{
    m_scoresX[GameState::Draw]     = 0;
    m_scoresX[GameState::WinnerO]  = -1;
    m_scoresX[GameState::WinnerX]  = 1;

    m_scoresO[GameState::Draw]     = 0;
    m_scoresO[GameState::WinnerO]  = 1;
    m_scoresO[GameState::WinnerX]  = -1;
}

Cell
ComputerPlayer::playMove(TicTacToeDataModel &model, XO sign)
{
    Cell move(0, 0);

    int bestScore = INT_MIN;

    for (size_t row = 0; row < 3; ++row) {
        for (size_t col = 0; col < 3; ++col) {
            // if the cell is empty
            if (model.getValue(Cell(row, col)) == XO::EMPTY) {

                // try playing the cell
                model.setValue(Cell(row, col), sign, true);

                int currentScore = minimax(model, 0, false, sign);

                // reset the cell
                model.setValue(Cell(row, col), XO::EMPTY, true);

                if (currentScore > bestScore) {
                    bestScore = currentScore;
                    move.row = row;
                    move.col = col;
                }
            }
        }
    }
    return move;
}

int
ComputerPlayer::minimax(TicTacToeDataModel &model, size_t depth, bool isMaximizing, XO sign)
{
    GameState state = model.getGameState();
    if (GameState::Playing != state) {
        return (sign == XO::X) ? m_scoresX[state] : m_scoresO[state];
    }

    if (isMaximizing) {
        // Maximimize computer's score
        int bestScore = INT_MIN;

        for (size_t row = 0; row < 3; ++row) {
            for (size_t col = 0; col < 3; ++col) {

                // if the cell is empty
                if (model.getValue(Cell(row, col)) == XO::EMPTY) {

                    // try playing the cell with computer's sign
                    model.setValue(Cell(row, col), sign, true);

                    int currentScore = minimax(model, depth + 1, false, sign);

                    // reset the cell
                    model.setValue(Cell(row, col), XO::EMPTY, true);

                    bestScore = std::max(currentScore, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        // Minimize opponent's score
        int bestScore = INT_MAX;

        for (size_t row = 0; row < 3; ++row) {
            for (size_t col = 0; col < 3; ++col) {

                // if the cell is empty
                if (model.getValue(Cell(row, col)) == XO::EMPTY) {

                    // try playing the cell with opponent's sign
                    model.setValue(Cell(row, col), (sign == XO::X ? XO::O : XO::X), true);

                    int currentScore = minimax(model, depth + 1, true, sign);

                    // reset the cell
                    model.setValue(Cell(row, col), XO::EMPTY, true);

                    bestScore = std::min(currentScore, bestScore);
                }
            }
        }
        return bestScore;
    }
}
