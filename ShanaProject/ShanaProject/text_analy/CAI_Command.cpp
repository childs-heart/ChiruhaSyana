#include "CAI_Command.h"
#include "CAI_TRI_Test.h"
#include "CAI_TRI_Equal.h"
#include "CAI_TRI_Value.h"
#include "CAI_TRI_And.h"
#include <string.h>
#include <stdlib.h>

/////////////////////////////
// OperatorƒNƒ‰ƒX
/////////////////////////////
CAIOperator::CAIOperator()
:m_Param1(0),m_Param2(0)
{
}

CAIOperator::CAIOperator( CAIEquation *param1,CAIEquation *param2 )
{
	SetEquation( param1 , param2 );
}

void CAIOperator::SetEquation( CAIEquation *param1,CAIEquation *param2 )
{
	m_Param1 = param1;
	m_Param2 = param2;
}
