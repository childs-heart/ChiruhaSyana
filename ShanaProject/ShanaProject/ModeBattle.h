#pragma once

#include "ResBattle.h"
#include "CLIB_Sprite.h"
#include "BattleMenu.h"

// �O���Q��
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

	// AI�N���X
	CAITableShana	*m_AITable[2];

	// Common�N���X
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

	// ����������
	void Initialize();

	void MacroEvent( CCommonData* common);				// ���[�U�[������̓��́i�C�x���g�j��t
	void MacroMove( CCommonData* common);				// �ړ�����
	void MacroAction( CCommonData* common);			// ���́i�C�x���g�j���e����̓�����{
	void MacroActionFinalize( CCommonData* common);	// ���́i�C�x���g�j���e����̓�����{
	void MacroInterfere( CCommonData* common);			// ���蓮��@�q�b�g�m�F�Ȃ�
	void MacroInterfereFinalize( CCommonData* common);	// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	void MacroDraw( CD3DDraw *draw, CCommonData* common);// �`�揈�����C���@��{��������Ă�
	void MacroDraw( CCommonData* common);				// �`�揈�����C���@��{��������Ă�
	void MacroDrawFinalize( CCommonData* common);		// �`�揈���㏈���@Draw�̌�ɌĂ�

public:
	CModeBattle( CGame* game, int player1 = 0, int player2 = 0 );
	virtual ~CModeBattle();

	void SetMode( int mode );

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
	bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	bool Move();							// �ړ�����
	bool Action();							// ���́i�C�x���g�j���e����̓�����{
	bool ActionFinalize();					// ���́i�C�x���g�j���e����̓�����{
	bool Interfere();						// ���蓮��@�q�b�g�m�F�Ȃ�
	bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
	bool DrawFinalize();					// �`�揈���㏈���@Draw�̌�ɌĂ�

	/************/
	/* �o�g���V�[�����������鐧��	*/
	/************/
	void BattlePause();
	void BattleResume();
};
