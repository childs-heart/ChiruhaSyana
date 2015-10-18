#pragma once

#include "ResBattle.h"
#include "CLIB_Sprite.h"
#include "BattleMenu.h"

// 前方参照
class CGame;
class D3DDraw;
class CAITableShana;
class CModeBattle : public CElement{
public:
	enum{
		SUB_MODE_FIGHT = 0,
		SUB_MODE_MENU
	};
private:
	int	m_Mode;
	int m_NextMode;
	int m_SubMode;
	int m_Flame;

	int m_Player1;
	int m_Player2;

	CGame*			m_Game;
	CResBattle		m_Resource;
	CDataBattleMenu m_BattleMenuData;

	// AIクラス
	CAITableShana	*m_AITable[2];

	// Commonクラス
	CCommonData		*m_CommonTitle;
//	CCommonData		*m_CommonChara;
	CCommonData		*m_CommonSystem;
	CCommonData		*m_CommonSystemFront;
	CCommonData		*m_CommonScene;
	CCommonData		*m_CommonEffect;
	CCommonData		*m_CommonEffectFront;
	CCommonData		*m_CommonBack;
	CCommonData		*m_CommonUtilScreen;
	CCommonData		*m_CommonBattleMenu;
	CCommonData		*m_CommonCpuPlayer;
	CCommonData		*m_CommonChara[2];

	// 初期化処理
	void Initialize();

	void MacroEvent( CCommonData* common);				// ユーザー等からの入力（イベント）受付
	void MacroMove( CCommonData* common);				// 移動処理
	void MacroAction( CCommonData* common);			// 入力（イベント）内容からの動作実施
	void MacroActionFinalize( CCommonData* common);	// 入力（イベント）内容からの動作実施
	void MacroInterfere( CCommonData* common);			// 判定動作　ヒット確認など
	void MacroInterfereFinalize( CCommonData* common);	// 最終結果　ヒット時の状態変化など、最後の処理を行う
	void MacroDraw( CD3DDraw *draw, CCommonData* common);// 描画処理メイン　基本こちらを呼ぶ
	void MacroDraw( CCommonData* common);				// 描画処理メイン　基本こちらを呼ぶ
	void MacroDrawFinalize( CCommonData* common);		// 描画処理後処理　Drawの後に呼ぶ

public:
	CModeBattle( CGame* game, int player1 = 0, int player2 = 0 );
	virtual ~CModeBattle();

	void SetMode( int mode );

	/************/
	/* オーバーライト群
	/************/
	bool Event();							// ユーザー等からの入力（イベント）受付
	bool Move();							// 移動処理
	bool Action();							// 入力（イベント）内容からの動作実施
	bool ActionFinalize();					// 入力（イベント）内容からの動作実施
	bool Interfere();						// 判定動作　ヒット確認など
	bool InterfereFinalize();				// 最終結果　ヒット時の状態変化など、最後の処理を行う
	bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
	bool DrawFinalize();					// 描画処理後処理　Drawの後に呼ぶ

	/************/
	/* バトルシーンをいじくる制御	*/
	/************/
	void BattlePause();
	void BattleResume();
};
