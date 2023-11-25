#pragma once

#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>

#include "Slider.h"
#include "../GameLib/IGameSettings.h"

class SettingsScreen : public QWidget
{
	Q_OBJECT

public:
	SettingsScreen(IGameSettings& settings, QWidget* parent = nullptr);

private:
	void AddFieldToLayout(QString fieldName, QWidget* widget = nullptr);
	void InitializeValues();
	void InitializeLayout();

private:
	IGameSettings& m_gameSettings;
	QGridLayout* m_layout;
	Slider* m_tableSizeSlider, * m_columnLimitSlider, * m_bridgeLimitSlider;
	QLineEdit* m_firstPlayerName, * m_secondPlayerName;
	QComboBox* m_firstPlayerColor, * m_secondPlayerColor;

	const static uint16_t minTableSize, maxTableSize;
	const static uint16_t minColumnLimit, maxColumnLimit;
	const static uint16_t minBridgeLimit, maxBridgeLimit;
	


};

