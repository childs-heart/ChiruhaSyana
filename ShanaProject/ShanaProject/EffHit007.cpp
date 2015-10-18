/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit007.h"
#include "EffHit007_1.h"
#include "EffHit007_2.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit007::CEffHit007( CResBattle *game, CShanaProt *target ):CSprite( game )
{

	new(game->m_CommonEffect) CEffHit007_1( game, target );
	new(game->m_CommonEffectFront) CEffHit007_2( game, target );

}

CEffHit007::~CEffHit007()
{
//	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit007::Move()
{
	return false;
}

bool CEffHit007::InterfereFinalize()
{
	return true;
}

bool CEffHit007::Draw(CD3DDraw *draw)
{
	return true;
}

bool CEffHit007::DrawFinalize()
{
	return true;
}