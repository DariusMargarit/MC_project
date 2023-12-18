export module TwixtParser;

export import "ITwixtParser.h";
import <variant>;


export namespace parser
{
	using MovesPositionsVariant = std::variant<FullMovesPositions, MovesPositions>;

	class TwixtParser : public ITwixtParser
	{
	public:
		TwixtParser(uint16_t boardSize);
		TwixtParser(const TwixtParser& other) = default;

		bool LoadPTG(std::string_view path) override;
		bool SavePTG(std::string_view path) override;

		void AddColumn(const Position& position, bool isFirstPlayer) override;
		void AddBridge(bool removed, const Position& firstPos, const Position& secondPos) override;

		GameRepresentation GetGameRepresentation() const override;

		void Clear() override;

	private:
		bool LoadBoardRepresentation(BoardRepresentation& board, std::ifstream& file);
		void LoadMoveRepresentation(MovesPositionsVariant movesRepresentation, std::ifstream& file);

	private:
		BoardRepresentation m_boardRepresentation;
		FullMovesPositions m_movesRepresentation;

	};
}

