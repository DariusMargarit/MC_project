#include "GameUI.h"
#include <QGridLayout>

GameUI::GameUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QGridLayout* mainGridLayout = new QGridLayout();
	QWidget* mainWidget = new QWidget();
}

GameUI::~GameUI()
{
}
