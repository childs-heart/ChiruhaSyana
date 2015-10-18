#pragma once

// 前方参照
class CResBattle;
class CShanaProt;
class CInput;

#include "CLIB_Sprite.h"

class CTestX : public CSprite{
protected:
	int	m_Blend;
	int rotx;
	int roty;
	CInput	*m_Input;

public:
	CTestX( CResBattle *game );
	float m_fX;
	float m_fY;
	float m_fZ;

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
	virtual ~CTestX();
	
};
