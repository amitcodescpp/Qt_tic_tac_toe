#include "tictactoecontroller.h"
#include <iostream>

TicTacToeController::TicTacToeController(QObject *parent)
    :  QObject(parent)
    , m_view()
    , m_model()
    , m_current_move(XO::X)
    , m_computerPlayer()
{
    connect(&m_view,
            &GameViewInterface::cellClickedSignal,
            this,
            userMove);
    connect(&m_view,
            &GameViewInterface::resetSignal,
            this,
            resetGame);
}

void
TicTacToeController::start()
{
    m_view.show();
}

TicTacToeController::~TicTacToeController()
{

}

void
TicTacToeController::computerMove()
{
    GameState state = m_model.getGameState();
    if (state != GameState::Playing) {
        return;
    }

    // get the computer move
    Cell move = m_computerPlayer.playMove(m_model, m_current_move);

    //std::cout << "[" << move.row << "][" << move.col << "] played by computer" << std::endl;

    // Update data model
    bool isValid = m_model.setValue(move, m_current_move);

    if (!isValid) {
        // computer clicked a non-empty cell
        // not possible
        std::cout << "This is not a valid computer move" << std::endl;
        assert(0 && "Invalid computer move");
    }

    // update the game board and view
    updateGame(move.row, move.col);
}

void
TicTacToeController::userMove(size_t row, size_t col)
{
    //std::cout << "[" << row << "][" << col << "] pressed" << std::endl;

    // Update data model
    bool isValid = m_model.setValue(Cell(row, col), m_current_move);

    if (!isValid) {
        // user clicked a non-empty cell
        std::cout << "This is not a valid user move" << std::endl;
        return;
    }

    // update the game board and view
    updateGame(row, col);

    // Computer plays the move
    computerMove();
}

void
TicTacToeController::updateGame(size_t row, size_t col)
{
    // Update View
    m_view.updateView(Cell(row, col), m_current_move);

    // check game status
    GameState state = m_model.getGameState();
    if (state != GameState::Playing) {
        m_view.resultPopup(state);
    }

    // Toggle player - between user and computer
    togglePlayer();
}

void
TicTacToeController::togglePlayer()
{
    if (m_current_move == XO::O) {
        m_current_move = XO::X;
    } else if (m_current_move == XO::X) {
        m_current_move = XO::O;
    } else {
        // not possible
        assert(0 && "Impossible state");
    }
}
void
TicTacToeController::resetGame()
{
    m_current_move = XO::X;
    m_view.resetView();
    m_model.reset();
    m_computerPlayer.playMove(m_model, m_current_move);
}

