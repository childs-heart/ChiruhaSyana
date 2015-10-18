#include "CAI_CommandShana.h"
#include "CAI_TRI_Test.h"
#include "CAI_TRI_Equal.h"
#include "CAI_TRI_Value.h"
#include "CAI_TRI_And.h"
#include "ShanaProt.h"
#include <string.h>
#include <stdlib.h>

/////////////////////////////
// OperatorƒNƒ‰ƒX
/////////////////////////////
CAINumberShana::CAINumberShana( CNpcAIShana *target )
:CAINumber(),m_Target(target)
{
}

void CAINumberShana::SetTarget( CNpcAIShana *target )
{
	m_Target = target;
}