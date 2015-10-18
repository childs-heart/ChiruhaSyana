#ifndef	__SHANAPROT
#define	__SHANAPROT

// �O���Q��
class CInput;
class CResBattle;
class C3DDraw;

#include "CLIB_Sprite.h"
#include "ShanaCommand.h"

//#include "CLIB_Element.h"
//#include "CLIB_DispObj.h"
//#include "CLIB_Anime.h"
//#include "CLIB_Texture.h"
//#include "CLIB_Sprite.h"
//#include "game.h"


enum ENUM_TESTCHAR_STATE{
	ENUM_TESTCHAR_STATE_INIT			= 0x00000000 ,
	ENUM_TESTCHAR_STATE_NONE			= 0x00000000 ,
	ENUM_TESTCHAR_GROUND				= 0x00010000 ,
	ENUM_TESTCHAR_STATE_NEUTRAL			,
	ENUM_TESTCHAR_STATE_WALK_FORWARD	,
	ENUM_TESTCHAR_STATE_WALK_BACK		,
	ENUM_TESTCHAR_STATE_ATTACK_LOW		,
	ENUM_TESTCHAR_STATE_ATTACK_MID		,
	ENUM_TESTCHAR_STATE_ATTACK_HIGH		,
	ENUM_TESTCHAR_STATE_ATTACK_EX		,
	ENUM_TESTCHAR_STATE_DAMAGE			,
	ENUM_TESTCHAR_STATE_BIG_DAMAGE		,
	ENUM_TESTCHAR_STATE_GUARD			,
	ENUM_TESTCHAR_STATE_CROUCH_DAMAGE	,
	ENUM_TESTCHAR_STATE_CROUCH			= 0x00020000,
	ENUM_TESTCHAR_STATE_CROUCH_FORWARD	,
	ENUM_TESTCHAR_STATE_CROUCH_BACK		,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_START,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_END,
	ENUM_TESTCHAR_STATE_CROUCH_GUARD	,
	ENUM_TESTCHAR_STATE_JUMP_SETUP		,

	ENUM_TESTCHAR_STATE_DUSH_FORWARD	,
	ENUM_TESTCHAR_STATE_DUSH_FORWARD_END,
	ENUM_TESTCHAR_STATE_DUSH_BACK		,

	ENUM_TESTCHAR_STATE_JUMP			= 0x00040000 ,
	ENUM_TESTCHAR_STATE_JUMP_NORMAL		,
	ENUM_TESTCHAR_STATE_JUMP_FORWARD	,
	ENUM_TESTCHAR_STATE_JUMP_BACK		,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX,
	ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD,
	ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK	,
	ENUM_TESTCHAR_STATE_JUMP_DUSH_END	,
	ENUM_TESTCHAR_STATE_JUMP_DAMAGE,
	ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE,
	ENUM_TESTCHAR_STATE_JUMP_BLOW_DOWN	,
	ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND	,
	ENUM_TESTCHAR_STATE_JUMP_GUARD		,
	ENUM_TESTCHAR_STATE_JUMP_RECOVER	,

	ENUM_TESTCHAR_STATE_DOWN			= 0x00080000 ,
	ENUM_TESTCHAR_STATE_GETUP			,			

	ENUM_TESTCHAR_STATE_THROW_STANDBY	= 0x00100000 ,
	ENUM_TESTCHAR_STATE_THROW			,
	ENUM_TESTCHAR_STATE_MISS_THROW		,
	ENUM_TESTCHAR_STATE_DAMAGE_THROW	,

	ENUM_TESTCHAR_STATE_SPECIAL_1		= 0x00200000 ,
	ENUM_TESTCHAR_STATE_SPECIAL_1_END	,
	ENUM_TESTCHAR_STATE_SPECIAL_2		,
	ENUM_TESTCHAR_STATE_SPECIAL_3		,
	ENUM_TESTCHAR_STATE_SPECIAL_3_2		,

	ENUM_TESTCHAR_STATE_FREEZE			= 0x00400000 ,

// ���̂Ƃ���g��Ȃ������ŁE�E�E�E
	ENUM_TESTCHAR_FLAG_NOT_DIR			= 0x01000000,
	ENUM_TESTCHAR_MASK_EXCEPT_FLAG		= 0x00FFFFFF		// �}�X�N�@�����t���O��

};

enum ENUM_TESTCHAR_SUB_STATE{
	ENUM_TESTCHAR_SUB_STATE_STAND	,
	ENUM_TESTCHAR_SUB_STATE_CROUCH	,
	ENUM_TESTCHAR_SUB_STATE_JUMP	,
	ENUM_TESTCHAR_SUB_STATE_DAMAGE	,
	ENUM_TESTCHAR_SUB_STATE_DOWN
};

enum ENUM_VECTOR{
	ENUM_VECTOR_UP = 0	,
	ENUM_VECTOR_DOWN	,
	ENUM_VECTOR_FWD		,
	ENUM_VECTOR_BACK
};

enum ENUM_DIRECTION{
	ENUM_DIR_RIGHT	= 1 ,
	ENUM_DIR_LEFT	= -1
};

enum ENUM_TESTCHAR_GUARD_INPUT{
	ENUM_TESTCHAR_GUARD_OFF,
	ENUM_TESTCHAR_GUARD_STAND,
	ENUM_TESTCHAR_GUARD_CROUCH,
	ENUM_TESTCHAR_GUARD_JUMP,
	ENUM_TESTCHAR_GUARD_ALL
};

enum ENUM_ACTION_ENABLE{
	ENUM_ACTION_ENABLE_MOVE		= 0x00000001,
	ENUM_ACTION_ENABLE_ATTACK	= 0x00000002,
	ENUM_ACTION_ENABLE_ALL		= 0xFFFFFFF
};

typedef struct CHARACTER_PARAM{
	int m_HpGauge;			// �q�b�g�|�C���g��
	int m_SpGauge;			// �r�o�Q�[�W
}ST_CHARACTER_PARAM;

typedef struct CHARACTER_SPEC{
	int		MAX_HP					;	// HP�Q�[�W
	int		MAX_SP					;	// SP�Q�[�W
	int		SPEED_FORWARD			;	// �O�i���x
	int		SPPED_BACK				;	// ��ޑ��x
	int		SPEED_JUMP				;	// �W�����v���x
	int		SPEED_JUMP_FORWARD		;	// �O�W�����v���x
	int		SPEED_JUMP_BACK			;	// ��W�����v���x
	float	DEFENSE					;	// �h���
	float	WEIGHT					;	// �d��
	int		FAINT					;	// �C��l
	float	SPIRIT					;	// �����l
	int		TIME_JUMP_STANBY		;	// �W�����v��������
	int		RANGE_THROW				;	// �����͈�
	int		RANGE_JUMP_THROW		;	// �W�����v�����͈�
	int		MAX_JUMP_STEP			;	// ���i�W�����v��
	int		MAX_JUMP_DUSH_STEP		;	// �󒆃_�b�V����
	int		SPEED_DUSH_FORWARD		;	// �O�i�_�b�V�����x
	int		SPEED_DUSH_BACK			;	// ��ރ_�b�V�����x
	int		SPEED_JUMP_DUSH_FORWARD	;	// �O�i�_�b�V�����x
	int		SPEED_JUMP_DUSH_BACK	;	// ��ރ_�b�V�����x
	int		SPEED_JUMP_FALL			;	// �W�����v�~���␳�l
	int		TIME_DOWN				;	// �_�E������
}ST_CHARACTER_SPEC;

class CHARACTER_COMMON_PARAMETER{
public:
	static const float AERIAL_DAMAGE_VECTOR;
	static const float AERIAL_DAMAGE_GRAVITY;
	static const float AIR_DAMAGE_VECTOR;
	static const float AIR_DAMAGE_GRAVITY;
	static const float AIR_GUARD_VECTOR;
	static const float AIR_GUARD_GRAVITY;
};

// �T�u��ԍ\����
typedef struct CHARACTER_CONDITION{
	int		IDLE ;
	int		ATTACK;
}ST_CHARACTER_CONDITION;

// �U����炢���̏��
typedef struct CHARACTER_DAMAGE_INFO{
	int		m_ComboCount;
}ST_CHARACTER_DAMAGE_INFO;

// �s���ۂɊւ�����
class CCharacterActionEnableSpec{
private:
	int		m_FullActionEnabled;	// ��ɍs���\
	int		m_NotCancelTime;		// �L�����Z���s�\����
	int		m_HitCancelTime;		// �q�b�g������L�����Z���\����
	int		m_EveryCancelTime;		// �q�b�g���Ȃ��Ă��L�����Z���\����
	bool	m_Hited;

public:
	void	SetSpec( int full_action_enabled, int not_chancel, int hit_chancel, int every_chancel );
	int		CanCancel( int flame, int hitted );
	void	HitAttack( );
};

class CShanaProt : public CSprite , public CCommandRefer{
protected:
	CInput				*m_Input;		// �C���v�b�g�N���X
	CCommandManager		*m_Command;
	CCommandManager		m_PlayerCommand;
	CResBattle			*m_ResBattle;

	int	m_Blend;

	char m_player;

	// �ΐ푊��Z�b�g
	virtual void SetTarget( CShanaProt* target );

	// ��ԑJ��
	virtual void ChangeState( int state );
	virtual void ChangeAnime( int animeNo , int animeFlame );
	// �A�j���[�V����
//	virtual void Animetion();
	// �ړ�
   	virtual void Transfer();

	// �ړ�����
	virtual void StartAir( float vec_x, float vec_y, int op1 , float gravity = 0.5f );
	virtual void EndAir( );
	virtual void DoAir();
	virtual char CanJump();
	virtual void IncreaseJump();
	virtual void ClearJump();
	virtual char CanJumpDush();
	virtual void IncreaseJumpDush();
	virtual void ClearJumpDush();

	// �U���q�b�g
	virtual void HitAttack();

	// �����q�b�g
	virtual void DecideThrow( int isThrow );

	// �L�����N�^�[�̌�������
	virtual void UpdateCharaDir();

	ST_CHARACTER_SPEC	m_Spec;

	// �L�����N�^�[�f�[�^
	int m_FieldY;
//	int m_HpGauge;			// �q�b�g�|�C���g��
//	int m_SpGauge;			// �r�o�Q�[�W
	CHARACTER_PARAM		m_Parameter;

//	int	m_Dir;				// ����
	RECT m_Body;			// �L�����̖{�̋�`

	int m_SubStatus;		// �T�u���
	int	m_Condition;		// ��Ԃ��̂Q�i�p�r����j
	int m_GuardInput;		// �h����
	int m_FlagActionEnabled;// �s���ۃt���O�B�ړ��ہA�U���ہA�h��ہ@�Ȃ�
	int m_HittedAttack;		// �U���q�b�g�t���O

	float m_Vector[2];		// [0]:���E�@[1]:�㉺
	float m_KnockBackVector[2];// �m�b�N�o�b�N�x�N�g��[0]:���E�@[1]:�㉺�i�㉺�͂Ȃ����ȁc�j

	float m_AirBase[2];		// �W�����v�n�_���W�@[0]:X�ʒu�@[1]:Y�ʒu
	float m_AirVector[2];	// �W�����v�x�N�g���@[0]:X�����@[1]:Y����
	float m_AirGravity;		// �󒆏d��
	float m_AirIncrease;	// �����l
	int	m_AirTime;			// �󒆑؋󎞊�
	int m_NumJump;			// ���i�W�����v��
	int m_NumJumpDush;		// �󒆃_�b�V����

public:
	int	m_StopedMoveCount;	// �q�b�g���̃L�����N�^�d�����ԃJ�E���^
	int m_ReceiveAttackTemplateState;
						// �U�������������̏�ԁB�����ɏ�Ԃ�ς���Ɛ揟���ɂȂ邩���Ԃ��ꎞ�ޔ��B
	ST_CHARACTER_DAMAGE_INFO	m_DamageInfo;

//	int	m_Flame;			// �t���[����
	int m_EnableDir;		// �����]����
	int m_FlagStateStep[5];	// �e��Ԃ�

	CShanaProt*	m_Target;	// �ΐ푊��
	CShanaProt*	m_KnockBackChara;	// �_���[�W���炢���̃L�����N�^

public:
	CCharacterActionEnableSpec	m_ActionSpec;

	CShanaProt( CResBattle *game, int x, int y, char player, CShanaProt* target = NULL );
	CShanaProt( CResBattle *game );

	// �����p�֐� 
	void SetCommand( CCommandManager * cmd );
	void SetDefaultCommand( );

	/************/
	/* ���C���F�I�[�o�[���C�g�Q
	/************/
	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �t���[���o�߂ɂ��ω�����A�ړ������i�W�����v�~�����j
	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
	virtual bool ActionFinalize();					// ���́i�C�x���g�j���e����̓�����{
	virtual bool Interfere();						// ���蓮��@�q�b�g�m�F����Ȃ�
	virtual bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
	virtual bool DrawFinalize();					// �`�揈���㏈���@Draw�̌�ɌĂ�
//	virtual bool Draw();					// �`�揈��

	virtual bool SetSpec();

	/******************* ���I�u�W�F�N�g����Ă΂��֐��S *************************/
	int	GetSpGauge();							// SP�Q�[�W��Ԃ�
	int GetHpGauge();							// HP�Q�[�W��Ԃ�
	CShanaProt* GetTarget();
	void NotifyPlayer( CShanaProt* m_Target );	// ���������炤
	void GetVector( int *x, int *y );			// ���݂̈ړ��ʂ�Ԃ�
	void SetVector( int x, int y );				// �ړ��ʂ��Z�b�g����
	void AddVector( int x, int y );				// ���݂̈ړ��ʂ𑝌�������
	int	IsCollisioned( CSprite* target );	// ����̍U���������Ă邩���ׂ�i�߂�l�F�q�b�g�E�h��E�~�X�j
	int IsThrown( CShanaProt* target );			// ����̓����������Ă邩�ǂ������ׂ�i�߂�l�FYES/NO�j
	virtual int ReceiveAttack( CSprite* target, CAnime *anime );	// ���肩��̍U�����󂯂�i�߂�l�F�q�b�g�E�h��E�~�X�j
	int ReceiveThrown( CShanaProt* target );	// ���肩��̓������󂯂�
	int IsActionEnaled( );						// �s���ۂ̂�Ԃ�
	ST_CHARACTER_DAMAGE_INFO*	GetDamageInfo();// �����̋�炢����Ԃ�

	/******************* ���d�p���錾 *********************************************/
	char getDir();		// CommandRefer����̏������z�֐�
	char GetDir();		// CSprite����̉��z�֐�

protected:
	virtual ~CShanaProt();
	void Initialize( CResBattle *game, int x, int y, char player, CShanaProt* target );
	
};

#endif	// 
