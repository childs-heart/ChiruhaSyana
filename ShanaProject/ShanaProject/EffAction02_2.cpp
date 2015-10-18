/********************/
/* �G�t�F�N�g�e�X�g	*/
/********************/

#include <math.h>
#include "EffAction02_2.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffAction02_2::CEffAction02_2( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// �������B
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_ACTION_02_2 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA_AIRDASH_FRONT );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// �������
	m_Target = target;
	m_Target->GetPosition( &m_X, &m_Y );
	m_Flame = 0;
	m_FlagGround = 0;
	m_Dir = m_Target->getDir() ;

	m_Target->GetPosition( &m_X, &m_Y );
	m_X -= m_Dir * 16;
	m_Y -= 64;

	// �u�����h���@�w��
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);

	m_DispObj->SetBlendColor( 0xffFFFFFF );

	m_Anime.ChangeAction( 1 , 0 );
}

CEffAction02_2::~CEffAction02_2()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffAction02_2::Move()
{
	// **�t���o�߂ŏI��
	m_Flame+=3;
	if( m_Flame == 12 ){
		return FALSE ;
	}

	m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255-m_Flame*22, 0xff, 0xff, 0xff) );	
	return TRUE;
}


bool CEffAction02_2::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// �`��
	// �摜�\����_
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;

/*�@��
	ST_IMAGE_DATA *anime ;
	anime = &m_Anime->m_AnimeData[m_AnimeImage] ;
	tex = m_Tex->GetTexture( m_Anime->m_AnimeData[m_AnimeImage].m_TextureNo ) ;
*/
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	float pay,pay2;
	pay = (float)(12-m_Flame) / 8.0f;
	pay2 = 0.2f + (float)m_Flame / 6.0f;
	m_DispObj->SetDestRect( m_X + anime->m_BaseX *pay2* m_Dir , m_Y - anime->m_BaseY * pay  ,
							m_X - ( ((long)texInfo.Width - anime->m_BaseX) * m_Dir )*pay2 ,
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) * pay  );
	draw->Draw( m_DispObj );

	return TRUE;
}
