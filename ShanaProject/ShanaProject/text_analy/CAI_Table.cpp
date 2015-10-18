#include "CAI_Cost.h"
#include "CAI_Action.h"
#include "CAI_ACT_Stop.h"
#include "CAI_Trigger.h"
#include "CAI_Table.h"
#include "CAI_Condition.h"
#include "CAI_ACT_Combo.h"
#include "CAI_Combo.h"
#include "CAI_ACT_NotAction.h"
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

/////////////////////////////
// AIテーブル
/////////////////////////////
CAITable::CAITable()
:MAX(50){
/*
m_CurrentNo		= 0;
	m_TagType		= 0;

	m_pTrigger		= new CAITrigger[MAX];
	m_pTriggerType	= new int[MAX];
	m_pCost			= new CAICost[MAX];
	m_pAction		= new CAIAction[MAX];
	m_pNullAction	= new CACTNoAction();
	m_pLastAction	= m_pNullAction;

	m_MaxActionNum	= 0;
	m_MaxCostNum	= 0;
	m_MaxTriggerNum	= 0;
*/
}

void CAITable::SetUp()
{
	m_CurrentNo		= 0;
	m_TagType		= 0;
	m_FirstTriggerFlag = true;

	m_ppTrigger		= new CAITrigger*[MAX];
	m_ppCost		= new CAICost*[MAX];
	m_ppAction		= new CAIAction*[MAX];
	m_ppGoCondition	= new char*[MAX];
	for(int i = 0 ; i < MAX ; i++ ){
		m_ppTrigger[i]	= new CAITrigger();
		m_ppCost[i]		= new CAICost();
		m_ppAction[i]	= new CAIAction();
		m_ppGoCondition[i] = new char[32];
	}
	m_pTriggerType	= new int[MAX];
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

CAITable::~CAITable()
{
	delete[] m_ppTrigger;
	delete m_pTriggerType;
	delete[] m_ppCost;
	delete[] m_ppAction;
	delete[] m_pCondition;
	delete m_pNullAction;
	delete[] m_ppGoCondition;
}

void CAITable::SetTag( char *data )
{
	if( strcmp( data, "TIGGER" ) == 0 ){
		m_TagType= TAG_TYPE_TRIGGER ;
	}
	else if( strcmp( data, "COST" ) == 0 ){
		m_TagType = TAG_TYPE_COST ;
	}
	else if( strcmp( data, "ACTION" ) == 0 ){
		m_TagType = TAG_TYPE_ACTION ;
	}
	else{
		m_TagType = TAG_TYPE_NONE;
	}
}

void CAITable::Add( char *data )
{
	// タグ内でない場合、タグが来るまで動かない
	if( ( data[0] == '[' )
	  ||( data[0] == '{' ) ){
		switch( m_TagType ){
			case TAG_TYPE_TRIGGER:
				m_ppTrigger[m_CurrentNo]->Analyze( );
				m_MaxTriggerNum++;
			break;

			case TAG_TYPE_COST:
//				m_MaxCostNum++;
//				m_ppCost[m_CurrentNo]->Add( data );
			break;

			case TAG_TYPE_ACTION:
//				m_MaxActionNum++;
//				m_ppAction[m_CurrentNo]->Add( data );
			break;

			case TAG_TYPE_COMBO:
				m_MaxCombo++;
			break;
		}
		m_Status = STATUS_TAG_SET_BIGINNING ;
		m_TagType = TAG_TYPE_NONE;
		memset( m_TagTemp, 0, 32 );
	}
	else if( data[0] == ':' ){
		// 初回だけしない
		if( m_FirstTriggerFlag ){
			m_FirstTriggerFlag = false;
		}
		else
		{
			m_CurrentNo++;
		}
		switch( m_TagType ){
			case TAG_TYPE_TRIGGER:
				m_ppTrigger[m_CurrentNo]->Analyze( );
				m_MaxTriggerNum++;
			break;

			case TAG_TYPE_COST:
//				m_MaxCostNum++;
//				m_ppCost[m_CurrentNo]->Add( data );
			break;

			case TAG_TYPE_ACTION:
//				m_MaxActionNum++;
//				m_ppAction[m_CurrentNo]->Add( data );
			break;
		}
		m_Status = STATUS_CONDITION_SET_BIGINNING;
		m_TagType = TAG_TYPE_NONE;
		m_pCondition[m_MaxConditionNum].SetCondition( &data[1], m_CurrentNo );
		m_Status = STATUS_IDLE;
		m_MaxConditionNum++;
	}
	else if( m_Status == STATUS_TAG_SET_BIGINNING ){
		// > だったらステータス更新＆タグ文字を判定
		if( ( data[0] == ']' )
		  ||( data[0] == '}' ) ){
			m_Status = STATUS_IDLE;
			if( strcmp( m_TagTemp, "TRIGGER" ) == 0 ){
				m_TagType = TAG_TYPE_TRIGGER ;
				// 初回だけしない
				if( m_FirstTriggerFlag ){
					m_FirstTriggerFlag = false;
				}
				else
				{
					m_CurrentNo++;
				}
			}
			if( strcmp( m_TagTemp, "COST" ) == 0 ){
				m_TagType = TAG_TYPE_COST ;
			}
			if( strcmp( m_TagTemp, "ACTION" ) == 0 ){
				m_TagType = TAG_TYPE_ACTION ;
			}
			if( strcmp( m_TagTemp, "COMMAND" ) == 0 ){
				m_TagType = TAG_TYPE_COMBO ;
			}
			if( strcmp( m_TagTemp, "GO" ) == 0 ){
				m_TagType = TAG_TYPE_GO ;
			}
		}
		// < でも >でも無い場合、タグ文字として、文字を借り置き
		else{
			strcpy( m_TagTemp, data );
		}
	}
	// たぶんこない
	else if( m_Status == STATUS_CONDITION_SET_BIGINNING ){
		m_pCondition[m_MaxConditionNum].SetCondition( data, m_CurrentNo );
		m_Status = STATUS_IDLE;
		m_MaxConditionNum++;
	}
	else{
		// 現在のタグ内によって文字セット先を変える
		switch( m_TagType ){
			case TAG_TYPE_TRIGGER:
				m_ppTrigger[m_CurrentNo]->Add( data );
			break;

			case TAG_TYPE_COST:
				m_ppCost[m_CurrentNo]->Add( data );
			break;

			case TAG_TYPE_ACTION:
				m_ppAction[m_CurrentNo]->Add( data, m_pCombo );
			break;

			case TAG_TYPE_COMBO:
				m_pCombo[m_MaxCombo].Add( data );
			break;

			case TAG_TYPE_GO:
				if( ( data[0] != '(' ) && ( data[0] != ')' ) ){
					strcpy( m_ppGoCondition[m_CurrentNo], data );
				}
			break;
		}
	}
}

void CAITable::AddEnd()
{
	switch( m_TagType ){
		case TAG_TYPE_TRIGGER:
			m_ppTrigger[m_CurrentNo]->Analyze( );
			m_CurrentNo++;
			m_MaxTriggerNum++;
		break;

		case TAG_TYPE_COST:
			m_MaxCostNum++;
//			m_pCost[m_CurrentNo].Add( data );
		break;

		case TAG_TYPE_ACTION:
			m_MaxActionNum++;
//			m_pAction[m_CurrentNo].Add( data );
		break;
	}
}

void CAITable::Judge()
{
	int loop;
	loop = 1;
//	while( loop ){	// トリガーが該当する場合、必ず何かアクションを起こす場合、ここを有効にする
		for( int i = 0 ; i < m_MaxTriggerNum ; i++ ){
			loop = 0;
			// トリガーで条件があうか
			if( m_ppTrigger[i]->Judge() ){
				loop = 1;
			   srand( (unsigned)time( NULL ) );
			   int r = rand();
			   r = rand();
				int cost = m_ppCost[i]->GetCost();
				if( cost > rand()%100 ){
					// アクション決定
					m_pLastAction = m_ppAction[i];
//					m_pAction[i].Run();
					loop =0;
					break;
				}
			}
		}
//	}
}

CAIAction* CAITable::GetAction()
{
	return m_pLastAction;
}

CACTUsageCombo* CAITable::GetCombo()
{
	return &m_LastCombo;
}

