#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;

#include "CLIB_Sprite.h"

class CEffAction02 : public CSprite{
protected:
	int	m_Blend;
	int m_HistoryX[10];
	int m_HistoryY[10];
	int m_FlagGround;
	int m_Life;

	float m_AirVector[2];
	float m_AirBase[2]	;
	float m_AirGravity	;
	int m_AirTime		;

	void StartAir( float vec_x, float vec_y, int op1, float gravity );
	void DoAir();
	void EndAir();

public:
	CEffAction02( CResBattle *game, CShanaProt *target );

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
//	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �ړ������i�W�����v�~�����j
	virtual bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
//	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Result();							// ���蓮��@�q�b�g�m�F�Ȃ�
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
	virtual bool DrawFinalize( );					// �`�揈�����C���@�㏈��
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CEffAction02();
	
};
