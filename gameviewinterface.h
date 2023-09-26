#ifndef GAMEVIEWINTERFACE_H
#define GAMEVIEWINTERFACE_H

#include "QObject"
#include "QMainWindow"
#include "QPushButton"
#include "commonUtil.h"
#include "ui_mainwindow.h"

class GameViewInterface : public QMainWindow
{
    Q_OBJECT

private:
    const static QString m_styleSheet;
    std::unique_ptr<Ui::MainWindow> ui;
    std::vector<std::vector<QPushButton*> > cells;

    void initialize();
    void updateGame(std::size_t row, std::size_t col);

public:
    GameViewInterface(QWidget *parent = nullptr);
    virtual ~GameViewInterface();

    void updateView(Cell cell, XO xo);
    void resetView();
    void resultPopup(GameState &boardState);

signals:
    void resetSignal();
    void cellClickedSignal(std::size_t row, std::size_t col);

};

#endif // GAMEVIEWINTERFACE_H
