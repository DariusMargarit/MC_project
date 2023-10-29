
#include <QGridLayout>
#include <QFontDatabase>

#include "GameUI.h"
#include "FileUtils.h"

GameUI::GameUI(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1100, 600);
    LoadFonts();

	QString stylesheet = FileUtils::StylesheetFileToString("stylesheets/default.qss");
	setStyleSheet(stylesheet);

    m_screens = new QStackedWidget();
    m_mainMenuScreen = new MainMenuScreen();
    m_screens->addWidget(m_mainMenuScreen);
    m_screens->setCurrentWidget(m_mainMenuScreen);
    setCentralWidget(m_screens);

}

GameUI::~GameUI()
{

}

void GameUI::mousePressEvent(QMouseEvent* event)
{
  
}

void GameUI::LoadFonts()
{
    QString path = ":/GameUI/fonts/";
    QFontDatabase::addApplicationFont(path + "Montserrat-Black.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Bold.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Light.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Medium.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Regular.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-SemiBold.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Thin.ttf");

}
