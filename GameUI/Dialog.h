#pragma once

#include <QDialog>

#include "Button.h"

class Dialog : public QDialog
{
public:
	Dialog(QWidget* parent = nullptr);

	template<typename T>
	void MakeDialog(T field)
	{
		QLabel* label = new QLabel();
		label->setText(QString(field));
		m_layout->addWidget(label);
	}

	template <typename T, typename...Ts>
	void MakeDialog(T field, Ts...fields)
	{
		MakeDialog(fields...);
	}

private:
	QGridLayout* m_layout;

};