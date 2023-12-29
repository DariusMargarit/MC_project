
#include <gtest/gtest.h>

#include "IGame.h"

class BoardTests : public testing::Test {

protected:
	void SetUp() override
	{
		m_gameSettings = IGameSettings::GetInstance();
		m_game = IGame::Produce(*m_gameSettings);
	}

	void TearDown() override
	{

	}

protected:
	IGamePtr m_game;
	IGameSettings* m_gameSettings;
};

TEST_F(BoardTests, PlaceColumnTest) {

	// the position should be valid before insertion
	EXPECT_EQ(m_game->PlaceColumn(Position(1, 1)), true);

	// get the inserted column
	auto insertedColumn = m_game->GetBoard()->GetElement(Position(1, 1));

	// expects that a column was inserted at Position(1, 1)
	EXPECT_TRUE(insertedColumn != nullptr);

	// expects that the found column is owned by Player1
	EXPECT_EQ(insertedColumn->GetPlayer()->GetColor(), m_gameSettings->GetFirstPlayerColor());

}

TEST_F(BoardTests, MakeBridgeIntersection1) 
{
	std::vector<Position> positions{ {6, 11}, {8, 10},  {8, 12},  {7, 12} };

	// the position should be valid before insertion
	for (auto position : positions)
	{
		EXPECT_EQ(m_game->PlaceColumn(position), true);
	}

	EXPECT_EQ(m_game->MakeBridge({ 6, 11 }, { 8, 12 }), true);
	EXPECT_EQ(m_game->MakeBridge({ 8, 10 }, { 7, 12 }), false);
}