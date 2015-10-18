#pragma once

#include "CLIB_D3DDraw.h"

class CCHARACTER{
public:
	int type;
	int state;
	int frame;
};

//==============================================================
// �^�X�N�N���X
//==============================================================
class CElement{
friend class CCommonData;

public:
	// �^�X�N���X�g�ւ̃|�C���^
	CCommonData* m_CommonData;

	// �O��̃^�X�N�ւ̃|�C���^
	CElement	*m_Prev;
	CElement	*m_Next;

	// �^�X�N���X�g���w�肵�Ȃ�new�𖳌��ɂ���
	void* operator new(size_t t) {}

protected:
	// new�̏����F
	// new���Z�q���ŃR�[�������B
	static void* operator_new(size_t t, CCommonData* task_list);

public:
	int m_iObjectType;

	// �R���X�g���N�^���f�X�g���N�^
	CElement();
	virtual ~CElement();

	// ������new���Z�q
	void* operator new( size_t t, CCommonData *task_list );
	// delete���Z�q�̃I�[�o�[���[�h
	void operator delete( void* p );
	// �����t����new���Z�q�ŃG���[����������Ǝ����I�ɂ�΂��B
	// �����A�R�[�����ꂽ��v���O�����̏I�����Ă����������B
	void operator delete( void* p, CCommonData *task_list );

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �ړ�����
	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
	virtual bool ActionFinalize();
	virtual bool Interfere();						// ���蓮��@�q�b�g�m�F�Ȃ�
	virtual bool InterfereFinalize();				// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
//	virtual bool Result();							// ���蓮��@�q�b�g�m�F�Ȃ�
//	virtual bool FlameResult();						// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
	virtual bool Draw();							// �`�揈��
	virtual bool DrawFinalize();					// �`�揈���㏈���@Draw�̌�ɌĂ�

//	void SetSelfPointer(CElement** pElement);		// �Ȃ̃|�C���^�Ԃ�
//	void SetCommonDataPointer(CCommonData *pCommonData);		// ���݂�CCommonData�̈ʒu�擾
//	virtual BOOL GetTexRect(TEXRECT *spTexRect); 			// �`�敔���֐�

#if 0
	int m_iAttackPower, m_iDurability;
	TEXRECT m_TexRect;			// �`��p�̍\����
	ANIDATA m_AniData;
	RECT m_sHitRect;			// �Փ˔���p�Z�`
	CCommonData* m_pCommonData;
	CElement** m_ppSelf;
	UINT m_iAttackAtr, m_iDefenceAtr;

	virtual void Collision(int iObjectType, int iDamage);		// �Փˏ���
#endif

};


//==============================================================
// �^�X�N���X�g�N���X
//==============================================================
class CCommonData{
friend class CElement;

public:
	// �A�N�e�B�u�^�X�N���X�g�A�t���[�^�X�N���X�g
	CElement	*m_ActiveTask;
	CElement	*m_FreeTask;

	// �^�X�N�̍ő�T�C�Y�A�^�X�N�̍ő吔
	int m_MaxTaskSize;
	int	m_MaxNumTask;
	
	// �t���[�^�X�N�̐�
	volatile int m_NumFreeTask;

	// �m�ۂ����������Ԓn
	char *m_Buf;

public:
	// �R���X�g���N�^���f�X�g���N�^
	CCommonData( int max_task_size, int max_num_task );
	virtual ~CCommonData();
	
	// �^�X�N�̐�
	int GetNumFreeTask();// { return NumFreeTask; }
	int GetNumActiveTask();// { return MaxNumTask-NumFreeTask; }

	// �S�^�X�N�̏���
	void DeleteTask();
};
