
#include <QPainter>

#include "PlayerBar.h"
#include "ColorUtils.h"

PlayerBar::PlayerBar(const IPlayer& player, QWidget* parent) 
	: QWidget{parent}
	, m_player{player}
	, m_layout{new QGridLayout{this}}
	, m_profilePicture{new QLabel{this}}
	, m_playerName{new QLabel{this}}
{
	setFixedHeight(60);

	QPixmap profilePicture(":/GameUI/images/profile.png");
	FillPixmapBackground(profilePicture);
	m_profilePicture->setPixmap(profilePicture);
	m_profilePicture->setFixedSize(60, 60);
	m_profilePicture->setObjectName("profilePicture");

	m_playerName->setText(QString(player.GetName().data()));
	m_playerName->setObjectName("playerName");

	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->addWidget(m_profilePicture, 0, 0, 2, 1);
	m_layout->addWidget(m_playerName, 0, 1);
	setLayout(m_layout);
}

void PlayerBar::FillPixmapBackground(QPixmap& pixmap)
{
	QColor targetColor = ColorUtils::TwixtColorToQColor(m_player.GetColor());
	QImage image = pixmap.toImage();

	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			if (image.pixelColor(x, y).alpha() == 0)
			{
				image.setPixelColor(x, y, targetColor);
			}
		}
	}
	pixmap = QPixmap::fromImage(image);
}



