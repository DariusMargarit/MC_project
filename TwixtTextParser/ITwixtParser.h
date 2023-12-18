
#pragma once

#include <vector>
#include <string>
#include <memory>

namespace parser
{
	enum class Piece;
	struct ITwixtParser;

	using std::uint16_t;
	using Position = std::pair<uint16_t, uint16_t>;
	using MovesPositions = std::vector<std::pair<Position, Position>>;
	using FullMovesPositions = std::vector<std::tuple<bool, Position, Position>>;
	using BoardRepresentation = std::vector<std::vector<Piece>>;
	using GameRepresentation = std::pair<BoardRepresentation, MovesPositions>;
	using TwixtParserPtr = std::shared_ptr<ITwixtParser>;

	enum class __declspec(dllexport) Piece
	{
		Empty,
		FirstPlayer,
		SecondPlayer
	};

	struct __declspec(dllexport) ITwixtParser
	{

		static TwixtParserPtr Produce(uint16_t boardSize);

		virtual bool Load(std::string_view path) = 0;
		virtual bool Save(std::string_view path) = 0;

		virtual void AddColumn(const Position& position, bool isFirstPlayer) = 0;
		virtual void AddBridge(const Position& firstPos, const Position& secondPos, bool removed) = 0;

		virtual GameRepresentation GetGameRepresentation() const = 0;

		virtual void Clear() = 0;

		virtual ~ITwixtParser() = default;

	};
}

