#include "CAI_ACT_Crouch.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// アクション
/////////////////////////////
int CACTCrouch::Run()
{

	m_Target->SetAIInput( COMMAND_NONE, 1 );// 作りかけ

	return 0;
}
