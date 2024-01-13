#include <gtest/gtest.h>

#include "Game.h"

class PlayerTests : public testing::Test {

protected:
	void SetUp() override
	{
		m_settings = IGameSettings::GetInstance();
		m_game = IGame::Produce(m_settings);
	}

	void TearDown() override
	{

	}

protected:
	IGameSettingsPtr m_settings;
	IGamePtr m_game;

};