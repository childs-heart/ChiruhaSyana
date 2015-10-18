#pragma once
/////////////////////////////
// AIèÛë‘
/////////////////////////////

class CAICondition
{

protected:
	char		m_ConditionName[32];

public:
	CAICondition();
	~CAICondition();

	void	SetCondition( char * name, unsigned short tableNo );
	char*	GetConditionName( );
	unsigned short GetConditionNo();
	unsigned short	m_TableNo;
};
