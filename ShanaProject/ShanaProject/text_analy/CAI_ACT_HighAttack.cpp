#include "CAI_ACT_HighAttack.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// �A�N�V����
/////////////////////////////
int CACTHighAttack::Run()
{
	m_Target->SetAIInput( COMMAND_ATTACK_HIGH );

	return 0;
}
