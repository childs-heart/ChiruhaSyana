#pragma once
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

#define FPSCOUNTER_QUERYPER_COUNTER        1
#define FPSCOUNTER_TIMEGETTIME             2
#define FPS_INTERVAL	16.6667f

class CFps
{
private:
	unsigned long m_OldTime;
	unsigned long m_NowTime;
	double m_Minimam;

	unsigned long m_PerSec;

	double m_NextUpdateTime;
	float m_Fps;
	
	static CFps* m_CFps;
	int m_FpsCnt;

    CFps( );
public:
	static CFps* GetCFps();

public:
    virtual ~CFps(void);

    // FPS値を取得
    int GetFPS();

    // アップデート
    void WaitNextUpdate();

protected:
};
