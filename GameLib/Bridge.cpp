module Bridge;

Bridge::Bridge(IColumn* firstColumn, IColumn* secondColumn)
	: m_firstColumn{firstColumn}
	, m_secondColumn{secondColumn}
{
	// Empty
}


 IColumn* Bridge::GetFirstColumn() const
{
	return m_firstColumn;
}

 IColumn* Bridge::GetSecondColumn() const
{
	return m_secondColumn;
}

 bool Bridge::HasPositions(IColumn* pos1,  IColumn* pos2) const
 {
	 return (m_firstColumn == pos1 && m_secondColumn == pos2) ||
		 (m_firstColumn == pos2 && m_secondColumn == pos1);
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

Bridge::Bridge(Bridge&& otherBridge) noexcept
{
	if (otherBridge.m_firstColumn)
		this->m_firstColumn = otherBridge.m_firstColumn;
	else
		this->m_firstColumn = nullptr;
	if (otherBridge.m_secondColumn)
		this->m_secondColumn = otherBridge.m_secondColumn;
	else
		this->m_secondColumn = nullptr;

	otherBridge.m_firstColumn = nullptr;
	otherBridge.m_secondColumn = nullptr;
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

Bridge& Bridge::operator=(Bridge&& otherBridge) noexcept
{
	if (this == &otherBridge)
	{
		otherBridge.m_firstColumn = nullptr;
		otherBridge.m_secondColumn = nullptr;
		return *this;
	}

	if (otherBridge.m_firstColumn)
		m_firstColumn = otherBridge.m_firstColumn;
	else
		m_firstColumn = nullptr;

	if (otherBridge.m_secondColumn)
		m_secondColumn = otherBridge.m_secondColumn;
	else
		m_secondColumn = nullptr;

	otherBridge.m_firstColumn = nullptr;
	otherBridge.m_secondColumn = nullptr;

	return *this;
}





