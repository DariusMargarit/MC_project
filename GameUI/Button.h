#pragma once

#include <QLabel>
#include <QGridLayout>

class Button : public QWidget
{

public:
	Button(QString headerText, QWidget* parent = nullptr, QString descriptionText = "", QPixmap* icon = nullptr);

	void SetTextColor(QColor color);
	void SetTextShadowColor(QColor color);
	void SetShadowColor(QColor color);

private:
	QGridLayout* m_layout;
	QLabel* m_headerLabel, * m_descriptionLabel, *m_iconLabel;
};

