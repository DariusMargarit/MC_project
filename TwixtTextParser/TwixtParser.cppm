export module TwixtParser;
import std;

using std::uint16_t;

export enum class __declspec(dllexport) Pieces
{
	FirstPlayer,
	SecondPlayer,
	Empty
};


export class __declspec(dllexport) TwixtParser
{
public:
	using Position = std::pair<uint16_t, uint16_t>;
	using BoardRepresentation = std::vector<std::vector<Pieces>>;
	using MovesString = std::vector<std::string>;
	using MovesPositions = std::vector<Position>;
	using GameRepresentation = std::pair<BoardRepresentation, MovesPositions>;

public:
	TwixtParser(uint16_t boardSize);

	bool Load(std::string_view path);
	bool Save(std::string_view path);

	void AddColumn(const Position& position, bool isFirstPlayer);
	void AddBridge(const Position& firstPos, const Position& secondPos, bool removed);

	GameRepresentation GetGameRepresentation() const;

	void Clear();

private:
	BoardRepresentation m_boardRepresentation;
	MovesString m_movesRepresentation;

};

