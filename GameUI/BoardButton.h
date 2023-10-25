#pragma once
#include <QWidget>
#include "Position.h"

class BoardButton : public QWidget
{
	Q_OBJECT

public:
	BoardButton(Position position, QWidget* parent = nullptr);
	~BoardButton() = default;

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	Position m_position;
};

