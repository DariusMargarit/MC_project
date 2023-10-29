
#include <QLabel>
#include <QGraphicsDropShadowEffect>

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

void MainMenuScreen::InitPage()
{

	QLabel* imageWidget = new QLabel();
	imageWidget->setObjectName("imageWidget");
	QPixmap presentationImage(":/GameUI/images/presentation.png");
	imageWidget->setPixmap(presentationImage);
	imageWidget->setScaledContents(true);

	QLabel* mainText = new QLabel("    Play Twixt\non the #1 App!");
	mainText->setObjectName("mainText");


	QWidget* playButton = new QWidget();
	InitButton(*playButton, "Play", "Play local with your friends");
	playButton->setObjectName("playButton");
	auto playButtonEffect = new QGraphicsDropShadowEffect();
	playButtonEffect->setXOffset(0);
	playButtonEffect->setYOffset(8);
	playButtonEffect->setColor("#466b3a");
	playButton->setGraphicsEffect(playButtonEffect);

	QWidget* settingsButton = new QWidget();
	InitButton(*settingsButton, "Settings", "Change the game settings");
	settingsButton->setObjectName("settingsButton");
	auto settingsButtonEffect = new QGraphicsDropShadowEffect();
	settingsButtonEffect->setXOffset(0);
	settingsButtonEffect->setYOffset(8);
	settingsButtonEffect->setColor("#333230");
	settingsButton->setGraphicsEffect(settingsButtonEffect);
	

	m_layout->addWidget(imageWidget, 0, 0, 4, 1);
	m_layout->addWidget(mainText, 0, 1, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(playButton, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(settingsButton, 3, 1, Qt::AlignCenter);
}

void MainMenuScreen::InitButton(QWidget& button, const QString& firstLabel, const QString& secondLabel)
{
	QGridLayout* buttonLayout = new QGridLayout();

	QLabel* titleLabel = new QLabel(firstLabel);
	titleLabel->setObjectName("titleLabel");

	QLabel* descriptionLabel = new QLabel(secondLabel);
	descriptionLabel->setObjectName("descriptionLabel");

	titleLabel->setScaledContents(true);
	descriptionLabel->setScaledContents(true);

	buttonLayout->addWidget(titleLabel, 0, 0, Qt::AlignLeft);
	buttonLayout->addWidget(descriptionLabel, 1, 0, Qt::AlignLeft);


	button.setLayout(buttonLayout);




}
