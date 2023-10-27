#pragma once
#include <QWidget>
#include <QGridLayout>

class MainMenuScreen : public QWidget
{
public:
	MainMenuScreen(QWidget* parent = nullptr);


private:
	QGridLayout* m_layout;

};

