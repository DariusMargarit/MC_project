module TwixtParser;

using namespace parser;

import <format>;
import <fstream>;
import <algorithm>;
import <ranges>;
import <regex>;


TwixtParserPtr parser::ITwixtParser::Produce(uint16_t boardSize)
{
	return std::make_shared<TwixtParser>(boardSize);
}

GameRepresentation parser::ITwixtParser::LoadSTN(std::string_view path)
{
	return GameRepresentation();
}

bool parser::ITwixtParser::SaveSTN(const GameRepresentation& game, std::string_view path)
{
	return false;
}

TwixtParser::TwixtParser(uint16_t boardSize)
	: m_boardRepresentation{ boardSize, std::vector<Piece>{boardSize, Piece::Empty} }
{
	// Empty
}

bool TwixtParser::LoadPTG(std::string_view path)
{
	std::ifstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;

	if (!LoadBoardRepresentation(m_boardRepresentation, file)) return false;
	LoadMoveRepresentation(m_movesRepresentation, file);

	file.close();
	
	return true;
}

bool TwixtParser::SavePTG(std::string_view path)
{
	std::ofstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;

	for (int row = 0; row < m_boardRepresentation.size(); row++)
	{
		for (int column = 0; column < m_boardRepresentation.size(); column++)
		{
			file << static_cast<int>(m_boardRepresentation[row][column]) << " ";
		}
		file << std::endl;
	}

	for (auto& move : m_movesRepresentation)
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
	}
	file.close();

	return false;
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
	return GameRepresentation();
}

void TwixtParser::Clear()
{
	// Empty
}

bool parser::TwixtParser::LoadBoardRepresentation(BoardRepresentation& board, std::ifstream& file)
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

void parser::TwixtParser::LoadMoveRepresentation(MovesPositionsVariant movesRepresentation, std::ifstream& file)
{
	std::regex pattern{ R"(\b\d+)" };
	std::string line;

	bool fullMovesPositions = std::holds_alternative<FullMovesPositions>(movesRepresentation);

	while (std::getline(file, line))
	{
		std::vector<uint16_t> positions;
		auto it{ std::sregex_iterator(line.begin(), line.end(), pattern) };

		for (&it; it != std::sregex_iterator(); ++it)
		{
			positions.push_back(std::stoi((*it).str()));
		}

		Position firstColumn { positions[0], positions[1] };
		Position secondColumn{ positions[2], positions[3] };

		if (fullMovesPositions)
		{
			bool removed = line[0] == '-' ? true : false;
			AddBridge(removed, firstColumn, secondColumn);
		}
		else
		{
			auto representation = std::get<MovesPositions>(movesRepresentation);
			representation.emplace_back(firstColumn, secondColumn);
		}
	}
}

