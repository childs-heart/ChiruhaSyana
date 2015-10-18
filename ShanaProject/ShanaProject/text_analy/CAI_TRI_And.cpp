#include "CAI_TRI_And.h"

CTRIAnd::CTRIAnd( )
:CAIOperator( )
{
}

CTRIAnd::CTRIAnd( CAIEquation *param1, CAIEquation *param2)
:CAIOperator( param1, param2 )
{
}

int CTRIAnd::GetValue()
{
	if( m_Param1->GetValue() && m_Param2->GetValue() )
	{
		return 1;
	}
	return 0;
}
