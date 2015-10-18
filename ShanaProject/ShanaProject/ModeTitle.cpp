#include "Game.h"
#include "ModeTitle.h"
#include "TitleMenu.h"
#include "TitleFlash.h"
#include "TitleLogo.h"
#include "ResBattle.h"
#include "d3dmain.h"
#include "ShanaMain.h"
#include "UTL_Screen.h"
#include "TitleRod.h"
#include "TitlePartB.h"
#include "TestX.h"
#include "TitleModel.h"

#include "DsoundMain.h"

CModeTitle::CModeTitle( CGame *game )
:m_Game( game )
{
	Initialize();
}

CModeTitle::~CModeTitle()
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

void CModeTitle::Initialize()
{
	// タスクリスト作成
	m_CommonScene	= new CCommonData( sizeof( CTitleMenu ), 5 );
	m_CommonSystem	= new CCommonData( sizeof( CTitleMenu ), 10 );
	m_CommonEffect	= new CCommonData( sizeof( CTitleMenu ), 10 );
	m_CommonBack	= new CCommonData( sizeof( CTitleModel ), 10 );
	m_CommonChara	= new CCommonData( sizeof( CTitleModel ), 5 );

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

bool CModeTitle::Move()
{
	int i;

	m_Mode = m_NextMode ;

	switch( m_Mode ){
		case 0:		// キャラクター作成などなど

			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_X ), ANIME_NO_EFF_X );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_BACK_WHITE ), TEXTURE_NO_SYS_BACK_WHITE );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_FLASH ), ANIME_NO_SYS_TITLE_FLASH );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_ZAN ), TEXTURE_NO_SYS_TITLE_ZAN );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_ROD ), ANIME_NO_SYS_TITLE_ROD );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_ZAN_ANIIME ), TEXTURE_NO_SYS_TITLE_ZAN_ANIIME );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_PART_B ), ANIME_NO_SYS_TITLE_PART_B );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_LOGO ), ANIME_NO_SYS_TITLE_LOGO );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_CHILD_LOGO ), TEXTURE_NO_SYS_CHILD_LOGO );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_MENU ), ANIME_NO_SYS_TITLE_MENU );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_MENU ), TEXTURE_NO_SYS_TITLE_MENU );
			m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_MODEL ), ANIME_NO_SYS_TITLE_MODEL );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_REIJI_MAIGO ), TEXTURE_NO_SYS_TITLE_REIJI_MAIGO );

			m_Game->m_MeshTestGroup->LoadXFile( 0, "asm_r.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 1, "asm_l.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 2, "gear_s.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 3, "gear_m.x" );
			m_Game->m_MeshTestGroup->LoadXFile( 4, "gear_l.x" );

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
			new(m_CommonSystem) CTitleLogo( &m_Resource );
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
	if( m_Mode == 10 ){
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
	else if( m_Mode == 7 ){
		m_Game->SetMode( 5 );
		SetMode( 8 );
	}
	MacroEvent( m_CommonBack );
	MacroMove( m_CommonBack );
	MacroEvent( m_CommonChara );
	MacroMove( m_CommonChara );
	MacroEvent( m_CommonSystem );
	MacroMove( m_CommonSystem );
//	m_Game->SetMode( 1 );
//	return FALSE;
	return TRUE;
}

void CModeTitle::SetMode( int mode )
{
	m_NextMode = mode ;
}

bool CModeTitle::Action()
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

bool CModeTitle::ActionFinalize()
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

bool CModeTitle::Interfere( )
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

bool CModeTitle::InterfereFinalize( )
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

bool CModeTitle::Draw( CD3DDraw* draw )
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
	MacroDraw( draw, m_CommonChara );
	// title
	MacroDraw( draw, m_CommonSystem );
	return TRUE;
}

bool CModeTitle::DrawFinalize()
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
	MacroDrawFinalize( m_CommonChara );
	MacroDrawFinalize( m_CommonSystem );
	return TRUE;
}

bool CModeTitle::Event()
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

void CModeTitle::BattlePause()
{
	m_SubMode = 0;
}

void CModeTitle::BattleResume()
{
	SetMode( 7 );
}

// 楽チンマクロ集
void CModeTitle::MacroAction( CCommonData *common)
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

void CModeTitle::MacroActionFinalize( CCommonData *common)
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

void CModeTitle::MacroDraw( CD3DDraw *draw, CCommonData *common)
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

void CModeTitle::MacroDraw( CCommonData *common)
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

void CModeTitle::MacroDrawFinalize( CCommonData *common)
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

void CModeTitle::MacroEvent( CCommonData *common)
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

void CModeTitle::MacroInterfere( CCommonData *common)
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

void CModeTitle::MacroInterfereFinalize( CCommonData *common)
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

void CModeTitle::MacroMove( CCommonData *common)
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

void CModeTitle::MacroDelete( CCommonData *common)
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
