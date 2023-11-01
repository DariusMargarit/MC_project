#pragma once

#include <QLabel>
#include <QGridLayout>

class Button : public QWidget
{
public:
	Button(QString firstLabel, QString secondLabel, QColor shadowColor, QPixmap icon, bool contrastButton);

private:
	QGridLayout* m_layout;
};

