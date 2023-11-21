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

signals:
	void Clicked(const EButtonPressed& button);

protected:
	void mousePressEvent(QMouseEvent* event) override;

private:
	void InitPageWidgets();
	bool WidgetIs(QWidget* widget, QString objectName);

private:
	QGridLayout* m_layout;
	QLabel* mainText;

};

