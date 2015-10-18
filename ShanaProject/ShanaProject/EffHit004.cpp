/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit004.h"
#include "EffHit004_1.h"
#include "EffHit004_2.h"
#include "EffHit004_3.h"
#include "EffHit004_4.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit004::CEffHit004( CResBattle *game, CShanaProt *target ):CSprite( game )
{

	new(game->m_CommonEffect) CEffHit004_1( game, target );
	new(game->m_CommonEffectFront) CEffHit004_2( game, target );
	new(game->m_CommonEffectFront) CEffHit004_3( game, target );
	new(game->m_CommonEffectFront) CEffHit004_4( game, target );

}

CEffHit004::~CEffHit004()
{
//	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit004::Move()
{
	return false;
}

bool CEffHit004::InterfereFinalize()
{
	return true;
}

bool CEffHit004::Draw(CD3DDraw *draw)
{
	return true;
}

bool CEffHit004::DrawFinalize()
{
	return true;
}