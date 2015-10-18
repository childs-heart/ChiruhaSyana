#include <string.h>
#include "CAI_Command.h"
#include "CAI_Table_Shana.h"
#include "CAITableFactoryShana.h"

/*
�e�[�u���t�@�N�g���[�̂��Ă邱��
�t�@�C�����當�������o���āA������e�[�u���ɓn��
���ۂɃe�[�u���̒��g���\�z���Ă���̂́A�e�[�u���N���X������Ă�
*/
void CAITableFactoryShana::ReadText()
{
	m_Table = new CAITableShana();
	m_Table->SetUp();
	m_File = fopen("test.txt","rt");

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

void CAITableFactoryShana::ReadText( CAITable* table )
{
	m_File = fopen("test.txt","rt");
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
