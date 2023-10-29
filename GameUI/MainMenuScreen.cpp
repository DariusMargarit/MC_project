
#include <QLabel>
#include <QMouseEvent>

#include "MainMenuScreen.h"
#include "FileUtils.h"

MainMenuScreen::MainMenuScreen(QWidget* parent)
{
	m_layout = new QGridLayout();
	InitPage();
	setLayout(m_layout);

	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	auto stylesheet = FileUtils::StylesheetFileToString("stylesheets/mainmenu.qss");
	setStyleSheet(stylesheet);
}

void MainMenuScreen::mousePressEvent(QMouseEvent* event)
{
	QWidget* selectedWidget = childAt(event->pos());
	if (!selectedWidget) return;
	if (WidgetIs(selectedWidget, "playButton"))
		emit(Clicked(EButtonPressed::playButton));
	else if (WidgetIs(selectedWidget, "settingsButton"))
		emit(Clicked(EButtonPressed::settingsButton));
}

void MainMenuScreen::InitPage()
{

	QLabel* imageWidget = new QLabel();
	imageWidget->setObjectName("imageWidget");
	QPixmap presentationImage(":/GameUI/images/presentation.png");
	imageWidget->setPixmap(presentationImage);
	imageWidget->setScaledContents(true);

	QLabel* mainText = new QLabel("    Play Twixt\non the #1 App!");
	mainText->setObjectName("mainText");


	Button* playButton = new Button("Play", "Play local with your friends", "#466b3a");
	playButton->setObjectName("playButton");
	Button* settingsButton = new Button("Settings", "Change the game settings", "#333230");
	settingsButton->setObjectName("settingsButton");
	

	m_layout->addWidget(imageWidget, 0, 0, 4, 1);
	m_layout->addWidget(mainText, 0, 1, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(playButton, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(settingsButton, 3, 1, Qt::AlignCenter);
}

bool MainMenuScreen::WidgetIs(QWidget* widget, QString objectName)
{
	return widget->parentWidget()->objectName() == objectName || widget->objectName() == objectName;
}

