#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;
class CCommonData;

#include "CLIB_Sprite.h"

class CChaRibbon : public CSprite{
protected:
	int	m_Blend;
	int m_Hitted;
	CResBattle*		m_ResBattle;
	CShanaProt*		m_Target;
	CCommonData*	m_Common;

	// �U���q�b�g
	void HitAttack();

public:
	CChaRibbon( CResBattle *game, CShanaProt *target, CCommonData *common );

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
//	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �ړ������i�W�����v�~�����j
//	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Result();							// ���蓮��@�q�b�g�m�F�Ȃ�
	virtual bool Interfere();						// ���蓮��@�q�b�g�m�F����Ȃ�
//	virtual bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CChaRibbon();
	
};
