#include "CAI_Action.h"
#include "CAI_ACT_Forward.h"
#include "CAI_ACT_Back.h"
#include "CAI_ACT_NotAction.h"
#include "CAI_ACT_Combo.h"
#include "Stdio.h"
#include <string.h>

/////////////////////////////
// �A�N�V����
/////////////////////////////
void CAIAction::Add( char *data , CAICombo* comboList )
{
	char* res ;
	int cnt = 0;
	const char derimit[] = ",";
	// ��������R���}��؂�
	res = strtok( data, derimit );

	// �A�N�V�����ǉ�
	CAIAction* act = MakeAction( res, comboList );
	// �����ɃA�N�V�������ǉ��ł�����A�p�����[�^�𐏎��ǉ�����
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
	// �@ ���Z���W���b�W
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
	// �A�Y���A�N�V�������Ȃ��ꍇ�A�R���{����T��
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
	// �������Ȃ�
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
