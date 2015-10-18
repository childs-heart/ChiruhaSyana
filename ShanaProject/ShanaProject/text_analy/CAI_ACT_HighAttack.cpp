#include "CAI_ACT_HighAttack.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
int CACTHighAttack::Run()
{
	m_Target->SetAIInput( COMMAND_ATTACK_HIGH );

	return 0;
}
