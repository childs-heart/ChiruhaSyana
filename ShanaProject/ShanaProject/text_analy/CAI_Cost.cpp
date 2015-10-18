#include "CAI_Cost.h"
#include <string.h>
#include <stdlib.h>
/////////////////////////////
// ÉRÉXÉg
/////////////////////////////
CAICost::CAICost()
{
	m_Value = 50;
}

void CAICost::Add( char *data )
{
	if( ( data[0] == '0' )
		|| (atoi(data))){
		m_Value = atoi(data);
	}
}

int CAICost::GetCost()
{
	return m_Value;
}

