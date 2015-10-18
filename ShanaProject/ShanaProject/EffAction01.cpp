/********************/
/* エフェクトテスト	*/
/********************/

#include "EffAction01.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffAction01::CEffAction01( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_ACTION_01 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_JUMP_LANDING );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_Flame = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
}

CEffAction01::~CEffAction01()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffAction01::Move()
{
	// 20フレ経過で終了
	m_Flame++;
	if( m_Flame == 11 ){
		return FALSE ;
	}
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(200,255,255,255) );
	return TRUE;
}

bool CEffAction01::Draw(CD3DDraw *draw)
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

//	m_Target->GetPosition( &m_X, &m_Y );

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	if( m_Flame > 7 ){
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255-m_Flame*25, 255,255,255 ));
	}
	float pay;
	m_DispObj->SetDestRect( m_X - anime->m_BaseX * 1.5 , m_Y - anime->m_BaseY  ,
							m_X + ( ((long)texInfo.Width - anime->m_BaseX) * 1.5 ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );

	return TRUE;
}
