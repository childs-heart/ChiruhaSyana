/********************/
/* エフェクトテスト	*/
/********************/

#include "UTL_AttackArea.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CUtilAttackArea::CUtilAttackArea( CResBattle *game, CSprite *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_ATTACK_AREA );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_ZAN );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	m_Tex->LoadTexture( 0, "back_white.bmp", NULL, 0x00000000 );
	m_Anime.m_AnimeSpec->CreateAction( 0, 1 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_X -= 0;
	m_Y -= 70;
	m_Flame = 0;
	m_Target = target;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

}

CUtilAttackArea::~CUtilAttackArea()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CUtilAttackArea::Move()
{
	m_Target->GetPosition( &m_X, &m_Y );
	
	return TRUE;
}

bool CUtilAttackArea::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Target->GetAnime()->GetCurrentMotion()->m_Image ;

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
//	tex->GetTextureInfo( &texInfo ) ;

	StMotionData	*attack;
	StMotionData	*wound;
	attack = m_Target->GetAnime()->GetCurrentMotion();
	wound = m_Target->GetAnime()->GetCurrentMotion();

	// 描画
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,0,0) );
//	m_DispObj->SetRotation( 1,-90,0,0, 0, 0);
	m_DispObj->SetTexture( tex );

	int i;
	int j;
	for( j = 0 ; j < attack->m_Attack.m_NumHit ; j++ ){
		m_DispObj->SetDestRect( m_X + attack->m_Attack.m_HitArea[j].left * 2 * -m_Target->GetDir() ,
								m_Y + attack->m_Attack.m_HitArea[j].top * 2 ,
								m_X + attack->m_Attack.m_HitArea[j].right * 2 * -m_Target->GetDir() ,
								m_Y + attack->m_Attack.m_HitArea[j].bottom * 2 );
		draw->Draw( m_DispObj );
	}

	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,0,0,255) );
	for( i = 0 ; i < wound->m_Wound.m_NumHit ; i++ ){
		m_DispObj->SetDestRect( m_X + wound->m_Wound.m_HitArea[i].left * 2 * -m_Target->GetDir(),
								m_Y + wound->m_Wound.m_HitArea[i].top * 2 ,
								m_X + wound->m_Wound.m_HitArea[i].right * 2 * -m_Target->GetDir(),
								m_Y + wound->m_Wound.m_HitArea[i].bottom * 2 );
		draw->Draw( m_DispObj );
	}
	return TRUE;
}
