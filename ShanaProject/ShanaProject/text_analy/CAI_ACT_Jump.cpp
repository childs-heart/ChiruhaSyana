#include "CAI_ACT_Jump.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// アクション
/////////////////////////////
int CACTJump::Run()
{
	m_Target->SetAIInput( COMMAND_UP );

	return 0;
}
