#ifndef	__TIMER
#define	__TIMER

// �O���Q��
class CResBattle;

#include "CLIB_Sprite.h"

class CTimer : public CSprite{
protected:
	int	m_Blend;
	float m_RotZ[2];		// ��]�p�x

	int m_TimerEnable;
	int m_TimeCount;

	DWORD m_StartTickCount;

public:
	CTimer( CResBattle *game );

	void SetTime( int count, int enabled );
	void Pause();
	void Resume();

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
	virtual ~CTimer();
	
};

#endif
