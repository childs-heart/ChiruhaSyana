#pragma once

// 前方参照
class CResGame;
class CDispObj;
class CDispObjGroup;
class CTextureGroup;

#include "CLIB_Anime.h"
#include "CLIB_Element.h"

typedef struct{
	int m_BaseX ;
	int m_BaseY ;
}ST_SPRITE_ANIME;

class CSprite : public CElement{
protected:
	CResGame		*m_Game;		// 
	CDispObj		*m_DispObj;		
	CDispObjGroup	*m_DispObjGroup;
	CTextureGroup	*m_Tex;			// テクスチャークラス
	CAnime			m_Anime;		// アニメーションクラス
	int				m_Dir;

	int m_X;				// X軸
	int m_Y;				// Y軸
	int m_State;			// 状態（ワーク変数として使用。用途は自由）
	int	m_Flame;			// フレーム数（ワーク用変数として使用。用途は自由）

	int m_AnimeNo;			// アニメNO
	int m_AnimeFlame;		// m_AnimeNoのアニメを表示したフレーム数
	int m_AnimeImage;		// m_AnimeNoで使うテクスチャー番号

public:
	CSprite( CResGame *game );
	virtual ~CSprite();

	/************/
	/* オーバーライト群
	/************/
	virtual bool Event();							// ユーザー等からの入力（イベント）受付
	virtual bool Move();							// 移動処理（ジャンプ降下等）
	virtual bool Action();							// 入力（イベント）内容からの動作実施
	virtual bool ActionFinalize();					// 入力（イベント）内容からの動作実施
	virtual bool Interfere();							// 判定動作　ヒット確認など
	virtual bool InterfereFinalize();					// 最終結果　ヒット時の状態変化など、最後の処理を行う
	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
	virtual bool Draw();							// 描画処理
	virtual bool DrawFinalize();					// 描画処理後処理　Drawの後に呼ぶ
//	virtual Draw( CDispObj *dispobj, CTextureGroup *tex); 
	void GetPosition(int *x, int *y);
	void SetPosition(int x, int y);
	void AddPosition(int x, int y);
	int GetState();									// 状態を返す
	int GetFlame();									// フレーム数を返す
	CAnime* GetAnime();

	/******************* 多重継承宣言 *********************************************/
	virtual char GetDir();

protected:
	void ChangeState( int state );
	bool Animation( );

private:
	CSprite();
};

