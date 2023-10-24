#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_GameUI.h"
#include "BoardButton.h";

class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    GameUI(QWidget *parent = nullptr);
    ~GameUI();

private:
    Ui::GameUIClass ui;
};
