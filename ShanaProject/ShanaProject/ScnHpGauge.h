#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;

#include "CLIB_Sprite.h"

class CScnHpGauge: public CSprite{
protected:
	int	m_Blend;
	CShanaProt*		m_Target ;
	int	m_Player;
	int m_CurrentHp;

public:
	CScnHpGauge( CResBattle *game , CShanaProt *target, int player );

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
//	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �ړ������i�W�����v�~�����j
//	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Result();							// ���蓮��@�q�b�g�m�F�Ȃ�
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CScnHpGauge();
	
};
