#include "NpcCommand.h"

void CNpcCommand::updateInput( char playerNo )
{
	int i,j ;

	if( m_Refer->getDir() != m_OldDir ){
		ReverseDir();
	}
	m_OldDir = m_Refer->getDir();
	// ヒストリー作成
	// バッファオーバーした長押し時間カウント
	for( i = 0 ; i <= ENUM_COMMAND_OPT4 ; i++ ){
		if( m_CommandData[m_SizeHistory - 1].m_Data[i] & m_StandardList[i] ){
			m_PassTime[ i ]++;
		}
		else{
			m_PassTime[ i ] = 0;
		}
		m_HoldTime[m_SizeHistory - 1][i] = m_PassTime[ i ];
	}

	// バッファシフト
	// 長押し時間カウント
	for( i = m_SizeHistory - 1 ; i > 0 ; i-- ){
		m_History[i] = m_History[ i-1 ];
		for( j = 0 ; j <= ENUM_COMMAND_OPT4 ; j++ ){
			if( m_CommandData[ i ].m_Data[ j ] & m_StandardList[ j ] ){
				m_HoldTime[ i ][ j ]++;
			}
			else{
				m_HoldTime[ i ][ j ] = 0;
			}
		}
	}

	// 最新のデータをセット
	m_History[0] = m_Standard ;

	m_Special = Judgement( 0 ) * m_CommandData[0].m_TechNo ;
	m_Special |= Judgement( 1 ) * m_CommandData[1].m_TechNo ;
	m_Special |= Judgement( 2 ) * m_CommandData[2].m_TechNo ;
	m_Special |= Judgement( 3 ) * m_CommandData[3].m_TechNo ;
	m_Special |= Judgement( 4 ) * m_CommandData[4].m_TechNo ;
	m_Special |= Judgement( 5 ) * m_CommandData[4].m_TechNo ;
}

void CNpcCommand::setSpecial( unsigned int spe )
{
	m_Special = spe;
}

void CNpcCommand::setStandard( unsigned int stnd )
{
	unsigned long oldStandard;

	// データ退避＆クリア
	oldStandard = m_Standard ;
	m_Standard	= 0;

	// 上
	if( stnd & COMMAND_UP ){
		if( oldStandard & COMMAND_UP ){
			m_Standard |= COMMAND_UP;
		}
		else{
			m_Standard |= COMMAND_MAKE_UP | COMMAND_UP ;
		}
	}
    
	// 下
	if( stnd & COMMAND_DOWN ){
		if( oldStandard & COMMAND_DOWN ){
			m_Standard |= COMMAND_DOWN;
		}
		else{
			m_Standard |= COMMAND_MAKE_DOWN | COMMAND_DOWN ;
		}
	}

	// 前後（右入力）
	if( stnd & COMMAND_FORWARD ){
		if( oldStandard & COMMAND_FORWARD ){
			m_Standard |= COMMAND_FORWARD;
		}
		else{
			m_Standard |= COMMAND_MAKE_FORWARD | COMMAND_FORWARD ;
		}
	}

	// 前後（左入力）
	if( stnd & COMMAND_BACK ){
		if( oldStandard & COMMAND_BACK ){
			m_Standard |= COMMAND_BACK;
		}
		else{
			m_Standard |= COMMAND_MAKE_BACK | COMMAND_BACK ;
		}
	}
	
	// ボタン入力１
	if( stnd & ( COMMAND_LOW ) ){
		if( oldStandard & COMMAND_LOW ){
			m_Standard |= COMMAND_LOW;
		}
		else{
			m_Standard |= COMMAND_ATTACK_LOW | COMMAND_LOW ;
		}
	}

	// ボタン入力２
	if( stnd & ( COMMAND_MID ) ){
		if( oldStandard & COMMAND_MID ){
			m_Standard |= COMMAND_MID;
		}
		else{
			m_Standard |= COMMAND_ATTACK_MID | COMMAND_MID ;
		}
	}

	// ボタン入力３
	if( stnd & ( COMMAND_HIGH ) ){
		if( oldStandard & COMMAND_HIGH ){
			m_Standard |= COMMAND_HIGH;
		}
		else{
			m_Standard |= COMMAND_ATTACK_HIGH | COMMAND_HIGH;
		}
	}

	// ボタン入力４
	if( stnd & ( COMMAND_EX ) ){
		if( oldStandard & COMMAND_EX ){
			m_Standard |= COMMAND_EX;
		}
		else{
			m_Standard |= COMMAND_ATTACK_EX | COMMAND_EX;
		}
	}

	// ボタン入力５
	if( stnd & ( COMMAND_OPT1 ) ){
		if( oldStandard & COMMAND_OPT1 ){
			m_Standard |= COMMAND_OPT1;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT1 | COMMAND_OPT1;
		}
	}

	// ボタン入力６
	if( stnd & ( COMMAND_OPT2 ) ){
		if( oldStandard & COMMAND_OPT2 ){
			m_Standard |= COMMAND_OPT2;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT2 | COMMAND_OPT2;
		}
	}

	// ボタン入力７
	if( stnd & ( COMMAND_OPT3 ) ){
		if( oldStandard & COMMAND_OPT3 ){
			m_Standard |= COMMAND_OPT3;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT3 | COMMAND_OPT3;
		}
	}

	// ボタン入力８
	if( stnd & ( COMMAND_OPT4 ) ){
		if( oldStandard & COMMAND_OPT4 ){
			m_Standard |= COMMAND_OPT4;
		}
		else{
			m_Standard |= COMMAND_ATTACK_OPT4 | COMMAND_OPT4;
		}
	}
}
