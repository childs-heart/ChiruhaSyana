/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit004_3.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit004_3::CEffHit004_3( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_004_3 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA_AIRDASH_FRONT );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// 初期状態
	int dir;
	m_Target = target;
	m_Target->GetPosition( &m_X, &m_Y );
	dir = m_Target->getDir() ;
	m_X -= dir * 110;
	m_Y -= 80;
	m_Flame = 0;
	m_FlagGround = 0;
	m_Dir = m_Target->getDir() ;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);

	m_DispObj->SetBlendColor( 0xffFFFFFF );

	m_Anime.ChangeAction( 0 , 0 );
}

CEffHit004_3::~CEffHit004_3()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit004_3::Move()
{
	// **フレ経過で終了
	m_Flame++;
	if( m_Flame == 30 ){
		return FALSE ;
	}
	m_X -= m_Dir;
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255-(m_Flame-8)*12, 0xff, 0xff, 0xff) );
	
	return TRUE;
}


bool CEffHit004_3::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

//	m_Target->GetPosition( &m_X, &m_Y );

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
	float pay;
//	m_Y -= 80;
	pay = 0.4f + (float)(m_Flame-8) / 22.0f;
	if( m_Flame > 8 ){
		m_DispObj->SetDestRect( m_X - anime->m_BaseX * pay * m_Dir , m_Y - anime->m_BaseY * pay  ,
								m_X + ( ((long)texInfo.Width - anime->m_BaseX) * m_Dir ) * pay ,
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) * pay  );
		draw->Draw( m_DispObj );
	}

	return TRUE;
}
