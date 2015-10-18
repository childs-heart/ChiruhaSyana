#pragma once
#include <windows.h>

// �摜�\���p�����[�^
typedef struct ST_IMAGE_DATA{
	DWORD	m_TextureNo;		// �\������摜�t�@�C���i�e�N�X�`���[�ԍ��j
	DWORD	m_Left , m_Top , m_Right , m_Bottom ;
	long	m_BaseX, m_BaseY;	// �\�����_�@�n�ʂ̐^�񒆂��w�肷��
	DWORD	m_Flag;
}StImageData;

// �\���G�t�F�N�g
typedef struct ST_ADD_EFFECT_DATA{
	DWORD	m_AnimationNo;
	int		m_Param1;		// ���g�p
	int		m_Param2;		// ���g�p
}StAddEffectData;

// �����ʉ�
typedef struct ST_ADD_SOUND_DATA{
	DWORD	m_SoundNo;
	int		m_Param1;		// ���g�p
}StAddSoundData;

// �U������p�����[�^
typedef struct ST_ATTACK_DATA{
	DWORD	m_NumHit;			// �����蔻�萔
	RECT	m_HitArea[10];		// �����蔻��
	int		m_Property;			// ����	(��i�A���i�A���i�j
	int		m_HitTargetAction;	// �_���[�W��H��킵�����́A����̏�ԁi�_�E���A������тȂǁj
	int		m_BaseDamage;		// ��{�_���[�W
	int		m_DamageSupply;		// �_���[�W�␳
	int		m_HitSpValue;		// SP�Q�[�W�����ʁi�q�b�g���j
	int		m_MissSpValue;		// SP�Q�[�W�����ʁi��U�莞�j
	int		m_HitStopedTime;	// �U���q�b�g���̎��L�����N�^�d������
	int		m_GuardStopedTime;	// �U���h�䎞�̎��L�����N�^�d������
	int		m_HitTargetStopedTime;	// �U���q�b�g���̑���L�����N�^�d������
	int		m_GuardTargetStopedTime;// �U���h�䎞�̑���L�����N�^�d������
	StAddEffectData	m_HitEffect[10];// �U���q�b�g���\���G�t�F�N�g
	StAddSoundData	m_HitSound[10];	// �U���q�b�g�������ʉ�
	StAddEffectData	m_GuardEffect[10];	// �U���h�䎞�\���G�t�F�N�g
	StAddSoundData	m_GuardSound[10];	// �U���h�䎞�����ʉ�
	DWORD	m_Type;				// �^�C�v�@����V�K�E����p���Ƃ��E�E�E
}StAttackData;

// ��炢����p�����[�^
typedef struct ST_WOUND_DATA{
	DWORD	m_NumHit;			// �����蔻�萔
	RECT	m_HitArea[10];		// ��炢����
//	int		
}StWoundData;

// ���[�V�����p�����[�^
typedef struct ST_MOTION_DATA{
	DWORD			m_Flame;	// �؍ݎ��ԁi�t���[���j0 �͖����؍�
	StImageData		m_Image;	// �\������摜�i�摜�\���p�����[�^�\���́j
	StAttackData	m_Attack;	// �����蔻��ǉ�
	StWoundData		m_Wound;	// ��炢����ǉ�
	StAddEffectData	m_Effect[10];	// �����\���G�t�F�N�g
	StAddSoundData	m_Sound[10];	// ���������ʉ�
	//�@�ق��A���낢��ǉ�
}StMotionData;

// �L�����Z���E�U������ہE���̑��A�ݒ�p�����[�^
typedef struct ST_ACTION_SPEC{
	int		m_EnableDir;			// �������]�\�i�A�N�V�����J�n�O�t���[�����ɔ��]���{�j
	int		m_CancelEnabled;		// �s���i�L�����Z���j�\
	int		m_NotCancelTime;		// �L�����Z���s�\����
	int		m_HitCancelTime;		// �ȍ~�q�b�g������L�����Z���\����
	int		m_EveryCancelTime;		// �ȍ~�q�b�g���Ȃ��Ă��L�����Z���\����
}StActoinSpecl;

// �U������
enum{
	ENUM_ATTACK_PROPERTY_LOW	= 0x00000001,
	ENUM_ATTACK_PROPERTY_MIDDLE	= 0x00000002,
	ENUM_ATTACK_PROPERTY_HIGH	= 0x00000004,
	ENUM_ATTACK_PROPERTY_JUMP	= 0x00000008,
	ENUM_ATTACK_PROPERTY_RESET	= 0x00000010
};

// �U���I�v�V����
enum{
	ENUM_ATTACK_TYPE_RESET		= 0x00000001
};

// �L�����N�^�[�A�N�V�����N���X
// ���A�N�V�����ˁu�����v�u���݁v�P��
// �����[�V�����˂P�A�N�V�����Ɋ܂܂��R�}
// 
class CAction{
public:
	// �o�^
	void SetMotionData( DWORD motion_num, DWORD tex_no, DWORD flame, DWORD baseX, DWORD baseY );
	void SetAttackData( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom );
	void SetAttackData( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom, int property = 1 );
	void SetAttackDataAbs( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom, int property = 1 );
	void SetAttackSpec( DWORD motion_num, int base_damage, int damage_supply, int type );
	void SetWoundData( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom );
	void SetWoundDataAbs( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom );

	void SetEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 = 0, int param2 = 0 );		// �����\���G�t�F�N�g
	void SetHitEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 = 0, int param2 = 0 );	// �U���q�b�g���\���G�t�F�N�g
	void SettGuardEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 = 0, int param2 = 0 );	// �U���h�䎞�\���G�t�F�N�g
	void SetSoundtData( DWORD motion_num, DWORD arg_num, DWORD sound_no, int param1 = 0 );		// ���������ʉ�
	void SetHitSoundData( DWORD motion_num, DWORD arg_num, DWORD sound_no, int param1 = 00 );	// �U���q�b�g�������ʉ�
	void SettGuardSoundData( DWORD motion_num, DWORD arg_num, DWORD sound_no, int param1 = 0 );	// �U���h�䎞�����ʉ�
//	void SetAnimeData( DWORD index, DWORD tex_no, DWORD flame, DWORD left, DWORD top, DWORD right, DWORD bottom, DWORD baseX, DWORD baseY );

	// �R���X�g���N�^���f�X�g���N�^
	CAction( );
	CAction( int num_motion );
	virtual ~CAction();

	// �A�j���[�V�����f�[�^�ǂݍ���
	void LoadMotionData( );

	// �P�A�N�V�������̃��[�V�����쐬
	void CreateMotion( int num_motion );

	StMotionData*	GetMotionData( DWORD moion_num );
	DWORD			GetMotionFlame( DWORD motion_num );
	bool			Collision( StMotionData* );

	// �P�A�N�V�������̃��[�V�������ׂĂ������
	StMotionData*	m_MotionData;
	// �P�A�N�V�������̐�
	DWORD	m_NumMotion;
	// �e���[�V�����̊J�n�ԍ�(���j
//	DWORD	*m_StartMotion;

private:
	// ���[�V������
};
