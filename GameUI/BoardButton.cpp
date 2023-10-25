#include "BoardButton.h"
#include <QPainter>
#include <QMouseEvent>

BoardButton::BoardButton(Position position, QWidget* parent)
	: m_position(position)
{

}

void BoardButton::mousePressEvent(QMouseEvent* event)
{
	qDebug() << m_position.GetX() << m_position.GetY();
}

void BoardButton::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	QBrush brush(Qt::black);
	
	QPoint center(width() / 2, height() / 2);
	int radius = qMin(width(), height()) / 6;
	painter.setBrush(brush);
	painter.drawEllipse(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
	
}
