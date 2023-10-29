#pragma once
#include <QWidget>
#include <QGridLayout>

class MainMenuScreen : public QWidget
{
public:
	MainMenuScreen(QWidget* parent = nullptr);

private:
	void InitPage();
	void InitButton(QWidget& button, const QString& firstLabel, const QString& secondLabel);

	QGridLayout* m_layout;

};

