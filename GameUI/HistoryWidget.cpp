#include <format>

#include "HistoryWidget.h"
#include "ColorUtils.h"

HistoryWidget::HistoryWidget(QWidget* parent) 
	: QListWidget{parent}
{

}

void HistoryWidget::AddColumnItem(IPlayer* player, const Position& position)
{
	QPixmap pixmap{ ":/GameUI/images/profile.png" };
	ColorUtils::FillPixmapBackground(pixmap, player->GetColor());
	QIcon icon{ std::move(pixmap) };

	std::string text = std::format("Column added at position ({}, {})", position.GetRow(), position.GetColumn());
	QListWidgetItem* item = new QListWidgetItem(icon, QString::fromStdString(std::move(text)));
	addItem(item);
}

void HistoryWidget::AddBridgeItem(IPlayer* player, Position& firstPosition, Position& secondPosition, bool removed)
{
	QPixmap pixmap{ ":/GameUI/images/profile.png" };
	ColorUtils::FillPixmapBackground(pixmap, player->GetColor());
	QIcon icon{ std::move(pixmap) };

	std::string text = std::format("Bridge between ({}, {}) -> ({}, {}) {}",
		firstPosition.GetRow(), firstPosition.GetColumn(),
		secondPosition.GetRow(), secondPosition.GetColumn(),
		removed ? "removed" : "added");

	QListWidgetItem* item = new QListWidgetItem(icon, QString::fromStdString(std::move(text)));
	addItem(item);
}
