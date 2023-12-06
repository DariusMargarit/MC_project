#include <QListWidget>

#include "IPlayer.h"
#include "Position.h"

class HistoryWidget : public QListWidget 
{
public:
	HistoryWidget(QWidget* parent);
	void AddColumnItem(IPlayer* player, const Position& position);
	void AddBridgeItem(IPlayer* player, Position& firstPosition, Position& secondPosition, bool removed = false);

};