#include "CAI_ACT_Combo.h"
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include "ShanaProt.h"
#include "CAI_Combo.h"
#include "CAI_ACT_UsageCombo.h"
#include "NpcAIShana.h"

/////////////////////////////
// コンボ
/////////////////////////////
CACTUsageCombo::CACTUsageCombo()
{
	m_Type = 0;
	m_Combo = 0;
}

CAICombo* CACTUsageCombo::GetCombo( )
{
	return m_Combo ;
}

void CACTUsageCombo::SetCombo( CAICombo* combo )
{
	m_Combo = combo;
	if( combo == 0 )
	{
		memset( m_Command, 0, sizeof( m_Command ) ) ;
		memset( m_Name, 0, sizeof( m_Name ) ) ;
		memset( m_Time, 0, sizeof( m_Time ) ) ;
		m_Type = 0 ;
		m_CurrentPoint = 0 ;
	}
	else{
		memcpy( m_Command, combo->m_Command, sizeof( m_Command ) ) ;
		memcpy( m_Name, combo->m_Name, sizeof( m_Name ) ) ;
		memcpy( m_Time, combo->m_Time, sizeof( m_Time ) ) ;
		m_Type = combo->m_Type ;
		m_CurrentPoint = 0 ;
	}
}

int CACTUsageCombo::GetAction() 
{
	int cur = m_CurrentPoint ;
	// すべての入力が終わった
	if( m_Time[m_CurrentPoint] != 0 ){
		m_Combo = NULL;
		return 0;
	}

	m_Time[m_CurrentPoint]--;

	if( m_Time[m_CurrentPoint] == 0 )
		m_CurrentPoint++;

	return m_Command[cur] ;
}

CACTUsageCombo::~CACTUsageCombo()
{
}

int CACTUsageCombo::Run() 
{
	int cur = m_CurrentPoint ;
	// すべての入力が終わった
	if( m_Time[m_CurrentPoint] == 0 ){
		m_Combo = NULL;
		return 0;
	}

	m_Time[m_CurrentPoint]--;

	if( m_Time[m_CurrentPoint] == 0 )
		m_CurrentPoint++;

	m_Target->SetAIInput(m_Command[cur]);
}
