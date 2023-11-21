#pragma once

#include <cstdint>

class _declspec(dllexport) Position
{
public:
	Position();
	Position(uint16_t x, uint16_t y);

	const uint16_t GetX() const;
	const uint16_t GetY() const;

	bool operator==(Position position);

private:
	uint16_t m_x, m_y;

};

