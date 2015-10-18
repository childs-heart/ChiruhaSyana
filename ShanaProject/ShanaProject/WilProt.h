#ifndef	__WILPROT
#define	__WILPROT

// �O���Q��
class CInput;
class CResBattle;
class C3DDraw;

#include "CLIB_Sprite.h"
#include "ShanaProt.h"
#include "ShanaCommand.h"

class CWilProt : public CShanaProt {
public:

	CWilProt( CResBattle *game, int x, int y, char player, CShanaProt* target = NULL );
	CWilProt( CResBattle *game );
	virtual ~CWilProt();

protected:
	// �ΐ푊��Z�b�g
//	virtual void SetTarget( CShanaProt* target );

	// ��ԑJ��
	virtual void ChangeState( int state );
//	virtual void ChangeAnime( int animeNo , int animeFlame );
	// �A�j���[�V����
//	virtual void Animetion();
	// �ړ�
// 	virtual void Transfer();

	// �ړ�����
//	virtual void StartAir( float vec_x, float vec_y, int op1 , float gravity = 0.5f );
	virtual void EndAir( );
	virtual void DoAir();
//	virtual char CanJump();
//	virtual void IncreaseJump();
//	virtual void ClearJump();
//	virtual char CanJumpDush();
//	virtual void IncreaseJumpDush();
//	virtual void ClearJumpDush();

	// �U���q�b�g
	virtual void HitAttack();

	// �����q�b�g
//	virtual void DecideThrow( int isThrow );

	// �L�����N�^�[�̌�������
//	virtual void UpdateCharaDir();

public:
	/************/
	/* ���C���F�I�[�o�[���C�g�Q
	/************/
//	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �t���[���o�߂ɂ��ω�����A�ړ������i�W�����v�~�����j
	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool ActionFinalize();					// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Interfere();						// ���蓮��@�q�b�g�m�F����Ȃ�
//	virtual bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
//	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
//	virtual bool DrawFinalize();					// �`�揈���㏈���@Draw�̌�ɌĂ�
//	virtual bool Draw();					// �`�揈��

	virtual bool SetSpec();

	/******************* ���I�u�W�F�N�g����Ă΂��֐��S *************************/
	virtual int ReceiveAttack( CSprite* target, CAnime *anime );	// ���肩��̍U�����󂯂�i�߂�l�F�q�b�g�E�h��E�~�X�j

	void Initialize( CResBattle *game, int x, int y, char player, CShanaProt* target );
};

#endif	// 
