#include <QPainter>
#include <QMouseEvent>

#include "BoardWidget.h"
#include "FileUtils.h"

BoardWidget::BoardWidget(const IBoard& gameBoard, QWidget* parent)
	: QWidget(parent)
	, m_gameBoard(gameBoard)

{
	setObjectName("board");
	setMouseTracking(true);

	QString stylesheet = FileUtils::StylesheetFileToString("./stylesheets/game.qss");
	setStyleSheet(stylesheet);


}

void BoardWidget::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);

	painter.setRenderHints(QPainter::Antialiasing);

	int boardSize = m_gameBoard.GetSize();

	const auto circleWidth = (float) width() / boardSize;
	const auto circleHeight = (float) height() / boardSize;

	float radius = qMin(circleWidth, circleHeight) / 4.0f;

	for (int row = 0; row < boardSize; ++row)
	{
		for (int column = 0; column < boardSize; ++column)
		{
			if (IsCorner(row, column)) continue;

			if (m_hovered.GetX() == row && m_hovered.GetY() == column)
			{
				painter.setBrush(QBrush(Qt::red));
			}
			else
			{
				painter.setBrush(QBrush(Qt::white));
			}
			
			const auto x = column * circleWidth + (circleWidth / 2.0f);
			const auto y = row * circleHeight + (circleHeight / 2.0f);
			painter.drawEllipse(x, y, radius, radius);
		}
	}

	//pen.setWidth(2);
	//pen.setColor("#e0ae48");
	//painter.setPen(pen);

	//QLineF topLine = GetLineDelimiter(EDirection::Top);
	//QLineF bottomLine = GetLineDelimiter(EDirection::Bottom);
	//painter.drawLine(topLine);
	//painter.drawLine(bottomLine);

	//pen.setColor("#54c49f");
	//painter.setPen(pen);

	//QLineF leftLine = GetLineDelimiter(EDirection::Left);
	//QLineF rightLine = GetLineDelimiter(EDirection::Right);
	//painter.drawLine(leftLine);
	//painter.drawLine(rightLine);

	
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{

}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
	int boardSize = m_gameBoard.GetSize();
	const auto circleWidth = (float)width() / boardSize;
	const auto circleHeight = (float)height() / boardSize;

	std::size_t line = event->position().y() / circleHeight;
	std::size_t col = event->position().x() / circleWidth;

	m_hovered = Position(line, col);
	update();

}

bool BoardWidget::IsCorner(int row, int column)
{
	int boardSize = m_gameBoard.GetSize();
	return (row == 0 && column == 0) ||
		(row == 0 && column == boardSize - 1) ||
		(row == boardSize - 1 && column == 0) ||
		(row == boardSize - 1 && column == boardSize - 1);
}

//QLineF Board::GetLineDelimiter(EDirection direction) const
//{
//	uint64_t size{ m_buttons.size() };
//	uint64_t row, column;
//	QPointF leftColumn, besideLeftColumn, rightColumn, besideRightColumn;
//	if (direction == EDirection::Top || direction == EDirection::Bottom)
//	{
//		row = direction == EDirection::Top ? 0 : size - 2;
//		leftColumn = m_buttons[row][1]->geometry().center();
//		besideLeftColumn = m_buttons[row + 1][1]->geometry().center();
//		rightColumn = m_buttons[row][size - 2]->geometry().center();
//		besideRightColumn = m_buttons[row + 1][size - 2]->geometry().center();
//	}
//	else
//	{
//		column = direction == EDirection::Left ? 0 : size - 2;
//		leftColumn = m_buttons[1][column]->geometry().center();
//		besideLeftColumn = m_buttons[1][column + 1]->geometry().center();
//		rightColumn = m_buttons[size - 2][column]->geometry().center();
//		besideRightColumn = m_buttons[size - 2][column+1]->geometry().center();
//	}
//
//	QPointF lineStart{ (leftColumn + besideLeftColumn) / 2.0f };
//	QPointF lineStop{ (rightColumn + besideRightColumn) / 2.0f };
//
//	return QLineF(lineStart, lineStop);
//}

