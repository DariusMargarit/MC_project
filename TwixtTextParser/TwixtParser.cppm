export module TwixtParser;

export import "ITwixtParser.h";

export namespace parser
{
	class TwixtParser : public ITwixtParser
	{
	public:
		TwixtParser(uint16_t boardSize);
		TwixtParser(const TwixtParser& other) = default;

		bool Load(std::string_view path) override;
		bool Save(std::string_view path) override;

		void AddColumn(const Position& position, bool isFirstPlayer) override;
		void AddBridge(const Position& firstPos, const Position& secondPos, bool removed) override;

		GameRepresentation GetGameRepresentation() const override;

		void Clear() override;


	private:
		BoardRepresentation m_boardRepresentation;
		FullMovesPositions m_movesRepresentation;

	};
}

