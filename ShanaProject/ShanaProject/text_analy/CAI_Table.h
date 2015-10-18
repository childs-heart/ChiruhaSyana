#pragma once
/////////////////////////////
// AIテーブル
/////////////////////////////
#include "CAI_ACT_UsageCombo.h"
class CAITrigger;
class CAICost;
class CAIAction;
class CAICondition;
class CACTCombo;
class CAICombo;

class CAITable
{
public:
	
	const int MAX ;

	enum a{
		TAG_TYPE_NONE	= 0,
		TAG_TYPE_TRIGGER	= 1,
		TAG_TYPE_COST	= 2,
		TAG_TYPE_ACTION	= 3,
		TAG_TYPE_COMBO = 4,
		TAG_TYPE_GO = 5
	};
	enum b{
		TRIGGER_TYPE_NORMAL = 0,
		TRIGGER_TYPE_ELSE = 1
	};
	enum c{
		STATUS_IDLE = 0,					// 文字解析 現在フラグなし
		STATUS_TAG_SET_BIGINNING = 1,		// 文字解析 現在[]内
		STATUS_CONDITION_SET_BIGINNING = 2 // 文字解析 現在Condition内（「:***」）
	};

protected:
	int			m_CurrentNo;
	int			m_TagType;
	int			m_Status;
	bool		m_FirstTriggerFlag ;
	int			m_RandomValueWeight ;

	CAITrigger** m_ppTrigger;
	int*		m_pTriggerType;
	CAICost**	m_ppCost;
	CAIAction**	m_ppAction;
	CAIAction*	m_pLastAction;
	CACTUsageCombo	m_LastCombo;
	CAIAction*	m_pNullAction;
	CAICondition*	m_pCondition;
	CAICombo*	m_pCombo;
	CACTCombo*	m_pActCombo;
	char**		m_ppGoCondition;

	int			m_MaxTriggerNum;
	int			m_MaxCostNum;
	int			m_MaxActionNum;
	int			m_MaxConditionNum;
	int			m_MaxCombo;

	char		m_TagTemp[32];

public:
	CAITable();
	~CAITable();

	virtual void SetUp( );
	void SetTag( char *data );
	void Add( char *data );
	void AddEnd( );
	void Judge();
	CACTUsageCombo*	GetCombo();
	CAIAction*	GetAction();

};
