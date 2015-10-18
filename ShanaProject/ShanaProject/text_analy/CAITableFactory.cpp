#include "CAITableFactory.h"
#include <string.h>
#include "CAI_Command.h"
#include "CAI_Table.h"

/*
テーブルファクトリーのしてること
ファイルから文字を取り出して、それをテーブルに渡す
実際にテーブルの中身を構築しているのは、テーブルクラスがやってる
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
			// 改行取り出し
			text[strlen(text)-1] = 0;
	
			// 解析
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
			// 改行取り出し
			text[strlen(text)-1] = 0;
	
			// 解析
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
	// 先頭・末尾に()をつけるかどうか
	GetWord( row, buf );
	if( ( buf[0] == '[' )
	  ||( buf[0] == '{' )
	  ||( buf[0] == ':' ) ){
		flag = false;
	}
	if( flag ){
		m_Table->Add( "(\0" );
	}
	// １ワード毎にテーブルセット
	while( (j = GetWord( &row[i], buf )) != 0 ){
		i+=j;
		m_Table->Add( buf );
		printf("%s\n",buf);
	}
	if( flag ){
		m_Table->Add( ")\0" );	
	}
}

// 戻り値　進んだ文字
int CAITableFactory::GetWord( char *data , char *store_word )
{
	int i = 0;
	int j = 0;
	char ch;

	store_word[j]=0;

	// 空白は省く
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
			// １文字目が↑だったら、２文字目に\0セット。
			// ' 'で来た場合、ここの条件は必ず偽。
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

// 戻り値　進んだ文字
CAITable *  CAITableFactory::GetTable()
{
	return m_Table;
}