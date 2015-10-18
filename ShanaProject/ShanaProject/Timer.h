#ifndef	__TIMER
#define	__TIMER

// 前方参照
class CResBattle;

#include "CLIB_Sprite.h"

class CTimer : public CSprite{
protected:
	int	m_Blend;
	float m_RotZ[2];		// 回転角度

	int m_TimerEnable;
	int m_TimeCount;

	DWORD m_StartTickCount;

public:
	CTimer( CResBattle *game );

	void SetTime( int count, int enabled );
	void Pause();
	void Resume();

	/************/
	/* オーバーライト群
	/************/
//	virtual bool Event();							// ユーザー等からの入力（イベント）受付
	virtual bool Move();							// 移動処理（ジャンプ降下等）
//	virtual bool Action();							// 入力（イベント）内容からの動作実施
//	virtual bool Result();							// 判定動作　ヒット確認など
	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
//	virtual bool Draw();							// 描画処理

protected:
	virtual ~CTimer();
	
};

#endif
