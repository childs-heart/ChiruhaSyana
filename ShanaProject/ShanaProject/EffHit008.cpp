/********************/
/* エフェクトテスト	*/
/********************/

#include "EffHit008.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit008::CEffHit008( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_008 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA802_2 );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

/*	m_Anime.m_AnimeSpec->CreateAction( 0, 10 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 0, 0, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 1, 1, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 2, 2, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 3, 3, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 4, 4, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 5, 5, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 6, 6, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 7, 7, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 8, 8, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 9, 9, 0, 320, 240 );
*/
	//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_X -= 0;
	m_Y -= 70;
	m_Flame = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);
}

CEffHit008::~CEffHit008()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit008::Move()
{
	// 45フレ経過で終了
	m_Flame++;
	if( m_Flame == 31 ){
		return FALSE ;
	}
	return TRUE;
}

bool CEffHit008::Draw( CD3DDraw *draw )
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
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY,
							m_X - anime->m_BaseX + (long)texInfo.Width ,
							m_Y - anime->m_BaseY + (long)texInfo.Height );

	draw->Draw( m_DispObj );

	return TRUE;
}
