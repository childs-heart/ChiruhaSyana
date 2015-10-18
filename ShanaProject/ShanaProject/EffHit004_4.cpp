/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit004_4.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit004_4::CEffHit004_4( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_004_4 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA_AIRDASH_FRONT );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// 初期状態
	m_Target = target;
	m_Target->GetPosition( &m_X, &m_Y );
	m_Flame = 0;
	m_FlagGround = 0;
	m_Dir = m_Target->getDir() ;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);

	m_DispObj->SetBlendColor( 0xffFFFFFF );

	m_Anime.ChangeAction( 1 , 0 );
}

CEffHit004_4::~CEffHit004_4()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit004_4::Move()
{
	// **フレ経過で終了
	m_Flame++;
	if( m_Flame == 21 ){
		return FALSE ;
	}

	m_Target->GetPosition( &m_X, &m_Y );
	m_X += m_Dir * 28;
	m_Y -= 64;

	m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255-(9-m_Flame)*22, 0xff, 0xff, 0xff) );	
	return TRUE;
}


bool CEffHit004_4::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

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
	float pay,pay2;
	pay = (float)(21-m_Flame) / 8.0f;
	pay2 = 0.2f + (float)(9-m_Flame) / 6.0f;
	if( m_Flame > 9 ){
		m_DispObj->SetDestRect( m_X + anime->m_BaseX *pay2* m_Dir , m_Y - anime->m_BaseY * pay  ,
								m_X - ( ((long)texInfo.Width - anime->m_BaseX) * m_Dir )*pay2 ,
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) * pay  );
		draw->Draw( m_DispObj );
	}

	return TRUE;
}
