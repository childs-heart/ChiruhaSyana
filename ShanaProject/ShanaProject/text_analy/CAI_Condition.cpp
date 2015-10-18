#include "CAI_Condition.h"
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

/////////////////////////////
// AIÉeÅ[ÉuÉã
/////////////////////////////
CAICondition::CAICondition()
{
}

void CAICondition::SetCondition(char * name, unsigned short tableNo )
{
	strcpy( m_ConditionName , name );
	m_TableNo = tableNo;
}

char* CAICondition::GetConditionName()
{
	return m_ConditionName ;
}

unsigned short CAICondition::GetConditionNo()
{
	return m_TableNo ;
}

CAICondition::~CAICondition()
{
}

