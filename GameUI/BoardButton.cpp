#include "BoardButton.h"
#include <QPainter>
#include <QMouseEvent>

BoardButton::BoardButton(QWidget* parent)
	: QWidget(parent)
	, m_hover(false)
{

}

void BoardButton::enterEvent(QEnterEvent* event)
{
	m_hover = true;
	repaint();
}

void BoardButton::leaveEvent(QEvent* event)
{
	m_hover = false;
	repaint();
}

void BoardButton::paintEvent(QPaintEvent* event)
{

	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);
	painter.setPen(nullptr);

	m_hover == true
		? painter.setBrush(QBrush(Qt::red))
		: painter.setBrush(QBrush(Qt::white));

	QPointF center(width() / 2.0f, height() / 2.0f);
	float radius = qMin(width(), height()) / 8.0f;

	painter.drawEllipse(center, radius, radius);
	
}
