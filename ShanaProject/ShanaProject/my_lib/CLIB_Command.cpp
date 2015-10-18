#include "CLIB_Input.h"
#include "CLIB_Command.h"

CCommandRefer::CCommandRefer()
{

}

void CCommand::setRefer( CCommandRefer *refer )
{
	m_Refer = refer ;
}

void  CCommand::setInput( CInput *input )
{
	m_Input = input ;
}

unsigned long CCommand::getStandardAction()
{
	return m_Standard ;
}

unsigned long CCommand::getSpecialAction()
{
	m_SpecialPoint = 32;
	for( ; m_SpecialPoint != 0 ; m_SpecialPoint-- )
	{
		if( m_Special & ( 1 << m_SpecialPoint ) ){
			return 1 << m_SpecialPoint;
		}
	}
	return 0;
}

void CCommand::updateInput( char playerNo )
{
	unsigned long oldStandard;
	unsigned long oldSpecial;

	unsigned long pad;
	char dir;

	// データ退避＆クリア
	oldStandard = m_Standard ;
	oldSpecial	= m_Special ;
	m_Standard	= 0;
	m_Special	= 0;

	// 向き取得
	dir = m_Refer->getDir();

	// 入力取得
	pad = m_Input->GetPadData( playerNo );

	// 入力なし系
	if( !( pad & PAD_MASK_DIR ) ){
		m_Standard |= COMMAND_NONE_DIR;
	}

	if( !( pad & PAD_MASK_BUTTON ) ){
		m_Standard |= COMMAND_NONE_ACTION;
	}

	// 上
	if( pad & PAD_UP ){
		if( oldStandard & COMMAND_UP ){
			m_Standard |= COMMAND_UP;
		}
		else{
			m_Standard |= COMMAND_MAKE_UP | COMMAND_UP ;
		}
	}
    
	// 下
	if( pad & PAD_DOWN ){
		if( oldStandard & COMMAND_DOWN ){
			m_Standard |= COMMAND_DOWN;
		}
		else{
			m_Standard |= COMMAND_MAKE_DOWN | COMMAND_DOWN ;
		}
	}

	// 前後（右入力）
	if( pad & PAD_RIGHT ){
		if( dir == DIRECTION_RIGHT ){
			if( oldStandard & COMMAND_FORWARD ){
				m_Standard |= COMMAND_FORWARD;
			}
			else{
				m_Standard |= COMMAND_MAKE_FORWARD | COMMAND_FORWARD ;
			}
		}
		else{
			if( oldStandard & COMMAND_BACK ){
				m_Standard |= COMMAND_BACK;
			}
			else{
				m_Standard |= COMMAND_MAKE_BACK | COMMAND_BACK ;
			}
		}
	}

	// 前後（左入力）
	if( pad & PAD_LEFT ){
		if( dir == DIRECTION_RIGHT ){
			if( oldStandard & COMMAND_BACK ){
				m_Standard |= COMMAND_BACK;
			}
			else{
				m_Standard |= COMMAND_MAKE_BACK | COMMAND_BACK ;
			}
		}
		else{
			if( oldStandard & COMMAND_FORWARD ){
				m_Standard |= COMMAND_FORWARD;
			}
			else{
				m_Standard |= COMMAND_MAKE_FORWARD | COMMAND_FORWARD ;
			}
		}
	}
	
	// ボタン入力１
	if( pad & ( PAD_BUTTON1 ) ){
		if( oldStandard & COMMAND_LOW ){
			m_Standard |= COMMAND_LOW;
		}
		else{
			m_Standard |= COMMAND_ATTACK_LOW | COMMAND_LOW ;
		}
	}

	// ボタン入力２
	if( pad & ( PAD_BUTTON2 ) ){
		if( oldStandard & COMMAND_MID ){
			m_Standard |= COMMAND_MID;
		}
		else{
			m_Standard |= COMMAND_ATTACK_MID | COMMAND_MID ;
		}
	}

	// ボタン入力３
	if( pad & ( PAD_BUTTON3 ) ){
		if( oldStandard & COMMAND_HIGH ){
			m_Standard |= COMMAND_HIGH;
		}
		else{
			m_Standard |= COMMAND_ATTACK_HIGH | COMMAND_HIGH;
		}
	}

	// ボタン入力４
	if( pad & ( PAD_BUTTON4 ) ){
		if( oldStandard & COMMAND_EX ){
			m_Standard |= COMMAND_EX;
		}
		else{
			m_Standard |= COMMAND_ATTACK_EX | COMMAND_EX;
		}
	}

	// ボタン入力５
	if( pad & ( PAD_BUTTON5 ) ){
		if( oldStandard & COMMAND_OPT1 ){
			m_Standard |= COMMAND_OPT1;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT1 | COMMAND_OPT1;
		}
	}

	// ボタン入力６
	if( pad & ( PAD_BUTTON6 ) ){
		if( oldStandard & COMMAND_OPT2 ){
			m_Standard |= COMMAND_OPT2;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT2 | COMMAND_OPT2;
		}
	}

	// ボタン入力７
	if( pad & ( PAD_BUTTON7 ) ){
		if( oldStandard & COMMAND_OPT3 ){
			m_Standard |= COMMAND_OPT3;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT3 | COMMAND_OPT3;
		}
	}

	// ボタン入力８
	if( pad & ( PAD_BUTTON8 ) ){
		if( oldStandard & COMMAND_OPT4 ){
			m_Standard |= COMMAND_OPT4;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT4 | COMMAND_OPT4;
		}
	}

}

/*
void CCommand::updateInput( char playerNo )
{
	unsigned long oldStandard;
	unsigned long oldSpecial;

	unsigned long pad[4];
	unsigned long padNo[11]
	unsigned long config[11]
	char dir;

	// データ退避＆クリア
	oldStandard = m_Standard ;
	oldSpecial	= m_Special ;
	m_Standard	= 0;
	m_Special	= 0;

	// 向き取得
	dir = m_Refer->getDir();

	// コンフィグデータ変換
	for( int i = 0 ; i < 4 ; i++ ){
		padNo[i] = m_ConfigData[i] / 100;
		config[i] = m_ConfigData[playerNo][i] % 100;
	}

	for( int i = 0 ; i < 6 ; i++ ){
		padNo[i+4] = m_ConfigData[i+4] / 100;
		config[i+4] = 1 << ( ( m_ConfigData[playerNo][i+4] % 100 );
	}

	// 入力取得
	for( int i = 0 ; i < 2 ; i++ ){
		pad[i] = m_Input->GetPadData( playerNo );
	}
	// 
}

*/
