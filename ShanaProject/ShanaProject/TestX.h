#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;
class CInput;

#include "CLIB_Sprite.h"

class CTestX : public CSprite{
protected:
	int	m_Blend;
	int rotx;
	int roty;
	CInput	*m_Input;

public:
	CTestX( CResBattle *game );
	float m_fX;
	float m_fY;
	float m_fZ;

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
	virtual ~CTestX();
	
};
