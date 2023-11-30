
#include <QLabel>
#include <QMouseEvent>

#include "MainMenuScreen.h"
#include "FileUtils.h"

MainMenuScreen::MainMenuScreen(QWidget* parent)
	: QWidget{ parent }
	, m_layout{ new QGridLayout{this} }
{
	// Init the page content
	InitPageWidgets();

	// Add rules for the layout
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_layout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(m_layout);

	// import the stylesheet for design
	auto stylesheet{ FileUtils::StylesheetFileToString("stylesheets/mainmenu.qss") };
	setStyleSheet(stylesheet);

	connect(m_playButton, SIGNAL(ButtonClicked()), SLOT(OnPlayButtonClicked()));
	connect(m_settingsButton, SIGNAL(ButtonClicked()), SLOT(OnSettingsButtonClicked()));

}

void MainMenuScreen::OnSettingsButtonClicked()
{
	emit(MenuClicked(EButtonPressed::settingsButton));
}

void MainMenuScreen::OnPlayButtonClicked()
{
	emit(MenuClicked(EButtonPressed::playButton));
}

void MainMenuScreen::InitPageWidgets()
{
	// Image init
	QLabel* imageWidget{ new QLabel(this) };
	imageWidget->setObjectName("imageWidget");
	QPixmap presentationImage(":/GameUI/images/presentation.png");
	imageWidget->setPixmap(presentationImage);
	imageWidget->setScaledContents(true);

	// Header text init
	m_mainText = new QLabel("    Play Twixt\non the #1 App!", this);
	m_mainText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_mainText->setObjectName("mainText");

	// Play button init
	auto playButtonIcon = new QPixmap(":/GameUI/images/controller.png");
	m_playButton = new Button("Play", this, "Play local with your friends", playButtonIcon);
	m_playButton->setObjectName("playButton");
	m_playButton->SetShadowColor("#466b3a");

	// Settings button init
	auto settingsButtonIcon = new QPixmap(":/GameUI/images/settings.png");
	m_settingsButton = new Button("Settings", this, "Change the game settings", settingsButtonIcon);
	m_settingsButton->setObjectName("settingsButton");
	m_settingsButton->SetShadowColor("#333230");
	m_settingsButton->SetTextColor("#C4C4C3");
	m_settingsButton->SetTextShadowColor("#242423");
	
	// Add widgets for the screen layout
	m_layout->addWidget(imageWidget, 0, 0, 4, 1);
	m_layout->addWidget(m_mainText, 0, 1, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(m_playButton, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(m_settingsButton, 3, 1, Qt::AlignCenter);
}
