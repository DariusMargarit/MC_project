#include "GameUI.h"
#include <QGridLayout>

GameUI::GameUI(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui.setupUi(this);
    m_screens = new QStackedWidget();
    setCentralWidget(m_screens);
    m_mainMenuScreen = new MainMenuScreen();
    m_screens->addWidget(m_mainMenuScreen);
    m_screens->setCurrentWidget(m_mainMenuScreen);
}

GameUI::~GameUI()
{

}

void GameUI::mousePressEvent(QMouseEvent* event)
{
  
}
