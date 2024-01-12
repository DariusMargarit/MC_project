#pragma once
#include "IColumn.h"
#include "Player.h"

class BulldozerColumn : public IColumn
{

public:
	BulldozerColumn() noexcept = default;
	BulldozerColumn(const BulldozerColumn& rhs) noexcept = default;
	BulldozerColumn(BulldozerColumn&& rhs) noexcept = default;
	~BulldozerColumn() = default;
	BulldozerColumn& operator=(const BulldozerColumn& rhs) noexcept = default;
	BulldozerColumn& operator=(BulldozerColumn&& rhs) noexcept = default;

	IPlayer* GetPlayer() const noexcept override;
private:
	static Player* m_bulldozer;

};