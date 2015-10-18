#include "CAI_TRI_OVER.h"

CTRIOver::CTRIOver( )
:CAIOperator( )
{
}

CTRIOver::CTRIOver( CAIEquation *param1, CAIEquation *param2)
:CAIOperator( param1, param2 )
{
}

int CTRIOver::GetValue()
{
	if( m_Param1->GetValue() < m_Param2->GetValue() )
	{
		return 1;
	}
	return 0;
}
