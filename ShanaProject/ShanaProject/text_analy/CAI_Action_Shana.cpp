#include "CAI_Action_Shana.h"
#include "CAI_ACT_Forward.h"
#include "CAI_ACT_Back.h"
#include "CAI_ACT_NotAction.h"
#include "CAI_ACT_Stop.h"
#include "CAI_ACT_DushForward.h"
#include "CAI_ACT_Jump.h"
#include "CAI_ACT_JumpForward.h"
#include "CAI_ACT_JumpBack.h"
#include "CAI_ACT_LowAttack.h"
#include "CAI_ACT_MidAttack.h"
#include "CAI_ACT_HighAttack.h"
#include "CAI_ACT_Combo.h"
#include "CAI_Combo.h"
#include "Stdio.h"
#include "ShanaProt.h"
#include "CAI_ACT_Forward.h"
#include <string.h>

/////////////////////////////
// アクション
/////////////////////////////
CAIActionShana::CAIActionShana( )
:CAIAction()
{
}

CAIActionShana::CAIActionShana( CNpcAIShana* target )
:CAIAction()
{
}

CAIActionShana::~CAIActionShana()
{
	if( m_Action != NULL ){
		delete m_Action;
	}
}

void CAIActionShana::SetTarget( CNpcAIShana *target )
{
	m_Target = target;
}

CAIAction* CAIActionShana::MakeAction( char *data, CAICombo* comboList = 0 )
{
	// ① 演算式ジャッジ
	if( strcmp( data, "Forward") == 0 ){
		m_Action  = new CACTForward();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "Back") == 0 ){
		m_Action  = new CACTBack();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "NoAction") == 0 ){
		m_Action  = new CACTNotAction();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "Stop") == 0 ){
		m_Action  = new CACTStop();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "DushForward") == 0 ){
		m_Action  = new CACTDushForward();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "Jump") == 0 ){
		m_Action  = new CACTJump();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "JumpForward") == 0 ){
		m_Action  = new CACTJumpForward();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "JumpBack") == 0 ){
		m_Action  = new CACTJumpBack();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "LowAttack") == 0 ){
		m_Action  = new CACTLowAttack();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "MidAttack") == 0 ){
		m_Action  = new CACTMidAttack();
		m_Action->SetTarget( m_Target );
	}
	else if( strcmp( data, "HighAttack") == 0 ){
		m_Action  = new CACTHighAttack();
		m_Action->SetTarget( m_Target );
	}
	else
	// ②該当アクションがない場合、コンボから探す
	{
		int i = 0;
		while( comboList[i].m_Name[0] ){
			if( strcmp( data, comboList[i].m_Name ) == 0 ){
				break;
			}
			i++;
		}
		if( comboList[i].m_Name[0] ){
			m_Action = new CACTCombo();
			m_Action->SetTarget( m_Target );
			m_FlagCombo = true;
			CACTCombo* combo ;
			combo = ( CACTCombo* )m_Action;
			combo->SerchCombo( data, comboList );
		}
	}
	return m_Action;	
}

void CAIActionShana::SetParam( int paraNo,char *param )
{
	// 何もしない
}
