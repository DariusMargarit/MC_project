#pragma once

#include <cstdint>

class _declspec(dllexport) Position
{
public:
	Position();
	Position(uint16_t row, uint16_t column);

	const uint16_t GetRow() const;
	const uint16_t GetColumn() const;

	bool IsEqual(uint16_t row, uint16_t column);

	bool operator==(Position position);

public:
	static const Position& EmptyPosition();

private:
	uint16_t m_row, m_column;

};

