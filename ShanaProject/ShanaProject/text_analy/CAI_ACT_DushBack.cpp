#include "CAI_ACT_DushBack.h"
#include "Stdio.h"
#include "ShanaProt.h"

#include "NpcAIShana.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
int CACTDushBack::Run()
{

	m_Target->SetAIInput( COMMAND_BACK, 2 );

	return 0;
}
