#include "CAI_ACT_JumpForward.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// �A�N�V����
/////////////////////////////
int CACTJumpForward::Run()
{
	m_Target->SetAIInput( COMMAND_UP | COMMAND_FORWARD );

	return 0;
}
