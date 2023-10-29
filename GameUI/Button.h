#pragma once

#include <QWidget>
#include <QGridLayout>

class Button : public QWidget
{
public:
	Button(QString firstLabel, QString secondLabel, QColor shadowColor);

private:
	QGridLayout* m_layout;
};

