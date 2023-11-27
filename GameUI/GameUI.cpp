
#include <QGridLayout>
#include <QFontDatabase>

#include "GameUI.h"
#include "FileUtils.h"

GameUI::GameUI(QWidget *parent)
    : QMainWindow{parent}
    , m_screens{new QStackedWidget{this}}
{
    resize(1100, 600);
    LoadFonts();
    InitializeMainMenu();

    // Set the stylesheet from file
	QString stylesheet = FileUtils::StylesheetFileToString("stylesheets/default.qss");
	setStyleSheet(stylesheet);

    // Connect buttons
	connect(m_mainMenuScreen, SIGNAL(MenuClicked(const EButtonPressed&)), SLOT(OnMainMenuButtonClicked(const EButtonPressed&)));

}

GameUI::~GameUI()
{

}

void GameUI::OnMainMenuButtonClicked(const EButtonPressed& button)
{
    qDebug() << (int) button;

    // Load game screen when button pressed 
    if (button == EButtonPressed::playButton)
    {
        m_gameScreen = new GameScreen(this);
        m_screens->addWidget(m_gameScreen);
        m_screens->setCurrentWidget(m_gameScreen);
    }
    else if (button == EButtonPressed::settingsButton)
    {
		IGameSettings* settings = IGameSettings::GetInstance();
		m_settingsScreen = new SettingsScreen(*settings);
        m_settingsScreen->exec();
            
    }
}

void GameUI::InitializeMainMenu()
{

    // Initialize the main menu screen
	m_mainMenuScreen = new MainMenuScreen(m_screens);

    // Add main menu screen to screen list
	m_screens->addWidget(m_mainMenuScreen);
	m_screens->setCurrentWidget(m_mainMenuScreen);

    // Display the screen
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
