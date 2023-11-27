#pragma once

#include <QDialog>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>

#include "Slider.h"
#include "Button.h"
#include "../GameLib/IGameSettings.h"

class SettingsScreen : public QDialog
{
	Q_OBJECT

public:
	SettingsScreen(IGameSettings& settings, QWidget* parent = nullptr);

private slots:
	void OnUpdateButtonClicked();
	void OnDiscardButtonClicked();

private:

	void AddFieldToLayout(QString fieldName, QWidget* widget = nullptr);
	void InitializeButtons();
	void InitializeValues();
	void InitializeComboBox(bool isFirstPlayerBox);
	void InitializeLayout();
	

private:
	IGameSettings& m_gameSettings;
	QGridLayout* m_layout;
	Slider* m_tableSizeSlider, * m_columnLimitSlider, * m_bridgeLimitSlider;
	QLineEdit* m_firstPlayerName, * m_secondPlayerName;
	QComboBox* m_firstPlayerColor, * m_secondPlayerColor;
	Button* m_updateButton, * m_discardButton;

	std::vector<EColor> m_colors;

	const static uint16_t minTableSize, maxTableSize;
	const static uint16_t minColumnLimit, maxColumnLimit;
	const static uint16_t minBridgeLimit, maxBridgeLimit;
	


};

