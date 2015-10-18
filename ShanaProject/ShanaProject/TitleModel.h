#pragma once

// 前方参照
class CResBattle;
class CShanaProt;
class CInput;

#include "CLIB_Sprite.h"

class CTitleModel : public CSprite{
protected:
	int	m_Blend;
	int m_BaseX;
	int m_BaseY;
	int m_BaseZ;
	int m_ObjX[10];
	int m_ObjY[10];
	int m_ObjZ[10];
	float m_ObjRange[10];
	int m_ObjMeshNo[10];
	float m_ObjRotX[10];
	float m_ObjRotY[10];
	float m_ObjRotZ[10];
	float m_ObjRotBeginY[10];
	float m_ObjRotXVal[10];
	float m_ObjRotYVal[10];
	float m_ObjRotZVal[10];
	float m_ObjRotBeginYVal[10];
	int rotx;
	int roty;
	CInput	*m_Input;

public:
	CTitleModel( CResBattle *game );
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
	virtual ~CTitleModel();
	
};
