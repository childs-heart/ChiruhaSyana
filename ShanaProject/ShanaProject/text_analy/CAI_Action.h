#pragma once
/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
class CNpcAIShana;
class CAICombo;
class CAIAction
{
public:
	CAIAction();
	~CAIAction();

	CAIAction * m_Action;
	CNpcAIShana * m_Target;
	bool m_FlagCombo;

	CAIAction* GetAction();
	void Add( char * , CAICombo* comboList = 0 );
	void Analyze();

	virtual CAIAction* MakeAction( char * , CAICombo* comboList = 0 );
	virtual void SetParam( int paraNo, char* param );
	virtual int Run();
	virtual void SetTarget( CNpcAIShana * target );
};
