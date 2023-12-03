#include "GameScreen.h"
#include "FileUtils.h"

#include "../GameLib/IGameSettings.h"


GameScreen::GameScreen(QWidget* parent)
	: QWidget{parent}
	, m_layout{new QGridLayout{this}}
	, m_selectedColumnPos{Position::EmptyPosition()}
{
	IGameSettings* settings{ IGameSettings::GetInstance() };
	m_game = IGame::Produce(*settings);
	m_board = new BoardWidget(*m_game->GetBoard(), settings->GetFirstPlayerColor(), settings->GetSecondPlayerColor(), this);
	m_board->setObjectName("board");

	m_firstPlayerBar = new PlayerBar(*m_game->GetFirstPlayer(), this);
	m_secondPlayerBar = new PlayerBar(*m_game->GetSecondPlayer(), this);

	m_layout->addWidget(m_firstPlayerBar);
	m_layout->addWidget(m_board);
	m_layout->addWidget(m_secondPlayerBar);
	setLayout(m_layout);

	connect(m_board,
	SIGNAL(BoardClicked(const Position&, const Qt::MouseButton&)),
	SLOT(OnBoardClicked(const Position&, const Qt::MouseButton&)));

	QString stylesheet{ FileUtils::StylesheetFileToString("./stylesheets/game.qss") };
	setStyleSheet(stylesheet);

}

void GameScreen::OnBoardClicked(const Position& position, const Qt::MouseButton& button)
{
	if (button == Qt::LeftButton)
	{
		m_game->PlaceColumn(position);
	}
	else if (button == Qt::RightButton)
	{
		auto currentColumn{ m_game->GetBoard()->GetElement(position) };
		if (!currentColumn)
		{
			return;
		}
		else if (m_selectedColumnPos == Position::EmptyPosition())
		{
			m_selectedColumnPos = position;
			m_board->ChangeSelectedColumn(position);
		}
		else
		{
			if (m_selectedColumnPos != position)
			{
				m_game->MakeBridge(m_selectedColumnPos, position);
			}

			m_selectedColumnPos = Position::EmptyPosition();
			m_board->ChangeSelectedColumn(Position::EmptyPosition());
		}
	}
}

