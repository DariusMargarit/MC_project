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

STNGameRepresentation parser::ITwixtParser::LoadSTN(std::string_view path)
{
	if (!TwixtParser::HasExtension(path, "stn")) return STNGameRepresentation();

	BoardRepresentation board;
	MovesPositions moves;
	
	std::ifstream file(std::string(std::move(path)));
	if (!file.is_open()) return STNGameRepresentation();

	uint16_t boardSize, element;
	file >> boardSize;
	board.resize(boardSize, std::vector<Piece>{boardSize, Piece::Empty});

	for (int row = 0; row < boardSize; row++)
	{
		for (int column = 0; column < boardSize; column++)
		{
			file >> element;
			if (element < 0 || element > 2) return STNGameRepresentation();
			if (element == 0) continue;
			board[row][column] = static_cast<Piece>(element);
		}
	}

	std::regex pattern{ R"(\b\d+)" };
	std::string line;

	while (std::getline(file, line))
	{

		std::vector<uint16_t> positions;
		auto it{ std::sregex_iterator(line.begin(), line.end(), pattern) };

		for (&it; it != std::sregex_iterator(); ++it)
		{
			positions.push_back(std::stoi((*it).str()));
		}
		if (positions.size() != 4) return STNGameRepresentation();

		Position firstPos{ positions[0], positions[1] };
		Position secondPos{ positions[2], positions[3] };

		moves.emplace_back(firstPos, secondPos);
	}

	return std::make_pair(board, moves);
}

bool parser::ITwixtParser::SaveSTN(const STNGameRepresentation& game, std::string_view path)
{
	std::ofstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;

	const auto& [board, simpleMoves] = game;

	for (int row = 0; row < board.size(); row++)
	{
		for (int column = 0; column < board.size(); column++)
		{
			file << static_cast<int>(board[row][column]) << " ";
		}
		file << std::endl;
	}

	file << std::endl;

	for (auto& move : simpleMoves)
	{
		const auto& [firstPos, secondPos] = move;
		const auto& [firstPosRow, firstPosColumn] = firstPos;
		const auto& [secondPosRow, secondPosColumn] = secondPos;

		const auto& lineFormat = std::format(
			"{} {} {} {}",
			firstPosRow, firstPosColumn,
			secondPosRow, secondPosColumn
		);
		file << lineFormat << std::endl;
	}

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

	file.close();
	
	return true;
}

bool TwixtParser::SavePTG(std::string_view path)
{
	std::ofstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;

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
	m_movesRepresentation.emplace_back(firstPos, secondPos);
}

MovesPositions parser::TwixtParser::GetGamePreview(int historyIndex) const
{
	/*STNGameRepresentation partialMoves(moves.begin(), moves.begin() + historyIndex);
	return std::move(partialMoves);*/
	return MovesPositions();
}

void TwixtParser::Clear()
{
	std::ranges::for_each(m_boardRepresentation, [](auto& row) { row.clear(); });
	m_boardRepresentation.clear();
	m_movesRepresentation.clear();
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

