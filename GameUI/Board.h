#pragma once

#include <QGridLayout>

#include "BoardButton.h"

enum class EDirection
{
	Top,
	Bottom,
	Left,
	Right,
};

class Board : public QWidget
{
	Q_OBJECT

public:
	Board(uint32_t size, QWidget* parent = nullptr);
	void InitializeButtons(uint32_t size);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	QLineF GetLineDelimiter(EDirection direction) const;

	QGridLayout* m_layout;
	std::vector<std::vector<BoardButton*>> m_buttons;
};

