#include "BoardNode.h"

BoardNode::BoardNode(const Board& board)
	: Board(board)
{
	// Empty
}

BoardNode::BoardNode(const BoardNode& other)
	:Board(other)
{
    for (const auto& child : other.m_children)
    {
		m_children.push_back(new BoardNode(*child));
    }
}

BoardNode::~BoardNode()
{
	for (auto& child : m_children)
	{
		delete child;
	}
}

BoardNode& BoardNode::operator=(const BoardNode& rhs)
{
    if (this != &rhs) // Check for self-assignment
    {
        static_cast<Board&>(*this) = rhs;

        for (auto& child : m_children)
        {
            delete child;
        }
        m_children.clear();

        for (const auto& child : rhs.m_children)
        {
            m_children.push_back(new BoardNode(*child));
        }
    }

    return *this;
}
