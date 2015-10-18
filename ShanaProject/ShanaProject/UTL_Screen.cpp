#include "UTL_Screen.h"
#include "ShanaProt.h"

int CUtlScreen::DISTANCE = 100;
int CUtlScreen::test1 = 0;
int CUtlScreen::test2 = 0;
int CUtlScreen::m_X = 0;
int CUtlScreen::m_Y = 0;

CUtlScreen::CUtlScreen( CShanaProt* target1, CShanaProt* target2 )
:
m_WorldWidth(1600),m_WorldHight(1200),
m_ScreenWidth(800),m_ScreenHight(600),
m_Target1(target1),m_Target2(target2)
{
	m_X = 400;
	m_Y = -m_ScreenHight;
	m_VibrationFlame = 0;
	m_VibrationX = 0;
	m_VibrationY = 0;
}

CUtlScreen::~CUtlScreen()
{
}

void CUtlScreen::GetBase(int *x, int *y)
{
	*x = m_X;
	*y = m_Y;
}

void CUtlScreen::GetWorld(int *width, int *hight)
{
	*width = m_WorldWidth;
	*hight = m_WorldHight;
}

void CUtlScreen::GetScreen(int *width, int *hight)
{
	*width = m_ScreenWidth;
	*hight = m_ScreenHight;
}

bool CUtlScreen::Move()
{
	int x1;
	int y1;
	int ax1;
	int ay1;
	int x2;
	int y2;
	int ax2;
	int ay2;
	int dx1;
	int dy1;
	int dx2;
	int dy2;
	int rightX;
	int leftX;
	int right_ox;
	int left_ox;
	int right_dx;
	int left_dx;

	int mx;
	int my;

	CShanaProt	*temp;

	m_Target1->GetPosition( &x1, &y1 );
	m_Target2->GetPosition( &x2, &y2 );
	m_Target1->GetVector( &dx1, &dy1 );
	m_Target2->GetVector( &dx2, &dy2 );
	ax1 = x1 + dx1;
	ax2 = x2 + dx2;
	ay1 = y1 + dy1;
	ay2 = y2 + dy2;
	if( ax1 > ax2 ){
		rightX	= ax1;
		leftX	= ax2;
		right_ox= x1;
		left_ox	= x2;
		right_dx= dx1;
		left_dx	= dx2;
	}
	else{
		rightX = ax2;
		leftX = ax1;
		right_ox= x2;
		left_ox	= x1;
		right_dx= dx2;
		left_dx	= dx1;
	}
	mx = 0;
	my = 0;

	int tmp = m_X - 400;
/*	x1 - temp;
//	y1;
	ax1 - temp;
//	ay1;
	x2 - temp;
//	y2;
	ax2 - temp;
//	ay2;
	dx1 - temp;
//	dy1;
	dx2 - temp;
//	dy2;
	rightX - temp;
	leftX - temp;
	right_ox - temp;
	left_ox - temp;
	right_dx - temp;
	left_dx - temp;
*/
	// ------------------------------------------
	// Ｘ軸
	// ------------------------------------------
	// 二つの距離を測る
	if( rightX - leftX > 800 ){
	}
	else if( rightX - leftX > 400 ){
		m_X = ( rightX + leftX ) >> 1 ;
	}
	else{
		if( rightX > (200 + m_X) ){
			m_X += rightX - 200 - m_X ;
		}
		else if( leftX < (-200 + m_X) ){
			m_X += leftX + 200 - m_X;
		}
	}

/*	if( rightX - leftX > 400 ){
		mx += ( 200 - leftX ) - ( rightX - 600 ) >> 1 ;
	}
	else{
		if( rightX > 600 ){
			mx += 600 - rightX ;
		}
		else if( leftX < 200 ){
			mx += 200 - leftX;
		}
	}
*/
	x1 -= tmp;
//	y1;
	ax1 -= tmp;
//	ay1;
	x2 -= tmp;
//	y2;
	ax2 -= tmp;
//	ay2;
//	dx1 -= tmp;
//	dy1;
//	dx2 -= tmp;
//	dy2;
	rightX -= tmp;
	leftX -= tmp;
	right_ox -= tmp;
	left_ox -= tmp;
	tmp = 400 - (( rightX + leftX ) >> 1);
	if( rightX - leftX > 800 ){
		if( tmp > 0 ){
			if( left_dx > 0 ){
///				mx -= leftX + mx ;
				mx = leftX + tmp ;
			}
			else if( left_ox + tmp < 0 ){
///				mx -= left_ox + mx ;
				mx = left_ox + tmp ;
			}
		}
		else if( tmp < 0 ){
			if( right_dx < 0 ){
///				mx -= rightX + mx - 800;
				mx = rightX + tmp - 800;
			}
			else if( right_ox + tmp > 800 ){
///				mx -= right_ox + mx - 800;
				mx = right_ox + tmp - 800;
			}
		}
	}
	m_X += mx;
//	if( m_X < ( -m_WorldWidth + m_ScreenWidth ) ){
/*	if( mx < ( -m_WorldWidth + m_ScreenWidth ) ){
		mx = mx - ( m_X + m_WorldWidth - m_ScreenWidth );
		m_X = -m_WorldWidth + m_ScreenWidth ;
	}
//	else if( m_X > 0 ){
	else if( mx > 0 ){
		mx = mx - m_X ;
		m_X = 0 ;
	}
*/	
	if( m_X < 400 ){
		m_X = 400;
	}
	else if( m_X > 1200){
		m_X = 1200;
	}
	// ------------------------------------------
	// Ｙ軸
	// ------------------------------------------
	my = (ay1>ay2)?ay2:ay1;
	if( my < 150 ){
		my -= 150 ;
		m_Y = (m_ScreenHight >> 1) + my ;
	}
	else{
		my = (m_ScreenHight >> 1) ;
		m_Y = my;
	}
	if( m_Y < -300 ){
		m_Y = -300 ;
	}

	m_Target1->AddVector( mx, 0 );
	m_Target2->AddVector( mx, 0 );
//	m_X += mx;
	test1 = m_X;
	test2 = m_Y;

	// 画面効果処理
	Vibration();

	return TRUE;
}

bool CUtlScreen::Draw( CD3DDraw *draw )
{
	// スクリーンキャラクタ対象のスクリーン処理
	draw->SetCenter( m_X + m_VibrationX, m_Y + m_VibrationY );
	m_Draw = draw;

	return true;
}

bool CUtlScreen::Draw()
{
	// スクリーンキャラクタ対象のスクリーン処理　後処理（元の座標に戻す）
	m_Draw->SetCenter( 400, 300 );

	return true;
}

void CUtlScreen::Vibration()
{
	if(  (  ( m_Target1->GetState() == ENUM_TESTCHAR_STATE_DOWN ) 
		  &&( m_Target1->GetFlame() == 3 ))
	  || ( (m_Target2->GetState() == ENUM_TESTCHAR_STATE_DOWN )
	     &&( m_Target2->GetFlame() == 3 )) ){

		m_VibrationFlame = 5;
		m_VibrationY = 5;
		m_VibrationX = 0;

	}

	if(  (  ( m_Target1->GetState() == ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND ) 
		  &&( m_Target1->GetFlame() == 0 ))
	  || ( (m_Target2->GetState() == ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND )
	     &&( m_Target2->GetFlame() == 0 )) ){

		m_VibrationFlame = 5;
		m_VibrationY = 0;
		m_VibrationX = 3;

	}

	if( m_VibrationFlame != 0 ){
		m_VibrationX *= -1;
		m_VibrationY *= -1;
		m_VibrationFlame --;
	}
}

void CUtlScreen::SetVibration(int state)
{
	switch( state )
	{
	case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
	case ENUM_TESTCHAR_STATE_ATTACK_EX:
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX:
		m_VibrationFlame = 5;
		m_VibrationY = 3;
		m_VibrationX = 0;
	}
}
