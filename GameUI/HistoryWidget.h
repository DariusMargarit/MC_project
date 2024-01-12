#include <QListWidget>

#include "IPlayer.h"
#include "Position.h"

// Adapter class
class HistoryWidget : public QListWidget 
{
	Q_OBJECT

public:
	HistoryWidget(QWidget* parent = nullptr);

	void AddColumnItem(IPlayer* player, const Position& position);
	void AddBridgeItem(IPlayer* player, Position& firstPosition, Position& secondPosition, bool removed = false);
};