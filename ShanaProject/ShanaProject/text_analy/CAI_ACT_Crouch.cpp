#include "CAI_ACT_DushForward.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// アクション
/////////////////////////////
int CACTDushForward::Run()
{

	m_Target->SetAIInput( COMMAND_FORWARD, 1 );

	return 0;
}
