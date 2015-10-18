#include "CAI_ACT_Forward.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
int CACTForward::Run()
{
	m_Target->SetAIInput( COMMAND_FORWARD );

	return 0;
}
