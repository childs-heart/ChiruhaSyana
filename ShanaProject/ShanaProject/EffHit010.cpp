/********************/
/* �G�t�F�N�g�e�X�g	*/
/********************/

#include "EffHit010.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit010::CEffHit010( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// �������B
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_010 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_HIT_UPPER );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	// �������
	target->GetPosition( &m_X, &m_Y );
	m_X -= 0;
	m_Y -= 70;
	m_Flame = 0;

	// �u�����h���@�w��
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
}

CEffHit010::~CEffHit010()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit010::Move()
{
	// 45�t���o�߂ŏI��
	m_Flame++;
	if( m_Flame == 12 ){
		return FALSE ;
	}
	return TRUE;
}

bool CEffHit010::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// �`��
	// �摜�\����_
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image ;

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;

	// �`��
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 240 - m_Flame * 21 , 255,255,255 ) );
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY,
							m_X - anime->m_BaseX + (long)texInfo.Width ,
							m_Y - anime->m_BaseY + (long)texInfo.Height );

	draw->Draw( m_DispObj );

	return TRUE;
}
