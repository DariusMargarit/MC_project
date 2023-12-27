#include "BoardNode.h"

BoardNode::BoardNode(const Board& board, IPlayer* maximizingPlayer, IPlayer* minimizingPlayer)
	: Board(board)
    , m_maximizingPlayer{maximizingPlayer}
    , m_minimizingPlayer{minimizingPlayer}
{
	// Empty
}

BoardNode::BoardNode(const BoardNode& other)
	:Board(other)
    , m_maximizingPlayer{ other.m_maximizingPlayer }
    , m_minimizingPlayer{ other.m_minimizingPlayer }
{
    for (const auto& child : other.m_children)
    {
        m_children.push_back(std::make_shared<BoardNode>(*child));
    }
}

std::vector<std::shared_ptr<BoardNode>> BoardNode::GetChildren()
{
    return m_children;
}

void BoardNode::InsertChildren(std::shared_ptr<BoardNode> children)
{
    m_children.push_back(children);
}

bool BoardNode::GameOver() const
{
    if (CheckWinner(m_maximizingPlayer) || CheckWinner(m_minimizingPlayer))
    {
        return true;
    }
    return false;
}

int16_t BoardNode::Evaluate() const
{
    return 0;
}

BoardNode& BoardNode::operator=(const BoardNode& rhs)
{
    if (this != &rhs) // Check for self-assignment
    {
        static_cast<Board&>(*this) = rhs;

        m_children.clear();

        for (const auto& child : rhs.m_children)
        {
            m_children.push_back(std::make_shared<BoardNode>(*child));
        }
    }

    return *this;
}
