#pragma once

#include "CLIB_Input.h"

enum{
	// 基本アクション
	COMMAND_NONE		= 0x00000003,
	COMMAND_NONE_ACTION	= 0x00000001,
	COMMAND_NONE_DIR	= 0x00000002,

	COMMAND_MASK_DIR	= 0x0000FF00,

	COMMAND_FORWARD		= 0x00000100,
	COMMAND_BACK		= 0x00000200,
	COMMAND_UP			= 0x00000400,
	COMMAND_DOWN		= 0x00000800,

	COMMAND_MAKE_FORWARD= 0x00001000,
	COMMAND_MAKE_BACK	= 0x00002000,
	COMMAND_MAKE_UP		= 0x00004000,
	COMMAND_MAKE_DOWN	= 0x00008000,

	COMMAND_LOW			= 0x00010000,
	COMMAND_MID			= 0x00020000,
	COMMAND_HIGH		= 0x00040000,
	COMMAND_EX			= 0x00080000,
	COMMAND_OPT1		= 0x00100000,
	COMMAND_OPT2		= 0x00200000,
	COMMAND_OPT3		= 0x00400000,
	COMMAND_OPT4		= 0x00800000,

	COMMAND_ATTACK_LOW	= 0x01000000,
	COMMAND_ATTACK_MID	= 0x02000000,
	COMMAND_ATTACK_HIGH	= 0x04000000,
	COMMAND_ATTACK_EX	= 0x08000000,
	COMMAND_ATTACK_OPT1	= 0x10000000,
	COMMAND_ATTACK_OPT2	= 0x20000000,
	COMMAND_ATTACK_OPT3	= 0x40000000,
	COMMAND_ATTACK_OPT4	= 0x80000000,

	// 拡張アクション
	COMMAND_THREW		= 0x00000001,
	COMMAND_DASH_FORWARD= 0x00000010,
	COMMAND_DASH_BACK	= 0x00000020,

	COMMAND_SPECIAL_A	= 0x00010000,
	COMMAND_SPECIAL_B	= 0x00020000,
	COMMAND_SPECIAL_C	= 0x00040000,
	COMMAND_SPECIAL_D	= 0x00080000,
	COMMAND_SPECIAL_E	= 0x00100000,

	
};

enum DIRECTION{
	DIRECTION_RIGHT	= -1,
	DIRECTION_LEFT	= 1
};

class CCommandRefer{
public:
	CCommandRefer();

	virtual char getDir() = 0 ;
private:
	
};

class CCommand{
public:
//	CCommand();

	void setInput( CInput *input );
	void setRefer( CCommandRefer *refer );

	unsigned long getStandardAction() ;
	unsigned long getSpecialAction() ;

	virtual void updateInput( char playerNo );

private:
	CInput *m_Input;
	int		m_SpecialPoint;

protected:
	CCommandRefer	*m_Refer;
	unsigned long m_Standard;
	unsigned long m_Special;

};
