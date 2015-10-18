/********************/
/* タイトル画面	*/
/********************/

#include "TitleFlash.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CTitleFlash::CTitleFlash( CResBattle *game ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_FLASH );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_CHILD_LOGO );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	// 初期状態
	m_Dx = 800;
	m_Dy = 0;
	m_X = 400;
	m_Y = 300;
	m_RodX = 400;
	m_RodY = 300;
	m_RodDx = 800;
	m_RodDy = 600;
	m_Flame = 0;
	m_State = 0;
	m_TargetX = 294 * ( 0.15f * m_Flame ) ;
	m_TargetY = 294 * ( 0.15f * m_Flame ) ;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_INVSRCALPHA);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CTitleFlash::~CTitleFlash()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CTitleFlash::Move()
{
	// 45フレ経過で終了
	m_Flame++;
	switch( m_State ){
	case 0:
		if( m_Flame == 20 ){
			m_State = 1 ;
			m_Flame = 0 ;
			m_TargetX = 512;
			m_TargetDx = 519;
			m_TargetY = 298;
			m_TargetDy = 389;
			m_RodDx = 400;
			m_RodDy = 300;
		}
		else{
			m_TargetX = 294 * ( 0.15f * m_Flame ) ;
			m_TargetY = 294 * ( 0.15f * m_Flame ) ;
		}
	break;

	case 1:
		if( m_Flame == 34 ){
			m_Flame = 0;
			m_State = 2;
			m_X = 400;
			m_Y = 200;
			m_TargetX = 400;
			m_TargetY = 298;
		}
		else{ // 240/370
		}
	break;

	case 2:
		if( m_Flame == 188 ){
			m_Flame = 0;
			m_State = 3;
			return FALSE;
		}
	break;
	}
	return TRUE;
}

bool CTitleFlash::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();
	StImageData *anime ;

	switch( m_State ){
	case 0:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// 描画
		// 画像表示基準点
		anime = &m_Anime.GetCurrentMotion()->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// 描画
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB((240/20*m_Flame+15),255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - m_TargetX , m_Y - m_TargetY ,
								m_X + m_TargetX , m_Y + m_TargetY );
		draw->Draw( m_DispObj );
	break;

	case 1:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_ONE);
		// 描画
		// 画像表示基準点
		anime = &m_Anime.GetCurrentMotion()->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// 描画
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB(255,255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - 900 , m_Y - 900 ,
								m_X + 900 , m_Y + 900 );
		draw->Draw( m_DispObj );
	break;
	case 2:
		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// 描画
		// 画像表示基準点
		anime = &m_Anime.GetMotionData( 0 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// 描画
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255-(int)((float)255/188*m_Flame),255,255,255) );
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - 900 , m_Y - 900 ,
								m_X + 900 , m_Y + 900 );
		draw->Draw( m_DispObj );
	break;

	}

	return TRUE;
}
