#pragma once

// 前方参照
class CResBattle;
class CCharaSelPuchi;
class CInput;
class CModeCharaSelect;

#include "CLIB_Sprite.h"

class CCharaSelCut: public CSprite{
protected:
	CInput*				m_Input;		// インプットクラス
	CModeCharaSelect*	m_Battle ;
	CCharaSelPuchi*		m_Target1 ;
	CCharaSelPuchi*		m_Target2 ;

/*	bool		m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	bool		m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int*		m_SelectItemImageNo[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int			m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;

	int			m_SelectTop;
	int			m_SelectItem;
*/
public:
	CCharaSelCut( CResBattle *game , CModeCharaSelect *battle_mode,
					CCharaSelPuchi* tar1 ,CCharaSelPuchi* tar2 );

	void	Setup();
	/************/
	/* オーバーライト群
	/************/
	bool Event();							// ユーザー等からの入力（イベント）受付
	bool Move();							// 移動処理（ジャンプ降下等）
//	virtual bool Action();							// 入力（イベント）内容からの動作実施
//	virtual bool Result();							// 判定動作　ヒット確認など
//	bool FlameResult();						// 最終結果　ヒット時の状態変化など、最後の処理を行う
	bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
//	virtual bool Draw();							// 描画処理

protected:
	virtual ~CCharaSelCut();
	
};
