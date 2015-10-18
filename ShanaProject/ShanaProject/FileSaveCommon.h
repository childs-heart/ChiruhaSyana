#pragma once

///////////////////////////////////////////////////////
// セクション 
//#define FILE_SAVE_SECTION_DISPLAY	_T("DISPLAY")	// 表示設定 
//#define FILE_SAVE_SECTION_1PKEY		_T("1P")		// 1P キーコンフィグ 
//#define FILE_SAVE_SECTION_2PKEY		_T("2P")		// 2P キーコンフィグ 
#define FILE_SAVE_SECTION_DISPLAY	("DISPLAY")	// 表示設定 
#define FILE_SAVE_SECTION_1PKEY		("1P")		// 1P キーコンフィグ 
#define FILE_SAVE_SECTION_2PKEY		("2P")		// 2P キーコンフィグ 

///////////////////////////////////////////////////////
// メンバーヘッダー 

//////////////////////////////
// 表示設定 
// 0x0000 = ウインドウ 
// 0x0001 = フルスクリーン 
//#define FILE_SAVE_DISPLAY_HEADER_VIEW	_T("VIEW")
#define FILE_SAVE_DISPLAY_HEADER_VIEW	("VIEW")

//////////////////////////////
// キーコンフィグ 
// 値のフォーマット = 0xABCC 
// A = 十字キー:0 / その他ボタン:1 
// B = パッドNo 
// CC = キーの値 
/*
#define FILE_SAVE_KEY_HEADER_UP		_T("UP")
#define FILE_SAVE_KEY_HEADER_DOWN	_T("DOWN")
#define FILE_SAVE_KEY_HEADER_LEFT	_T("LEFT")
#define FILE_SAVE_KEY_HEADER_RIGHT	_T("RIGHT")
#define FILE_SAVE_KEY_HEADER_A		_T("A")
#define FILE_SAVE_KEY_HEADER_B		_T("B")
#define FILE_SAVE_KEY_HEADER_C		_T("C")
#define FILE_SAVE_KEY_HEADER_D		_T("D")
#define FILE_SAVE_KEY_HEADER_AB		_T("AB")
#define FILE_SAVE_KEY_HEADER_CD		_T("CD")
#define FILE_SAVE_KEY_HEADER_START	_T("START")
*/

#define FILE_SAVE_KEY_HEADER_UP		("UP")
#define FILE_SAVE_KEY_HEADER_DOWN	("DOWN")
#define FILE_SAVE_KEY_HEADER_LEFT	("LEFT")
#define FILE_SAVE_KEY_HEADER_RIGHT	("RIGHT")
#define FILE_SAVE_KEY_HEADER_A		("A")
#define FILE_SAVE_KEY_HEADER_B		("B")
#define FILE_SAVE_KEY_HEADER_C		("C")
#define FILE_SAVE_KEY_HEADER_D		("D")
#define FILE_SAVE_KEY_HEADER_AB		("AB")
#define FILE_SAVE_KEY_HEADER_CD		("CD")
#define FILE_SAVE_KEY_HEADER_START	("START")

///////////////////////////////////////////////////////