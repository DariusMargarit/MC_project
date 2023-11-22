#pragma once

#include <cstdint>

class _declspec(dllexport) Position
{
public:
	Position();
	Position(uint16_t row, uint16_t column);

	const uint16_t GetRow() const;
	const uint16_t GetColumn() const;

	bool operator==(Position position);

private:
	uint16_t m_row, m_column;

};

