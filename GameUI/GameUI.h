#pragma once

#include <QStackedWidget>

#include "ui_GameUI.h"
#include "MainMenuScreen.h";
#include "SettingsScreen.h";
#include "GameScreen.h";

class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    GameUI(QWidget *parent = nullptr);
    ~GameUI();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::GameUIClass m_ui;
    QStackedWidget* m_screens;
    MainMenuScreen* m_mainMenuScreen;
    SettingsScreen* m_settingsScreen;
    GameScreen* m_gameScreen;
};
