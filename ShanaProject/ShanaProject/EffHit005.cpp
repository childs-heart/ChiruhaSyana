/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit005.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit005::CEffHit005( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_005 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_HIT_ZAN2 );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->ma_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_Flame = 1;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);

//	m_DispObj->SetBlendColor( 0xffFFFFFF );

	// ランダム回転
	m_DispObj->SetRotation( 0,0,1, (( rand()%45 )+45) * target->getDir() ,2,( rand()%30 ));

	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );

}

CEffHit005::~CEffHit005()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit005::Move()
{
	// 10フレ経過で終了
	m_Flame++;
	if( m_Flame == 11 ){
		return FALSE ;
	}
	m_DispObj->SetScale((m_Flame)*1.4);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(80-m_Flame*7,
										255-m_Flame*m_Flame*2,
										255-m_Flame*m_Flame*25,
										255) );

	return TRUE;
}

/*
bool CEffHit005::Draw( CD3DDraw *draw )
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

	int arg;

	int centerX;
	centerX = ( m_HistoryX[arg] + m_X )/2;
	// 描画
	m_DispObj->SetRotation( 0,0,0,0, 1, atan2( subX, subY ) * (57.29583)+180 );
	m_DispObj->SetTexture( tex );

	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY,
							m_X - anime->m_BaseX + (long)texInfo.Width ,
							m_Y - anime->m_BaseY + (long)texInfo.Height );

	draw->Draw( m_DispObj );

	return TRUE;
}
*/
