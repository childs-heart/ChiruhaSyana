#pragma once

#include "ResBattle.h"
#include "CLIB_Sprite.h"
#include "BattleMenu.h"

// �O���Q��
class CGame;
class D3DDraw;
class CTitleRod;
class CTitlePartB;

class CModeCharaSelect : public CElement{
public:
	enum{
		SUB_MODE_OPEN = 0,
		SUB_MODE_MENU ,
	};
private:
	int	m_Mode;
	int m_NextMode;
	int m_SubMode;
	int m_Flame;

	int m_decidePlayer1;
	int	m_decidePlayer2;

	CGame*			m_Game;
	CResBattle		m_Resource;

	// Common�N���X
	CCommonData		*m_CommonSystem;
	CCommonData		*m_CommonBack;
	CCommonData		*m_CommonChara;
	CCommonData		*m_CommonScene;
	CCommonData		*m_CommonEffect;

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
	void MacroDelete( CCommonData* common);		// �`�揈���㏈���@Draw�̌�ɌĂ�

public:
	CModeCharaSelect( CGame* game );
	virtual ~CModeCharaSelect();

	void SetMode( int mode );
	void DecideChara(int player, int decide);
	int	 GetDecideChara( int player);

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
