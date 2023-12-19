export module TwixtParser;

export import "ITwixtParser.h";


export namespace parser
{
	using FullMovesPositions = std::vector<std::tuple<bool, Position, Position>>;

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

		static bool LoadBoardRepresentation(BoardRepresentation& board, std::ifstream& file);
		static bool LoadMoveRepresentation(FullMovesPositions& moves, bool isFullMove, std::ifstream& file);
		static void SaveGame(BoardRepresentation board, FullMovesPositions moves, std::ofstream& file);
		static MovesPositions ConvertFullMovesToSimpleMoves(const FullMovesPositions& moves);
		static FullMovesPositions ConvertSimpleMovesToFullMoves(const MovesPositions& moves);
		static bool HasExtension(const std::string_view filePath, const std::string_view extension);
	private:
		template<size_t FirstArg, size_t SecondArg, class... T>
		static auto TupleToPair(std::tuple<T...> t)
		{
			return std::make_pair(std::get<FirstArg>(t), std::get<SecondArg>(t));
		}

	private:
		BoardRepresentation m_boardRepresentation;
		FullMovesPositions m_movesRepresentation;

	};
}

