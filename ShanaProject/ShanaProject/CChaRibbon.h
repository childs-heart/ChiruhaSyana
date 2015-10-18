#pragma once

// 前方参照
class CResBattle;
class CShanaProt;
class CCommonData;

#include "CLIB_Sprite.h"

class CChaRibbon : public CSprite{
protected:
	int	m_Blend;
	int m_Hitted;
	CResBattle*		m_ResBattle;
	CShanaProt*		m_Target;
	CCommonData*	m_Common;

	// 攻撃ヒット
	void HitAttack();

public:
	CChaRibbon( CResBattle *game, CShanaProt *target, CCommonData *common );

	/************/
	/* オーバーライト群
	/************/
//	virtual bool Event();							// ユーザー等からの入力（イベント）受付
	virtual bool Move();							// 移動処理（ジャンプ降下等）
//	virtual bool Action();							// 入力（イベント）内容からの動作実施
//	virtual bool Result();							// 判定動作　ヒット確認など
	virtual bool Interfere();						// 判定動作　ヒット確認判定など
//	virtual bool InterfereFinalize();				// 最終結果　ヒット時の状態変化など、最後の処理を行う
	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
//	virtual bool Draw();							// 描画処理

protected:
	virtual ~CChaRibbon();
	
};
