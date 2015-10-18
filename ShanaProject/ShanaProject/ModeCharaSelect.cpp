#include "Game.h"
#include "ModeCharaSelect.h"
#include "CharaSelMenu.h"
#include "CharaSelBack.h"
#include "CharaSelCut.h"
#include "CharaSelPuchi.h"
#include "ResBattle.h"
#include "d3dmain.h"
#include "ShanaMain.h"
#include "UTL_Screen.h"

#include "DsoundMain.h"

CModeCharaSelect::CModeCharaSelect( CGame *game )
:m_Game(game), m_decidePlayer1(0), m_decidePlayer2(1)
{
	Initialize();
}

CModeCharaSelect::~CModeCharaSelect()
{
	MacroDelete( m_CommonBack );
	MacroDelete( m_CommonChara );
	MacroDelete( m_CommonSystem );
	MacroDelete( m_CommonBack );
	MacroDelete( m_CommonScene );
	delete m_CommonChara;
	delete m_CommonScene;
	delete m_CommonBack;
	delete m_CommonSystem;
	delete m_CommonEffect;
}

void CModeCharaSelect::Initialize()
{
	// タスクリスト作成
	m_CommonScene	= new CCommonData( sizeof( CCharaSelMenu ), 5 );
	m_CommonSystem	= new CCommonData( sizeof( CCharaSelPuchi ), 10 );
	m_CommonEffect	= new CCommonData( sizeof( CCharaSelMenu ), 10 );
	m_CommonBack	= new CCommonData( sizeof( CCharaSelMenu ), 10 );
	m_CommonChara	= new CCommonData( sizeof( CCharaSelPuchi ), 5 );

	// リソース作成
	m_Resource.m_AnimationManager	= m_Game->m_AnimationManager;
	m_Resource.m_CommonEffect		= m_CommonEffect;
	m_Resource.m_CommonMode			= m_Game->m_CommonMode;
	m_Resource.m_CommonBack			= m_CommonBack;
	m_Resource.m_CommonSystem		= m_CommonSystem;
	m_Resource.m_CommonScene		= m_CommonScene;
	m_Resource.m_D3DDraw			= &m_Game->m_D3DDraw;
	m_Resource.m_DispObjGroup		= m_Game->m_DispObjGroup;
	m_Resource.m_Input				= m_Game->m_Input;
	m_Resource.m_MeshTestGroup		= m_Game->m_MeshTestGroup;
	m_Resource.m_TextureManager		= m_Game->m_TextureManager;

	// 最初のモード
	m_Mode = 0;
	m_NextMode = 0;
	m_SubMode = 0;

}

bool CModeCharaSelect::Move()
{
	int i;

	m_Mode = m_NextMode ;

	CCharaSelPuchi* player1;
	CCharaSelPuchi* player2;
	switch( m_Mode ){
		case 0:		// キャラクター作成などなど

			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_CHARA_SELECT_MENU ), ANIME_NO_CHARA_SELECT_MENU );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_CHARA_SELECT_MENU ), TEXTURE_NO_CHARA_SELECT_MENU );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_CHARA_SELECT_BACK ), ANIME_NO_CHARA_SELECT_BACK );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_CHARA_SELECT_BACK ), TEXTURE_NO_CHARA_SELECT_BACK );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_CHARA_SELECT_CUTIN ), ANIME_NO_CHARA_SELECT_CUTIN );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_CHARA_SELECT_CUTIN ), TEXTURE_NO_CHARA_SELECT_CUTIN );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_CHARA_SELECT_PUCHI ), ANIME_NO_CHARA_SELECT_PUCHI );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_CHARA_SELECT_PUCHI ), TEXTURE_NO_CHARA_SELECT_PUCHI );
/*			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_CHILD_LOGO ), TEXTURE_NO_SYS_CHILD_LOGO );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_MENU ), ANIME_NO_SYS_TITLE_MENU );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_MENU ), TEXTURE_NO_SYS_TITLE_MENU );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_MODEL ), ANIME_NO_SYS_TITLE_MODEL );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_REIJI_MAIGO ), TEXTURE_NO_SYS_TITLE_REIJI_MAIGO );

			m_Game->m_MeshTestGroup->LoadXFile( 0, "asm_r.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 1, "asm_l.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 2, "gear_s.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 3, "gear_m.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 4, "gear_l.x" );
*/
//			new(m_CommonChara) CTestX( &m_Resource );
//			m_TitleRod = new(m_CommonSystem)CTitleRod( &m_Resource );
//			new(m_CommonChara) CTitlePartB( &m_Resource );
//			new(m_CommonChara) CTitleModel( &m_Resource );
//			SetMode( 2 );
//			m_TitlePartB = new(m_CommonChara) CTitlePartB( &m_Resource );
			SetMode( 1 );
			m_Flame = 0;
			break;

		case 1:
//			m_Flame=0;
//			new(m_CommonSystem) CTitlePartB( &m_Resource );
//			SetMode( 4 );
			new(m_CommonSystem) CCharaSelBack( &m_Resource , this );
			player1 = new(m_CommonChara) CCharaSelPuchi( &m_Resource , this, 0 );
			player2 = new(m_CommonChara) CCharaSelPuchi( &m_Resource , this, 1 );
			new(m_CommonSystem) CCharaSelCut( &m_Resource , this, player1, player2 );
			new(m_CommonSystem) CCharaSelMenu( &m_Resource , this );
			m_Flame = 0;
			SetMode( 10 );
			break;
	}


	// MOVEメイン
	CElement*	cEle;
	CElement*	cEleNext;

/*	cEle = m_CommonScene->m_ActiveTask->m_Next;
	while( cEle->m_Next != m_CommonScene->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Event();
		if( cEle->Move() == FALSE ){
			delete cEle;
		}
		else{
//			cEle->Action();
		}
		cEle = cEleNext ;
	}

	MacroMove( m_CommonBattleMenu );
	MacroMove( m_CommonTitle );
*/
/*	if( m_SubMode == 0 ){
		// event
		MacroEvent( m_CommonCpuPlayer );
		// move
		MacroMove( m_CommonCpuPlayer );

		for( int i = 0 ; i < 2 ; i++ ){
			// event
			MacroEvent( m_CommonChara[i] );
		}
		for( int i = 0 ; i < 2 ; i++ ){
			// move
			MacroMove( m_CommonChara[i] );
		}

		MacroMove( m_CommonEffect );
		MacroMove( m_CommonEffectFront );
		MacroMove( m_CommonSystem );
		MacroMove( m_CommonUtilScreen );
		MacroMove( m_CommonBack );
		MacroMove( m_CommonSystemFront );
	}
*/
	// シーン制御
/*	if( m_Mode == 10 ){
		m_Flame++;
		if( m_Flame == 200){
			// BGM START
			SBArr[ENUM_BGM_TITLE].SB_lpDSB->SetCurrentPosition(0);
			SBArr[ENUM_BGM_TITLE].SB_lpDSB->Play(0,0,0);
		}
		else if( m_Flame == 480 ){
			m_Flame = 0;
			SetMode(2);
		}
	}
	else if( m_Mode == 2 ){
		m_Flame++;
		if( m_Flame == 1){
			m_TitleRod = new(m_CommonSystem)CTitleRod( &m_Resource );
//			new(m_CommonChara) CTitleMenu( &m_Resource , this );
			SetMode( 3 );
		}
	}
	else if( m_Mode == 3 ){
		if( (m_TitleRod->GetState() == 6)&&
			(m_TitleRod->GetFlame() == 0) ){
				new(m_CommonChara) CTitleMenu( &m_Resource , this );
		}
		if( (m_TitleRod->GetState() == 7)&&
			(m_TitleRod->GetFlame() == 1380) ){
			m_Flame=0;
			new(m_CommonSystem) CTitlePartB( &m_Resource );
			SetMode( 4 );
		}
	}
	else if( m_Mode == 4 ){
		m_Flame++;
		if( m_Flame == 20){
			new(m_CommonBack) CTitleModel( &m_Resource );
			SetMode( 5 );
		}
	}
*/	if( m_Mode == 7 ){
		m_Game->SetMode( 1 );
		SetMode( 8 );
	}

	MacroEvent( m_CommonSystem );
	MacroMove( m_CommonSystem );
	MacroEvent( m_CommonBack );
	MacroMove( m_CommonBack );
	MacroEvent( m_CommonChara );
	MacroMove( m_CommonChara );
//	m_Game->SetMode( 1 );
//	return FALSE;
	return TRUE;
}

void CModeCharaSelect::SetMode( int mode )
{
	m_NextMode = mode ;
}

bool CModeCharaSelect::Action()
{
	CElement*	cEle;
	CElement*	cEleNext;

/*
	if( m_SubMode == 0 ){
		MacroAction( m_CommonCpuPlayer );

		for( int i = 0 ; i < 2 ; i++ ){
			MacroAction( m_CommonChara[i] );
		}

		MacroAction( m_CommonEffect );
		MacroAction( m_CommonEffectFront );
		MacroAction( m_CommonSystem );
		MacroAction( m_CommonUtilScreen );
		MacroAction( m_CommonBack );
		MacroAction( m_CommonSystemFront );
	}
*/
	MacroAction( m_CommonBack );
	MacroAction( m_CommonChara );
	MacroAction( m_CommonSystem );

	return TRUE;

}

bool CModeCharaSelect::ActionFinalize()
{
/*
	CElement*	cEle;
	CElement*	cEleNext;

	if( m_SubMode == 0 ){
		MacroActionFinalize( m_CommonCpuPlayer );

		for( int i = 0 ; i < 2 ; i++ ){
			MacroActionFinalize( m_CommonChara[i] );
		}

		MacroActionFinalize( m_CommonEffect );
		MacroActionFinalize( m_CommonEffectFront );
		MacroActionFinalize( m_CommonSystem );
		MacroActionFinalize( m_CommonUtilScreen );
		MacroActionFinalize( m_CommonBack );
		MacroActionFinalize( m_CommonSystemFront );
	}
*/
	MacroActionFinalize( m_CommonBack );
	MacroActionFinalize( m_CommonChara );
	MacroActionFinalize( m_CommonSystem );
	return TRUE;

}

bool CModeCharaSelect::Interfere( )
{
	// MOVEメイン
/*
	CElement*	cEle;
	CElement*	cEleNext;

	if( m_SubMode == 0 ){
		MacroInterfere( m_CommonCpuPlayer );

		for( int i = 0 ; i < 2 ; i++ ){
			MacroInterfere( m_CommonChara[i] );
		}

		MacroInterfere( m_CommonEffect );
		MacroInterfere( m_CommonEffectFront );
		MacroInterfere( m_CommonSystem );
		MacroInterfere( m_CommonUtilScreen );
		MacroInterfere( m_CommonBack );
		MacroInterfere( m_CommonSystemFront );

	}
*/
	MacroInterfere( m_CommonBack );
	MacroInterfere( m_CommonChara );
	MacroInterfere( m_CommonSystem );
	return TRUE;
}

bool CModeCharaSelect::InterfereFinalize( )
{
	// MOVEメイン
/*	CElement*	cEle;
	CElement*	cEleNext;

	if( m_SubMode == 0 ){

		for( int i = 0 ; i < 2 ; i++ ){
			MacroInterfereFinalize( m_CommonChara[i] );
		}

		MacroInterfereFinalize( m_CommonEffect );
		MacroInterfereFinalize( m_CommonEffectFront );
		MacroInterfereFinalize( m_CommonSystem );
		MacroInterfereFinalize( m_CommonUtilScreen );
		MacroInterfereFinalize( m_CommonBack );
		MacroInterfereFinalize( m_CommonSystemFront );
		MacroInterfereFinalize( m_CommonCpuPlayer );
	}
*/
	MacroInterfereFinalize( m_CommonBack );
	MacroInterfereFinalize( m_CommonChara );
	MacroInterfereFinalize( m_CommonSystem );
	return TRUE;
}

bool CModeCharaSelect::Draw( CD3DDraw* draw )
{
	CElement*	cEle;
	CElement*	cEleNext;

	// 戦闘中
	// スクリーン１回目（最初）
/*	MacroDraw( draw, m_CommonUtilScreen );
	MacroDraw( draw, m_CommonBack );

	// スクリーン（後処理）
	MacroDraw( m_CommonUtilScreen );

	MacroDraw( draw, m_CommonSystem );

	// 戦闘中
	// スクリーン２回目（最初）
	MacroDraw( draw, m_CommonUtilScreen );
	MacroDraw( draw, m_CommonEffect );

	if( m_Resource.GetReceivedAttackPlayer() == 0 ){
		MacroDraw( draw, m_CommonChara[0] );
		MacroDraw( draw, m_CommonChara[1] );
	}
	else{
		MacroDraw( draw, m_CommonChara[1] );
		MacroDraw( draw, m_CommonChara[0] );
	}

	MacroDraw( draw, m_CommonEffectFront );

	// スクリーン（後処理）
	MacroDraw( m_CommonUtilScreen );

	MacroDraw( draw, m_CommonSystemFront );
	MacroDraw( draw, m_CommonScene );

	// バトルメニュー
	if( m_SubMode == SUB_MODE_MENU ){
		cEle = m_CommonBattleMenu->m_ActiveTask->m_Next;
		if( cEle != m_CommonBattleMenu->m_ActiveTask ){
			cEle->Draw( draw );
		}
	}
*/

	MacroDraw( draw, m_CommonBack );
	// title
	MacroDraw( draw, m_CommonSystem );
	MacroDraw( draw, m_CommonChara );
	return TRUE;
}

bool CModeCharaSelect::DrawFinalize()
{
	// MOVEメイン
/*	CElement*	cEle;
	CElement*	cEleNext;

	if( m_SubMode == 0 ){

		for( int i = 0 ; i < 2 ; i++ ){
			MacroDrawFinalize( m_CommonChara[i] );
		}

		MacroDrawFinalize( m_CommonEffect );
		MacroDrawFinalize( m_CommonEffectFront );
		MacroDrawFinalize( m_CommonSystem );
		MacroDrawFinalize( m_CommonUtilScreen );
		MacroDrawFinalize( m_CommonBack );
		MacroDrawFinalize( m_CommonSystemFront );
		MacroDrawFinalize( m_CommonCpuPlayer );
	}
*/
	MacroDrawFinalize( m_CommonBack );
	MacroDrawFinalize( m_CommonSystem );
	MacroDrawFinalize( m_CommonChara );
	return TRUE;
}

bool CModeCharaSelect::Event()
{
/*	CElement*	cEle;
	CElement*	cEleNext;

	cEle = m_CommonSystem->m_ActiveTask->m_Next;
	while( cEle->m_Next != m_CommonSystem->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Event( );
		cEle = cEleNext ;
	}
*/
	return TRUE;
}

/*bool CModeBattle::Action()
{
	return TRUE;
}
*/

void CModeCharaSelect::BattlePause()
{
	m_SubMode = 0;
}

void CModeCharaSelect::BattleResume()
{
	SetMode( 7 );
}

void CModeCharaSelect::DecideChara(int player, int decide)
{
	if (player == 0)
	{
		m_decidePlayer1 = decide;
	}
	if (player == 1)
	{
		m_decidePlayer2 = decide;
	}
}

int CModeCharaSelect::GetDecideChara(int player)
{
	if (player == 0)
	{
		return m_decidePlayer1;
	}
	if (player == 1)
	{
		return m_decidePlayer2;
	}
}

// 楽チンマクロ集
void CModeCharaSelect::MacroAction( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Action() ;
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroActionFinalize( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;

	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->ActionFinalize() ;
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroDraw( CD3DDraw *draw, CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Draw( draw );
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroDraw( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Draw( );
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroDrawFinalize( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->DrawFinalize() ;
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroEvent( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Event();
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroInterfere( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Interfere() ;
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroInterfereFinalize( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->InterfereFinalize() ;
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroMove( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		if( cEle->Move() == FALSE ){
			delete cEle;
		}
		else{
//				cEle->Action();
		}
		cEle = cEleNext ;
	}
}

void CModeCharaSelect::MacroDelete( CCommonData *common)
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = common->m_ActiveTask->m_Next;
	while( cEle->m_Next != common->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		delete cEle;
		cEle = cEleNext ;
	}
}
