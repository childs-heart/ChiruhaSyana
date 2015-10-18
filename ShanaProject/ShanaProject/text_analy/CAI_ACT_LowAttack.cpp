#include "CAI_ACT_LowAttack.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
int CACTLowAttack::Run()
{
	m_Target->SetAIInput( COMMAND_ATTACK_LOW );

	return 0;
}
