export module TwixstParser;
import std;

using std::uint16_t;
using Position = std::pair<uint16_t, uint16_t>;
using MoveList = std::vector<std::string>;
using BoardRepresentation = std::vector<std::vector<Pieces>>;

export enum class Pieces
{
	FirstPlayer,
	SecondPlayer,
	Empty
};

export class TwixtParser
{
public:
	TwixtParser(uint16_t boardSize);

	bool Load(std::string_view path);
	bool Save(std::string_view path);

	void AddColumn(const Position& position, bool isFirstPlayer);
	void AddBridge(const Position& firstPos, const Position& secondPos, bool isFirstPlayer, bool removed);

	// Compute with standard twixt notation
	std::string_view ComputeSTN();
	// Compute with portable twixt game
	std::string_view ComputePTG();

	void Clear();


private:
	std::string m_boardRepresentation;
	MoveList m_movesRepresentation;

};