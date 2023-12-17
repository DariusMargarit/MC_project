
#pragma once

#include <vector>
#include <string>
#include <memory>

enum class Pieces;
struct ITwixtParser;

using std::uint16_t;
using Positionn = std::pair<uint16_t, uint16_t>;
using MovesString = std::vector<std::string>;
using MovesPositions = std::vector<Positionn>;
using BoardRepresentation = std::vector<std::vector<Pieces>>;
using GameRepresentation = std::pair<BoardRepresentation, MovesPositions>;
using TwixtParserPtr = std::shared_ptr<ITwixtParser>;

enum class __declspec(dllexport) Pieces
{
	FirstPlayer,
	SecondPlayer,
	Empty
};

struct __declspec(dllexport) ITwixtParser
{

	//static TwixtParserPtr Produce(uint16_t boardSize);

	virtual bool Load(std::string_view path) = 0;
	virtual bool Save(std::string_view path) = 0;


	virtual void AddColumn(const Positionn& position, bool isFirstPlayer) = 0;
	virtual void AddBridge(const Positionn& firstPos, const Positionn& secondPos, bool removed) = 0;

	virtual GameRepresentation GetGameRepresentation() const = 0;

	virtual void Clear() = 0;

	virtual ~ITwixtParser() = default;

};

