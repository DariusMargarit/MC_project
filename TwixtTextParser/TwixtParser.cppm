export module TwixtParser;

export import "ITwixtParser.h";


export namespace parser
{
	class TwixtParser : public ITwixtParser
	{
	public:
		TwixtParser(uint16_t boardSize);
		TwixtParser(const TwixtParser& other) = default;

		bool LoadPTG(std::string_view path) override;
		bool SavePTG(std::string_view path) override;

		void AddColumn(const Position& position, bool isFirstPlayer) override;
		void AddBridge(bool removed, const Position& firstPos, const Position& secondPos) override;

		MovesPositions GetGamePreview(int historyIndex) const override;

		void Clear() override;

		static bool HasExtension(const std::string_view filePath, const std::string_view extension);


	private:
		BoardRepresentation m_boardRepresentation;
		MovesPositions m_movesRepresentation;
		ColumnPositions m_columnPositions;

	};
}

