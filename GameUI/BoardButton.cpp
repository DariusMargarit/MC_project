#include "BoardButton.h"
#include <QPainter>
#include <QMouseEvent>

BoardButton::BoardButton(QWidget* parent)
{

}

void BoardButton::mousePressEvent(QMouseEvent* event)
{

}

void BoardButton::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	int textX = 5;
	int textY = 5;
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	QBrush brush(Qt::black);
	int centerX = width() / 2;
	int centerY = height() / 2;
	int radius = qMin(width(), height()) / 6;
	painter.setBrush(brush);
	painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
	
}
