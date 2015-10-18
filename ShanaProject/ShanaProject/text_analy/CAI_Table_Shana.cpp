#include "CAI_Cost.h"
#include "CAI_ACT_Stop.h"
#include "CAI_Action_Shana.h"
#include "CAI_Trigger_Shana.h"
#include "CAI_Table.h"
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include "CAI_Table_Shana.h"
#include "CAI_ACT_NotAction.h"
#include "CAI_Condition.h"
#include "CAI_ACT_Combo.h"
#include "CAI_Combo.h"

/////////////////////////////
// AIテーブル
/////////////////////////////
CAITableShana::CAITableShana()
:CAITable()
{
/*
m_CurrentNo		= 0;
	m_TagType		= 0;

	m_pTrigger		= new CAITriggerShana[MAX];
	m_pTriggerType	= new int[MAX];
	m_pCost			= new CAICost[MAX];
	m_pAction		= new CAIActionShana[MAX];
	m_pNullAction	= new CACTNoAction();
	m_pLastAction	= m_pNullAction;

	m_MaxActionNum	= 0;
	m_MaxCostNum	= 0;
	m_MaxTriggerNum	= 0;
*/
}

void CAITableShana::SetUp()
{
//	CAITable::SetUp();

	m_CurrentNo		= 0;
	m_TagType		= 0;
	m_FirstTriggerFlag = true;
	m_ConditionCurrentIndex = 0;

	m_ppTrigger		= new CAITrigger*[MAX];
	m_ppCost		= new CAICost*[MAX];
	m_ppAction		= new CAIAction*[MAX];
	m_ppGoCondition	= new char*[MAX];
	for(int i = 0 ; i < MAX ; i++ ){
		m_ppTrigger[i]	= new CAITriggerShana();
		m_ppCost[i]		= new CAICost();
		m_ppAction[i]	= new CAIActionShana();
		m_ppGoCondition[i] = new char[32];
	}

	m_pTriggerType	= new int[5];
	m_pNullAction	= new CACTStop();
	m_pLastAction	= m_pNullAction;
	m_pCondition	= new CAICondition[100];
	m_pCombo		= new CAICombo[100];
	m_pActCombo		= new CACTCombo[100];

	m_MaxActionNum	= 0;
	m_MaxCostNum	= 0;
	m_MaxTriggerNum	= 0;
	m_MaxConditionNum = 0;
	m_MaxCombo = 0;

}

CAITableShana::~CAITableShana()
{
}

void CAITableShana::SetTarget( CNpcAIShana * target )
{
	CAITriggerShana* tri;
	CAIActionShana* act;
	CNpcAIShana* ai;
	ai = (CNpcAIShana*)target;
	for( int i = 0 ; i < MAX ; i++ ){
		tri = (CAITriggerShana*)m_ppTrigger[i];
		tri->SetTarget( target );
//		act = (CAIActionShana*)&m_pAction[i];
//		act->SetTarget( target );
		m_ppAction[i]->SetTarget( target );
	}
	m_pNullAction->SetTarget( target );
	m_LastCombo.SetTarget( target );

}

void CAITableShana::Judge()
{
	if( m_pLastAction->m_FlagCombo ){
		if ( m_LastCombo.GetCombo() != NULL )
		{
			return ;
		}
	}
	int loop;
	loop = 1;
	int cost ;
	static int r = time( NULL ) + (int)this;
	r = rand();
//	while( loop ){	// トリガーが該当する場合、必ず何かアクションを起こす場合、ここを有効にする
	for( int i = m_pCondition[m_ConditionCurrentIndex].GetConditionNo() ;
			(( i < m_MaxTriggerNum ) && ( i != m_pCondition[m_ConditionCurrentIndex+1].GetConditionNo())) ; i++ ){
		loop = 0;
		// トリガーで条件があうか
		if( m_ppTrigger[i]->Judge() ){
			loop = 1;
//			srand( r );//(unsigned)time( NULL ) + r + (int)this );
//			r = rand();
			cost = m_ppCost[i]->GetCost();
			if( cost > r%100 ){
				// アクション決定
				m_pLastAction = m_ppAction[i];
//					m_pAction[i].Run();
				loop =0;
				// コンボの場合、コンボ設定
				if( m_pLastAction->m_FlagCombo ){
					CACTCombo* combo = (CACTCombo*)m_pLastAction->GetAction();
					m_LastCombo.SetCombo( combo->m_Combo ) ;
				}else{
					m_LastCombo.SetCombo( NULL );
				}

				// コンディション変更
				if( m_ppGoCondition[i][0] != 0 )
				{
					for( int j = 0 ; j < m_MaxConditionNum ; j++ ){
						if( strcmp( m_ppGoCondition[i], m_pCondition[j].GetConditionName() ) == 0 ){
							// 次のコンディションを決定する
							m_ConditionCurrentIndex = j;//m_pCondition[j].GetConditionNo() ;
						}
					}
				}
				break;
			}
		}
	}
//	}
}
