#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;
class CInput;
class CModeBattle;
class CDataBattleMenu;

#include "CLIB_Sprite.h"

class CCpuPlayer: public CSprite{
protected:
	CInput*			m_Input;		// �C���v�b�g�N���X
	CModeBattle*	m_Battle ;
	CShanaProt*		m_Target ;
	CDataBattleMenu* m_Data ;

public:
	unsigned long	m_PadTemp[4];

	CCpuPlayer( CResBattle *game , CModeBattle *battle_mode , CDataBattleMenu *battle_menu);

//	void	Setup();
	/************/
	/* �I�[�o�[���C�g�Q
	/************/
	bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	bool Move();							// �ړ������i�W�����v�~�����j
	bool InterfereFinalize();						// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
	bool DrawFinalize();					// �`�揈���㏈���@Draw�̌�ɌĂ�
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CCpuPlayer();
	
};
