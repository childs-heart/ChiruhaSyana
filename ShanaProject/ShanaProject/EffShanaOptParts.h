#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;

#include "CLIB_Sprite.h"

class CEffShanaOptParts : public CSprite{
protected:
	int	m_Blend;

	int m_Vector[2];
	float m_fX, m_fY;

public:
	CEffShanaOptParts( CResBattle *game, CSprite *target );

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
//	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �ړ������i�W�����v�~�����j
//	virtual bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
//	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Result();							// ���蓮��@�q�b�g�m�F�Ȃ�
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CEffShanaOptParts();
	
};
