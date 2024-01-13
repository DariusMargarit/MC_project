#pragma once

#include "Dialog.h"

Dialog::Dialog(QWidget* parent /*= nullptr*/) : QDialog{ parent }
, m_layout{ new QGridLayout(this) }
{
	// Empty
}
