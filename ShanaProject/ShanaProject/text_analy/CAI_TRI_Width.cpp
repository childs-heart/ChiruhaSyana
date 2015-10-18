#include "CAI_TRI_Width.h"
#include "ResBattle.h"
#include "ShanaProt.h"

CTRIWidth::CTRIWidth( CNpcAIShana* target )
:CAINumberShana( target )
{
}

int CTRIWidth::GetValue()
{
	CResBattle *res = CResBattle::GetResBattle();

	int x1,y1,x2,y2;
	res->m_Player[0]->GetPosition( &x1, &y1 );
	res->m_Player[1]->GetPosition( &x2, &y2 );

	return abs( x1 - x2 ) ;
}
