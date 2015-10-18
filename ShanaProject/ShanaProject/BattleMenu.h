#pragma once

// 前方参照
class CResBattle;
class CShanaProt;
class CInput;
class CModeBattle;

#include "CLIB_Sprite.h"

class CDataBattleMenu{
public:
	enum{
		SELECT_TOP_RESET = 0,
		SELECT_TOP_STATUS_1P,
		SELECT_TOP_STATUS_2P,
		SELECT_TOP_AIR_PASSIVE,
		SELECT_TOP_AUTO_GUARD,
		SELECT_TOP_SP_GAUGE,
		SELECT_TOP_INFORMATION_DISP,
		SELECT_TOP_VIEW_SCREEN,
		SELECT_TOP_CHANGE_CHAR,
		SELECT_TOP_EXIT,
		SELECT_TOP_MAX_VALUE
	};
	enum{
		STATUS_ITEM_MANUAL = 0,
		STATUS_ITEM_STAND	,
		STATUS_ITEM_CROUCH	,
		STATUS_ITEM_JUMP
	};
	enum{
		PASSIVE_ITEM_NEUTRAL = 0,
		PASSIVE_ITEM_FRONT,
		PASSIVE_ITEM_BACK
	};
	enum{
		GAUGE_ITEM_NORMAL = 0,
		GAUGE_ITEM_MAX,
		GAUGE_ITEM_INFINITY
	};
	enum{
		DISP_ITEM_OFF = 0,
		DISP_ITEM_ON
	};
public:
	WORD	m_StatusPlayer[2];
	WORD	m_AutoAttack[2];
	WORD	m_AutoRecover[2];
	WORD	m_AutoGuard[2];
	WORD	m_GaugeCtrl[2];
	WORD	m_InfoDisp;

	CDataBattleMenu();
	void	SetValue( int top, int value );
	int		GetValue( int top );
};

class CBattleMenu: public CSprite{
protected:
	CInput*			m_Input;		// インプットクラス
	CModeBattle*	m_Battle ;
	CShanaProt*		m_Target ;
	CDataBattleMenu* m_Data ;

	bool		m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_MAX_VALUE] ;
	bool		m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_MAX_VALUE] ;
	int*		m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_MAX_VALUE] ;
	int			m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_MAX_VALUE] ;

	int			m_SelectTop;
	int			m_SelectItem;

public:
	CBattleMenu( CResBattle *game , CModeBattle *battle_mode , CDataBattleMenu* data , CShanaProt *target );

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
	virtual ~CBattleMenu();
	
};
