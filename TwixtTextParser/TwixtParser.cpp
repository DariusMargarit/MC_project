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

TwixtParser::TwixtParser(uint16_t boardSize)
	: m_boardRepresentation{ boardSize, std::vector<Piece>{boardSize, Piece::Empty} }
{
	// Empty
}

bool TwixtParser::Load(std::string_view path)
{
	std::ifstream file(std::string(std::move(path)));
	if (!file.is_open()) return false;

	uint16_t boardSize, element;
	file >> boardSize;
	m_boardRepresentation.resize(boardSize, std::vector<Piece>{boardSize, Piece::Empty});

	for (int row = 0; row < boardSize; row++)
	{
		for (int column = 0; column < boardSize; column++)
		{
			file >> element;
			if (element < 0 || element > 2) return false;
			if (element == 0) continue;
			m_boardRepresentation[row][column] = static_cast<Piece>(element);
		}
	}

	std::regex pattern{ R"(\b\d+)" };
	std::string line;

	while(std::getline(file, line)) 
	{
		bool removed = line[0] == '-' ? true : false;
		std::vector<uint16_t> positions;
		auto it{ std::sregex_iterator(line.begin(), line.end(), pattern) };

		for (&it; it != std::sregex_iterator(); ++it)
		{
			positions.push_back(std::stoi((*it).str()));
		}

		Position firstColumn{ positions[0], positions[1] };
		Position secondColumn{ positions[2], positions[3] };

		AddBridge(removed, firstColumn, secondColumn);
	}
	file.close();
	
	return true;
}

bool TwixtParser::Save(std::string_view path)
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

