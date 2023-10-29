
#include <QGraphicsDropShadowEffect>
#include <QLabel>

#include "Button.h"

Button::Button(QString firstLabel, QString secondLabel, QColor shadowColor)
{
	m_layout = new QGridLayout();

	QLabel* titleLabel = new QLabel(firstLabel);
	titleLabel->setObjectName("titleLabel");

	QLabel* descriptionLabel = new QLabel(secondLabel);
	descriptionLabel->setObjectName("descriptionLabel");

	titleLabel->setScaledContents(true);
	descriptionLabel->setScaledContents(true);

	m_layout->addWidget(titleLabel, 0, 0, Qt::AlignLeft);
	m_layout->addWidget(descriptionLabel, 1, 0, Qt::AlignLeft);

	auto buttonEffect = new QGraphicsDropShadowEffect();
	buttonEffect->setXOffset(0);
	buttonEffect->setYOffset(8);
	buttonEffect->setColor(shadowColor);
	setGraphicsEffect(buttonEffect);

	setLayout(m_layout);
}

