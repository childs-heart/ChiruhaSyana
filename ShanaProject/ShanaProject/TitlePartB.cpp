/********************/
/* ƒ^ƒCƒgƒ‹‰æ–Ê	*/
/********************/

#include "TitlePartB.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CTitlePartB::CTitlePartB( CResBattle *game ):CSprite( game )
{
	// Ž‘Œ¹’²’B
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_PART_B );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_CHILD_LOGO );
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
	m_TargetX = 294 * ( 0.15f * m_Flame ) ;
	m_TargetY = 294 * ( 0.15f * m_Flame ) ;

	// ƒuƒŒƒ“ƒh•û–@Žw’è
	m_DispObj->SetDestBlend(D3DBLEND_INVSRCALPHA);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );

	// ƒ‰ƒ“ƒ_ƒ€‰ñ“]
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CTitlePartB::~CTitlePartB()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CTitlePartB::Move()
{
	// 45ƒtƒŒŒo‰ß‚ÅI—¹
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
			m_Y = 135;
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
		}
	break;

	case 3:
		if( m_Flame == 6000 ){
			m_Flame = 0;
			m_State = 3;
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

	}

	return TRUE;
}

bool CTitlePartB::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();
	StImageData *anime ;

	switch( m_State ){
	case 0:
		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetCurrentMotion()->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB((240/20*m_Flame+15),255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - m_TargetX , m_Y - m_TargetY ,
								m_X + m_TargetX , m_Y + m_TargetY );
		draw->Draw( m_DispObj );
	break;

	case 1:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_ONE);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetCurrentMotion()->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB(255,255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - 1000 , m_Y - 1000 ,
								m_X + 1000 , m_Y + 1000 );
		draw->Draw( m_DispObj );
	break;
	case 2:
		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 1 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
								m_X + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );

		draw->Draw( m_DispObj );

		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 0 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255-(int)((float)255/188*m_Flame),255,255,255) );
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - 1000 , m_Y - 1000 ,
								m_X + 1000 , m_Y + 1000 );
		draw->Draw( m_DispObj );
	break;

	case 3:
		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// •`‰æ
		// ‰æ‘œ•\Ž¦Šî€“_
		anime = &m_Anime.GetMotionData( 1 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// •`‰æ
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
								m_X + ( ((long)texInfo.Width - anime->m_BaseX)),
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );

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
	}

	return TRUE;
}
