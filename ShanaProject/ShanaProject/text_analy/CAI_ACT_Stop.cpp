#include "CAI_ACT_Stop.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// アクション
/////////////////////////////
int CACTStop::Run()
{
	m_Target->SetAIInput( COMMAND_NONE );
	m_Target->SetAIInputSP( 0 );

	return 0;
}
