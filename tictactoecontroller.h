#ifndef TICTACTOECONTROLLER_H
#define TICTACTOECONTROLLER_H

#include "QObject"
#include "gameviewinterface.h"
#include "tictactoedatamodel.h"
#include "computerplayer.h"

class TicTacToeController : public QObject
{
    Q_OBJECT

private:
    // View (UI) for the game
    GameViewInterface m_view;

    // Underlying data model for the game data
    TicTacToeDataModel m_model;

    // Current move
    XO m_current_move;

    // Computer Player
    ComputerPlayer m_computerPlayer;

public:
    TicTacToeController(QObject *parent = nullptr);
    virtual ~TicTacToeController();

    // initialize the game by setting up
    // signals and slots
    void initialize();

    // Starts the game
    void start();

    void togglePlayer();

private:
    void computerMove();
    void updateGame(size_t, size_t);

public slots:
    // Signal handler for signals emitted by the view
    // when user clicks on the UI to provide inputs
    void userMove(size_t row, size_t col);

    // Signal handler for signals emiitted by the view
    // when user resets the game (new game)
    void resetGame();

};

#endif // TICTACTOECONTROLLER_H
