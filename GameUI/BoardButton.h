#pragma once
#include <QWidget>

class BoardButton : public QWidget
{
	Q_OBJECT
public:
	BoardButton(QWidget* parent = nullptr);
	~BoardButton() = default;

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
};

