#include "CAI_ACT_MidAttack.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
int CACTMidAttack::Run()
{
	m_Target->SetAIInput( COMMAND_ATTACK_MID );

	return 0;
}
