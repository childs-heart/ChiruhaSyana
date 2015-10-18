/********************/
/* タイトルタスク	*/
/********************/

#include "EffShanaOptParts.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"
//#include "CLIB_D3DDraw.h"

CEffShanaOptParts::CEffShanaOptParts( CResBattle *game, CSprite *target ):CSprite( game )
{
	int rnd;

	rnd = rand();
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_SHANA_OPT_PARTS );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_GUARD_CANCEL );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_Y -= 100 - ( rnd % 100 );
	m_X -= ( rnd % 50 ) * target->GetDir();
	m_Flame = 0;
	m_fX = 0;
	m_fY = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
	m_Vector[0] = ( 1 + rand()%3 ) * target->GetDir() ;
	m_Vector[1] = ( -1 + rand()%4 );
}

CEffShanaOptParts::~CEffShanaOptParts()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffShanaOptParts::Move()
{
	m_X += m_Vector[0];
	m_Y += m_Vector[1];
	// 45フレ経過で終了
	m_Flame++;
	if( m_Flame == 200 ){
		return FALSE ;
	}
	return TRUE;
}

bool CEffShanaOptParts::Draw( CD3DDraw *draw )
{
	m_DispObj->SetTexture( NULL );
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,250,50,50) );
	m_DispObj->SetDestRect( m_X , m_Y ,
							m_X + 3,
							m_Y + 3 );

	draw->Draw( m_DispObj );

	return TRUE;
}
