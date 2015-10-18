#pragma once
/////////////////////////////
// アクション コマンド
/////////////////////////////
#include "CAI_Action.h"
class CAIAction;
class CNpcAIShana;
class CAICombo;
class CACTUsageCombo:public CAIAction
{
public:
	CACTUsageCombo();
	~CACTUsageCombo();

	char  m_Type;
	short m_Time[10];
	int	  m_Command[10];
	char m_Name[32];
	short m_CurrentPoint;
	CAICombo* m_Combo;

	virtual int Run();
	int GetAction();
	void SetCombo( CAICombo* combo );
	CAICombo* GetCombo( );
};
