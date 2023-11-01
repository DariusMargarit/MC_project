
#include <QGraphicsDropShadowEffect>

#include "Button.h"

Button::Button(QString firstLabel, QString secondLabel, QColor shadowColor, QPixmap icon, bool contrastButton)
{
	m_layout = new QGridLayout();

	QLabel* titleLabel = new QLabel(firstLabel);
	titleLabel->setObjectName("titleLabel");

	QLabel* descriptionLabel = new QLabel(secondLabel);
	descriptionLabel->setObjectName("descriptionLabel");


	QLabel* iconLabel = new QLabel();
	iconLabel->setPixmap(icon);
	iconLabel->setObjectName("buttonIcon");

	titleLabel->setScaledContents(true);
	descriptionLabel->setScaledContents(true);

	m_layout->addWidget(iconLabel, 0, 0, 2, 1, Qt::AlignLeft);
	m_layout->addWidget(titleLabel, 0, 1, 1, 3, Qt::AlignLeft);
	m_layout->addWidget(descriptionLabel, 1, 1, 1, 3, Qt::AlignLeft);

	auto titleEffect = new QGraphicsDropShadowEffect();
	titleEffect->setXOffset(0);
	titleEffect->setYOffset(1);

	auto descriptionEffect = new QGraphicsDropShadowEffect();
	descriptionEffect->setXOffset(0);
	descriptionEffect->setYOffset(1);

	auto iconEffect = new QGraphicsDropShadowEffect();
	iconEffect->setColor("#171716");
	iconEffect->setOffset(1);
	iconEffect->setBlurRadius(2);

	if (contrastButton) {
		titleLabel->setStyleSheet("color: #C4C4C3;");
		descriptionLabel->setStyleSheet("color: #C4C4C3;");

		titleEffect->setColor("#242423");
		descriptionEffect->setColor("#242423");
	}

	titleLabel->setGraphicsEffect(titleEffect);
	descriptionLabel->setGraphicsEffect(descriptionEffect);
	iconLabel->setGraphicsEffect(iconEffect);

	auto buttonEffect = new QGraphicsDropShadowEffect();
	buttonEffect->setXOffset(0);
	buttonEffect->setYOffset(8);
	buttonEffect->setColor(shadowColor);
	setGraphicsEffect(buttonEffect);

	setLayout(m_layout);
}

