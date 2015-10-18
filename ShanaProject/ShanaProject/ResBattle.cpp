#include "ResBattle.h"
#include "UTL_Screen.h"

CResBattle* CResBattle::m_ResBattle=NULL ;

CResBattle* CResBattle::GetResBattle()
{
	return m_ResBattle;
}

CResBattle::CResBattle()
{
	m_ResBattle = this;
}

void CResBattle::GetScreenPosition( int *x, int *y )
{
	*x = CUtlScreen::m_X;
	*y = CUtlScreen::m_Y;
}

int CResBattle::GetDamage(int base_damage, int hit )
{
	if( hit > 20 ){
		hit = 20;
	}
	int dame = (float)( 21 - hit ) / ( 19+hit) * base_damage ;
	if( dame < 25){
		dame = 25;
	}
	return dame;
}

void CResBattle::NotifyReceivedAttack( int player )
{
	m_ReceivedAttackPlayer = player;
}

void CResBattle::NotifyHittedAttack( int state )
{
	m_Screen->SetVibration( state );
}

int CResBattle::GetReceivedAttackPlayer( )
{
	return m_ReceivedAttackPlayer;
}

void CResBattle::SetUtilScreen(CUtlScreen *screen)
{
	m_Screen = screen;
}
