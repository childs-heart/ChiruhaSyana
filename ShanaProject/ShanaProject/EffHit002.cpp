/********************/
/* エフェクトテスト	*/
/********************/

#include "EffHit002.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit002::CEffHit002( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_002 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SYOUGEKI );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_X -= 0 ;
	m_Y -= 70;
	m_Flame = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);

	m_DispObj->SetBlendColor( 0xffFf0000 );

	// ランダム回転
	m_DispObj->SetRotation( 0,0,1,90-10*target->getDir(),0,0 );
}

CEffHit002::~CEffHit002()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit002::Move()
{
	// 10フレ経過で終了
	m_Flame++;
	if( m_Flame == 10 ){
		return FALSE ;
	}
	return TRUE;
}

bool CEffHit002::Draw( CD3DDraw *draw )
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
//	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(200,255,0,0) );
//	m_DispObj->SetRotation( 1,-90,0,0, 0, 0);
	m_DispObj->SetTexture( tex );

	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255-m_Flame*20,	255 ,255, 255 ));
	m_DispObj->SetDestRect( m_X - ( m_Flame * 50 ) ,
							m_Y - ( m_Flame * 50 ) ,
							m_X + ( m_Flame * 50 ) ,
							m_Y + ( m_Flame * 50 ) );

	draw->Draw( m_DispObj );

	return TRUE;
}
