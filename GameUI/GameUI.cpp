#include "GameUI.h"
#include <QGridLayout>

GameUI::GameUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QGridLayout* mainGridLayout = new QGridLayout();
    m_board = new Board(10);
    mainGridLayout->addWidget(m_board);
    ui.centralWidget->setLayout(mainGridLayout);
}

GameUI::~GameUI()
{
}
