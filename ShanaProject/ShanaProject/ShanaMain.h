//-----------------------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------------------
// 重複インクルードの回避
#ifndef __SHANA_MAIN
#define __SHANA_MAIN 

#define	CAPTION			"シャナプロジェクト（仮）"

//ウィンドウ関係

#define	W_WIDTH				800						// ウィンドウの幅
#define	W_HEIGHT			600						// ウィンドウの高さ

//#define ID_TIMER			32767					// タイマー
#define PI					3.141592f				// 円周率
#define RAD					180/PI					// 1ラジアン

extern HWND				win_hwnd;							// ウィンドウのハンドル
extern HINSTANCE		hInst;								// インスタンス
extern HINSTANCE		g_hinst;								// インスタンス

#endif