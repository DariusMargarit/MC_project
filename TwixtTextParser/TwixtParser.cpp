module TwixtParser;

TwixtParser::TwixtParser(uint16_t boardSize)
	: m_boardRepresentation{boardSize, std::vector<Pieces>(boardSize, Pieces::Empty)}
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

void TwixtParser::AddColumn(const Position& position, bool isFirstPlayer)
{
	// Empty
}

void TwixtParser::AddBridge(const Position& firstPos, const Position& secondPos, bool removed)
{
	// Empty
}

TwixtParser::GameRepresentation TwixtParser::GetGameRepresentation() const
{
	return GameRepresentation();
}

void TwixtParser::Clear()
{
	// Empty
}
