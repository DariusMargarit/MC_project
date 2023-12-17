module TwixtParser;

import <format>;

//TwixtParserPtr ITwixtParser::Produce(uint16_t boardSize)
//{
//	return std::make_shared<TwixtParser>(boardSize);
//}


TwixtParser::TwixtParser(uint16_t boardSize)
	: m_boardRepresentation{ boardSize, std::vector<Pieces>{boardSize, Pieces::Empty} }
{
	// Empty
}

bool TwixtParser::Load(std::string_view path)
{
	return false;
}

bool TwixtParser::Save(std::string_view path)
{
	return false;
}

void TwixtParser::AddColumn(const Positionn& position, bool isFirstPlayer)
{
	auto& [row, column] = position;
	m_boardRepresentation[row][column] = isFirstPlayer ? Pieces::FirstPlayer : Pieces::SecondPlayer;
}

void TwixtParser::AddBridge(const Positionn& firstPos, const Positionn& secondPos, bool removed)
{
	auto& [firstRow, firstColumn] = firstPos;
	auto& [secondRow, secondColumn] = secondPos;

	std::string currentMove(removed ? "-" : "");
	currentMove.append(std::format("{} {} {} {}", firstRow, firstColumn, secondRow, secondColumn));
	m_movesRepresentation.push_back(currentMove);
}

GameRepresentation TwixtParser::GetGameRepresentation() const
{
	return GameRepresentation();
}

void TwixtParser::Clear()
{
	// Empty
}

