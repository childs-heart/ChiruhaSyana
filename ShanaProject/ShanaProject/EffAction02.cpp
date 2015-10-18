/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffAction02.h"
#include "EffAction02_1.h"
#include "EffAction02_2.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffAction02::CEffAction02( CResBattle *game, CShanaProt *target ):CSprite( game )
{

	new(game->m_CommonEffect) CEffAction02_1( game, target );
	new(game->m_CommonEffectFront) CEffAction02_2( game, target );

}

CEffAction02::~CEffAction02()
{
//	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffAction02::Move()
{
	return false;
}

bool CEffAction02::InterfereFinalize()
{
	return true;
}

bool CEffAction02::Draw(CD3DDraw *draw)
{
	return true;
}

bool CEffAction02::DrawFinalize()
{
	return true;
}