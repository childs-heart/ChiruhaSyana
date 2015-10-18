#pragma once
#include "CAI_Action.h"
/////////////////////////////
// アクション コマンド
/////////////////////////////
class CAIAction;
class CNpcAIShana;
class CAICombo;
class CACTCombo:public CAIAction
{
public:
	CACTCombo();
	~CACTCombo();

	CAIAction * m_Action;
	CNpcAIShana * m_Target;

	char  m_Type;
	short m_Time[10];
	int	  m_Command[10];
	char m_Name[32];
	CAICombo* m_Combo;

	int GetAction();
	void Add( char * );
	void Analyze();
	void Strip( char * );
	void SerchCombo( char* name , CAICombo* comboList = 0 );

//	virtual CAIAction* MakeAction( char * );
//	virtual void SetParam( int paraNo, char* param );
//	virtual int Run();
//	virtual void SetTarget( CNpcAIShana * target );
};
