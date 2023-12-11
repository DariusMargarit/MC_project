#include <QListWidget>

#include "IPlayer.h"
#include "Position.h"

// Adapter class
class HistoryWidget : public QListWidget 
{
public:
	HistoryWidget(QWidget* parent = nullptr);

	void AddColumnItem(IPlayer* player, const Position& position);
	void AddBridgeItem(IPlayer* player, Position& firstPosition, Position& secondPosition, bool removed = false);
};