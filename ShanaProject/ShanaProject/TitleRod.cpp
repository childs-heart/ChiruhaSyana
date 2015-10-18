/********************/
/* ƒ^ƒCƒgƒ‹‰æ–Ê	*/
/********************/

#include "TitleRod.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CTitleRod::CTitleRod( CResBattle *game ):CSprite( game )
{
	// Ž‘Œ¹’²’B
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_ROD );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_ZAN_ANIIME );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	// ‰Šúó‘Ô
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

	// ƒuƒŒƒ“ƒh•û–@Žw’è
	m_DispObj->SetDestBlend(D3DBLEND_INVSRCALPHA);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );

	// ƒ‰ƒ“ƒ_ƒ€‰ñ“]
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CTitleRod::~CTitleRod()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CTitleRod::Move()
{
	// 45ƒtƒŒŒo‰ß‚ÅI—¹
	m_Flame++;
	switch( m_State ){
	case 0:
		if( m_Flame == 60 ){
			m_State = 1 ;
			m_Flame = 0 ;
			m_TargetX = 515;
			m_TargetDx = 519;
			m_TargetY = 296;
			m_TargetDy = 389;
			m_TargetDy = 400;
			m_RodDx = 400;
			m_RodDy = 300;
		}
	break;

	case 1:
		if( m_Flame == 84 ){
			m_Flame = 0;
			m_State = 2;
		}
		else{ // 240/370 36/-20
			m_X = 400+(float)( m_TargetX - 400 ) / 84 * m_Flame;
			m_Y = 300+(float)( m_TargetY - 300 ) / 84 * m_Flame;
			m_RodDx = (800 - ((float)( 800 - m_TargetDx ) / 84 * m_Flame)) /2 ;
			m_RodDy = (600 - ((float)( 600 - m_TargetDy ) / 84 * m_Flame)) /2 ;
		}
	break;

	case 2:
		if( m_Flame == 1 ){
			m_Flame = 0;
			m_State = 3;
			m_TargetX = 400;
			m_TargetY = 298;
		}
	break;

	case 3://title in
		if( m_Flame == 60 ){
			m_Flame = 0;
			m_State = 4;
		}
	break;

	case 4:
		if( m_Flame == 70 ){
			m_Flame = 0;
			m_State = 5;
			m_TargetX = 400;
			m_TargetY = 298;
		}
	break;

	case 5:
		if( m_Flame == 20 ){
			m_Flame = 0;
			m_State = 6;
			m_X = 400;
			m_Y = 135;
		}
	break;

	case 6:
		if( m_Flame == 60 ){
			m_Flame = 0;
			m_State = 7;
		}
	break;

	case 7:
		if( m_Flame == 1400 ){
			m_Flame --;
			m_State = 8;
			return FALSE;
		}
	break;
	}

	return TRUE;
}

bool CTitleRod::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();
	StImageData *anime ;

	switch( m_State ){
	case 0:
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetCurrentMotion()->m_Image ;

		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;

		// •`‰æ
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
								m_X + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );

		draw->Draw( m_DispObj );
	break;

	case 1:
	case 2:
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetCurrentMotion()->m_Image ;

		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;

		// •`‰æ
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - m_RodDx , m_Y - m_RodDy ,
								m_X + m_RodDx ,	m_Y + m_RodDy );

		draw->Draw( m_DispObj );
	break;

	case 3:
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetCurrentMotion()->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255-(255/60*m_Flame),255,255,255) );
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - m_RodDx , m_Y - m_RodDy ,
								m_X + m_RodDx ,	m_Y + m_RodDy );
		draw->Draw( m_DispObj );

		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 17 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB((255/60*m_Flame),255,255,255) );
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_TargetX - anime->m_BaseX , m_TargetY - anime->m_BaseY ,
								m_TargetX + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_TargetY + ( (long)texInfo.Height - anime->m_BaseY ) );
		draw->Draw( m_DispObj );
	break;

	case 4:
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 17 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_TargetX - anime->m_BaseX , m_TargetY - anime->m_BaseY ,
								m_TargetX + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_TargetY + ( (long)texInfo.Height - anime->m_BaseY ) );
		draw->Draw( m_DispObj );
		break;

	case 5:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 17 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255,255,255,255 ));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_TargetX - anime->m_BaseX , m_TargetY - anime->m_BaseY ,
								m_TargetX + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_TargetY + ( (long)texInfo.Height - anime->m_BaseY ) );
		draw->Draw( m_DispObj );

		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 18 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB((255/60*m_Flame+5),255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( 0,0,800,600 );
		draw->Draw( m_DispObj );
		break;

	case 6:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 19 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255,255,255,255 ));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
								m_X + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
		draw->Draw( m_DispObj );

		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 18 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB(255-(255/60*m_Flame+5),255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( 0,0,800,600 );
		draw->Draw( m_DispObj );
		break;

	case 7:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 19 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255,255,255,255 ));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
								m_X + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
		draw->Draw( m_DispObj );
		break;
	}

	return TRUE;
}
