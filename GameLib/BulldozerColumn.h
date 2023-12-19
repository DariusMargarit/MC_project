#pragma once
#include "IColumn.h"
#include "Player.h"

class BulldozerColumn : public IColumn
{
	
public:
	BulldozerColumn() noexcept;
	BulldozerColumn(const BulldozerColumn& rhs) noexcept;
	BulldozerColumn(BulldozerColumn&& rhs) noexcept = default;
	~BulldozerColumn();
	BulldozerColumn& operator=(const BulldozerColumn& rhs) noexcept;
	BulldozerColumn& operator=(BulldozerColumn&& rhs) noexcept = default;

	IPlayer* GetPlayer() const noexcept override;
private:
		IPlayer* m_bulldozer;
	
};

