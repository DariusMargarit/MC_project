export module Bridge;

export import "IColumn.h";

export class Bridge
{
public:
	Bridge(IColumn* firstColumn,IColumn* secondColumn);
	Bridge(const Bridge& otherBridge);
	Bridge(Bridge&& otherBridge) noexcept;
	~Bridge() = default;

    IColumn* GetFirstColumn() const;
	IColumn* GetSecondColumn() const;

	Bridge& operator=(const Bridge& otherBridge);
	Bridge& operator=(Bridge&& otherBridge) noexcept;

private:
	IColumn* m_firstColumn, * m_secondColumn;
};