#pragma once

#include <windows.h>
#include "CLIB_Action.h"

/*typedef struct{
	DWORD	m_TextureNo;
	DWORD	m_Left , m_Top , m_Right , m_Bottom ;
	long	m_BaseX, m_BaseY;
	DWORD	m_Flame;
	DWORD	m_Flag;
}ST_IMAGE_DATA;
*/

//==============================================================
// アニメーション詳細クラス
// アニメーションパターンとか知ってる
// ※アクション⇒「歩き」「屈み」単位
// ※アニメーション⇒アクションの集合体　キャラ単位
//==============================================================
class CAnimeSpec{
public:
	// アニメ登録
	void SetAnimeData( DWORD index, DWORD tex_no, DWORD flame, DWORD baseX, DWORD baseY );
//	void SetAnimeData( DWORD index, DWORD tex_no, DWORD flame, DWORD left, DWORD top, DWORD right, DWORD bottom, DWORD baseX, DWORD baseY );

	// コンストラクタ＆デストラクタ
	CAnimeSpec( );
	CAnimeSpec( int num );
	virtual ~CAnimeSpec();

	// アニメーションデータ読み込み
	void LoadAnimeData( );
	
	// 20070901　リファクタリング
	CAction*		GetActionData( DWORD action_no );
//	StMotionData*	GetMotionData( DWORD motion_no );

	void LoadActionData();
	void CreateAction( DWORD action_no, DWORD num_motion );

	CAction*	m_Action;		// アクションデータ
	DWORD		m_NumAction;	// アクションの保持数
};

//==============================================================
// アニメーションクラス
// 各オブジェクト毎が保持するデータが入ってる
//==============================================================
class CAnime{
public:
	// コンストラクタ＆デストラクタ
	CAnime();
	virtual ~CAnime();

	CAnimeSpec*		m_AnimeSpec;	// アニメーションデータ

	CAction*		GetActionData( DWORD action_no );
	StMotionData*	GetMotionData( DWORD motion_no );
	CAction*		GetCurrentAction();
	DWORD			GetCurrentImageNo();
	StMotionData*	GetCurrentMotion();
	int				GetCurrentActionNo();

	void StepFlame( int num );
	void ChangeAction( DWORD action_no , DWORD motion_no = 0 );
	int	 IsCollisioned( CAnime* target_anime );
	void AttackHit();
	int	 IsAttackEnabled();
	int	 IsCollisionJudge();

	int m_CurrentActionNo;		// 現在のアクション番号
	int m_CurrentMotionNo;		// 現在のアクションで表示中のモーション番号
	int m_ActionFlame;			// m_CurrentMotionNoのモーションを表示したフレーム数

	// ↓アニメーションフラグ群
	// 判定有効・無効
	int	m_AttackJudgeEnable;
	int	m_CollisionJudgeEnable;

};

//==============================================================
// アニメーションクラスグループ
//==============================================================
class CAnimeGroup{
};
