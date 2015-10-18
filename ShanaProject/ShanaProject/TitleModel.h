#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;
class CInput;

#include "CLIB_Sprite.h"

class CTitleModel : public CSprite{
protected:
	int	m_Blend;
	int m_BaseX;
	int m_BaseY;
	int m_BaseZ;
	int m_ObjX[10];
	int m_ObjY[10];
	int m_ObjZ[10];
	float m_ObjRange[10];
	int m_ObjMeshNo[10];
	float m_ObjRotX[10];
	float m_ObjRotY[10];
	float m_ObjRotZ[10];
	float m_ObjRotBeginY[10];
	float m_ObjRotXVal[10];
	float m_ObjRotYVal[10];
	float m_ObjRotZVal[10];
	float m_ObjRotBeginYVal[10];
	int rotx;
	int roty;
	CInput	*m_Input;

public:
	CTitleModel( CResBattle *game );
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
	virtual ~CTitleModel();
	
};
