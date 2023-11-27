#pragma once

#include "Button.h"

enum class EButtonPressed
{
	playButton,
	settingsButton,
};

class MainMenuScreen : public QWidget
{
	Q_OBJECT

public:
	MainMenuScreen(QWidget* parent = nullptr);

public slots:
	void OnSettingsButtonClicked();
	void OnPlayButtonClicked();

signals:
	void MenuClicked(const EButtonPressed& button);

private:
	void InitPageWidgets();

private:
	QGridLayout* m_layout;
	QLabel* m_mainText, *m_imageWidget;
	Button* m_settingsButton, * m_playButton;

};

