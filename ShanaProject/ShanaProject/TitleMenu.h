#pragma once

// 前方参照
class CResBattle;
class CShanaProt;
class CInput;
class CModeTitle;

#include "CLIB_Sprite.h"

class CDataTitleMenu{
public:
	enum{
		TITLE_TOP_ARCADE = 0,
		TITLE_TOP_VERSUS,
		TITLE_TOP_TRAINNING,
		TITLE_TOP_OPTION,
		TITLE_TOP_EXIT,
		TITLE_TOP_MAX_VALUE
	};
public:
	CDataTitleMenu();
	void	SetValue( int top, int value );
	int		GetValue( int top );
};

class CTitleMenu: public CSprite{
protected:
	CInput*			m_Input;		// インプットクラス
	CModeTitle*		m_Battle ;
	CShanaProt*		m_Target ;
	CDataTitleMenu* m_Data ;

	bool		m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	bool		m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int*		m_SelectItemImageNo[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int			m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;

	int			m_SelectTop;
	int			m_SelectItem;

public:
	CTitleMenu( CResBattle *game , CModeTitle *battle_mode );

	void	Setup();
	void	OnButtom( int item );
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
	virtual ~CTitleMenu();
	
};
