#pragma once
/////////////////////////////
// AIèÛë‘
/////////////////////////////

class CAICombo
{

protected:

public:
	CAICombo();
	~CAICombo();

	CAIAction * m_Action;
	CNpcAIShana * m_Target;

	void Add( char * );
	void Analyze();
/*	int GetAction();

	virtual CAIAction* MakeAction( char * );
	virtual void SetParam( int paraNo, char* param );
	virtual int Run();
	virtual void SetTarget( CNpcAIShana * target );

	void	SetCondition( char * name, unsigned short tableNo );
	unsigned short	m_TableNo;
*/
};
