#pragma once

#include <windows.h>
#include "CLIB_Action.h"

/*typedef struct{
	DWORD	m_TextureNo;
	DWORD	m_Left , m_Top , m_Right , m_Bottom ;
	long	m_BaseX, m_BaseY;
	DWORD	m_Flame;
	DWORD	m_Flag;
}ST_IMAGE_DATA;
*/

//==============================================================
// �A�j���[�V�����ڍ׃N���X
// �A�j���[�V�����p�^�[���Ƃ��m���Ă�
// ���A�N�V�����ˁu�����v�u���݁v�P��
// ���A�j���[�V�����˃A�N�V�����̏W���́@�L�����P��
//==============================================================
class CAnimeSpec{
public:
	// �A�j���o�^
	void SetAnimeData( DWORD index, DWORD tex_no, DWORD flame, DWORD baseX, DWORD baseY );
//	void SetAnimeData( DWORD index, DWORD tex_no, DWORD flame, DWORD left, DWORD top, DWORD right, DWORD bottom, DWORD baseX, DWORD baseY );

	// �R���X�g���N�^���f�X�g���N�^
	CAnimeSpec( );
	CAnimeSpec( int num );
	virtual ~CAnimeSpec();

	// �A�j���[�V�����f�[�^�ǂݍ���
	void LoadAnimeData( );
	
	// 20070901�@���t�@�N�^�����O
	CAction*		GetActionData( DWORD action_no );
//	StMotionData*	GetMotionData( DWORD motion_no );

	void LoadActionData();
	void CreateAction( DWORD action_no, DWORD num_motion );

	CAction*	m_Action;		// �A�N�V�����f�[�^
	DWORD		m_NumAction;	// �A�N�V�����̕ێ���
};

//==============================================================
// �A�j���[�V�����N���X
// �e�I�u�W�F�N�g�����ێ�����f�[�^�������Ă�
//==============================================================
class CAnime{
public:
	// �R���X�g���N�^���f�X�g���N�^
	CAnime();
	virtual ~CAnime();

	CAnimeSpec*		m_AnimeSpec;	// �A�j���[�V�����f�[�^

	CAction*		GetActionData( DWORD action_no );
	StMotionData*	GetMotionData( DWORD motion_no );
	CAction*		GetCurrentAction();
	DWORD			GetCurrentImageNo();
	StMotionData*	GetCurrentMotion();
	int				GetCurrentActionNo();

	void StepFlame( int num );
	void ChangeAction( DWORD action_no , DWORD motion_no = 0 );
	int	 IsCollisioned( CAnime* target_anime );
	void AttackHit();
	int	 IsAttackEnabled();
	int	 IsCollisionJudge();

	int m_CurrentActionNo;		// ���݂̃A�N�V�����ԍ�
	int m_CurrentMotionNo;		// ���݂̃A�N�V�����ŕ\�����̃��[�V�����ԍ�
	int m_ActionFlame;			// m_CurrentMotionNo�̃��[�V������\�������t���[����

	// ���A�j���[�V�����t���O�Q
	// ����L���E����
	int	m_AttackJudgeEnable;
	int	m_CollisionJudgeEnable;

};

//==============================================================
// �A�j���[�V�����N���X�O���[�v
//==============================================================
class CAnimeGroup{
};
