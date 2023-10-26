#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_GameUI.h"
#include "Board.h";

class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    GameUI(QWidget *parent = nullptr);
    ~GameUI();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::GameUIClass ui;
    Board* m_board;
};
