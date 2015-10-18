#include "CAI_TRI_UNDER.h"

CTRIUnder::CTRIUnder( )
:CAIOperator( )
{
}

CTRIUnder::CTRIUnder( CAIEquation *param1, CAIEquation *param2)
:CAIOperator( param1, param2 )
{
}

int CTRIUnder::GetValue()
{
	if( m_Param1->GetValue() > m_Param2->GetValue() )
	{
		return 1;
	}
	return 0;
}
