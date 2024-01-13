#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "IPlayer.h"

class PlayerBar : public QWidget
{
public:
	PlayerBar(const IPlayer& player, bool turn, QWidget* parent = nullptr);
	void Update(bool playerTurn);

private:
	const IPlayer& m_player;
	QGridLayout* m_layout;
	QLabel* m_profilePicture, * m_playerName;

};