
#include <gtest/gtest.h>

#include "IGame.h"

class BoardTests : public testing::Test {

protected:
	void SetUp() override
	{
		m_player1 = IPlayer::Produce("Mihai", "red");
		m_player2 = IPlayer::Produce("Cosmin", "blue");
		m_game = IGame::Produce(m_player1, m_player2, 24);
	}

	void TearDown() override
	{
		delete m_game;
		delete m_player1;
		delete m_player2;
	}

protected:
	IGame* m_game;
	IPlayer* m_player1;
	IPlayer* m_player2;
};

TEST_F(BoardTests, PlaceColumnTest) {

	// the position should be valid before insertion
	EXPECT_NO_THROW(m_game->PlaceColumn(Position(1, 1)));

	// get the inserted column
	auto insertedColumn = m_game->GetBoard()->GetElement(Position(1, 1));

	// expects that a column was inserted at Position(1, 1)
	EXPECT_TRUE(insertedColumn != nullptr);

	// expects that the found column is owned by Player1
	EXPECT_EQ(insertedColumn->GetPlayer(), m_player1);

}