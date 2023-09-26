#include "gameviewinterface.h"
#include <QMessageBox>

const QString GameViewInterface::m_styleSheet = "font: bold 72px;"
                                                "min-height: 200px;"
                                                "max-height: 200px;"
                                                "min-width:  200px;"
                                                "max-width:  200px;";

GameViewInterface::GameViewInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}


GameViewInterface::~GameViewInterface()
{

}

void
GameViewInterface::initialize()
{
    // build the layout
    cells.resize(3);
    for (auto& cell : cells) {
        cell.resize(3);
    }

    for (size_t row = 0; row < cells.size(); row++) {
        for (size_t col = 0; col < cells[row].size(); col++) {
            QPushButton *cell = new QPushButton();
            cell->setStyleSheet(GameViewInterface::m_styleSheet);
            cell->setText("");
            ui->gridLayout->addWidget(cell, row, col);
            connect(cell,
                    QPushButton::clicked,
                    this,
                    [=] { updateGame(row, col); });
            cells[row][col] = cell;
        }
    }
    connect(ui->newGameButton,
            QPushButton::clicked,
            this,
            [=] { emit resetSignal(); });
}

void
GameViewInterface::updateView(Cell cell, XO xo)
{
    QString str = "";
    switch (xo) {
        case XO::EMPTY:
            break;
        case XO::O:
            str = "O";
            break;
        case XO::X:
            str = "X";
            break;
    }

    cells[cell.row][cell.col]->setText(str);
}

void
GameViewInterface::resetView()
{
    for (size_t row = 0; row < cells.size(); row++) {
            for (size_t col = 0; col < cells[row].size(); col++) {
                cells[row][col]->setText("");
            }
    }
}

void
GameViewInterface::updateGame(std::size_t row, std::size_t col)
{
    emit cellClickedSignal(row, col);
}

void GameViewInterface::resultPopup(GameState &boardState)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Result");

    QString msg = "";
    switch (boardState) {
        case GameState::WinnerX:
            msg = "X Won!";
            break;
        case GameState::WinnerO:
            msg = "O Won!";
            break;
        case GameState::Draw:
            msg = "Game is a draw!";
            break;
        default:
            break;
    }

    msgBox.setText(msg);
    msgBox.exec();
}

