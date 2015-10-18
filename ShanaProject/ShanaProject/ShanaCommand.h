#pragma once

#include "CLIB_Command.h"

typedef struct{
	int				m_Num;			// ���͐�
	int				m_TechNo;		// �Z�ԍ�
	int				m_ValidTime;	// �L������
	int				m_Priority;		// �D��x
	unsigned long	m_Data[20];		// ���̓f�[�^	
	unsigned long	m_Flag[20];		// �t���O
	unsigned long	m_Time[20];		// ����������
} StCommandSequence;

enum{
	ENUM_COMMAND_FORWARD	= 0,
	ENUM_COMMAND_BACK		,
	ENUM_COMMAND_UP			,
	ENUM_COMMAND_DOWN		,

	ENUM_COMMAND_LOW		,
	ENUM_COMMAND_MID		,
	ENUM_COMMAND_HIGH		,
	ENUM_COMMAND_EX			,
	ENUM_COMMAND_OPT1		,
	ENUM_COMMAND_OPT2		,
	ENUM_COMMAND_OPT3		,
	ENUM_COMMAND_OPT4
};

// �t���O�W
enum{
	ENUM_COMMAND_FLAG_DIR_EQUAL	= 0x00000001		// �����L�[���S��v
};

class CCommandManager : public CCommand{
protected:
	int						m_SizeHistory;			// �ߋ����̓o�b�t�@�T�C�Y
	unsigned long*			m_History;				// �ߋ����̓o�b�t�@
	unsigned long**			m_HoldTime;				// ���������͎���
	unsigned long			m_PassTime[20];			// �ߋ����͂���߂������͎���

	StCommandSequence		m_CommandData[10];		// �R�}���h����

	void					ReverseDir();			// ���͔��]
	char					m_OldDir;				// �������]�p
	unsigned long			m_DirMask;				// �������]�p

//	CCommandManager( );
public:
	static	unsigned long	m_StandardList[20];		// CCommand�񋓎q�Ƃ̊֘A�t��

	CCommandManager( );
	CCommandManager( int num_history );
	~CCommandManager();

	virtual void updateInput( char playerNo ) ;
	StCommandSequence* GetCommandSequence( int SequenceNo );
	void SetCommandSequence( int CharacterNo );
	char Judgement( int SequenceNo );
};
