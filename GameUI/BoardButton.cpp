#include "BoardButton.h"
#include <QPainter>
#include <QMouseEvent>

BoardButton::BoardButton(Position position, QWidget* parent)
	: m_position(position)
{

}

void BoardButton::paintEvent(QPaintEvent* event)
{

	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QBrush brush(Qt::black);
	painter.setBrush(brush);

	QPointF center(width() / 2.0f, height() / 2.0f);
	float radius = qMin(width(), height()) / 6.0f;

	painter.drawEllipse(center, radius, radius);
	
}
