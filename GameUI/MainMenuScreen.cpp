
#include <QLabel>
#include <QMouseEvent>

#include "MainMenuScreen.h"
#include "FileUtils.h"

MainMenuScreen::MainMenuScreen(QWidget* parent)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{
	// Init the page content
	InitPageWidgets();

	// Add rules for the layout
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_layout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(m_layout);

	// import the stylesheet for design
	auto stylesheet = FileUtils::StylesheetFileToString("stylesheets/mainmenu.qss");
	setStyleSheet(stylesheet);
}

void MainMenuScreen::mousePressEvent(QMouseEvent* event)
{
	QWidget* selectedWidget = childAt(event->pos());

	if (!selectedWidget) return;

	// Emit click on play button widget clicked
	if (WidgetIs(selectedWidget, "playButton"))
		emit(Clicked(EButtonPressed::playButton));
	// Emit click on settings button clicked
	else if (WidgetIs(selectedWidget, "settingsButton"))
		emit(Clicked(EButtonPressed::settingsButton));
}

void MainMenuScreen::InitPageWidgets()
{
	// Image init
	QLabel* imageWidget = new QLabel(this);
	imageWidget->setObjectName("imageWidget");
	QPixmap presentationImage(":/GameUI/images/presentation.png");
	imageWidget->setPixmap(presentationImage);
	imageWidget->setScaledContents(true);

	// Header text init
	mainText = new QLabel("    Play Twixt\non the #1 App!", this);
	mainText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mainText->setObjectName("mainText");

	// Play button init
	auto playButtonIcon = new QPixmap(":/GameUI/images/controller.png");
	Button* playButton = new Button("Play", this, "Play local with your friends", playButtonIcon);
	playButton->setObjectName("playButton");
	playButton->SetShadowColor("#466b3a");

	// Settings button init
	auto settingsButtonIcon = new QPixmap(":/GameUI/images/settings.png");
	Button* settingsButton = new Button("Settings", this, "Change the game settings", settingsButtonIcon);
	settingsButton->setObjectName("settingsButton");
	settingsButton->SetShadowColor("#333230");
	settingsButton->SetTextColor("#C4C4C3");
	settingsButton->SetTextShadowColor("#242423");
	
	// Add widgets for the screen layout
	m_layout->addWidget(imageWidget, 0, 0, 4, 1);
	m_layout->addWidget(mainText, 0, 1, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(playButton, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(settingsButton, 3, 1, Qt::AlignCenter);
}

bool MainMenuScreen::WidgetIs(QWidget* widget, QString objectName)
{
	return widget->parentWidget()->objectName() == objectName || widget->objectName() == objectName;
}

