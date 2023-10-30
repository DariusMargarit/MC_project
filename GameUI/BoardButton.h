#pragma once
#include <QWidget>
#include <QEvent>

#include "Position.h"

class BoardButton : public QWidget
{
	Q_OBJECT

public:
	BoardButton(QWidget* parent = nullptr);
	~BoardButton() = default;

protected:
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	bool m_hover;

};

