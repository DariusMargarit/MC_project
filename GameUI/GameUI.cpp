
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

    InitializeScreen();
}

GameUI::~GameUI()
{

}

void GameUI::OnMainMenuButtonClicked(const EButtonPressed& button)
{
    qDebug() << (int) button;
}

void GameUI::mousePressEvent(QMouseEvent* event)
{
  
}

void GameUI::InitializeScreen()
{
	m_screens = new QStackedWidget();
	m_mainMenuScreen = new MainMenuScreen();
	connect(m_mainMenuScreen, &MainMenuScreen::Clicked, this, &GameUI::OnMainMenuButtonClicked);
	m_screens->addWidget(m_mainMenuScreen);
	m_screens->setCurrentWidget(m_mainMenuScreen);
	setCentralWidget(m_screens);
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
