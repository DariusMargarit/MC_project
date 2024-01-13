
#include <QPainter>

#include "PlayerBar.h"
#include "ColorUtils.h"

PlayerBar::PlayerBar(const IPlayer& player, bool turn, QWidget* parent) 
	: QWidget{parent}
	, m_player{player}
	, m_layout{new QGridLayout{this}}
	, m_profilePicture{new QLabel{this}}
	, m_playerName{new QLabel{this}}
{
	setFixedHeight(60);
	m_profilePicture->setFixedSize(60, 60);
	m_profilePicture->setObjectName("profilePicture");
	m_playerName->setObjectName("playerName");

	Update(turn);

	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->addWidget(m_profilePicture, 0, 0, 2, 1);
	m_layout->addWidget(m_playerName, 0, 1);

	setLayout(m_layout);
}

void PlayerBar::Update(bool playerTurn)
{
	QPixmap profilePicture(":/GameUI/images/profile.png");
	ColorUtils::FillPixmapBackground(profilePicture, m_player.GetColor());
	m_profilePicture->setPixmap(profilePicture);
	m_playerName->setText(QString(m_player.GetName().data()) + (playerTurn ? " (turn)" : ""));

	setLayout(m_layout);
}


