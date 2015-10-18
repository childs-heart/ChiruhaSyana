#include "CAI_Trigger_Shana.h"
#include "CAI_TRI_Equal.h"
#include "CAI_TRI_And.h"
#include "CAI_TRI_Value.h"
#include "CAI_TRI_Test.h"
#include "CAI_TRI_Width.h"
#include "CAI_Command.h"
#include <string.h>
#include <stdlib.h>

/////////////////////////////
// TriggerƒNƒ‰ƒX
/////////////////////////////
CAITriggerShana::CAITriggerShana( )
:CAITrigger()
{
}

CAITriggerShana::CAITriggerShana( CNpcAIShana *target )
:CAITrigger(), m_Target(target)
{
}

CAITriggerShana::~CAITriggerShana()
{

}

void CAITriggerShana::SetTarget( CNpcAIShana* target )
{
	m_Target = target;
}

bool CAITriggerShana::MakeEquation( char * data, CAIEquation **temp )
{
	CAINumberShana* tri;
	if( strcmp( data, "test" ) == 0 ){
		*temp = new CTRITest();
		return true;
	}
	else if( strcmp( data, "width" ) == 0 ){
		*temp = new CTRIWidth(m_Target);
		tri = (CAINumberShana*)*temp;
		return true;
	}
	return false;

}
