#include "CLIB_Action.h"

// �R���X�g���N�^
CAction::CAction()
{
	m_NumMotion		= 0;
	m_MotionData	= NULL;
}

// �R���X�g���N�^
CAction::CAction( int num )
{
	CreateMotion( num );
}

// �f�X�g���N�^
CAction::~CAction()
{
	if( m_MotionData != NULL ){
		delete []m_MotionData;
	}
}

//
//  �֐�: LoadMotionData( )
//
//  �ړI: �A�j���[�V�����f�[�^�ǂݍ���
//
//  �p�����[�^:
//�@�����F
//�@�@�@
void CAction::LoadMotionData()
{
}

//
//  �֐�: SetMotionData( )
//
//  �ړI: ���[�V�����f�[�^�ǂݍ���
//
//  �p�����[�^:
//		para1�F���[�V�����ԍ�
//		para2�F�e�N�X�`���[�ԍ�
//		para3�F����
//	  para4 5�F���W�I�t�Z�b�g
//�@�����F
//�@�@�@
void CAction::SetMotionData( DWORD motion_num, DWORD tex_no, DWORD flame, DWORD baseX, DWORD baseY )
{
	m_MotionData[motion_num].m_Flame				= flame;
	m_MotionData[motion_num].m_Image.m_TextureNo	= tex_no;
	m_MotionData[motion_num].m_Image.m_BaseX		= baseX;
	m_MotionData[motion_num].m_Image.m_BaseY		= baseY;
}

void CAction::SetAttackData( DWORD motion_num, DWORD arg_num, int left, int top, int right ,int bottom, int property )
{
	if( m_MotionData[motion_num].m_Attack.m_NumHit <= arg_num ){
		m_MotionData[motion_num].m_Attack.m_NumHit = arg_num+1;
	}
	m_MotionData[motion_num].m_Attack.m_HitArea[arg_num].left = left;
	m_MotionData[motion_num].m_Attack.m_HitArea[arg_num].top = top;
	m_MotionData[motion_num].m_Attack.m_HitArea[arg_num].right = right;
	m_MotionData[motion_num].m_Attack.m_HitArea[arg_num].bottom = bottom;
	m_MotionData[motion_num].m_Attack.m_Property = property ;
}

void CAction::SetAttackDataAbs( DWORD motion_num, DWORD arg_num, int left, int top, int right ,int bottom, int property )
{
	SetAttackData( motion_num, arg_num
		, left - m_MotionData[motion_num].m_Image.m_BaseX
		, top - m_MotionData[motion_num].m_Image.m_BaseY
		, right - m_MotionData[motion_num].m_Image.m_BaseX
		, bottom - m_MotionData[motion_num].m_Image.m_BaseY
		, property
		);
}

void CAction::SetAttackSpec( DWORD motion_num, int base_damage, int damage_supply, int type )
{
	m_MotionData[motion_num].m_Attack.m_BaseDamage = base_damage;
	m_MotionData[motion_num].m_Attack.m_DamageSupply = damage_supply;
	m_MotionData[motion_num].m_Attack.m_Type = type;
}

void CAction::SetWoundData( DWORD motion_num, DWORD arg_num, int left, int top, int right ,int bottom )
{
	if( m_MotionData[motion_num].m_Wound.m_NumHit <= arg_num ){
        m_MotionData[motion_num].m_Wound.m_NumHit = arg_num+1;
	}
	m_MotionData[motion_num].m_Wound.m_HitArea[arg_num].left = left;
	m_MotionData[motion_num].m_Wound.m_HitArea[arg_num].top = top;
	m_MotionData[motion_num].m_Wound.m_HitArea[arg_num].right = right;
	m_MotionData[motion_num].m_Wound.m_HitArea[arg_num].bottom = bottom;
}

void CAction::SetWoundDataAbs( DWORD motion_num, DWORD arg_num, int left, int top, int right ,int bottom )
{
	SetWoundData( motion_num, arg_num
		, left - m_MotionData[motion_num].m_Image.m_BaseX
		, top - m_MotionData[motion_num].m_Image.m_BaseY
		, right - m_MotionData[motion_num].m_Image.m_BaseX
		, bottom - m_MotionData[motion_num].m_Image.m_BaseY
		);
}

StMotionData* CAction::GetMotionData( DWORD motion_num )
{
	return &m_MotionData[motion_num];
}

DWORD CAction::GetMotionFlame( DWORD motion_num )
{
	return m_MotionData[motion_num].m_Flame;
}

void CAction::CreateMotion( int num_motion )
{
	m_NumMotion		= num_motion;

	if( m_MotionData ) delete[] m_MotionData;
	m_MotionData	= new StMotionData[num_motion];
	memset( m_MotionData, 0, sizeof( StMotionData ) * num_motion );
}

// �����\���G�t�F�N�g
void CAction::SetEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 , int param2 ){
	m_MotionData[motion_num].m_Effect[arg_num].m_AnimationNo = animation_no;
	m_MotionData[motion_num].m_Effect[arg_num].m_Param1 = param1;
	m_MotionData[motion_num].m_Effect[arg_num].m_Param2 = param2;
}

// �U���q�b�g���\���G�t�F�N�g
void CAction::SetHitEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 , int param2 ){
//	m_MotionData[motion_num].m_HitEffect[arg_num].m_AnimationNo = animation_no;
//	m_MotionData[motion_num].m_HitEffect[arg_num].m_Param1 = param1;
//	m_MotionData[motion_num].m_HitEffect[arg_num].m_Param2 = param2;
}

// �U���h�䎞�\���G�t�F�N�g
void CAction::SettGuardEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1, int param2 ){
//	m_MotionData[motion_num].m_GuardEffect[arg_num].m_AnimationNo = animation_no;
//	m_MotionData[motion_num].m_GuardEffect[arg_num].m_Param1 = param1;
//	m_MotionData[motion_num].m_GuardEffect[arg_num].m_Param2 = param2;
}

// ���������ʉ�
void CAction::SetSoundtData( DWORD motion_num, DWORD arg_num, DWORD sound_no, int param1 ){
	m_MotionData[motion_num].m_Sound[arg_num].m_SoundNo = sound_no;
	m_MotionData[motion_num].m_Sound[arg_num].m_Param1 = param1;
}

// �U���q�b�g�������ʉ�
void CAction::SetHitSoundData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 ){
//	m_MotionData[motion_num].m_HitSound[arg_num].m_SoundNo = sound_no;
//	m_MotionData[motion_num].m_HitSound[arg_num].m_Param1 = param1;
}

// �U���h�䎞�����ʉ�
void CAction::SettGuardSoundData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param10 ){
//	m_MotionData[motion_num].m_GuardSound[arg_num].m_SoundNo = sound_no;
//	m_MotionData[motion_num].m_GuardSound[arg_num].m_Param1 = param1;
}
