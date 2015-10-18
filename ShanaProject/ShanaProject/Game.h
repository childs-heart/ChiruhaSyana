#pragma once

#include "CLIB_Util.h"
#include "CLIB_Element.h"
#include "CLIB_DispObj.h"
#include "CLIB_Texture.h"
#include "CLIB_D3DDraw3.h"
#include "CLIB_Input.h"
#include "CLIB_Anime.h"
//#include "CLIB_Movie.h"

#define	MAX_NUM_DISPOBJ		11000
#define	MAX_NUM_TEX_TITLE	10
#define	MAX_NUM_TEX_CHARA	100
#define	MAX_NUM_TEX_SYSTEM	100

class CModeTitle;
class CModeCharaSelect;

class CGame{
private:
	int	m_Mode;
	int m_NextMode;
	CModeTitle *m_ModeTitle;
	CModeCharaSelect *m_ModeCharaSel;

	void initialize();

public:
	CGame();
	~CGame();

	void GameMain();
	void SetMode( int mode );

	// 描画クラス
	CD3DDraw3		m_D3DDraw;
	// 描画オブジェクトグループ
	CDispObjGroup	*m_DispObjGroup;
	// テクスチャーグループ
	CTextureGroupManager	*m_TextureManager;
	// メッシュファイルグループ
	CXFileGroup		*m_MeshTestGroup;
	// Commonクラス
	CCommonData		*m_CommonMode;
	// アニメーションクラス
	CAnimationManager	*m_AnimationManager;
	// ダイレクトインプットクラス
	CInput			*m_Input;

};

//extern CGame *Game;
