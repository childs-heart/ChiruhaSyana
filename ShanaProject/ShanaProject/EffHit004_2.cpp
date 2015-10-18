/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit004_2.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit004_2::CEffHit004_2( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_004_2 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA308 );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// 初期状態
	m_Target = target;
	m_Target->GetPosition( &m_X, &m_Y );
	m_Flame = 0;
	m_FlagGround = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_INVSRCCOLOR);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);

	m_DispObj->SetBlendColor( 0xffFFFFFF );

	m_Anime.ChangeAction( 1 , 0 );
}

CEffHit004_2::~CEffHit004_2()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit004_2::Move()
{
	// **フレ経過で終了
	m_Flame++;
	if( m_Flame == 21 ){
		return FALSE ;
	}
	
	return TRUE;
}


bool CEffHit004_2::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	m_Target->GetPosition( &m_X, &m_Y );

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;

/*　旧
	ST_IMAGE_DATA *anime ;
	anime = &m_Anime->m_AnimeData[m_AnimeImage] ;
	tex = m_Tex->GetTexture( m_Anime->m_AnimeData[m_AnimeImage].m_TextureNo ) ;
*/
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	int dir;
	dir = m_Target->getDir() ;
	m_DispObj->SetDestRect( m_X - anime->m_BaseX * dir , m_Y - anime->m_BaseY ,
							m_X + ( ((long)texInfo.Width - anime->m_BaseX) * dir ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );

	return TRUE;
}
