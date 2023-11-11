
#include <QGraphicsDropShadowEffect>

#include "Button.h"

Button::Button(QString firstLabel, QString secondLabel, QColor shadowColor, QPixmap icon, bool contrastButton, QWidget* parent)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{
	// Title
	QLabel* titleLabel = new QLabel(firstLabel, this);
	titleLabel->setObjectName("titleLabel");

	// Description
	QLabel* descriptionLabel = new QLabel(secondLabel, this);
	descriptionLabel->setObjectName("descriptionLabel");

	// Button icon
	QLabel* iconLabel = new QLabel(this);
	iconLabel->setPixmap(icon);
	iconLabel->setObjectName("buttonIcon");

	// Add drop shadow to title
	auto titleEffect = new QGraphicsDropShadowEffect(titleLabel);
	titleEffect->setXOffset(0);
	titleEffect->setYOffset(1);

	// Add drop shadow to description
	auto descriptionEffect = new QGraphicsDropShadowEffect(descriptionLabel);
	descriptionEffect->setXOffset(0);
	descriptionEffect->setYOffset(1);

	// Add drop shadow to button icon
	auto iconEffect = new QGraphicsDropShadowEffect(iconLabel);
	iconEffect->setColor("#171716");
	iconEffect->setOffset(1);
	iconEffect->setBlurRadius(2);

	// if the button is in contrast, modify the colors to be more visible
	if (contrastButton) {
		titleLabel->setStyleSheet("color: #C4C4C3;");
		descriptionLabel->setStyleSheet("color: #C4C4C3;");

		titleEffect->setColor("#242423");
		descriptionEffect->setColor("#242423");
	}

	// Add the created effects to widgets
	titleLabel->setGraphicsEffect(titleEffect);
	descriptionLabel->setGraphicsEffect(descriptionEffect);
	iconLabel->setGraphicsEffect(iconEffect);

	// Add a shadow to widget
	auto buttonEffect = new QGraphicsDropShadowEffect(this);
	buttonEffect->setXOffset(0);
	buttonEffect->setYOffset(8);
	buttonEffect->setColor(shadowColor);
	setGraphicsEffect(buttonEffect);

	// Add widgets to layout
	m_layout->addWidget(iconLabel, 0, 0, 2, 1, Qt::AlignLeft);
	m_layout->addWidget(titleLabel, 0, 1, 1, 3, Qt::AlignLeft);
	m_layout->addWidget(descriptionLabel, 1, 1, 1, 3, Qt::AlignLeft);

	// Set the layout
	setLayout(m_layout);
}

