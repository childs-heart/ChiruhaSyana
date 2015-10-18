#include "CAITableFactory.h"
#include <string.h>
#include "CAI_Command.h"
#include "CAI_Table.h"

/*
�e�[�u���t�@�N�g���[�̂��Ă邱��
�t�@�C�����當�������o���āA������e�[�u���ɓn��
���ۂɃe�[�u���̒��g���\�z���Ă���̂́A�e�[�u���N���X������Ă�
*/
void CAITableFactory::ReadText()
{
	m_Table = new CAITable();
	m_File = fopen("trigger.txt","rt");

	char	text[256];
	while( !feof( m_File ) ){
		text[0]='\0';
		fgets( text, 256, m_File );
		if( strlen(text) != 0 ){
			// ���s���o��
			text[strlen(text)-1] = 0;
	
			// ���
			AnalyzeRow( text );

		}
	}
//	m_Table->Analyze();
//	printf("--judge--%d\n",m_Table->Judge());
	m_Table->AddEnd( );	
	fclose( m_File );
}

void CAITableFactory::ReadText( CAITable* table )
{
	m_File = fopen("trigger.txt","rt");
	m_Table = table;

	char	text[256];
	while( !feof( m_File ) ){
		text[0]='\0';
		fgets( text, 256, m_File );
		if( strlen(text) != 0 ){
			// ���s���o��
			text[strlen(text)-1] = 0;
	
			// ���
			AnalyzeRow( text );

		}
	}
//	m_Table->Analyze();
//	printf("--judge--%d\n",m_Table->Judge());
	m_Table->AddEnd( );	
	fclose( m_File );
}

void CAITableFactory::AnalyzeWord( char *word )
{
}

void CAITableFactory::AnalyzeRow( char *row )
{
	char buf[1024];

	int i = 0;
	int j = 0;
	bool flag = true;
	// �擪�E������()�����邩�ǂ���
	GetWord( row, buf );
	if( ( buf[0] == '[' )
	  ||( buf[0] == '{' )
	  ||( buf[0] == ':' ) ){
		flag = false;
	}
	if( flag ){
		m_Table->Add( "(\0" );
	}
	// �P���[�h���Ƀe�[�u���Z�b�g
	while( (j = GetWord( &row[i], buf )) != 0 ){
		i+=j;
		m_Table->Add( buf );
		printf("%s\n",buf);
	}
	if( flag ){
		m_Table->Add( ")\0" );	
	}
}

// �߂�l�@�i�񂾕���
int CAITableFactory::GetWord( char *data , char *store_word )
{
	int i = 0;
	int j = 0;
	char ch;

	store_word[j]=0;

	// �󔒂͏Ȃ�
	while( data[i] ==' ' ){
		i++;
	}
	for( ; i < strlen( data ) ; i++,j++ ){
		ch = data[i];
		store_word[j] = ch;
		if( ( ch == ' ' )
			||( ch == '=' )
			||( ch == '[' )
			||( ch == ']' )
			||( ch == '{' )
			||( ch == '}' )
			){
			// �P�����ڂ�����������A�Q�����ڂ�\0�Z�b�g�B
			// ' '�ŗ����ꍇ�A�����̏����͕K���U�B
			if( j == 0 ){
				i++;
				j++;
			}
			store_word[j]=0;
			return i;
		}
	}
	if( j == 0 ){
		j++;
	}
	store_word[j]=0;
	return i;
}

// �߂�l�@�i�񂾕���
CAITable *  CAITableFactory::GetTable()
{
	return m_Table;
}