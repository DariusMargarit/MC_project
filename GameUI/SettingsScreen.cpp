#include "SettingsScreen.h"


SettingsScreen::SettingsScreen(IGameSettings& settings, QWidget* parent)
	: QDialog{parent}
	, m_gameSettings{settings}
	, m_layout{new QGridLayout{this}}
	, m_tableSizeSlider{new QSlider{Qt::Horizontal, this}}
	, m_columnSizeSlider{new QSlider{Qt::Horizontal, this}}
	, m_bridgesSizeSlider{new QSlider{Qt::Horizontal, this}}
	, m_tableSizeLabel{new QLabel{this}}
	, m_columnSizeLabel{new QLabel{this}}
	, m_bridgesSizeLabel{new QLabel{this}}
	, m_firstPlayerName{new QLineEdit{this}}
	, m_secondPlayerName{new QLineEdit{this}}
	, m_firstPlayerColor{ new QComboBox{this} }
	, m_secondPlayerColor{ new QComboBox{this} }
{
	InitializeLayout();
	setLayout(m_layout);
}

void SettingsScreen::InitializeLayout()
{
	// Board settings related widgets
	m_layout->addWidget(m_tableSizeSlider, 0, 0, 1, 3, Qt::AlignCenter);
	m_layout->addWidget(m_tableSizeLabel, 0, 3, 1, 1, Qt::AlignCenter);
	m_layout->addWidget(m_columnSizeSlider, 1, 0, 1, 3, Qt::AlignCenter);
	m_layout->addWidget(m_columnSizeLabel, 1, 3, 1, 1, Qt::AlignCenter);
	m_layout->addWidget(m_bridgesSizeSlider, 2, 0, 1, 3, Qt::AlignCenter);
	m_layout->addWidget(m_bridgesSizeLabel, 2, 3, 1, 1, Qt::AlignCenter);

	// Player settings related widgets
	m_layout->addWidget(m_firstPlayerName, 3, 0, Qt::AlignCenter);
	m_layout->addWidget(m_firstPlayerColor, 3, 1, Qt::AlignCenter);
	m_layout->addWidget(m_secondPlayerName, 4, 0, Qt::AlignCenter);
	m_layout->addWidget(m_secondPlayerColor, 4, 1, Qt::AlignCenter);



}
