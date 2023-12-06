
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
		delete m_game;
	}

protected:
	IGame* m_game;
	IGameSettings* m_gameSettings;
};

TEST_F(BoardTests, PlaceColumnTest) {

	// the position should be valid before insertion
	EXPECT_NO_THROW(m_game->PlaceColumn(Position(1, 1)));

	// get the inserted column
	auto insertedColumn = m_game->GetBoard()->GetElement(Position(1, 1));

	// expects that a column was inserted at Position(1, 1)
	EXPECT_TRUE(insertedColumn != nullptr);

	// expects that the found column is owned by Player1
	EXPECT_EQ(insertedColumn->GetPlayer()->GetColor(), m_gameSettings->GetFirstPlayerColor());

}