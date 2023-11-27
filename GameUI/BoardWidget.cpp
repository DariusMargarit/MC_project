#include <QPainter>
#include <QMouseEvent>

#include "BoardWidget.h"
#include "FileUtils.h"
#include "ColorUtils.h"

BoardWidget::BoardWidget(const IBoard& gameBoard, EColor firstPlayerColor, EColor secondPlayerColor, QWidget* parent) : QWidget(parent)
	, m_gameBoard(gameBoard)
	, m_firstPlayerColor(firstPlayerColor)
	, m_secondPlayerColor(secondPlayerColor)

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
	const auto circleWidth = static_cast<float>(width() / boardSize);
	const auto circleHeight = static_cast<float>(height() / boardSize);
	float radius;

	for (int row = 0; row < boardSize; ++row)
	{
		for (int column = 0; column < boardSize; ++column)
		{
			if (IsCorner(row, column)) continue;

			if (auto element{ m_gameBoard.GetElement(row, column) }; element)
			{
				QColor color = ColorUtils::TwixtColorToQColor(element->GetPlayer()->GetColor());
				radius = static_cast<float>(qMin(circleWidth, circleHeight) / largeCircleMagnification);
				painter.setPen(color);
				painter.setBrush(std::move(QBrush(color)));
			}
			else if (m_hovered.IsEqual(row, column))
			{
				QColor color = Qt::black;
				radius = static_cast<float>(qMin(circleWidth, circleHeight) / largeCircleMagnification);
				painter.setPen(color);
				painter.setBrush(std::move(QBrush(std::move(color))));
			}
			else
			{
				QColor color = Qt::white;
				radius = static_cast<float>(qMin(circleWidth, circleHeight) / smallCircleMagnification);
				painter.setPen(color);
				painter.setBrush(std::move(color));
			}
			
			QRectF circleRect(column * circleWidth, row * circleHeight, circleWidth, circleHeight);
			painter.drawEllipse(circleRect.center(), radius, radius);
		}
	}

	QPen pen;
	QColor firstPlayerColor = ColorUtils::TwixtColorToQColor(m_firstPlayerColor);
	pen.setWidth(2);
	pen.setColor(std::move(firstPlayerColor));
	painter.setPen(pen);

	QLineF topLine = GetLineDelimiter(EDirection::Top);
	QLineF bottomLine = GetLineDelimiter(EDirection::Bottom);
	painter.drawLine(topLine);
	painter.drawLine(bottomLine);

	QColor secondPlayerColor = ColorUtils::TwixtColorToQColor(m_secondPlayerColor);
	pen.setColor(std::move(secondPlayerColor));
	painter.setPen(pen);

	QLineF leftLine = GetLineDelimiter(EDirection::Left);
	QLineF rightLine = GetLineDelimiter(EDirection::Right);
	painter.drawLine(leftLine);
	painter.drawLine(rightLine);

	
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
	Position pos{ CoordinatesToPosition(event->position()) };
	if (IsCorner(pos.GetRow(), pos.GetColumn())) return;

	emit(BoardClicked(std::move(pos)));
	update();
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
	m_hovered = CoordinatesToPosition(event->position());
	update();
}

void BoardWidget::leaveEvent(QEvent* event)
{
	m_hovered = Position::EmptyPosition();
}

Position BoardWidget::CoordinatesToPosition(QPointF pos) const
{
	const auto boardSize = m_gameBoard.GetSize();
	const auto circleWidth = (float)width() / boardSize;
	const auto circleHeight = (float)height() / boardSize;

	std::size_t line = pos.y() / circleHeight;
	std::size_t col = pos.x() / circleWidth;

	return std::move(Position(line, col));

}

bool BoardWidget::IsCorner(int row, int column) const
{
	const auto boardSize = m_gameBoard.GetSize();
	return (row == 0 && column == 0) ||
		(row == 0 && column == boardSize - 1) ||
		(row == boardSize - 1 && column == 0) ||
		(row == boardSize - 1 && column == boardSize - 1);
}

QLineF BoardWidget::GetLineDelimiter(EDirection direction) const
{
	const auto boardSize = m_gameBoard.GetSize();
	const auto circleWidth = static_cast<float>(width() / boardSize);
	const auto circleHeight = static_cast<float>(height() / boardSize);
	QPointF lineStart, lineStop;

	if (direction == EDirection::Top || direction == EDirection::Bottom)
	{
		QPointF leftCircle, besideLeftCircle, rightCircle, besideRightCircle;
		const auto row = direction == EDirection::Top ? 0 : boardSize - 2;
		const auto leftColumn = 1;
		const auto rightColumn = boardSize - 2;

		leftCircle = { (leftColumn + 0.5f) * circleWidth, (row + 0.5f) * circleHeight};
		besideLeftCircle = { (leftColumn + 0.5f) * circleWidth, (row + 1.5f) * circleHeight };
		rightCircle = { (rightColumn + 0.5f) * circleWidth, (row + 0.5f) * circleHeight };
		besideRightCircle = { (rightColumn + 0.5f) * circleWidth, (row + 1.5f) * circleHeight };

		lineStart = (leftCircle + besideLeftCircle) / 2.0f;
		lineStop = (rightCircle + besideRightCircle) / 2.0f;
	}
	else
	{
		QPointF topCircle, besideTopCircle, bottomCircle, besideBottomCircle;
		const auto topRow = 1;
		const auto bottomRow = boardSize - 2;
		const auto column = direction == EDirection::Left ? 0 : boardSize - 2;

		topCircle = { (column + 0.5f) * circleWidth, (topRow + 0.5f) * circleHeight };
		besideTopCircle = { (column + 1.5f) * circleWidth, (topRow + 0.5f) * circleHeight };
		bottomCircle = { (column + 0.5f) * circleWidth, (bottomRow + 0.5f) * circleHeight };
		besideBottomCircle = { (column + 1.5f) * circleWidth, (bottomRow + 0.5f) * circleHeight };

		lineStart = (topCircle + besideTopCircle) / 2.0f;
		lineStop = (bottomCircle + besideBottomCircle) / 2.0f;
	}


	return QLineF(lineStart, lineStop);
}

