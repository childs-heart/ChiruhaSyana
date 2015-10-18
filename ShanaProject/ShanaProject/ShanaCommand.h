#pragma once

#include "CLIB_Command.h"

typedef struct{
	int				m_Num;			// 入力数
	int				m_TechNo;		// 技番号
	int				m_ValidTime;	// 有効期限
	int				m_Priority;		// 優先度
	unsigned long	m_Data[20];		// 入力データ	
	unsigned long	m_Flag[20];		// フラグ
	unsigned long	m_Time[20];		// 長押し時間
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

// フラグ集
enum{
	ENUM_COMMAND_FLAG_DIR_EQUAL	= 0x00000001		// 方向キー完全一致
};

class CCommandManager : public CCommand{
protected:
	int						m_SizeHistory;			// 過去入力バッファサイズ
	unsigned long*			m_History;				// 過去入力バッファ
	unsigned long**			m_HoldTime;				// 長押し入力時間
	unsigned long			m_PassTime[20];			// 過去入力から過ぎた入力時間

	StCommandSequence		m_CommandData[10];		// コマンド時間

	void					ReverseDir();			// 入力反転
	char					m_OldDir;				// 向き反転用
	unsigned long			m_DirMask;				// 向き反転用

//	CCommandManager( );
public:
	static	unsigned long	m_StandardList[20];		// CCommand列挙子との関連付け

	CCommandManager( );
	CCommandManager( int num_history );
	~CCommandManager();

	virtual void updateInput( char playerNo ) ;
	StCommandSequence* GetCommandSequence( int SequenceNo );
	void SetCommandSequence( int CharacterNo );
	char Judgement( int SequenceNo );
};
