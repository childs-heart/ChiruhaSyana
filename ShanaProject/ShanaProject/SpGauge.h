#ifndef	__SPGAUGE
#define	__SPGAUGE

#include "ShanaProt.h"
#include "Game.h"
#include "CLIB_Element.h"
#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"

class CResBattle;

enum ENUM_SPGAUGE_STATE{
	ENUM_SPGAUGE_STATE_GAUGE0 = 0,
	ENUM_SPGAUGE_STATE_GAUGE1_IN ,
	ENUM_SPGAUGE_STATE_GAUGE1	 ,
	ENUM_SPGAUGE_STATE_GAUGE2_IN ,
	ENUM_SPGAUGE_STATE_GAUGE2	 ,
	ENUM_SPGAUGE_STATE_GAUGE3_IN ,
	ENUM_SPGAUGE_STATE_GAUGE3
};
enum ENUM_SPGAUGE_VAL{
	ENUM_SPGAUGE_VAL_GAUGE1 = 100,
	ENUM_SPGAUGE_VAL_GAUGE2 = 200,
	ENUM_SPGAUGE_VAL_GAUGE3 = 300
};

class CSpGauge : public CSprite{
private:
	CShanaProt		*m_Target;
	int			m_Player;

//	int m_X;
//	int m_Y;
//	int m_State;
//	int	m_Flame;

//	int m_AnimeFlame;		// アニメフレーム数
//	int m_AnimeNo;			// アニメNO
//	int m_AnimeImgae;		// 表示テクスチャー番号

public:
	CSpGauge( CResGame *game , CShanaProt *target , int player );
	~CSpGauge();

	virtual bool Move();
	bool Draw( CD3DDraw *draw );
//	virtual bool Draw();

	void	ChangeState( int state );

private:
	CSpGauge();

};

#endif
