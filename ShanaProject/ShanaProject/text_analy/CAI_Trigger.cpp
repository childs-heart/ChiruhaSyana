#include "CAI_Trigger.h"
#include "CAI_TRI_Equal.h"
#include "CAI_TRI_Over.h"
#include "CAI_TRI_Under.h"
#include "CAI_TRI_And.h"
#include "CAI_TRI_Value.h"
#include "CAI_TRI_Test.h"
#include "CAI_TRI_Width.h"
#include "CAI_Command.h"
#include <string.h>
#include <stdlib.h>

/////////////////////////////
// Trigger�N���X
/////////////////////////////
CAITrigger::CAITrigger()
:MAX_SIZE(100){
	m_Term = 0;
	m_Value1 = 0;
	m_Value2 = 0;
	m_Operation = 0;
	m_LastOperation = 0;
	m_Size	= 0;
	for( int i = 0 ; i < MAX_SIZE ; i++ ){
		m_Data[i] = new char[32];
		memset( m_Data[i], 0, 32 );
	}
//	memset( m_Data, 0, 20*32 );
}

CAITrigger::~CAITrigger()
{
	for( int i = 0 ; i < m_Term ; i++ ){
		if( m_EquationTable[i] != 0 ){
			delete this->m_EquationTable[i];
		}
	}
	for( int i = 0 ; i < MAX_SIZE ; i++ ){
		delete m_Data[i] ;
	}
	m_Term = 0;
}

void CAITrigger::AddEquation( CAIEquation *equ )
{
	m_EquationTable[m_Term] = equ;
	m_Term++;
}

int	CAITrigger::Judge()
{
	if( m_LastOperation != 0 ){
		return m_LastOperation->GetValue();
	}
	else{
		return 0;
	}
}

void CAITrigger::Add( char * data )
{
	strcpy( m_Data[m_Size], data );
	m_Size++;
}

void CAITrigger::Analyze( )
{
	int arg;
	CAIEquation * tmp;

	arg = 0;
	while( arg < m_Size ){
		arg = Indent( arg, &tmp );
	}
}

int CAITrigger::Indent( int start, CAIEquation ** term )
{
	char * data;

	CAIEquation * tmp;
	CAIOperator * ope;
	tmp = 0;

	CAIEquation * value1 = 0;
	CAIEquation * value2 = 0;
	CAIOperator * operation = 0;
	CAIOperator * lastOperation = 0;

	while( start < m_Size ){
		data = m_Data[start];
		ope = 0;
		tmp = 0;
		start ++;


		// �A ���Z���W���b�W
		if( strcmp( data, "=") == 0 ){
			ope = new CTRIEqual();
		}
		else if( strcmp( data, "<" ) == 0){
			ope = new CTRIOver();
		}
		else if( strcmp( data, ">" ) == 0){
			ope = new CTRIUnder();
		}
		// ���Z���q�b�g������A�z��ɂɃZ�b�g
		if( ope != 0 ){
			AddEquation( ope );
			operation = ope ;
			*term = ope;
		}

		//�@�@ ����q�i�C���f���g�j����
		if( strcmp( data, "(" ) == 0 ){
			start = Indent( start, &tmp );
			if( ( operation == 0 ) && ( value1 != 0 ) ){
				ope = new CTRIAnd();
				operation = ope ;
			AddEquation( ope );
			*term = ope;
			}
			// &&�}��
		}
		else if( strcmp( data, ")" ) == 0 ){
			return start;
		}
		//�@�A �����A�����W���b�W
		else if( MakeEquation( data, &tmp ) ){
		}
		else if(
			( data[0] == '0' )
			|| ( atoi( data ) )
			){
			tmp = new CTRIValue( atoi(data) );
		}

		// �����A�������q�b�g������A�z��ɒǉ����Ӂi����/�E�Ӂj�ɃZ�b�g
		if( tmp != 0 ){
			if( value1 == 0 ){
				value1 = tmp ;
			}
			else if( ( value2 == 0 ) && ( operation == 0 )){
				return start-1;
			}
			else{
				value2 = tmp ;
			}
			AddEquation( tmp );
		}

		// ���ӂ���������牉�Z���ɃZ�b�g
		if( value2 != 0 )
		{
			operation->SetEquation( value1, value2 );
//			AddEquation( ope );
//			*term = ope;
			m_LastOperation = operation;
			//���̍��ӂ́A����̉��Z���ɂȂ�
			value1 = operation;
			value2 = 0;
			operation = 0;
		}
	}
	return start;
}


void CAITrigger::Analyze_( char * data )
{
	CAIEquation * tmp;
	CAIOperator * ope;
	tmp = 0;
	//�@�@ �����A�����W���b�W
	if( strcmp( data, "test" ) == 0 ){
		tmp = new CTRITest();
	}
	else if(
		  ( data[0] == '0' )
		  || ( atoi( data ) )
		){
        tmp = new CTRIValue( atoi(data) );
	}
	// �����A�������q�b�g������A�z��ɒǉ����Ӂi����/�E�Ӂj�ɃZ�b�g
	if( tmp != 0 ){
		if( m_Value1 == 0 ){
			m_Value1 = tmp ;
		}
		else{
			m_Value2 = tmp ;
		}
		AddEquation( tmp );
	}

	// ���ӂ���������牉�Z���ɃZ�b�g
	if( m_Value2 != 0 )
	{
		m_Operation->SetEquation( m_Value1, m_Value2 );
		m_LastOperation = m_Operation;
		//���̍��ӂ́A����̉��Z���ɂȂ�
		m_Value1 = m_Operation;
		m_Value2 = 0;
		m_Operation = 0;
	}

	// �A ���Z���W���b�W
	ope = 0;
	if( strcmp( data, "=") == 0 ){
		ope = new CTRIEqual();
	}
	// ���Z���q�b�g������A�z��ɂɃZ�b�g
	if( ope != 0 ){
		AddEquation( ope );
		m_Operation = ope ;
	}
}

bool CAITrigger::MakeEquation( char * data, CAIEquation **temp )
{
	if( strcmp( data, "test" ) == 0 ){
		*temp = new CTRITest();
		return true;
	}
}
