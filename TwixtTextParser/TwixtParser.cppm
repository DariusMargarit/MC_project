export module TwixtParser;

export import "ITwixtParser.h";

export class TwixtParser : public ITwixtParser
{
public:
	TwixtParser(uint16_t boardSize);
	bool Load(std::string_view path) override;
	bool Save(std::string_view path) override;

	void AddColumn(const Positionn& position, bool isFirstPlayer) override;
	void AddBridge(const Positionn& firstPos, const Positionn& secondPos, bool removed) override;

	GameRepresentation GetGameRepresentation() const override;

	void Clear() override;


private:
	BoardRepresentation m_boardRepresentation;
	MovesString m_movesRepresentation;

};


