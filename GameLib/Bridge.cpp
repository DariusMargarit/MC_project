module Bridge;

Bridge::Bridge(IColumn* firstColumn, IColumn* secondColumn)
	: m_firstColumn{firstColumn}
	, m_secondColumn{secondColumn}
{
}


const IColumn* Bridge::GetFirstColumn() const
{
	return m_firstColumn;
}

const IColumn* Bridge::GetSecondColumn() const
{
	return m_secondColumn;
}

Bridge::Bridge(const Bridge& otherBridge)
{
	if (otherBridge.m_firstColumn)
		this->m_firstColumn = otherBridge.m_firstColumn;
	else
		this->m_firstColumn = nullptr;
	if (otherBridge.m_secondColumn)
		this->m_secondColumn = otherBridge.m_secondColumn;
	else
		this->m_secondColumn = nullptr;

}

Bridge& Bridge::operator=(const Bridge& otherBridge)
{
	if (this == &otherBridge)
		return *this;

	if (otherBridge.m_firstColumn)
		m_firstColumn = otherBridge.m_firstColumn;
	else
		m_firstColumn = nullptr;


	if (otherBridge.m_secondColumn)
		m_secondColumn = otherBridge.m_secondColumn;
	else
		m_secondColumn = nullptr;


	return *this;
}





