#include "CAI_Action.h"
#include "CAI_ACT_Forward.h"
#include "CAI_ACT_Back.h"
#include "CAI_ACT_NotAction.h"
#include "CAI_ACT_Combo.h"
#include "Stdio.h"
#include <string.h>

/////////////////////////////
// アクション
/////////////////////////////
void CAIAction::Add( char *data , CAICombo* comboList )
{
	char* res ;
	int cnt = 0;
	const char derimit[] = ",";
	// 文字列をコンマ区切り
	res = strtok( data, derimit );

	// アクション追加
	CAIAction* act = MakeAction( res, comboList );
	// 無事にアクションが追加できたら、パラメータを随時追加する
	if( act != NULL ){
		res = strtok( NULL, derimit );
		while( res != NULL ){
			act->SetParam( cnt, res );
			cnt ++;
			res = strtok( NULL, derimit );
		}
	}
}

CAIAction* CAIAction::MakeAction( char *data , CAICombo* comboList )
{
	// ① 演算式ジャッジ
	if( strcmp( data, "Forward") == 0 ){
		m_Action  = new CACTForward();
	}
	else if( strcmp( data, "Back") == 0 ){
		m_Action  = new CACTBack();
	}
	else if( strcmp( data, "NoAction") == 0 ){
		m_Action  = new CACTNotAction();
	}
	else
	// ②該当アクションがない場合、コンボから探す
	{
		m_Action = new CACTCombo();
		m_Action->SetTarget( m_Target );
		m_FlagCombo = true;
		CACTCombo* combo ;
		combo = ( CACTCombo* )m_Action;
		combo->SerchCombo( data, comboList );
	}

	return m_Action;
}

void CAIAction::SetParam( int paraNo, char* param )
{
	// 何もしない
}

CAIAction::CAIAction()
{
	m_Action	= NULL;
	m_Target	= NULL;
	m_FlagCombo	= false;
}

CAIAction::~CAIAction()
{
	if( m_Action != NULL ){
		delete m_Action;
	}
}

CAIAction* CAIAction::GetAction( )
{
	return m_Action;
}

void CAIAction::SetTarget( CNpcAIShana *target )
{
	m_Target = target;
}

int CAIAction::Run()
{
	if( m_Action != NULL ){
		m_Action->Run();
	}

	return 0;
}
