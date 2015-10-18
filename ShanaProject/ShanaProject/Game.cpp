#include <stdio.h>
#include "Game.h"
#include "ShanaProt.h"
#include "d3dmain.h"
#include "ShanaMain.h"
#include "TitleMenu.h"
#include "ModeBattle.h"
#include "ModeTitle.h"
#include "ModeCharaSelect.h"
#include "SysLogo2.h"
#include "FileSave.h"
#include "FileSaveCommon.h"
#include "CLIB_FPS.h"
//#include "testtask.h"

CGame::CGame()
{
	initialize();
}

CGame::~CGame()
{
	delete m_CommonMode;
	delete m_DispObjGroup;
//	delete m_TexTitleGroup;
//	delete m_TexCharaGroup;
//	delete m_TexSystemGroup;
	delete m_TextureManager;
	delete m_AnimationManager;
	delete m_MeshTestGroup;
	delete m_Input;
}

void CGame::initialize()
{
	m_DispObjGroup	= new CDispObjGroup( MAX_NUM_DISPOBJ );
	m_TextureManager = new CTextureGroupManager( lpD3Ddev );
	m_AnimationManager = new CAnimationManager( );
	m_CommonMode	= new CCommonData( sizeof( CModeBattle ), 2 );
	m_MeshTestGroup	= new CXFileGroup( 10, lpD3Ddev );
	m_Input			= new CInput( g_hinst, win_hwnd, 2 );
	m_ModeTitle		= NULL;
	m_ModeCharaSel	= NULL;

	char file_path[1024];
	file_path[0]=0;
	DWORD len;
	//起動ディレクトリ名、ファイル名取得
	len = GetModuleFileName(NULL,file_path,1024);

	//パスの分解
	int last=0;
	int i=0;
	while( (i<1024) && (file_path[i]!=NULL) ){
		if( file_path[i] == '\\' )
			last = i;
		i++;
	}
	file_path[last] = NULL;
	unsigned long keyconfig[20];
	memset(keyconfig, 0 , sizeof(long)*20 );
	// 設定ファイル読み込み
	// 設定ファイル
	CFileSave	fileSave;
	sprintf( file_path, "%s\\ConfigTool.ini\0", file_path );
	fileSave.Open(file_path);
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_UP, &keyconfig[0] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_DOWN, &keyconfig[1] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_LEFT, &keyconfig[2] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_RIGHT, &keyconfig[3] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_A, &keyconfig[4] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_B, &keyconfig[5] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_C, &keyconfig[6] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_D, &keyconfig[7] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_START, &keyconfig[8] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_AB, &keyconfig[9] );
	fileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_CD, &keyconfig[10] );
	if( keyconfig[0] == 0 ) keyconfig[0] = 0x0 * 0 + 0x1;
	if( keyconfig[1] == 0 ) keyconfig[1] = 0x0 * 0 + 0x2;
	if( keyconfig[2] == 0 ) keyconfig[2] = 0x0 * 0 + 0x8;
	if( keyconfig[3] == 0 ) keyconfig[3] = 0x0 * 0 + 0x4;
	for( int i = 0 ; i < 7 ; i++ ){
		if( keyconfig[i+4] == 0 ) keyconfig[i+4] = 0x0 + i ;
	}
	m_Input->SetConfigData( 0, keyconfig );

	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_UP, &keyconfig[0] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_DOWN, &keyconfig[1] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_LEFT, &keyconfig[2] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_RIGHT, &keyconfig[3] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_A, &keyconfig[4] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_B, &keyconfig[5] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_C, &keyconfig[6] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_D, &keyconfig[7] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_START, &keyconfig[8] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_AB, &keyconfig[9] );
	fileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_CD, &keyconfig[10] );
	if( keyconfig[0] == 0 ) keyconfig[0] = 0x100 * 1 + 0x1;
	if( keyconfig[1] == 0 ) keyconfig[1] = 0x100 * 1 + 0x2;
	if( keyconfig[2] == 0 ) keyconfig[2] = 0x100 * 1 + 0x8;
	if( keyconfig[3] == 0 ) keyconfig[3] = 0x100 * 1 + 0x4;
	for( int i = 0 ; i < 7 ; i++ ){
		if( keyconfig[i+4] == 0 ) keyconfig[i+4] = 0x100 + i ;
	}
	m_Input->SetConfigData( 1, keyconfig );

	m_NextMode		= 5 ;
	m_Mode			= 5 ;

}

void CGame::SetMode( int mode )
{
	m_NextMode = mode ;
}

void CGame::GameMain()
{

	int i;

	CShanaProt*	player1;
	CShanaProt*	player2;

	m_Mode = m_NextMode ;
	switch( m_Mode ){
		case 0:
			// タイトルのスタート
			m_ModeTitle = new(m_CommonMode) CModeTitle( this );
			SetMode( 2 );
			break;

		case 1:
			// バトルモードスタート
			new(m_CommonMode) CModeBattle( this, m_ModeCharaSel->GetDecideChara( 0 ), m_ModeCharaSel->GetDecideChara( 1 ));
			SetMode( 2 );
			break;

		case 3:
			// タイトルモードの削除	
			if( m_ModeTitle != NULL ){
				delete m_ModeTitle;
				m_ModeTitle = NULL;
			}
			if( m_ModeCharaSel != NULL ){
				delete m_ModeCharaSel;
				m_ModeCharaSel = NULL;
			}
			SetMode( 2 );
			break;

		case 4:
			// 
			new(m_CommonMode) CModeBattle( this );
			SetMode( 2 );
			break;

		case 5:
			// キャラセレクトのスタート
			m_ModeCharaSel = new(m_CommonMode) CModeCharaSelect( this );
			if( m_ModeTitle != NULL ){
				delete m_ModeTitle;
				m_ModeTitle = NULL;
			}
			SetMode( 2 );
			break;

	}

	m_Input->UpDateState();

	CElement*	cEle;
	CElement*	cEleNext;

	// MOVE Main
	cEle = m_CommonMode->m_ActiveTask->m_Next;
	while( cEle->m_Next != m_CommonMode->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		if( cEle->Move() == FALSE ){
			delete cEle;
		}
		else{
			cEle->Action();
			cEle->ActionFinalize();
			cEle->Interfere();
			cEle->InterfereFinalize();
		}
		cEle = cEleNext ;
	}

	// Begin the scene.
	LPDIRECT3DDEVICE9 d3ddevice;
	d3ddevice = m_D3DDraw.GetDevice();
	d3ddevice->BeginScene();
	// 画面クリア
	d3ddevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0);

/*	for( i=0 ; i<4 ; i++ ){
		if( m_DispObjGroup->m_CDisp[i].m_Visible == TRUE ){
			m_D3DDraw.Draw( &m_DispObjGroup->m_CDisp[i] );
		}
	}
*/
	cEle = m_CommonMode->m_ActiveTask->m_Next;
	while( cEle->m_Next != m_CommonMode->m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		cEle->Draw( &m_D3DDraw );
		cEle->DrawFinalize();
		cEle = cEleNext ;
	}

	d3ddevice->EndScene();

//	CFps::GetCFps()->WaitNextUpdate();

	// 画面に表示（バッファスワップ）
	d3ddevice->Present( NULL, NULL, NULL, NULL );

}

