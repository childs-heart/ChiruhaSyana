#include "CAI_ACT_Crouch.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// �A�N�V����
/////////////////////////////
int CACTCrouch::Run()
{

	m_Target->SetAIInput( COMMAND_NONE, 1 );// ��肩��

	return 0;
}
