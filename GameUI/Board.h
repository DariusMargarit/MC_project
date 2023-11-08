#pragma once

#include <QGridLayout>

#include "BoardButton.h"

enum class EDirection
{
	top,
	bottom,
	left,
	right,
};

class Board : public QWidget
{
public:
	Board(uint32_t size);
	void InitializeButtons(uint32_t size);

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	QLineF GetLineDelimiter(EDirection direction) const;

	QGridLayout* m_layout;
	std::vector<std::vector<BoardButton*>> m_buttons;
};

