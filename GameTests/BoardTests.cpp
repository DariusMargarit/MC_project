
#include <gtest/gtest.h>

#include "Board.h"
#include "Player.h"

class BoardTests : public testing::Test {

protected:
	void SetUp() override
	{
		m_board = std::make_shared<Board>(24);
		m_player1 = new Player("player1", EColor::Blue, 50, 50);
		m_player2 = new Player("player2", EColor::Red, 50, 50);
	}

	void TearDown() override
	{

	}

protected:
	BoardPtr m_board;
	Player* m_player1, *m_player2;

};

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
//TEST_F(BoardTests, MakeBridgeIntersection1) 
//{
//	std::vector<Position> positions{ {6, 11}, {8, 10},  {8, 12},  {7, 12} };
//
//	// the position should be valid before insertion
//	for (auto position : positions)
//	{
//		EXPECT_EQ(m_game->PlaceColumn(position), true);
//	}
//
//	EXPECT_EQ(m_game->MakeBridge({ 6, 11 }, { 8, 12 }), true);
//	EXPECT_EQ(m_game->MakeBridge({ 8, 10 }, { 7, 12 }), false);
//}
//
//TEST_F(BoardTests, MakeBridgeIntersection2)
//{
//	std::vector<Position> positions{ {2, 2}, {4, 3},  {3, 4},  {2, 4} };
//
//	// the position should be valid before insertion
//	for (auto position : positions)
//	{
//		EXPECT_EQ(m_game->PlaceColumn(position), true);
//	}
//
//	EXPECT_EQ(m_game->MakeBridge({ 2, 2 }, { 3, 4 }), true);
//	EXPECT_EQ(m_game->MakeBridge({ 4, 3 }, { 2, 4 }), false);
//}
//
//TEST_F(BoardTests, MakeBridgeTest)
//{
//	std::vector<Position> positions{ {9, 3}, {10, 3},  {10, 4},  {9, 4} };
//
//	// the position should be valid before insertion
//	for (auto position : positions)
//	{
//		EXPECT_EQ(m_game->PlaceColumn(position), true);
//	}
//
//	EXPECT_EQ(m_game->MakeBridge({ 9, 3 }, { 10, 4 }), false);
//	EXPECT_EQ(m_game->MakeBridge({ 10, 3 }, { 9, 4 }), false);
//}
//
//TEST_F(BoardTests, MakeBridgeDifferentColumnsTest)
//{
//	
//	Position firstColumn = {5,5} ;
//	Position secondColumn = { 7,6 };
//
//	EXPECT_EQ(m_game->PlaceColumn(firstColumn), true);
//	EXPECT_EQ(m_game->PlaceColumn(secondColumn), true);
//
//
//	EXPECT_EQ(m_game->MakeBridge(firstColumn, secondColumn), false);
//	
//}

