#pragma once

#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

#include "../GameLib/IGameSettings.h"

class SettingsScreen : public QWidget
{
	Q_OBJECT

public:
	SettingsScreen(IGameSettings& settings, QWidget* parent = nullptr);

private:
	void InitializeLayout();

private:
	IGameSettings& m_gameSettings;
	QGridLayout* m_layout;
	QSlider* m_tableSizeSlider, * m_columnSizeSlider, * m_bridgesSizeSlider;
	QLabel* m_tableSizeLabel, * m_columnSizeLabel, * m_bridgesSizeLabel;
	QLineEdit* m_firstPlayerName, * m_secondPlayerName;
	QComboBox* m_firstPlayerColor, * m_secondPlayerColor;
	


};

