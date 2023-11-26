
#include <QGraphicsDropShadowEffect>

#include "Button.h"

Button::Button(QString headerText, QWidget* parent, QString descriptionText, QPixmap* icon)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{
	// Header
	m_headerLabel = new QLabel(headerText, this);
	m_headerLabel->setObjectName("titleLabel");

	// Description
	m_descriptionLabel = new QLabel(descriptionText, this);
	m_descriptionLabel->setObjectName("descriptionLabel");

	// Add icon if exists
	if (icon)
	{
		m_iconLabel = new QLabel(this);
		m_iconLabel->setPixmap(*icon);
		m_iconLabel->setObjectName("iconLabel");
	}

	// Add drop shadow to title
	auto titleEffect = new QGraphicsDropShadowEffect(m_headerLabel);
	titleEffect->setXOffset(0);
	titleEffect->setYOffset(1);

	// Add drop shadow to description
	auto descriptionEffect = new QGraphicsDropShadowEffect(m_descriptionLabel);
	descriptionEffect->setXOffset(0);
	descriptionEffect->setYOffset(1);

	if (icon)
	{
		// Add drop shadow to button icon
		auto iconEffect = new QGraphicsDropShadowEffect(m_iconLabel);
		iconEffect->setColor("#171716");
		iconEffect->setOffset(1);
		iconEffect->setBlurRadius(2);

		m_iconLabel->setGraphicsEffect(iconEffect);
	}

	// Add the created effects to labels
	m_headerLabel->setGraphicsEffect(titleEffect);
	m_descriptionLabel->setGraphicsEffect(descriptionEffect);

	// Add a shadow to widget
	auto buttonEffect = new QGraphicsDropShadowEffect(this);
	buttonEffect->setXOffset(0);
	buttonEffect->setYOffset(8);
	setGraphicsEffect(buttonEffect);

	// Add the widgets to layout
	if (icon && !descriptionText.isEmpty())
	{
	
		// add all widgets if exists
		m_layout->addWidget(m_iconLabel, 0, 0, 2, 1, Qt::AlignLeft);
		m_layout->addWidget(m_headerLabel, 0, 1, 1, 3, Qt::AlignLeft);
		m_layout->addWidget(m_descriptionLabel, 1, 1, 1, 3, Qt::AlignLeft);
	}
	else if (icon && descriptionText.isEmpty())
	{
		// add only the header and description label
		m_layout->addWidget(m_iconLabel, 0, 0, Qt::AlignLeft);
		m_layout->addWidget(m_headerLabel, 0, 1, 1, 3, Qt::AlignLeft);
	}
	else if (!icon && !descriptionText.isEmpty())
	{
		// add only the header and icon
		m_layout->addWidget(m_headerLabel, 0, 0, Qt::AlignLeft);
		m_layout->addWidget(m_descriptionLabel, 1, 0, Qt::AlignLeft);
	}
	else
	{
		m_layout->addWidget(m_headerLabel);
	}


	// Set the layout
	setLayout(m_layout);
}

void Button::SetTextColor(QColor color)
{
	m_headerLabel->setStyleSheet("color: " + color.name());
	m_descriptionLabel->setStyleSheet("color: " + color.name());
}

void Button::SetTextShadowColor(QColor color)
{
	auto headerShadow = qobject_cast<QGraphicsDropShadowEffect*>(m_headerLabel->graphicsEffect());
	auto descriptionShadow = qobject_cast<QGraphicsDropShadowEffect*>(m_descriptionLabel->graphicsEffect());

	headerShadow->setColor(color);
	descriptionShadow->setColor(color);
}

void Button::SetShadowColor(QColor color)
{
	auto shadow = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
	shadow->setColor(color);
}

