/************************/
/* バトル中のメニュー	*/
/************************/

#include "CpuPlayer.h"
#include "BattleMenu.h"
#include "ModeBattle.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Input.h"

CCpuPlayer::CCpuPlayer( CResBattle *game, CModeBattle *battle_mode, CDataBattleMenu *battle_manu ):CSprite( game )
{
	m_Input = game->m_Input ;
	m_Battle = battle_mode;
	m_Data = battle_manu;

	// 資源調達
//	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( 95 );
//	m_Tex					= game->m_TextureManager->GetTextureGroup( 95 );
//	m_DispObjGroup			= m_Game->m_DispObjGroup;
//	m_DispObj				= m_DispObjGroup->GetDispObj();

//	Setup();
}

CCpuPlayer::~CCpuPlayer()
{
}

bool CCpuPlayer::Event()
{
//	m_Input->UpDateState_Pad();

	return true;
}

bool CCpuPlayer::Move()
{
//	m_Input->UpDateState_Pad();
	unsigned long pad1,pad2 ;
	// メニュー非表示中

	for( int i = 0 ; i < 2 ; i++ ){
		m_PadTemp[i] = m_Input->GetPadData( i );
	}

	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_1P ) == CDataBattleMenu::STATUS_ITEM_MANUAL ){
	}
	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_1P ) == CDataBattleMenu::STATUS_ITEM_STAND ){
		m_Input->SetPadData( 0, PAD_NONE );
	}
	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_1P ) == CDataBattleMenu::STATUS_ITEM_CROUCH ){
		m_Input->SetPadData( 0, PAD_DOWN_ON );
	}
	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_1P ) == CDataBattleMenu::STATUS_ITEM_JUMP ){
		m_Input->SetPadData( 0, PAD_UP_ON );
	}

	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_2P ) == CDataBattleMenu::STATUS_ITEM_MANUAL ){
	}
	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_2P ) == CDataBattleMenu::STATUS_ITEM_STAND ){
		m_Input->SetPadData( 1, PAD_NONE );
	}
	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_2P ) == CDataBattleMenu::STATUS_ITEM_CROUCH ){
		m_Input->SetPadData( 1, PAD_DOWN_ON );
	}
	if( m_Data->GetValue( CDataBattleMenu::SELECT_TOP_STATUS_2P ) == CDataBattleMenu::STATUS_ITEM_JUMP ){
		m_Input->SetPadData( 1, PAD_UP_ON );
	}
	return TRUE;
}

bool CCpuPlayer::InterfereFinalize()
{
	for( int i = 0 ; i < 2 ; i++ ){
		m_Input->SetPadData( i, m_PadTemp[i] );
	}

	return TRUE;
}

bool CCpuPlayer::Draw( CD3DDraw *draw )
{

	return true;
}

bool CCpuPlayer::DrawFinalize( )
{

	return true;
}
