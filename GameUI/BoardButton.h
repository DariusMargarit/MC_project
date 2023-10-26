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
	void paintEvent(QPaintEvent* event) override;

private:

};

