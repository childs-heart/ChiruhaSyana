#pragma once

// �O���Q��
class CResBattle;

#include "CLIB_Sprite.h"

class CTitleFlash : public CSprite{
protected:
	int m_Dx;
	int m_Dy;
	int m_TitleX;
	int m_TitleY;
	int m_RodX;
	int m_RodY;
	int m_RodDx;
	int m_RodDy;
	int m_TargetX;
	int m_TargetY;
	int m_TargetDx;
	int m_TargetDy;


public:
	CTitleFlash( CResBattle *game );

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
	virtual ~CTitleFlash();
	
};
