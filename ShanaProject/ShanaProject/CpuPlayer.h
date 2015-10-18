#pragma once

// 前方参照
class CResBattle;
class CShanaProt;
class CInput;
class CModeBattle;
class CDataBattleMenu;

#include "CLIB_Sprite.h"

class CCpuPlayer: public CSprite{
protected:
	CInput*			m_Input;		// インプットクラス
	CModeBattle*	m_Battle ;
	CShanaProt*		m_Target ;
	CDataBattleMenu* m_Data ;

public:
	unsigned long	m_PadTemp[4];

	CCpuPlayer( CResBattle *game , CModeBattle *battle_mode , CDataBattleMenu *battle_menu);

//	void	Setup();
	/************/
	/* オーバーライト群
	/************/
	bool Event();							// ユーザー等からの入力（イベント）受付
	bool Move();							// 移動処理（ジャンプ降下等）
	bool InterfereFinalize();						// 最終結果　ヒット時の状態変化など、最後の処理を行う
	bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
	bool DrawFinalize();					// 描画処理後処理　Drawの後に呼ぶ
//	virtual bool Draw();							// 描画処理

protected:
	virtual ~CCpuPlayer();
	
};
