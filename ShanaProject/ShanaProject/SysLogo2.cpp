/********************/
/* ロゴタスク		*/
/********************/

#include "SysLogo2.h"
#include "ShanaProt.h"
#include "ResGame.h"
#include "ResGame.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"
#include "CLIB_D3DDraw2.h"

CSysLogo2::CSysLogo2( CResGame *game ):CSprite( game )
{
	// 資源調達
	game->m_TextureManager->SetupTextureGroup( game->m_TextureManager->GetTextureGroup( 8 ), 8 );

	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_LOGO_2 );
	m_Tex			= game->m_TextureManager->GetTextureGroup( 8 );
	m_DispObjGroup	= m_Game->m_DispObjGroup;
	m_DispObj		= m_DispObjGroup->GetDispObj();
	m_Tex->LoadTexture( 0, "A2ポスター扉.jpg" );
	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 98 );

	m_DispObj->SetSrcBlend( D3DBLEND_SRCALPHA);
	m_DispObj->SetDestBlend( D3DBLEND_INVSRCALPHA);

	m_State = 0;
}

CSysLogo2::~CSysLogo2()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CSysLogo2::Move()
{
	m_Flame +=2;
	if( m_Flame > 255 ){
		if( m_State == 0 ){
			m_State = 1;
			m_Flame = 0;
		}
		else if( m_State == 1 ){
			return FALSE;
		}
	}
	return TRUE;
}

bool CSysLogo2::Draw( CD3DDraw *draw )
{
	CD3DDraw2	*draw2 = (CD3DDraw2*)(draw) ;
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;

/*　旧
	ST_IMAGE_DATA *anime ;
	anime = &m_Anime->m_AnimeData[m_AnimeImage] ;
	tex = m_Tex->GetTexture( m_Anime->m_AnimeData[m_AnimeImage].m_TextureNo ) ;
*/
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X + ( 800 - anime->m_BaseX ),
							m_Y + ( 600 - anime->m_BaseY ) );

	if( m_State == 0 ){
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB( m_Flame ,0xff,0xff,0xff ));
	}
	else{
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255-m_Flame ,0xff,0xff,0xff ));
	}
	draw2->Draw( m_DispObj );
//	draw2->Draw2( m_DispObj , m_Flame );

	return FALSE;
}

bool CSysLogo2::Draw( )
{
	return TRUE;
}
