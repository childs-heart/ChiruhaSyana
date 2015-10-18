#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;

#include "CLIB_Sprite.h"

enum ENUM_COMBO_INFO_STATE{
	ENUM_COMBO_INFO_STATE_IDLE	,
	ENUM_COMBO_INFO_STATE_COMBO	,
	ENUM_COMBO_INFO_STATE_END
};

class CScnComboInfo: public CSprite{
protected:
	int	m_Blend;
	CShanaProt*		m_Target ;
	int	m_Player;
	int m_Combo;

public:
	CScnComboInfo( CResBattle *game , CShanaProt *target, int player );

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
//	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
//	virtual bool Move();							// �ړ������i�W�����v�~�����j
//	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool ActionFinalize();					// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Interfere();						// ���蓮��@�q�b�g�m�F����Ȃ�
	virtual bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CScnComboInfo();
	
};
