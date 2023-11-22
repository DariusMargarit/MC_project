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
	BoardWidget(const IBoard& gameBoard, QWidget* parent = nullptr);

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
	Position m_hovered;

};

