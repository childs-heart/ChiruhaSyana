#include "CAI_Combo.h"
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

/////////////////////////////
// コンボ
/////////////////////////////
CAICombo::CAICombo()
{
}

void CAICombo::Add( char * name )
{
	if( name[0] == '}' ){
		// 次のアクションへ
	}
		strcpy( m_ConditionName , name );
		m_TableNo = tableNo;
	}
}

CAICombo::~CAICombo()
{
}
