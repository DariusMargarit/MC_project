module TwixtParser;

using namespace parser;

import <format>;
import <fstream>;
import <algorithm>;
import <regex>;
import <ranges>;


TwixtParserPtr parser::ITwixtParser::Produce(uint16_t boardSize)
{
	return std::make_shared<TwixtParser>(boardSize);
}

GameRepresentation parser::ITwixtParser::LoadSTN(std::string_view path)
{
	BoardRepresentation board;
	FullMovesPositions moves;
	
	std::ifstream file(std::string(std::move(path)));
	if (!file.is_open()) return GameRepresentation();
	
	if (!TwixtParser::LoadBoardRepresentation(board, file)) return GameRepresentation();
	if (!TwixtParser::LoadMoveRepresentation(moves, false, file)) return GameRepresentation();

	MovesPositions simpleMoves = TwixtParser::ConvertFullMovesToSimpleMoves(moves);
	return std::make_pair(board, simpleMoves);
}

bool parser::ITwixtParser::SaveSTN(const GameRepresentation& game, std::string_view path)
{
	std::ofstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;

	const auto& [board, simpleMoves] = game;
	FullMovesPositions fullMoves = TwixtParser::ConvertSimpleMovesToFullMoves(simpleMoves);

	TwixtParser::SaveGame(board, fullMoves, file);

	return true;
}

TwixtParser::TwixtParser(uint16_t boardSize)
	: m_boardRepresentation{ boardSize, std::vector<Piece>{boardSize, Piece::Empty} }
{
	// Empty
}

bool TwixtParser::LoadPTG(std::string_view path)
{
	if (!HasExtension(path, "ptg")) return false;
	Clear();
	
	std::ifstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;

	if (!LoadBoardRepresentation(m_boardRepresentation, file)) return false;
	if (!LoadMoveRepresentation(m_movesRepresentation, true, file)) return false;

	file.close();
	
	return true;
}

bool TwixtParser::SavePTG(std::string_view path)
{
	std::ofstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;
	
	SaveGame(m_boardRepresentation, m_movesRepresentation, file);

	file.close();

	return true;
}

void TwixtParser::AddColumn(const Position& position, bool isFirstPlayer)
{
	auto& [row, column] = position;
	m_boardRepresentation[row][column] = isFirstPlayer ? Piece::FirstPlayer : Piece::SecondPlayer;
}

void TwixtParser::AddBridge(bool removed, const Position& firstPos, const Position& secondPos)
{
	m_movesRepresentation.emplace_back(removed, firstPos, secondPos);
}

GameRepresentation TwixtParser::GetGameRepresentation() const
{
	MovesPositions moves = ConvertFullMovesToSimpleMoves(m_movesRepresentation);
	return std::make_pair(m_boardRepresentation, std::move(moves));
}

void TwixtParser::Clear()
{
	std::ranges::for_each(m_boardRepresentation, [](auto& row) { row.clear(); });
	m_boardRepresentation.clear();
	m_movesRepresentation.clear();
}

bool TwixtParser::LoadBoardRepresentation(BoardRepresentation& board, std::ifstream& file)
{
	uint16_t boardSize, element;
	file >> boardSize;
	board.resize(boardSize, std::vector<Piece>{boardSize, Piece::Empty});

	for (int row = 0; row < boardSize; row++)
	{
		for (int column = 0; column < boardSize; column++)
		{
			file >> element;
			if (element < 0 || element > 2) return false;
			if (element == 0) continue;
			board[row][column] = static_cast<Piece>(element);
		}
	}
	return true;
}

bool TwixtParser::LoadMoveRepresentation(FullMovesPositions& moves, bool isFullMove, std::ifstream & file)
{
	std::regex pattern{ R"(\b\d+)" };
	std::string line;

	while (std::getline(file, line))
	{
		bool removed = isFullMove
			? line[0] == '-' ? true : false
			: false;

		std::vector<uint16_t> positions;
		auto it{ std::sregex_iterator(line.begin(), line.end(), pattern) };

		for (&it; it != std::sregex_iterator(); ++it)
		{
			positions.push_back(std::stoi((*it).str()));
		}
		if (positions.size() != 4) return false;

		Position firstPos { positions[0], positions[1] };
		Position secondPos{ positions[2], positions[3] };

		moves.emplace_back(removed, firstPos, secondPos);
	}
	return true;
}

void parser::TwixtParser::SaveGame(BoardRepresentation board, FullMovesPositions moves, std::ofstream& file)
{
	for (int row = 0; row < board.size(); row++)
	{
		for (int column = 0; column < board.size(); column++)
		{
			file << static_cast<int>(board[row][column]) << " ";
		}
		file << std::endl;
	}

	file << std::endl;

	for (auto& move : moves)
	{
		const auto& [removed, firstPos, secondPos] = move;
		const auto& [firstPosRow, firstPosColumn] = firstPos;
		const auto& [secondPosRow, secondPosColumn] = secondPos;

		const auto& lineFormat = std::format(
			"{} {} {} {} {}",
			removed ? '-' : '+',
			firstPosRow, firstPosColumn,
			secondPosRow, secondPosColumn
		);
		file << lineFormat << std::endl;
	}
}

MovesPositions TwixtParser::ConvertFullMovesToSimpleMoves(const FullMovesPositions& moves)
{
	MovesPositions simpleMoves;
	for (const auto& move : moves)
	{
		simpleMoves.push_back(std::move(TupleToPair<1, 2, bool, Position, Position>(move)));
	}

	return std::move(simpleMoves);
}

FullMovesPositions parser::TwixtParser::ConvertSimpleMovesToFullMoves(const MovesPositions& moves)
{
	FullMovesPositions fullMoves;
	for (const auto& move : moves)
	{
		const auto& [firstPos, secondPos] = move;
		fullMoves.push_back({ false, firstPos, secondPos });
	}
	return std::move(fullMoves);
}

bool TwixtParser::HasExtension(const std::string_view filePath, const std::string_view extension)
{
	size_t dotPos = filePath.find_last_of(".");
	if (dotPos == std::string::npos) return false;
	std::string actualExtension = std::string(filePath.substr(dotPos + 1));
	std::string currentExtension = std::string(extension);

	std::ranges::for_each(actualExtension, [](char& c) {c = std::tolower(c); });
	std::ranges::for_each(currentExtension, [](char& c) {c = std::tolower(c); });
	if (actualExtension == extension) return true;
	return false;
}

