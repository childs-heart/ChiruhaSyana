#include "Game.h"
#include "ModeBattle.h"
#include "BattleMenu.h"
#include "ResBattle.h"
#include "d3dmain.h"
#include "SysLogo2.h"
//#include "Title.h"
#include "ShanaProt.h"
#include "WilProt.h"
#include "ShanaMain.h"
//#include "SpTest.h"
#include "ScnHpGauge.h"
#include "SpGauge.h"
#include "Timer.h"
#include "EffTest.h"
#include "ScnBack.h"
#include "ScnBackMisago.h"
#include "EffShanaOptParts.h"
#include "UTL_Screen.h"
#include "CpuPlayer.h"
#include "ScnComboInfo.h"
#include "EffHit001.h"
#include "EffHit003.h"
#include "UTL_AttackArea.h"
#include "TestX.h"

#include "DsoundMain.h"
#include "NpcAIShana.h"
#include "CAI_Table.h"
#include "CAI_Table_Shana.h"

CModeBattle::CModeBattle( CGame *game , int player1, int player2)
:m_Game(game), m_Player1(player1), m_Player2(player2)
{
	Initialize();
}

CModeBattle::~CModeBattle()
{
	delete m_CommonTitle;
	delete m_CommonChara[0];
	delete m_CommonChara[1];
	delete m_CommonScene;
	delete m_CommonBack;
	delete m_CommonSystem;
	delete m_CommonSystemFront;
	delete m_CommonEffect;
	delete m_CommonEffectFront;
	delete m_CommonCpuPlayer;
	delete m_CommonBattleMenu;
	delete m_CommonUtilScreen;

	delete m_AITable[0];
	delete m_AITable[1];
}

void CModeBattle::Initialize()
{
	// タスクリスト作成
	m_CommonTitle	= new CCommonData( sizeof( CSysLogo2 ), 1 );
	m_CommonScene	= new CCommonData( sizeof( CBattleMenu ), 5 );
	m_CommonSystem	= new CCommonData( sizeof( CTimer ), 10 );
	m_CommonSystemFront	= new CCommonData( sizeof( CTimer ), 10 );
	m_CommonEffect	= new CCommonData( sizeof( CEffHit003 ), 1000 );
	m_CommonEffectFront= new CCommonData( sizeof( CEffHit003 ), 1000 );
	m_CommonBattleMenu = new CCommonData( sizeof( CBattleMenu ), 1 );
	m_CommonCpuPlayer = new CCommonData( sizeof( CNpcAIShana ), 4 );
	m_CommonUtilScreen = new CCommonData( sizeof( CUtlScreen ) , 1 );
	m_CommonBack	= new CCommonData( sizeof( CScnBackMisago ) , 2 );
	m_CommonChara[0] = new CCommonData( sizeof( CShanaProt ), 5 );
	m_CommonChara[1] = new CCommonData( sizeof( CShanaProt ), 5 );

	m_AITable[0]		= new CAITableShana();
	m_AITable[0]->SetUp();
	m_AITable[1]		= new CAITableShana();
	m_AITable[1]->SetUp();

	// リソース作成
	m_Resource.m_AnimationManager	= m_Game->m_AnimationManager;
	m_Resource.m_CommonChara[0]		= m_CommonChara[0];
	m_Resource.m_CommonChara[1]		= m_CommonChara[1];
	m_Resource.m_CommonEffect		= m_CommonEffect;
	m_Resource.m_CommonEffectFront	= m_CommonEffectFront;
	m_Resource.m_CommonMode			= m_Game->m_CommonMode;
	m_Resource.m_CommonUtilScreen	= m_CommonUtilScreen;
	m_Resource.m_CommonBack			= m_CommonBack;
	m_Resource.m_CommonSystem		= m_CommonSystem;
	m_Resource.m_CommonSystemFront	= m_CommonSystemFront;
	m_Resource.m_CommonScene		= m_CommonScene;
	m_Resource.m_CommonTitle		= m_CommonTitle;
	m_Resource.m_D3DDraw			= &m_Game->m_D3DDraw;
	m_Resource.m_DispObjGroup		= m_Game->m_DispObjGroup;
	m_Resource.m_Input				= m_Game->m_Input;
//	m_Resource.m_ConfigData			= m_Game->;
	m_Resource.m_MeshTestGroup		= m_Game->m_MeshTestGroup;
	m_Resource.m_TextureManager		= m_Game->m_TextureManager;

	// 最初のモード
	m_Mode = 0;
	m_NextMode = 1;
	m_SubMode = 0;

}

bool CModeBattle::Move()
{
	int i;

	CShanaProt*	player1;
	CShanaProt*	player2;

	m_Mode = m_NextMode ;
	CUtlScreen* screen;
	switch( m_Mode ){
		case 0:		// キャラクター作成などなど
			// キャラ変更するときはここと、ちょっとしたのSetupAnimationあたりを変える
//			new(m_CommonTitle) CSysLogo( this );
//			new(m_CommonSystem) CSpGauge( this, (CShanaProt *)m_CommonChara->m_ActiveTask->m_Next);
//			new(m_CommonSystem) CVitalGauge( this, (CShanaProt *)m_CommonChara->m_ActiveTask->m_Next);
//			new(m_CommonSystem) CTimer( this, (CShanaProt *)m_CommonChara->m_ActiveTask->m_Next);
			if (m_Player1 == 0){
				player1 = new(m_CommonChara[0]) CShanaProt( &m_Resource ,300,500,0 );
			}
			if (m_Player1 == 1){
				player1 = new(m_CommonChara[0]) CWilProt(&m_Resource, 300, 500, 0);
			}
			if (m_Player2 == 0){
				player2 = new(m_CommonChara[1]) CShanaProt(&m_Resource, 500, 500, 1, player1);
			}
			if (m_Player2 == 1){
				player2 = new(m_CommonChara[1]) CWilProt(&m_Resource, 500, 500, 1, player1);
			}
			m_Resource.m_Player[0] = player1;
			m_Resource.m_Player[1] = player2;
//AI
//			new(m_CommonCpuPlayer) CNpcAIShana( &m_Resource, this, m_AITable[0], player1 );
//			new(m_CommonCpuPlayer) CNpcAIShana( &m_Resource, this, m_AITable[1], player2 );

			//			new(m_CommonChara[0]) CUtilAttackArea( &m_Resource ,player1) ;
			new(m_CommonChara[1]) CUtilAttackArea( &m_Resource ,player2 );

			for( int i = ANIMEGROUP_NO_EFFECT ; i <= ANIME_NO_SYS_TIMER ; i++ ){
				m_Game->m_AnimationManager->SetupAnimation( m_Game->m_AnimationManager->GetAnimation( i ), i );
			}

			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_GUARD_CANCEL ), TEXTURE_NO_EFF_GUARD_CANCEL );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TIME ), TEXTURE_NO_SYS_TIME );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_STA_RURIDAN ), TEXTURE_NO_STA_RURIDAN );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_HP ), TEXTURE_NO_SYS_HP );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_SP ), TEXTURE_NO_SYS_SP );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_BATTLE_MENU ), TEXTURE_NO_SYS_BATTLE_MENU );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_HIT_ZAN1 ), TEXTURE_NO_EFF_HIT_ZAN1 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_COMBO ), TEXTURE_NO_SYS_COMBO );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA802_1 ), TEXTURE_NO_EFF_SHA802_1 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SYOUGEKI ), TEXTURE_NO_EFF_SYOUGEKI );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_BACK_WHITE ), TEXTURE_NO_SYS_BACK_WHITE );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA308 ), TEXTURE_NO_EFF_SHA308 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_HIT_ZAN2 ), TEXTURE_NO_EFF_HIT_ZAN2 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_GUARD ), TEXTURE_NO_EFF_GUARD );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_TAIKUUTI ), TEXTURE_NO_EFF_TAIKUUTI );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA303_1 ), TEXTURE_NO_EFF_SHA303_1 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA_AIRDASH_FRONT ), TEXTURE_NO_EFF_SHA_AIRDASH_FRONT );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA408 ), TEXTURE_NO_EFF_SHA408 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_JUMP_LANDING ), TEXTURE_NO_EFF_JUMP_LANDING );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA802_2 ), TEXTURE_NO_EFF_SHA802_2 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA303_2 ), TEXTURE_NO_EFF_SHA303_2 );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_HIT_UPPER ), TEXTURE_NO_EFF_HIT_UPPER );
			m_Game->m_TextureManager->SetupTextureGroup( m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_HIT_LINE ), TEXTURE_NO_EFF_HIT_LINE );

			if (m_Player1 == 0){
				m_Game->m_AnimationManager->SetupAnimation(m_Game->m_AnimationManager->GetAnimation(0), 0);//shana
				m_Game->m_TextureManager->SetupTextureGroup(m_Game->m_TextureManager->GetTextureGroup(0), 0, 0);//shana
			}
			if (m_Player1 == 1){
				m_Game->m_AnimationManager->SetupAnimation(m_Game->m_AnimationManager->GetAnimation(0), 1);//will
				m_Game->m_TextureManager->SetupTextureGroup(m_Game->m_TextureManager->GetTextureGroup(0), 1, 0);//will
			}

			if (m_Player2 == 0){
				m_Game->m_AnimationManager->SetupAnimation(m_Game->m_AnimationManager->GetAnimation(1), 0);//shana
				m_Game->m_TextureManager->SetupTextureGroup(m_Game->m_TextureManager->GetTextureGroup(1), 0, 0);//shana
			}
			if (m_Player2 == 1){
				m_Game->m_AnimationManager->SetupAnimation(m_Game->m_AnimationManager->GetAnimation(1), 1);//will
				m_Game->m_TextureManager->SetupTextureGroup(m_Game->m_TextureManager->GetTextureGroup(1), 1, 0);//will
			}
//			m_game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 0 );
//			m_game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

			new(m_CommonBack) CScnBack( &m_Resource );
			new(m_CommonSystem) CScnHpGauge( &m_Resource, player1, 1 ); 
			new(m_CommonSystem) CScnHpGauge( &m_Resource, player2, 2 ); 
			new(m_CommonSystem) CTimer( &m_Resource );
			new(m_CommonSystemFront) CSpGauge( &m_Resource, player1, 1 ); 
			new(m_CommonSystemFront) CSpGauge( &m_Resource, player2, 2 ); 
			screen = new(m_CommonUtilScreen) CUtlScreen( player1, player2 );
			m_Resource.SetUtilScreen( screen );
			new(m_CommonSystem) CScnComboInfo( &m_Resource, player1, 1 ); 
			new(m_CommonSystem) CScnComboInfo( &m_Resource, player2, 2 ); 
			new(m_CommonBattleMenu)	CBattleMenu( &m_Resource, this, &m_BattleMenuData, player1 );
//			new(m_CommonCpuPlayer)	CCpuPlayer( &m_Resource, this, &m_BattleMenuData );
//			new(m_CommonChara) CSysLogo2( this ); 
//			new(m_CommonTitle) CTestTask( this );
//			new(m_CommonEffectFront) CTestX( &m_Resource );
			SetMode( 4 );
			break;

		case 1:
			new(m_CommonTitle) CSysLogo2( &m_Resource );
//			SBArr[ENUM_SE_BATTLE_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
//			SBArr[ENUM_SE_BATTLE_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
			m_Flame = 0;
			SetMode( 3 );
			break;

		case 2:
			m_Game->SetMode( 3 );
			SetMode( 0 );
			break;
	}


	// MOVEメイン
	CElement*	cEle;
	CElement*	cEleNext;

	if( m_Mode == 3 ){
		m_Flame++;
		if( m_Flame * 2 > 255 ){
			SetMode( 2 );
		}
	}

	cEle = m_CommonScene->m_ActiveTask->m_Next;
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

	if( m_SubMode == 0 ){
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

	return TRUE;
}

void CModeBattle::SetMode( int mode )
{
	m_NextMode = mode ;
}

bool CModeBattle::Action()
{
	CElement*	cEle;
	CElement*	cEleNext;

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

	return TRUE;

}

bool CModeBattle::ActionFinalize()
{
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

	return TRUE;

}

bool CModeBattle::Interfere( )
{
	// MOVEメイン
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

	return TRUE;
}

bool CModeBattle::InterfereFinalize( )
{
	// MOVEメイン
	CElement*	cEle;
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

	return TRUE;
}

bool CModeBattle::Draw( CD3DDraw* draw )
{
	CElement*	cEle;
	CElement*	cEleNext;

	// 戦闘中
	// スクリーン１回目（最初）
	MacroDraw( draw, m_CommonUtilScreen );
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

	// title
	MacroDraw( draw, m_CommonTitle );

	return TRUE;
}

bool CModeBattle::DrawFinalize()
{
	// MOVEメイン
	CElement*	cEle;
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
	return TRUE;
}

bool CModeBattle::Event()
{
	CElement*	cEle;
	CElement*	cEleNext;

	cEle = m_CommonSystem->m_ActiveTask->m_Next;
	while( cEle->m_Next != m_CommonSystem->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Event( );
		cEle = cEleNext ;
	}
	return TRUE;
}

/*bool CModeBattle::Action()
{
	return TRUE;
}
*/

void CModeBattle::BattlePause()
{
	m_SubMode = SUB_MODE_MENU;
}

void CModeBattle::BattleResume()
{
	m_SubMode = SUB_MODE_FIGHT;
}

// 楽チンマクロ集
void CModeBattle::MacroAction( CCommonData *common)
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

void CModeBattle::MacroActionFinalize( CCommonData *common)
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

void CModeBattle::MacroDraw( CD3DDraw *draw, CCommonData *common)
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

void CModeBattle::MacroDraw( CCommonData *common)
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

void CModeBattle::MacroDrawFinalize( CCommonData *common)
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

void CModeBattle::MacroEvent( CCommonData *common)
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

void CModeBattle::MacroInterfere( CCommonData *common)
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

void CModeBattle::MacroInterfereFinalize( CCommonData *common)
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

void CModeBattle::MacroMove( CCommonData *common)
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
