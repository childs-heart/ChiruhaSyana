//-----------------------------------------------------------------------------------------
// TITLE:シャナプロジェクト（仮	
// Programmer:T.Ueki T.shimizu							
//															
//-----------------------------------------------------------------------------------------
#include <objbase.h>
#include <windows.h>
#include <stdio.h>
#include "ShanaMain.h"		// メインヘッダファイル
#include "d3dmain.h"
#include "Game.h"
#include "DsoundMain.h"
#include "FileSave.h"
#include "FileSaveCommon.h"

HWND			win_hwnd;							// ウィンドウのハンドル
MSG				msg;
HINSTANCE		hInst;								// インスタンス
HINSTANCE		g_hinst;
int end_sw = 0;											// メインループ終了管理変数
int FullS = 0;										// 0:ウィンドウモード 1:フルスクリーンモード

CGame		*Game;

void ShowInfoDialog( HINSTANCE , HWND );

//-----------------------------------------------------------------------------------------
// プロトタイプ宣言部分
//-----------------------------------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,char *CmdLine,int CmdShow);
LRESULT CALLBACK win_proc(HWND win_hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

//-----------------------------------------------------------------------------------------
// システムメイン - 毎フレーム呼ばれる関数です
//-----------------------------------------------------------------------------------------
void sys_main()
{
	// メインルーチンの最初
	Game->GameMain();
}

//-----------------------------------------------------------------------------------------
// WinMain - WINDOWSアプリの最初に実行される場所
//-----------------------------------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,char *CmdLine,int CmdShow)
{
	HRESULT hr;

	WNDCLASS winc;

//	hr = CoInitialize(NULL);
//    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	ZeroMemory(&winc,sizeof(WNDCLASS));
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.hCursor = LoadCursor(NULL,IDC_ARROW);
	winc.hInstance = hInst;
	winc.lpfnWndProc = win_proc;
	winc.lpszClassName = "DRBMAIN";
	RegisterClass(&winc);

	char file_path[1024];
	DWORD len;
	//起動ディレクトリ名、ファイル名取得
	len = GetModuleFileName(NULL,file_path,1024);
	if(len == 0)
		return	false;

	//パスの分解
	int last=0;
	int i=0;
	while( (i<1024) && (file_path[i]!=NULL) ){
		if( file_path[i] == '\\' )
			last = i;
		i++;
	}
	file_path[last] = NULL;
//	SetCurrentDirectory( file_path );

//	StConfigData keyconfig[2];
	// 設定ファイル
	CFileSave	fileSave;
//	fileSave.Open("D:\\child_heart\\program\\ShanaProject\\ShanaProject\\ConfigTool.ini");
	sprintf( file_path, "%s\\ConfigTool.ini\0", file_path );
	fileSave.Open(file_path);
	fileSave.ReadMember(FILE_SAVE_SECTION_DISPLAY,FILE_SAVE_DISPLAY_HEADER_VIEW,(DWORD*)&FullS);
/*	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_UP, &keyconfig[0].m_Dir[0] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_DOWN, &keyconfig[0].m_Dir[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_LEFT, &keyconfig[0].m_Dir[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_RIGHT, &keyconfig[0].m_Dir[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_UP, &keyconfig[1].m_Dir[0] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_DOWN, &keyconfig[1].m_Dir[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_LEFT, &keyconfig[1].m_Dir[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_RIGHT, &keyconfig[1].m_Dir[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_A, &keyconfig[0].m_Button[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_B, &keyconfig[0].m_Button[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_C, &keyconfig[0].m_Button[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_D, &keyconfig[0].m_Button[4] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_START, &keyconfig[0].m_Button[5] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_AB, &keyconfig[0].m_Button[6] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_CD, &keyconfig[0].m_Button[7] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_A, &keyconfig[1].m_Button[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_B, &keyconfig[1].m_Button[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_C, &keyconfig[1].m_Button[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_D, &keyconfig[1].m_Button[4] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_START, &keyconfig[1].m_Button[5] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_AB, &keyconfig[1].m_Button[6] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_CD, &keyconfig[1].m_Button[7] );
*/
	if( FullS == 0 ){
		hr = MessageBox(NULL,"フルスクリーンモードで起動しますか？\n起動する場合は「はい」を、ウィンドウモードで起動する場合は「いいえ」を選択してください。","画面モードの選択",MB_YESNO | MB_ICONQUESTION);
//		hr = 0;//MessageBox(NULL,"フルスクリーンモードで起動しますか？\n起動する場合は「はい」を、ウィンドウモードで起動する場合は「いいえ」を選択してください。","画面モードの選択",MB_YESNO | MB_ICONQUESTION);
		
		if(hr == IDYES)FullS=2;			//「はい」選択時フルスクリーン判別変数に1を代入
		else FullS=1;
	}
	int width,height;

//	FullS=1;
	// ウインドウの大きさを計算
	FullS--;
	if (FullS)
	{
		// フルスクリーン時はそのままで OK
		width = W_WIDTH;
		height = W_HEIGHT;
	}
	else
	{
		// ウインドウ時はウインドウの外枠のサイズを考慮する
		width = W_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2;
		height = W_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
	}

	// ウインドウを作成
	win_hwnd = CreateWindow("DRBMAIN",
							CAPTION,
							WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							width,
							height,
							NULL,
							NULL,
							hInst,
							NULL);

	//DirectX初期化
	hr = D3Dinit( win_hwnd, W_WIDTH, W_HEIGHT, FullS);
	if FAILED(hr)
	{
		return false;			//初期化出来なかったら終了
	}

	// DirectSound初期化
	// 全てのSE情報をバッファに展開
	hr = Dsoundinit( win_hwnd );
	if FAILED(hr)
	{
		return false;			//初期化出来なかったら終了
	}

	g_hinst=hInst;

	Game = new CGame();
	Game->m_D3DDraw.SetDevice( lpD3Ddev );
	Game->m_D3DDraw.SetCenter( 400,300 );

	ShowWindow( win_hwnd, CmdShow );

	// インフォウィンドウ表示
	if(!FullS){
//		ShowInfoDialog( g_hinst , win_hwnd );
	}

	//メインループで回せ回せ
	//end_swが1の時に終わる	
	while (!end_sw)
	{
		// メッセージが来ているか?
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			// メッセージの処理
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		sys_main();
/*		else
		{
			sys_main();
		}
*/
	}

	delete Game;
	D3D_END();
//    CoUninitialize();
	//終了する
	return false;
}
//-----------------------------------------------------------------------------------------
//	メインウィンドウ(NAME:DRBMAIN)プロシージャ
//-----------------------------------------------------------------------------------------
LRESULT CALLBACK win_proc(HWND win_hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{     
	
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		end_sw=1;
		return false;
	}
	return DefWindowProc(win_hwnd,msg,wParam,lParam);

}
