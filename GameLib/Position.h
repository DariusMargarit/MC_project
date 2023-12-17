#pragma once

#include <cstdint>
#include <utility>

class Position
{
public:
	Position() noexcept;
	Position(const uint16_t& row, const uint16_t& column) noexcept;
	Position(const Position& otherPosition) noexcept;
	Position(Position&& otherPosition) noexcept;

	const uint16_t GetRow() const noexcept;
	const uint16_t GetColumn() const noexcept;

	bool IsEqual(const uint16_t& row, const uint16_t& column) const;

	bool operator==(const Position& position) const;
	bool operator!=(const Position& position) const;
	Position& operator=(const Position& position);
	Position& operator=(Position&& position) noexcept;

public:
	static const Position& EmptyPosition() noexcept;

private:
	uint16_t m_row, m_column;

};

