/********************/
/* エフェクトテスト	*/
/********************/

#include "EffHit001.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit001::CEffHit001( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_001 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_HIT_ZAN1 );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 94 );

	m_SubColor[0] = 0;
	m_SubColor[1] = 16;
	m_SubColor[2] = 64;
	m_SubColor[3] = 80;
	m_SubColor[4] = 128;
	m_SubColor[5] = 144;
	m_SubColor[6] = 160;
	m_SubColor[7] = 176;
	m_SubColor[8] = 184;
	m_SubColor[9] = 196;

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_X -= 0;
	m_Y -= 70;
	m_Flame = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	m_DispObj->SetBlendColor( 0xffFFFFFF );

	// ランダム回転
	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CEffHit001::~CEffHit001()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit001::Move()
{
	// 10フレ経過で終了
	m_Flame++;
	if( m_Flame == 10 ){
		return FALSE ;
	}
	return TRUE;
}

bool CEffHit001::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image ;

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;

	// 描画
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(200,255,255,255) );
//	m_DispObj->SetRotation( 1,-90,0,0, 0, 0);
	m_DispObj->SetTexture( tex );

	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(200-m_Flame*20,
								255,
								255-m_SubColor[m_Flame],
								255-m_SubColor[m_Flame]) );
	if( m_Flame < 2 ){
		m_DispObj->SetDestRect( m_X - ( anime->m_BaseX * ( m_Flame + 1 ) ) ,
								m_Y - ( anime->m_BaseY * ( m_Flame + 2 ) ) ,
								m_X + ( anime->m_BaseX * ( m_Flame + 1 ) ) ,
								m_Y + ( anime->m_BaseY * ( m_Flame + 2 ) ));
	}else{
		m_DispObj->SetDestRect( m_X - ( anime->m_BaseX * ( m_Flame + 1 ) ) ,
								m_Y - ( anime->m_BaseY - ( m_Flame * 4 ) ) ,
								m_X + ( anime->m_BaseX * ( m_Flame + 1 ) ) ,
								m_Y + ( anime->m_BaseY - ( m_Flame * 4 ) ) );
	}

	draw->Draw( m_DispObj );

	return TRUE;
}
