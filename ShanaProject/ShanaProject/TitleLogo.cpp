/********************/
/* �^�C�g�����	*/
/********************/

#include "TitleLogo.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CTitleLogo::CTitleLogo( CResBattle *game ):CSprite( game )
{
	// �������B
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_LOGO );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_CHILD_LOGO );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	// �������
	m_X = 400;
	m_Y = 300;

	// �u�����h���@�w��
	m_DispObj->SetDestBlend(D3DBLEND_INVSRCALPHA);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );

	// �����_����]
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CTitleLogo::~CTitleLogo()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CTitleLogo::Move()
{
	// 45�t���o�߂ŏI��
	m_Flame++;
	switch( m_State ){
	case 0:
		if( m_Flame == 60 ){
			m_State = 1 ;
			m_Flame = 0 ;
		}
	break;

	case 1:
		if( m_Flame == 180 ){
			m_Flame = 0;
			m_State = 2;
		}
	break;

	case 2:
		if( m_Flame == 60 ){
			return FALSE;
		}
	break;
	}
	return TRUE;
}

bool CTitleLogo::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();
	StImageData *anime ;

	switch( m_State ){
	case 0:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// �`��
		// �摜�\����_
		anime = &m_Anime.GetMotionData( 2 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// �`��
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB(((int)((float)254/60*m_Flame)),255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY,
								m_X + (long)texInfo.Width - anime->m_BaseX,
								m_Y + (long)texInfo.Height - anime->m_BaseY );
		draw->Draw( m_DispObj );
	break;

	case 1:
		m_DispObj->SetDestBlend(D3DBLEND_ZERO);
		m_DispObj->SetSrcBlend(D3DBLEND_ONE);
		// �`��
		// �摜�\����_
		anime = &m_Anime.GetMotionData( 2 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// �`��
		m_DispObj->SetBlendColor(D3DCOLOR_ARGB(255,255,255,255));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY,
								m_X + (long)texInfo.Width - anime->m_BaseX,
								m_Y + (long)texInfo.Height - anime->m_BaseY );
		draw->Draw( m_DispObj );
	break;
	case 2:
		m_DispObj->SetDestBlend(D3DBLEND_ONE);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		// �`��
		// �摜�\����_
		anime = &m_Anime.GetMotionData( 2 )->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// �`��
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB(254-(int)((float)254/60*m_Flame),255,255,255) );
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY,
								m_X + (long)texInfo.Width - anime->m_BaseX,
								m_Y + (long)texInfo.Height - anime->m_BaseY );
		draw->Draw( m_DispObj );
	break;

	}

	return TRUE;
}
