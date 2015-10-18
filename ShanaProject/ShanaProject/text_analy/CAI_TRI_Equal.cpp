#include "CAI_TRI_Equal.h"

CTRIEqual::CTRIEqual( )
:CAIOperator( )
{
}

CTRIEqual::CTRIEqual( CAIEquation *param1, CAIEquation *param2)
:CAIOperator( param1, param2 )
{
}

int CTRIEqual::GetValue()
{
	if( m_Param1->GetValue() == m_Param2->GetValue() )
	{
		return 1;
	}
	return 0;
}
