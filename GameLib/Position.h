#pragma once

#include <cstdint>

class _declspec(dllexport) Position
{
public:
	Position();
	Position(const uint16_t& row, const uint16_t& column);

	const uint16_t GetRow() const noexcept;
	const uint16_t GetColumn() const noexcept;

	bool IsEqual(const uint16_t& row, const uint16_t& column);

	bool operator==(Position& position);

public:
	static const Position& EmptyPosition();

private:
	uint16_t m_row, m_column;

};

