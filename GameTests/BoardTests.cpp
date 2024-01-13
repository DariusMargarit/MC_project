
#include <gtest/gtest.h>

#include "Board.h"
#include "Player.h"

class BoardTests : public testing::Test {

protected:
	void SetUp() override
	{
		m_board = std::make_shared<Board>(24);
		m_player1 = std::make_shared<Player>("player1", EColor::Blue, 50, 50);
		m_player2 = std::make_shared<Player>("player2", EColor::Red, 50, 50);
	}

	void TearDown() override
	{

	}

protected:
	BoardPtr m_board;
	PlayerPtr m_player1, m_player2;

};

TEST_F(BoardTests, GetElementTest) {

	// Place some columns on the board
	EXPECT_EQ(m_board->PlaceColumn({ 2, 2 }, m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn({ 2, 7 }, m_player2), true);
	EXPECT_EQ(m_board->PlaceColumn({ 4, 2 }, m_player1), true);

	// Test valid positions
	const IColumnPtr column1 = m_board->GetElement({ 2, 2 });
	const IColumnPtr column2 = m_board->GetElement({ 2, 7 });
	const IColumnPtr column3 = m_board->GetElement({ 4, 2 });

	// Ensure columns at valid positions are not nullptr
	EXPECT_NE(column1, nullptr);
	EXPECT_NE(column2, nullptr);
	EXPECT_NE(column3, nullptr);

	// Test invalid positions
	const IColumnPtr invalidColumn1 = m_board->GetElement({ 0, 0 });
	const IColumnPtr invalidColumn2 = m_board->GetElement({ 0, 23 });

	// Ensure columns at invalid positions are nullptr
	EXPECT_EQ(invalidColumn1, nullptr);
	EXPECT_EQ(invalidColumn2, nullptr);
}

TEST_F(BoardTests, PlaceColumnTest1) {

	// the position should be valid before insertion
	EXPECT_EQ(m_board->PlaceColumn(Position(1, 1), m_player1), true);

	// get the inserted column
	auto insertedColumn = m_board->GetElement(Position(1, 1));

	// expects that a column was inserted at Position(1, 1)
	EXPECT_TRUE(insertedColumn != nullptr);

	// expects that the found column is owned by Player1
	EXPECT_EQ(insertedColumn->GetPlayer(), m_player1);

}
TEST_F(BoardTests, PlaceColumnTest2) {

	// the position should be valid before insertion
	EXPECT_EQ(m_board->PlaceColumn(Position(4,7), m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn(Position(4, 7), m_player2), false);
	// get the inserted column
	auto insertedColumn = m_board->GetElement(Position(4, 7));

	// expects that a column was inserted at Position(4, 7)
	EXPECT_TRUE(insertedColumn != nullptr);

	// expects that the found column is owned by Player1
	EXPECT_EQ(insertedColumn->GetPlayer(), m_player1);

}

TEST_F(BoardTests, PlaceWrongColumnTest) {

	
	EXPECT_EQ(m_board->PlaceColumn(Position(0, 0),m_player1), false);
	EXPECT_EQ(m_board->PlaceColumn(Position(0, 23), m_player1), false);
	EXPECT_EQ(m_board->PlaceColumn(Position(23, 0), m_player1), false);
	EXPECT_EQ(m_board->PlaceColumn(Position(23, 23), m_player1), false);

}

TEST_F(BoardTests, RemoveColumnTest) {

	Position positionToRemove{ 2, 3 };
	EXPECT_EQ(m_board->PlaceColumn(positionToRemove, m_player1), true);

	uint16_t columnsBeforeRemoval = m_board->RemoveColumn(positionToRemove);
	const IColumnPtr removedColumn = m_board->GetElement(positionToRemove);
	EXPECT_EQ(removedColumn, nullptr);


}

TEST_F(BoardTests, RemoveBridgeTest) {

	Position firstPosition{ 2, 3 }, secondPosition{ 4, 4 };

	EXPECT_EQ(m_board->PlaceColumn(firstPosition, m_player2), true);
	EXPECT_EQ(m_board->PlaceColumn(secondPosition, m_player2), true);

	EXPECT_EQ(m_board->MakeBridge(firstPosition, secondPosition, m_player2), true);

	EXPECT_EQ(m_board->RemoveBridge(firstPosition, secondPosition, m_player2), true);
	

}

TEST_F(BoardTests, MakeValidBridgeTest)
{
	Position pos{ {8,10} };
	std::vector<Position> positions{  {6,11},  {7,12},  {9, 12}, {10,11}, {10,9}, {9,8}, {7,8}, {6,9} };

	EXPECT_EQ(m_board->PlaceColumn(pos, m_player1), true);

	for (auto position : positions)
	{
				EXPECT_EQ(m_board->PlaceColumn(position,m_player1), true);
				EXPECT_EQ(m_board->MakeBridge(pos,position,m_player1), true);
	}
	

}

TEST_F(BoardTests, MakeBridgeDifferentColumnsTest)
{
	
	Position firstColumn = {5,5} ;
	Position secondColumn = { 7,6 };

	EXPECT_EQ(m_board->PlaceColumn(firstColumn,m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn(secondColumn,m_player2), true);

	EXPECT_EQ(m_board->MakeBridge(firstColumn, secondColumn,m_player2), false);
	
}

TEST_F(BoardTests, ValidateBridgeTest)
{

	Position firstColumn = { 5,5 };
	EXPECT_EQ(m_board->PlaceColumn(firstColumn, m_player1), true);
	
	EXPECT_EQ(m_board->MakeBridge(firstColumn, Position{ 7,6 }, m_player1), false);
	EXPECT_EQ(m_board->MakeBridge(Position{0,0}, Position{2,1}, m_player1), false);
	EXPECT_EQ(m_board->MakeBridge(Position{ 4,2 }, Position{ 2,1 }, m_player1), false);
	
}

TEST_F(BoardTests, MakeBridgeIntersection1) 
{
	Position pos1{ 6,11 }, pos2{ 8,12 }, pos3{ 8,10 }, pos4{ 7,12 };
	
	EXPECT_EQ(m_board->PlaceColumn(pos1, m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn(pos2, m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn(pos3, m_player2), true);
	EXPECT_EQ(m_board->PlaceColumn(pos4, m_player2), true);

	EXPECT_EQ(m_board->MakeBridge(pos1, pos2,m_player1), true);
	EXPECT_EQ(m_board->MakeBridge(pos3,pos4,m_player2), false);
}

TEST_F(BoardTests, MakeBridgeIntersection2)
{

	Position pos1{ 2, 2 }, pos2{ 3, 4 }, pos3{ 4, 3 }, pos4{ 2, 4 };
	
	EXPECT_EQ(m_board->PlaceColumn(pos1, m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn(pos2, m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn(pos3, m_player2), true);
	EXPECT_EQ(m_board->PlaceColumn(pos4, m_player2), true);

	EXPECT_EQ(m_board->MakeBridge(pos1, pos2, m_player1), true);
	EXPECT_EQ(m_board->MakeBridge(pos3, pos4, m_player2), false);

	
}

TEST_F(BoardTests, ClearTest)
{

	EXPECT_EQ(m_board->PlaceColumn({ 2, 2 }, m_player1), true);
	EXPECT_EQ(m_board->PlaceColumn({ 2, 7 }, m_player2), true);
	EXPECT_EQ(m_board->PlaceColumn({ 4, 2 }, m_player1), true);

	m_board->Clear();

	for (uint16_t row{ 0 }; row < m_board->GetSize(); ++row)
	{
		for (uint16_t column{ 0 }; column < m_board->GetSize(); ++column)
		{
			const IColumnPtr columnPtr = m_board->GetElement({ row, column });
			EXPECT_EQ(columnPtr, nullptr);
		
		}
	}


}






