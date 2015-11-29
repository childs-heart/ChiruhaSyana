#pragma once

// �^�u���E�C���h�E�T�C�Y 
#define SETTTING_WND_WIDTH	338
#define SETTTING_WND_HEIGHT	338

// ini �t�@�C�����[�h���̃f�t�H���g 
#define PRIVATE_PROFILE_DEFAULT_STRING	TEXT("ERROR")

////////////////////////////////////////////////////////////////////
// ���b�Z�[�WID 
#define WM_SET_CONFIG	WM_USER + 0x0001
#define WM_TIME_PROC	WM_USER + 0x0002

////////////////////////////////////////////////////////////////////
// �R���g���[��ID / �E�C���h�EID  

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
// �ݒ荀��ID 

enum
{
	SETTING_ITEM_VIEW = 0x7001,			// ��ʕ\�� 
	SETTING_ITEM_KEY_UP,				// �� 
	SETTING_ITEM_KEY_DOWN,				// �� 
	SETTING_ITEM_KEY_LEFT,				// �� 
	SETTING_ITEM_KEY_RIGHT,				// �E 
	SETTING_ITEM_KEY_FEEBLE,			// �� 
	SETTING_ITEM_KEY_MIDDLE,			// �� 
	SETTING_ITEM_KEY_STRONG,			// �� 
	SETTING_ITEM_KEY_SPECIAL,			// ���� 
	SETTING_ITEM_KEY_FEEBLE_MIDDLE,		// �� + �� 
	SETTING_ITEM_KEY_STRONG_SPECIAL,	// �� + ���� 
	SETTING_ITEM_KEY_START,				// START 
};

// �L�[�R���t�B�O �v���C���[ID 
#define PLAYER_ID_1P	0x0100
#define PLAYER_ID_2P	0x0200

////////////////////////////////////////////////////////////////////
// �ݒ�l 

// ��ʕ\��  
enum
{
	SETTING_VALUE_VIEW_WINDOW = 0x0001,	// �E�B���h�E 
	SETTING_VALUE_VIEW_FULL,			// �t���X�N���[�� 
};

////////////////////////////////////////////////////////////////////
