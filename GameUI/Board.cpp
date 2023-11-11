#include <QPainter>
#include <QMouseEvent>

#include "Board.h"
#include "FileUtils.h"

Board::Board(uint32_t size, QWidget* parent)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{
	setObjectName("board");

	m_layout->setSpacing(0);
	m_layout->setContentsMargins(0, 0, 0, 0);

	InitializeButtons(size);

	QString stylesheet = FileUtils::StylesheetFileToString("./stylesheets/game.qss");
	setStyleSheet(stylesheet);


}

void Board::InitializeButtons(uint32_t size)
{
	m_buttons.resize(size);
	for (int row = 0; row < size; row++)
	{
		m_buttons[row].resize(size);
		for (int column = 0; column < size; column++)
		{
			if ((row == 0 || row == size - 1) && (column == 0 || column == size - 1))
				continue;
			m_buttons[row][column] = new BoardButton();
			m_layout->addWidget(m_buttons[row][column], row, column);
		}
	}
	this->setLayout(m_layout);
}

void Board::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	QPen pen;

	pen.setWidth(2);
	pen.setColor("#e0ae48");
	painter.setPen(pen);

	QLineF topLine = GetLineDelimiter(EDirection::Top);
	QLineF bottomLine = GetLineDelimiter(EDirection::Bottom);
	painter.drawLine(topLine);
	painter.drawLine(bottomLine);

	pen.setColor("#54c49f");
	painter.setPen(pen);

	QLineF leftLine = GetLineDelimiter(EDirection::Left);
	QLineF rightLine = GetLineDelimiter(EDirection::Right);
	painter.drawLine(leftLine);
	painter.drawLine(rightLine);

	
}

void Board::mousePressEvent(QMouseEvent* event)
{
	QWidget* selectedWidget = childAt(event->pos());
	if (qobject_cast<BoardButton*>(selectedWidget))
	{
		int index = m_layout->indexOf(selectedWidget);
		int row, column, rowSpan, columnSpan;
		m_layout->getItemPosition(index, &row, &column, &rowSpan, &columnSpan);
		qDebug() << row << column;
	}
}

QLineF Board::GetLineDelimiter(EDirection direction) const
{
	uint64_t size{ m_buttons.size() };
	uint64_t row, column;
	QPointF leftColumn, besideLeftColumn, rightColumn, besideRightColumn;
	if (direction == EDirection::Top || direction == EDirection::Bottom)
	{
		row = direction == EDirection::Top ? 0 : size - 2;
		leftColumn = m_buttons[row][1]->geometry().center();
		besideLeftColumn = m_buttons[row + 1][1]->geometry().center();
		rightColumn = m_buttons[row][size - 2]->geometry().center();
		besideRightColumn = m_buttons[row + 1][size - 2]->geometry().center();
	}
	else
	{
		column = direction == EDirection::Left ? 0 : size - 2;
		leftColumn = m_buttons[1][column]->geometry().center();
		besideLeftColumn = m_buttons[1][column + 1]->geometry().center();
		rightColumn = m_buttons[size - 2][column]->geometry().center();
		besideRightColumn = m_buttons[size - 2][column+1]->geometry().center();
	}

	QPointF lineStart{ (leftColumn + besideLeftColumn) / 2.0f };
	QPointF lineStop{ (rightColumn + besideRightColumn) / 2.0f };

	return QLineF(lineStart, lineStop);
}

