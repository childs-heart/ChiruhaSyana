#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;
class CInput;
class CModeBattle;
class CDataBattleMenu;
class CAITableShana;
class CAIAction;
class CNpcCommand;
class CAICombo;

#include "CLIB_Sprite.h"
#include "CLIB_Command.h"
class CAIRunningAction
{
public:
	CAIRunningAction();
	void SetCombo( CAICombo* act );
	void Run();

	char  m_Type;
	short m_Time[10];
	int	  m_Command[10];
	char m_Name[32];

};

class CNpcAIShana: public CSprite , public CCommandRefer{
protected:
	CInput*			m_Input;		// �C���v�b�g�N���X
	CNpcCommand*	m_Command;		// �R�}���h�N���X
	CModeBattle*	m_Battle ;
	CShanaProt*		m_Target ;
	CAITableShana*	m_AITable ;
	CAIAction*		m_AIAction;

	CAIRunningAction	m_RunningAction;
	unsigned long	m_AIInput;

public:
	int				m_JudgeWaitTime;
	void SetAIInput( unsigned int nrInput, unsigned int spInput = 0 );
	void SetAIInputSP( unsigned int Input );
	unsigned long	m_PadTemp[5];

	CNpcAIShana( CResBattle *game , CModeBattle *battle_mode , CAITableShana *ai, CShanaProt *target);

//	void	Setup();
	/************/
	/* �I�[�o�[���C�g�Q
	/************/
	virtual bool Event();							// 1.���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// 2.�ړ������i�W�����v�~�����j
//	virtual bool Action();							// 3.���́i�C�x���g�j���e����̓�����{
//	virtual bool ActionFinalize();					// 4.���́i�C�x���g�j���e����̓�����{
//	virtual bool Interfere();						// 5.���蓮��@�q�b�g�m�F�Ȃ�
	virtual bool InterfereFinalize();				// 6.�ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	virtual bool Draw( CD3DDraw *draw );			// 7.�`�揈�����C���@��{��������Ă�
//	virtual bool Draw();							// 8.�`�揈��
	virtual bool DrawFinalize();					// 9.�`�揈���㏈���@Draw�̌�ɌĂ�

	/******************* ���d�p���錾 *********************************************/
	char getDir();		// CommandRefer����̏������z�֐�

protected:
	virtual ~CNpcAIShana();
	
};
