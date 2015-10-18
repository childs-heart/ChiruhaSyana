/********************/
/* �w�i�N���X		*/
/********************/

#include "ScnBack.h"
#include "ScnBackMisago.h"

#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

#include "UTL_Screen.h"

CScnBack::CScnBack( CResBattle *game ):CSprite( game )
{
	// �������B
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_SCN_BACK );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_STA_RURIDAN );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );
	m_DispObj->SetSrcBlend( D3DBLEND_ONE);
	m_DispObj->SetDestBlend( D3DBLEND_ZERO);

	// �������
//	m_X = -600;
	m_X = 0;
	m_Y = -600;
	m_Flame = 0;

	// �A�j���[�V�����̃^�X�N��V�K�쐬����
	new(game->m_CommonBack) CScnBackMisago( game ,this );

	// �u�����h���@�w��
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// �����_����]
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CScnBack::~CScnBack()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CScnBack::Move()
{

	m_Flame+=5;

	if( m_Flame > 255 ){
		m_Flame=255;
	}
	return TRUE;
}

bool CScnBack::Draw( CD3DDraw *draw )
{
//	CD3DDraw2	*draw2 = (CD3DDraw2*)(draw) ;
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// �`��
	// �摜�\����_
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;
//	m_X = CUtlScreen::test1;
//	m_Y = CUtlScreen::test2;

/*�@��
	ST_IMAGE_DATA *anime ;
	anime = &m_Anime->m_AnimeData[m_AnimeImage] ;
	tex = m_Tex->GetTexture( m_Anime->m_AnimeData[m_AnimeImage].m_TextureNo ) ;
*/
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X + ( (long)texInfo.Width - anime->m_BaseX ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );

//	draw2->Draw2( m_DispObj , m_Flame );

	return TRUE;
}
