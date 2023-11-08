export module IColumn;

export enum class _declspec(dllexport) EPlayer {
	FirstPlayer,
	SecondPlayer
};

export struct _declspec(dllexport) IColumn
{
	virtual ~IColumn() = default;
	virtual const EPlayer& GetPlayer() const = 0;
};