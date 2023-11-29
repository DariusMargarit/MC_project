#pragma once

#include <cstdint>

class _declspec(dllexport) Position
{
public:
	Position();
	Position(uint16_t row, uint16_t column);

	const uint16_t GetRow() const noexcept;
	const uint16_t GetColumn() const noexcept;

	bool IsEqual(const uint16_t& row, const uint16_t& column);

	bool operator==(const Position& position);
	bool operator!=(const Position& position);

public:
	static const Position& EmptyPosition();

private:
	uint16_t m_row, m_column;

};

