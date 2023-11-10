export module Column;

export import "IColumn.h";

export class Column : public IColumn
{
public:
	Column(IPlayer* player);
	Column(const Column& other);

	Column& operator=(const Column&);

	IPlayer* GetPlayer() const override;

private:
	IPlayer* m_player;
};