/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit006.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit006::CEffHit006( CResBattle *game, CShanaProt *target ):CSprite( game ),m_Target(target)
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_006 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_TAIKUUTI );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->ma_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_Flame = 1;
	m_TargetStatus = target->GetState();
	m_Dir = target->getDir();

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_INVSRCCOLOR);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );

}

CEffHit006::~CEffHit006()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit006::Move()
{
	// 30フレ経過で終了
	m_Flame++;
	if( m_Target->GetState() != m_TargetStatus ){
		return FALSE ;
	}
//	m_DispObj->SetScale((m_Flame)*1.4);
//	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(80-m_Flame*7,
//										255-m_Flame*m_Flame*2,
//										255-m_Flame*m_Flame*25,
//										255) );

	return TRUE;
}

bool CEffHit006::Draw( CD3DDraw *draw )
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
	m_Target->GetPosition(&m_X, &m_Y);
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X + ( -anime->m_BaseX ) * 2 * m_Dir ,
										m_Y + ( -anime->m_BaseY ) * 2,
										m_X + ( (long)texInfo.Width - anime->m_BaseX ) * 2 * m_Dir ,
										m_Y + ( (long)texInfo.Height - anime->m_BaseY ) * 2 ,0);

	draw->Draw( m_DispObj );


	return TRUE;
}

