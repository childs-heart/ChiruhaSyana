#include "CAI_ACT_Back.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// アクション
/////////////////////////////
int CACTBack::Run()
{
	m_Target->SetAIInput( COMMAND_BACK );

	return 0;
}
