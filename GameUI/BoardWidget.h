#pragma once

#include <QGridLayout>
#include <QWidget>

#include "../GameLib/IBoard.h"

enum class EDirection
{
	Top,
	Bottom,
	Left,
	Right,
};

class BoardWidget : public QWidget
{
	Q_OBJECT

public:
	BoardWidget(const IBoard& gameBoard, EColor firstPlayerColor, EColor secondPlayerColor, QWidget* parent = nullptr);

	void ChangeSelectedColumn(const Position& selectedColumn);

signals:
	void BoardClicked(const Position& position, const Qt::MouseButton& button);


protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;

private:
	Position CoordinatesToPosition(QPointF pos) const;
	QPointF PositionToCoordinates(uint16_t row, uint16_t column) const;
	bool IsCorner(int row, int column) const;
	QLineF GetLineDelimiter(EDirection direction) const;
	float CalculateRadius(bool isSmallCircle) const;

private:
	const IBoard& m_gameBoard;
	EColor m_firstPlayerColor, m_secondPlayerColor;

	static const size_t smallCircleScalingFactor{12};
	static const size_t largeCircleScalingFactor{3};

	Position m_hovered;
	Position m_selected;

};

