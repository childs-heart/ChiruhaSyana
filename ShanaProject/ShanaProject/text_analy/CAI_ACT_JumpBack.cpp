#include "CAI_ACT_JumpBack.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// アクション
/////////////////////////////
int CACTJumpBack::Run()
{
	m_Target->SetAIInput( COMMAND_UP | COMMAND_BACK );

	return 0;
}
