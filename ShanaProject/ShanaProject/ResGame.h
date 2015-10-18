#pragma once

// 前方参照
class CD3DDraw;
class CDispObjGroup;
class CTextureGroupManager;
class CAnimationManager;
class CXFileGroup;
class CCommonData;
class CInput;

class CResGame{
public:
	// 描画クラス
	CD3DDraw		*m_D3DDraw;
	// 描画オブジェクトグループ
	CDispObjGroup	*m_DispObjGroup;
	// テクスチャーグループ
	CTextureGroupManager	*m_TextureManager;
	// アニメーションクラス
	CAnimationManager	*m_AnimationManager;
	// メッシュファイルグループ
	CXFileGroup		*m_MeshTestGroup;
	// Commonクラス
	CCommonData		*m_CommonMode;
	// ダイレクトインプットクラス
	CInput			*m_Input;
};
