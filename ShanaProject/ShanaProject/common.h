#pragma once

// タブ内ウインドウサイズ 
#define SETTTING_WND_WIDTH	338
#define SETTTING_WND_HEIGHT	338

// ini ファイルロード時のデフォルト 
#define PRIVATE_PROFILE_DEFAULT_STRING	TEXT("ERROR")

////////////////////////////////////////////////////////////////////
// メッセージID 
#define WM_SET_CONFIG	WM_USER + 0x0001
#define WM_TIME_PROC	WM_USER + 0x0002

////////////////////////////////////////////////////////////////////
// コントロールID / ウインドウID  

// CConfigToolDlg 
enum
{
	ID_WND_VIEW_SETTING = 0x1001,
	ID_WND_KEY_CONFIG_1P,
	ID_WND_KEY_CONFIG_2P,
};

// CViewSettingWnd 
enum
{
	ID_GRP_VIEW_DISPLAY = 0x2001,
	ID_RBT_VIEW_WINDOW,
	ID_RBT_VIEW_FULL,
};

////////////////////////////////////////////////////////////////////
// 設定項目ID 

enum
{
	SETTING_ITEM_VIEW = 0x7001,			// 画面表示 
	SETTING_ITEM_KEY_UP,				// 上 
	SETTING_ITEM_KEY_DOWN,				// 下 
	SETTING_ITEM_KEY_LEFT,				// 左 
	SETTING_ITEM_KEY_RIGHT,				// 右 
	SETTING_ITEM_KEY_FEEBLE,			// 弱 
	SETTING_ITEM_KEY_MIDDLE,			// 中 
	SETTING_ITEM_KEY_STRONG,			// 強 
	SETTING_ITEM_KEY_SPECIAL,			// 特殊 
	SETTING_ITEM_KEY_FEEBLE_MIDDLE,		// 弱 + 中 
	SETTING_ITEM_KEY_STRONG_SPECIAL,	// 強 + 特殊 
	SETTING_ITEM_KEY_START,				// START 
};

// キーコンフィグ プレイヤーID 
#define PLAYER_ID_1P	0x0100
#define PLAYER_ID_2P	0x0200

////////////////////////////////////////////////////////////////////
// 設定値 

// 画面表示  
enum
{
	SETTING_VALUE_VIEW_WINDOW = 0x0001,	// ウィンドウ 
	SETTING_VALUE_VIEW_FULL,			// フルスクリーン 
};

////////////////////////////////////////////////////////////////////
