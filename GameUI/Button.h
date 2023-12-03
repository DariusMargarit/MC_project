#pragma once

#include <QLabel>
#include <QGridLayout>

class Button : public QWidget
{
	Q_OBJECT

public:
	Button(QString headerText, QWidget* parent = nullptr, QString descriptionText = "", QPixmap* icon = nullptr);

	QLabel* GetHeaderLabel() const;
	QLabel* GetDescriptionLabel() const;

	void SetTextColor(QColor color);
	void SetTextShadowColor(QColor color);
	void SetShadowColor(QColor color);
	void SetShadowYOffset(int offset);

signals:
	void ButtonClicked();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	QGridLayout* m_layout;
	QLabel* m_headerLabel, * m_descriptionLabel, * m_iconLabel;
};

