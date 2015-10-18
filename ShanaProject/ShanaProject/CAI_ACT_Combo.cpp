#include "CAI_ACT_Combo.h"
#include "CAI_Combo.h"
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include "ShanaProt.h"

/////////////////////////////
// コンボ
/////////////////////////////
CACTCombo::CACTCombo()
{
	m_Type = 0;
}

void CACTCombo::Add( char * data )
{
	char * sep;
	int	subType = m_Type ;
	int i = 0;
	int j = 0;
	const char derimit[] = ",";
	
	switch( data[0] )
	{
		case '(':
		case ')':
		case '=':
			return;
			break;
	}

	if( strncmp( data, "name" , 4 ) == 0){
		m_Type = 1;
	}
	else if( strncmp( data, "command" , 7 ) == 0){
		m_Type = 2;
	}
	else if( strncmp( data, "time" , 4 ) == 0){
		m_Type = 3;
	}
	if( ( m_Type == subType ) && ( m_Type != 0 ) )
	{
		switch( m_Type )
		{
		case 1:
			strcpy( m_Name, data ) ;
		break;

		case 2:
			// 文字列を,区切り
			sep = strtok( data, derimit );
			do{
				// 一区切り取り出し
				// スペース取り
				Strip( sep );
				j = 0;
				m_Command[i] = 0;
				// そこからコマンドに変換
				while( sep[j] != 0 )
				{
					m_Time[i] = atoi( sep );
					if( m_Time[i] > 0 )
					{
						int k = 1;
						while( m_Time[i] > (k*10) ){
							k++;
						}
                        j += k;
					}
					else
					{
						m_Time[i] = 1; // default
					}
					switch( sep[j] )
					{
						case 'U':
							m_Command[i] |= COMMAND_UP ;
						break;
						case 'D':
							m_Command[i] |= COMMAND_DOWN ;
						break;
						case 'F':
							m_Command[i] |= COMMAND_FORWARD ;
						break;
						case 'B':
							m_Command[i] |= COMMAND_BACK ;
						break;
						case 'a':
							m_Command[i] |= COMMAND_LOW ;
						break;
						case 'b':
							m_Command[i] |= COMMAND_MID ;
						break;
						case 'c':
							m_Command[i] |= COMMAND_HIGH;
						break;
						case 'd':
							m_Command[i] |= COMMAND_EX;
						break;
					}
					j++;
				}
				i++;
			}while( sep = strtok( NULL, derimit ) );
		break;

		case 3:
			m_Time[i] = atoi( data );
		break;
		}
	}
}

void CACTCombo::Strip( char * data ) 
{
	int len = strlen( data );
	for( int i = 0 ; i < len ; i++ )
	{
		while( data[i] == ' ')
		{
			for( int j = i ; j < len-1 ; j++ )
			{
				data[j] = data[j+1];
				len--;
			}
		}
	}
}

CACTCombo::~CACTCombo()
{
}

void CACTCombo::SerchCombo( char* name, CAICombo* comboList  ) 
{
	int i = 0;
	while( comboList[i].m_Name ){
		if( strcmp( name, comboList[i].m_Name ) == 0){
			this->m_Combo = &comboList[i] ;
			break;
		}
		i++;
	}
}
