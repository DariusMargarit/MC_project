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

	static const QColor TwixtColorToQColor(EColor color);

signals:
	void BoardClicked(const Position& position);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;

private:
	Position CoordinatesToPosition(QPointF pos) const;
	bool IsCorner(int row, int column) const;
	QLineF GetLineDelimiter(EDirection direction) const;

private:
	const IBoard& m_gameBoard;
	EColor m_firstPlayerColor, m_secondPlayerColor;

	static const size_t smallCircleMagnification = 8;
	static const size_t largeCircleMagnification = 5;

	Position m_hovered;

};

