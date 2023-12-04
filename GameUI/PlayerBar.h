#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "IPlayer.h"

class PlayerBar : public QWidget
{
public:
	PlayerBar(const IPlayer& player, QWidget* parent = nullptr);


private:
	void FillPixmapBackground(QPixmap& pixmap);

	const IPlayer& m_player;
	QGridLayout* m_layout;
	QLabel* m_profilePicture, * m_playerName;

};