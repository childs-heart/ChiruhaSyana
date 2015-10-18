#include "CAI_Action.h"
#include "CAI_ACT_NotAction.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
CACTNotAction::CACTNotAction()
:CAIAction()
{
	m_WaitTime = 0;
}

int CACTNotAction::Run()
{
//	m_Target->SetAIInput( 0 );
//	m_Target->SetAIInputSP( 0 );
	m_Target->m_JudgeWaitTime = m_WaitTime;
	return 0;
}

void CACTNotAction::SetParam( int paraNo, char * param )
{
	m_WaitTime = atoi( param );
}
