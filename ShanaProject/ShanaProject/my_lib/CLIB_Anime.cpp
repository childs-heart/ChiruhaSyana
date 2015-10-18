#include "CLIB_Anime.h"

// �R���X�g���N�^
CAnime::CAnime()
{
	m_CurrentActionNo	= 0;
	m_CurrentMotionNo	= 0;
	m_ActionFlame		= 0;
	m_CollisionJudgeEnable = 0;
}

CAnime::~CAnime()
{
}

// ���t�@�N�^�����O
// �֐�: 
void CAnime::StepFlame( int num )
{
	// �\�����̃��[�V�������A�j���Ȃ��������ꍇ�A�֐��I��
	if( GetCurrentMotion()->m_Flame == 0 ){
		return ;
	}

	while( m_ActionFlame >= GetCurrentMotion()->m_Flame ){
		m_ActionFlame -= GetCurrentMotion()->m_Flame;
		if( m_ActionFlame >= 0 ){
			m_CurrentMotionNo++;
			if( GetCurrentMotion()->m_Attack.m_Type & ENUM_ATTACK_TYPE_RESET )
			{
				m_AttackJudgeEnable = 1;
			}
		}
		if( m_CurrentMotionNo >= GetCurrentAction()->m_NumMotion ){
			m_CurrentMotionNo = 0;
		}
		// �\�����̃��[�V�������A�j���Ȃ��������ꍇ�A�֐��I��
		if( GetCurrentMotion()->m_Flame == 0 ){
			return ;
		}
	}
	// �t���[���o��
	m_ActionFlame += num;

}

void CAnime::ChangeAction( DWORD action_no , DWORD motion_no )
{
	m_CurrentActionNo		= action_no;
	m_CurrentMotionNo		= motion_no;
	m_ActionFlame			= 0;
	m_AttackJudgeEnable		= 1;
	m_CollisionJudgeEnable	= 1;
}

CAction* CAnime::GetActionData( DWORD action_no )
{
	return m_AnimeSpec->GetActionData( action_no );
}

StMotionData* CAnime::GetMotionData( DWORD motion_no )
{
	return m_AnimeSpec->GetActionData( m_CurrentActionNo )->GetMotionData( motion_no );
}

DWORD CAnime::GetCurrentImageNo()
{
	return m_AnimeSpec->m_Action[m_CurrentActionNo].GetMotionFlame( m_CurrentMotionNo );
}

StMotionData* CAnime::GetCurrentMotion()
{
	return m_AnimeSpec->m_Action[m_CurrentActionNo].GetMotionData( m_CurrentMotionNo );
}

CAction* CAnime::GetCurrentAction( )
{
	return &m_AnimeSpec->m_Action[m_CurrentActionNo];
}

int CAnime::GetCurrentActionNo( )
{
	return m_CurrentActionNo;
}

int	CAnime::IsCollisioned( CAnime* target_anime )
{
	StMotionData* attack = GetCurrentMotion();
	StMotionData* wound = target_anime->GetCurrentMotion();

	RECT	myrect;
	RECT	destrect;
	RECT	hitrect;
	int		mybaseX, mybaseY, destbaseX, destbaseY ;

	destbaseX = attack->m_Image.m_BaseX ;
	destbaseY = attack->m_Image.m_BaseY ;
	mybaseX = wound->m_Image.m_BaseX ;
	mybaseY = wound->m_Image.m_BaseY ;

	int i;
	int j;
	for( j = 0 ; j < attack->m_Attack.m_NumHit ; j++ ){
		SetRect( &destrect, destbaseX + attack->m_Attack.m_HitArea[j].left,
							destbaseY + attack->m_Attack.m_HitArea[j].top,
							destbaseX + attack->m_Attack.m_HitArea[j].right,
							destbaseY + attack->m_Attack.m_HitArea[j].bottom );
		for( i = 0 ; i < wound->m_Wound.m_NumHit ; i++ ){
			SetRect(&myrect,mybaseX + wound->m_Wound.m_HitArea[i].left,
							mybaseY + wound->m_Wound.m_HitArea[i].top,
							mybaseX + wound->m_Wound.m_HitArea[i].right,
							mybaseY + wound->m_Wound.m_HitArea[i].bottom );

			if( myrect.left > myrect.right ){
				int tmp = myrect.left;
				myrect.left = myrect.right ;
				myrect.right = tmp;
			}
			if( myrect.top > myrect.bottom ){
				int tmp = myrect.bottom;
				myrect.bottom = myrect.top ;
				myrect.top = tmp;
			}

			if( destrect.left > destrect.right ){
				int tmp = destrect.left;
				destrect.left = destrect.right ;
				destrect.right = tmp;
			}
			if( destrect.top > destrect.bottom ){
				int tmp = destrect.bottom;
				destrect.bottom = destrect.top ;
				destrect.top = tmp;
			}

			// ����
			if( IntersectRect( &hitrect, &myrect, &destrect ) != 0 ){
				return 1;
			}
		}
	}

	return 0;
}

void CAnime::AttackHit()
{
	m_AttackJudgeEnable = 0;
}

int	CAnime::IsCollisionJudge()
{
	return m_CollisionJudgeEnable;
}

int CAnime::IsAttackEnabled()
{
	return m_AttackJudgeEnable;
}

//////////////////////////////////////////////////
////
///////////////////////////////////////////////////
// �R���X�g���N�^
CAnimeSpec::CAnimeSpec()
{
	m_NumAction			= 200;
	m_Action			= new CAction[m_NumAction] ;
}

// �R���X�g���N�^
CAnimeSpec::CAnimeSpec( int num )
{
	m_NumAction		= num;
	m_Action		= new CAction[m_NumAction] ;
}

// �f�X�g���N�^
CAnimeSpec::~CAnimeSpec()
{
	if( m_Action != NULL ){
		delete[] m_Action;
	}
}

//
//  �֐�: LoadAnimeData( )
//
//  �ړI: �A�j���[�V�����f�[�^�ǂݍ���
//
//  �p�����[�^:
//�@�����F
//�@�@�@
void CAnimeSpec::LoadAnimeData()
{
	if( m_Action != NULL ){
		delete[] m_Action;
	}
	m_Action		= new CAction[100];
}

//
//  �֐�: SetAnimeData( )
//
//  �ړI: �A�j���[�V�����f�[�^�ǂݍ���
//
//  �p�����[�^:
//		para1�F�A�j���ԍ�
//		para2�F�e�N�X�`���[�ԍ�
//		para3�F����
//	  para4 5�F���W�I�t�Z�b�g
//�@�����F
//�@�@�@
//void CAnimeSpec::SetAnimeData( DWORD index, DWORD tex_no, DWORD flame, DWORD baseX, DWORD baseY )
//{
//	m_Action[index].m_TextureNo	= tex_no;
//	m_Action[index].m_Flame		= flame;
//	m_Action[index].m_BaseX		= baseX;
//	m_Action[index].m_BaseY		= baseY;
//}

//StMotionData* CAnimeSpec::GetMotionData( DWORD motion_no )
//{
//	return m_Action[m_CurrentActionNo].GetMotionData( motion_no );
//}

void CAnimeSpec::CreateAction( DWORD action_no, DWORD num_motion )
{
//	if( m_Action ) delete[] m_Action;
	m_Action[action_no].CreateMotion( num_motion );
}

void CAnimeSpec::LoadActionData( )
{
}

CAction* CAnimeSpec::GetActionData( DWORD motion_no )
{
	return &m_Action[motion_no];
}

