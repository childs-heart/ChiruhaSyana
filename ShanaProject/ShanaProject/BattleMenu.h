#pragma once

// �O���Q��
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
	CInput*			m_Input;		// �C���v�b�g�N���X
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
	/* �I�[�o�[���C�g�Q
	/************/
	bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	bool Move();							// �ړ������i�W�����v�~�����j
//	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Result();							// ���蓮��@�q�b�g�m�F�Ȃ�
//	bool FlameResult();						// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CBattleMenu();
	
};
