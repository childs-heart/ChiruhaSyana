#include "ShanaCommand.h"

unsigned long CCommandManager::m_StandardList[20]= {COMMAND_FORWARD,
													COMMAND_BACK,
													COMMAND_UP,
													COMMAND_DOWN,
													COMMAND_LOW,
													COMMAND_MID,
													COMMAND_HIGH,
													COMMAND_EX,
													COMMAND_OPT1,
													COMMAND_OPT2,
													COMMAND_OPT3,
													COMMAND_OPT4};

CCommandManager::CCommandManager( )
{
	int num_history = 60 ;
	m_SizeHistory	= num_history ;
	m_History		= new unsigned long[num_history];

	m_HoldTime		= new unsigned long*[num_history];
	for( int i = 0 ; i < num_history ; i++ ){
		m_HoldTime[ i ] = new unsigned long[20];
	}
	m_DirMask		= 0xFFFFFFFF - (COMMAND_MAKE_BACK | COMMAND_MAKE_FORWARD | COMMAND_FORWARD | COMMAND_BACK) ;
}

CCommandManager::CCommandManager( int num_history )
{
	m_SizeHistory	= num_history ;
	m_History		= new unsigned long[num_history];

	m_HoldTime		= new unsigned long*[num_history];
	for( int i = 0 ; i < num_history ; i++ ){
		m_HoldTime[ i ] = new unsigned long[20];
	}

}

CCommandManager::~CCommandManager( )
{
	for( int i = 0 ; i < m_SizeHistory ; i++ ){
		delete	[]m_HoldTime[i];
	}
	delete []m_HoldTime;

	delete []m_History;
}

void CCommandManager::SetCommandSequence( int chara_no )
{
	switch( chara_no ){
		case 0:
			m_CommandData[0].m_Num		= 3;
			m_CommandData[0].m_TechNo	= 1;
			m_CommandData[0].m_Priority = 1;
			m_CommandData[0].m_ValidTime= 16;
			m_CommandData[0].m_Data[0]	= COMMAND_MAKE_FORWARD;
			m_CommandData[0].m_Flag[0]	= 0;
			m_CommandData[0].m_Time[0]	= 0;
			m_CommandData[0].m_Data[1]	= 0x00000002;
			m_CommandData[0].m_Flag[1]	= 0;
			m_CommandData[0].m_Time[1]	= 0;
			m_CommandData[0].m_Data[2]	= COMMAND_MAKE_FORWARD;
			m_CommandData[0].m_Flag[2]	= 0;
			m_CommandData[0].m_Time[2]	= 0;

			m_CommandData[1].m_Num		= 3;
			m_CommandData[1].m_TechNo	= 2;
			m_CommandData[1].m_Priority = 1;
			m_CommandData[1].m_ValidTime= 16;
			m_CommandData[1].m_Data[0]	= COMMAND_MAKE_BACK;
			m_CommandData[1].m_Flag[0]	= 0;
			m_CommandData[1].m_Time[0]	= 0;
			m_CommandData[1].m_Data[1]	= 0x00000002;
			m_CommandData[1].m_Flag[1]	= 0;
			m_CommandData[1].m_Time[1]	= 0;
			m_CommandData[1].m_Data[2]	= COMMAND_MAKE_BACK;
			m_CommandData[1].m_Flag[2]	= 0;
			m_CommandData[1].m_Time[2]	= 0;

			m_CommandData[2].m_Num		= 3;
			m_CommandData[2].m_TechNo	= 4;
			m_CommandData[2].m_Priority = 2;
			m_CommandData[2].m_ValidTime= 16;
			m_CommandData[2].m_Data[0]	= COMMAND_DOWN ;
			m_CommandData[2].m_Flag[0]	= ENUM_COMMAND_FLAG_DIR_EQUAL;
			m_CommandData[2].m_Time[0]	= 0;
			m_CommandData[2].m_Data[1]	= COMMAND_DOWN | COMMAND_MAKE_FORWARD;
			m_CommandData[2].m_Flag[1]	= 0;
			m_CommandData[2].m_Time[1]	= 0;
			m_CommandData[2].m_Data[2]	= COMMAND_FORWARD;
			m_CommandData[2].m_Flag[2]	= 0;
			m_CommandData[2].m_Time[2]	= 0;
			m_CommandData[2].m_Data[2]	= COMMAND_FORWARD | COMMAND_ATTACK_LOW;
			m_CommandData[2].m_Flag[2]	= ENUM_COMMAND_FLAG_DIR_EQUAL;
			m_CommandData[2].m_Time[2]	= 0;

			m_CommandData[3].m_Num		= 1;
			m_CommandData[3].m_TechNo	= 8;
			m_CommandData[3].m_Priority = 2;
			m_CommandData[3].m_ValidTime= 2;
			m_CommandData[3].m_Data[0]	= COMMAND_ATTACK_LOW | COMMAND_ATTACK_MID ;
			m_CommandData[3].m_Flag[0]	= 0;
			m_CommandData[3].m_Time[0]	= 0;

			// 昇竜_1
			m_CommandData[4].m_Num		= 3;
			m_CommandData[4].m_TechNo	= 16;
			m_CommandData[4].m_Priority = 1;
			m_CommandData[4].m_ValidTime= 16;
			m_CommandData[4].m_Data[0]	= COMMAND_FORWARD;
			m_CommandData[4].m_Flag[0]	= ENUM_COMMAND_FLAG_DIR_EQUAL;
			m_CommandData[4].m_Time[0]	= 0;
//			m_CommandData[4].m_Data[1]	= COMMAND_MAKE_DOWN | COMMAND_DOWN ;
			m_CommandData[4].m_Data[1]	= COMMAND_DOWN ;
			m_CommandData[4].m_Flag[1]	= ENUM_COMMAND_FLAG_DIR_EQUAL;
			m_CommandData[4].m_Time[1]	= 0;
			m_CommandData[4].m_Data[2]	= COMMAND_DOWN | COMMAND_FORWARD | COMMAND_ATTACK_LOW;
			m_CommandData[4].m_Flag[2]	= 0;
			m_CommandData[4].m_Time[2]	= 0;
			// 昇竜_2
			m_CommandData[5].m_Num		= 4;
			m_CommandData[5].m_TechNo	= 16;
			m_CommandData[5].m_Priority = 1;
			m_CommandData[5].m_ValidTime= 16;
			m_CommandData[5].m_Data[0]	= COMMAND_FORWARD;
			m_CommandData[5].m_Flag[0]	= ENUM_COMMAND_FLAG_DIR_EQUAL;
			m_CommandData[5].m_Time[0]	= 0;
//			m_CommandData[5].m_Data[1]	= COMMAND_MAKE_DOWN | COMMAND_DOWN ;
			m_CommandData[5].m_Data[1]	= COMMAND_DOWN ;
			m_CommandData[5].m_Flag[1]	= ENUM_COMMAND_FLAG_DIR_EQUAL;
			m_CommandData[5].m_Time[1]	= 0;
			m_CommandData[5].m_Data[2]	= COMMAND_DOWN | COMMAND_FORWARD ;
			m_CommandData[5].m_Flag[2]	= 0;
			m_CommandData[5].m_Time[2]	= 0;
			m_CommandData[5].m_Data[3]	= COMMAND_FORWARD | COMMAND_ATTACK_LOW;
			m_CommandData[5].m_Flag[3]	= 0;
			m_CommandData[5].m_Time[3]	= 0;
//			m_CommandData[4].m_Data[2]	= COMMAND_FORWARD | COMMAND_ATTACK_LOW;
//			m_CommandData[4].m_Flag[2]	= ENUM_COMMAND_FLAG_DIR_EQUAL;
//			m_CommandData[4].m_Time[2]	= 0;

			break;
	}

}

void CCommandManager::updateInput( char playerNo )
{
	int i,j ;
	// 親クラスの関数を呼ぶ
	CCommand::updateInput( playerNo );

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

	m_Special = Judgement( 0 ) * m_CommandData[0].m_TechNo ;;
	m_Special |= Judgement( 1 ) * m_CommandData[1].m_TechNo ;
	m_Special |= Judgement( 2 ) * m_CommandData[2].m_TechNo ;
	m_Special |= Judgement( 3 ) * m_CommandData[3].m_TechNo ;
	m_Special |= Judgement( 4 ) * m_CommandData[4].m_TechNo ;
	m_Special |= Judgement( 5 ) * m_CommandData[5].m_TechNo ;

}

char CCommandManager::Judgement( int SequenceNo )
{	
	// 中身ない場合は即リターン
	if(	(m_CommandData[SequenceNo].m_Data[m_CommandData[SequenceNo].m_Num-1] & m_History[0]) == 0 ){
		return 0;
	}

	int i = m_CommandData[SequenceNo].m_ValidTime;
	int idx = 0;
//	int his = 1;
	bool res = false;
	while( i >= 0 ){
		res = false;
		if( m_CommandData[SequenceNo].m_Flag[idx] == ENUM_COMMAND_FLAG_DIR_EQUAL ){
			res = (( (m_CommandData[SequenceNo].m_Data[idx] | COMMAND_MASK_DIR) & m_History[i] ) == m_CommandData[SequenceNo].m_Data[idx]) ;
		}
		else{
			res = (( m_CommandData[SequenceNo].m_Data[idx] & m_History[i] ) == m_CommandData[SequenceNo].m_Data[idx]) ;
		}
		if( res ){
			idx++;
			if( idx >= m_CommandData[SequenceNo].m_Num ){
				return 1;
			}
		}
		i--;
	}
	return 0;
}

void CCommandManager::ReverseDir()
{
	unsigned long tmp; 

	for( int i = m_SizeHistory - 1 ; i > 0 ; i-- ){
		tmp = 0;

		if( m_History[i] & COMMAND_MAKE_BACK ){
			tmp |= COMMAND_MAKE_FORWARD ;
		}
		if( m_History[i] & COMMAND_MAKE_FORWARD ){
			tmp |= COMMAND_MAKE_BACK ;
		}
		if( m_History[i] & COMMAND_BACK ){
			tmp |= COMMAND_FORWARD ;
		}
		if( m_History[i] & COMMAND_FORWARD ){
			tmp |= COMMAND_MAKE_BACK ;
		}
		m_History[i] = ( m_History[i] & m_DirMask ) | tmp ;
	}
}
