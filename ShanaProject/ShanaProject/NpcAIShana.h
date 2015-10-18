#pragma once

// 前方参照
class CResBattle;
class CShanaProt;
class CInput;
class CModeBattle;
class CDataBattleMenu;
class CAITableShana;
class CAIAction;
class CNpcCommand;
class CAICombo;

#include "CLIB_Sprite.h"
#include "CLIB_Command.h"
class CAIRunningAction
{
public:
	CAIRunningAction();
	void SetCombo( CAICombo* act );
	void Run();

	char  m_Type;
	short m_Time[10];
	int	  m_Command[10];
	char m_Name[32];

};

class CNpcAIShana: public CSprite , public CCommandRefer{
protected:
	CInput*			m_Input;		// インプットクラス
	CNpcCommand*	m_Command;		// コマンドクラス
	CModeBattle*	m_Battle ;
	CShanaProt*		m_Target ;
	CAITableShana*	m_AITable ;
	CAIAction*		m_AIAction;

	CAIRunningAction	m_RunningAction;
	unsigned long	m_AIInput;

public:
	int				m_JudgeWaitTime;
	void SetAIInput( unsigned int nrInput, unsigned int spInput = 0 );
	void SetAIInputSP( unsigned int Input );
	unsigned long	m_PadTemp[5];

	CNpcAIShana( CResBattle *game , CModeBattle *battle_mode , CAITableShana *ai, CShanaProt *target);

//	void	Setup();
	/************/
	/* オーバーライト群
	/************/
	virtual bool Event();							// 1.ユーザー等からの入力（イベント）受付
	virtual bool Move();							// 2.移動処理（ジャンプ降下等）
//	virtual bool Action();							// 3.入力（イベント）内容からの動作実施
//	virtual bool ActionFinalize();					// 4.入力（イベント）内容からの動作実施
//	virtual bool Interfere();						// 5.判定動作　ヒット確認など
	virtual bool InterfereFinalize();				// 6.最終結果　ヒット時の状態変化など、最後の処理を行う
	virtual bool Draw( CD3DDraw *draw );			// 7.描画処理メイン　基本こちらを呼ぶ
//	virtual bool Draw();							// 8.描画処理
	virtual bool DrawFinalize();					// 9.描画処理後処理　Drawの後に呼ぶ

	/******************* 多重継承宣言 *********************************************/
	char getDir();		// CommandReferからの純粋仮想関数

protected:
	virtual ~CNpcAIShana();
	
};
