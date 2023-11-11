export module Column;

export import "IColumn.h";

export class Column : public IColumn
{
public:
	Column(IPlayer* player);
	Column(const Column& other);
	Column(Column&& other) noexcept;
	Column& operator=(const Column& other);
	Column& operator=(Column&& other) noexcept;

	IPlayer* GetPlayer() const override;

private:
	IPlayer* m_player;
};