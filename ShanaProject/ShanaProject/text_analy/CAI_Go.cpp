#include "CAI_Combo.h"
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

/////////////////////////////
// �R���{
/////////////////////////////
CAICombo::CAICombo()
{
}

void CAICombo::Add( char * name )
{
	if( name[0] == '}' ){
		// ���̃A�N�V������
	}
		strcpy( m_ConditionName , name );
		m_TableNo = tableNo;
	}
}

CAICombo::~CAICombo()
{
}
