/************************/
/* バトル中のメニュー	*/
/************************/

#include "NpcAIShana.h"
#include "BattleMenu.h"
#include "ModeBattle.h"
#include "ResBattle.h"
#include "CAI_Table_Shana.h"
#include "CAI_Action.h"
#include "NpcCommand.h"
#include "ShanaProt.h"

#include "CLIB_DispObj.h"
#include "CLIB_Input.h"
#include "CAI_Combo.h"
#include "CAI_ACT_Forward.h"
#include "CAITableFactoryShana.h"

CNpcAIShana::CNpcAIShana( CResBattle *game, CModeBattle *battle_mode, CAITableShana *ai, CShanaProt *target )
:CSprite( game )
{
	m_Input = game->m_Input ;
	m_Battle = battle_mode;
	m_AITable = ai;
	m_AITable->SetTarget( this );
	m_Target = target;
	m_Command = new CNpcCommand();

	m_Target->SetCommand( m_Command );			// プレイヤーのパッド乗っ取り
	m_Command->setRefer( this );
	m_Command->SetCommandSequence( 0 );
	m_Command->setStandard( 0 );
	m_Command->setSpecial( 0 );

	CAITableFactoryShana	ai_fact;
	ai_fact.ReadText( ai );
	m_JudgeWaitTime = 0;
}

CNpcAIShana::~CNpcAIShana()
{
	delete m_Command ;
}

bool CNpcAIShana::Event()
{

	if( m_JudgeWaitTime == 0 ){
		m_AITable->Judge();
		m_AIAction = m_AITable->GetAction();
		if( m_AIAction->m_FlagCombo ){
			m_AITable->GetCombo()->Run();
		}
		else{
			m_AIAction->Run();
		}
//		m_RunningAction.SetCombo( m_AITable->GetCombo() );

	}
	else
	{
		m_JudgeWaitTime --;
	}
	//  CACTForward act;
	//	act.SetTarget( this );
	//	act.Run();
	return true;
}

bool CNpcAIShana::Move()
{
	unsigned long pad1,pad2 ;
	// メニュー非表示中

	return true;
}

bool CNpcAIShana::InterfereFinalize()
{
//	m_Target->SetDefaultCommand( );				// プレイヤーのパッド乗っ取り
	return true;
}

bool CNpcAIShana::Draw( CD3DDraw *draw )
{

	return true;
}

void CNpcAIShana::SetAIInput( unsigned int nrInput, unsigned int spInput )
{
	for( int i = 4 ; i > 0 ; i-- ){
		m_PadTemp[i] = m_PadTemp[i-1];
	}
	m_PadTemp[0] = nrInput;

	m_Command->setStandard( nrInput );
	m_Command->setSpecial( spInput );
	m_Command->updateInput( 0 );
}

void CNpcAIShana::SetAIInputSP( unsigned int input )
{
	for( int i = 4 ; i > 0 ; i-- ){
		m_PadTemp[i] = m_PadTemp[i-1];
	}
	m_PadTemp[0] = input;
	m_Command->setSpecial( input );
}

bool CNpcAIShana::DrawFinalize()
{
	return TRUE;
}

// キャラの向き取得
char CNpcAIShana::getDir( ){

	return m_Dir;

}


CAIRunningAction::CAIRunningAction()
{
}

void CAIRunningAction::SetCombo( CAICombo* combo )
{
	memcpy( m_Command, combo->m_Command, sizeof( m_Command ) );
	memcpy( m_Name, combo->m_Name, sizeof( m_Command ) );
	memcpy( m_Time, combo->m_Time, sizeof( m_Command ) );
	m_Type = combo->m_Type ;
}
