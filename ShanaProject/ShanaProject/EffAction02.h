#pragma once

// 前方参照
class CResBattle;
class CShanaProt;

#include "CLIB_Sprite.h"

class CEffAction02 : public CSprite{
protected:
	int	m_Blend;
	int m_HistoryX[10];
	int m_HistoryY[10];
	int m_FlagGround;
	int m_Life;

	float m_AirVector[2];
	float m_AirBase[2]	;
	float m_AirGravity	;
	int m_AirTime		;

	void StartAir( float vec_x, float vec_y, int op1, float gravity );
	void DoAir();
	void EndAir();

public:
	CEffAction02( CResBattle *game, CShanaProt *target );

	/************/
	/* オーバーライト群
	/************/
//	virtual bool Event();							// ユーザー等からの入力（イベント）受付
	virtual bool Move();							// 移動処理（ジャンプ降下等）
	virtual bool InterfereFinalize();				// 最終結果　ヒット時の状態変化など、最後の処理を行う
//	virtual bool Action();							// 入力（イベント）内容からの動作実施
//	virtual bool Result();							// 判定動作　ヒット確認など
	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
	virtual bool DrawFinalize( );					// 描画処理メイン　後処理
//	virtual bool Draw();							// 描画処理

protected:
	virtual ~CEffAction02();
	
};
