#pragma once

// 前方参照
class CResBattle;
class CShanaProt;

#include "CLIB_Sprite.h"

enum ENUM_COMBO_INFO_STATE{
	ENUM_COMBO_INFO_STATE_IDLE	,
	ENUM_COMBO_INFO_STATE_COMBO	,
	ENUM_COMBO_INFO_STATE_END
};

class CScnComboInfo: public CSprite{
protected:
	int	m_Blend;
	CShanaProt*		m_Target ;
	int	m_Player;
	int m_Combo;

public:
	CScnComboInfo( CResBattle *game , CShanaProt *target, int player );

	/************/
	/* オーバーライト群
	/************/
//	virtual bool Event();							// ユーザー等からの入力（イベント）受付
//	virtual bool Move();							// 移動処理（ジャンプ降下等）
//	virtual bool Action();							// 入力（イベント）内容からの動作実施
//	virtual bool ActionFinalize();					// 入力（イベント）内容からの動作実施
//	virtual bool Interfere();						// 判定動作　ヒット確認判定など
	virtual bool InterfereFinalize();				// 最終結果　ヒット時の状態変化など、最後の処理を行う
	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
//	virtual bool Draw();							// 描画処理

protected:
	virtual ~CScnComboInfo();
	
};
