#include "CLIB_FPS.h"

CFps* CFps::m_CFps(NULL);

// コンストラクタ
CFps::CFps()
{
	// 精度を上げる
	timeBeginPeriod(1);

    // 生成時の時刻（ミリ秒）を取得
	unsigned long tmp;
	tmp = timeGetTime();

    m_OldTime = (double)tmp;
	m_NowTime = (double)tmp;
	m_PerSec = tmp;

	m_FpsCnt = 0;
	m_Fps = 0;
	m_Minimam = 0;
}


// デストラクタ
CFps::~CFps(void)
{
	timeEndPeriod(1);    // タイマーの精度を戻す
}

CFps* CFps::GetCFps()
{
	if( m_CFps == NULL ){
		m_CFps = new CFps();
	}
	return m_CFps;
}

// FPS値を取得
void CFps::WaitNextUpdate()
{
	unsigned long tmp;
	tmp = timeGetTime();
	int wait;
	double old = m_OldTime;

	if( old + FPS_INTERVAL > tmp ){
		wait =  old + FPS_INTERVAL - tmp ;
		Sleep( wait );
	} 
	m_NowTime = (double)tmp;
	if( m_PerSec + 1000 <= m_NowTime ){
		m_Fps = m_FpsCnt;
		m_FpsCnt=0;
		m_PerSec += 1000;
	}
	m_FpsCnt++;

	m_Minimam += 0.6667f;
	m_OldTime = m_OldTime + 16;
	if( m_Minimam > 1 ){
		m_OldTime++;
		m_Minimam--;
	}
	if( m_OldTime + 16.6667 < tmp ){
		m_OldTime = (float)tmp;
	}
//	QueryPerformanceFrequency();
//	int old = m_OldTime;
//	m_OldTime = tmp + m_OldTime - old ;
}

int CFps::GetFPS()
{
	return m_Fps;
}
