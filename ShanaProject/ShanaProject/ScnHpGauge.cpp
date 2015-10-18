/********************/
/* 体力ゲージクラス	*/
/********************/

#include "ScnHpGauge.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CScnHpGauge::CScnHpGauge( CResBattle *game, CShanaProt *target, int player ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_SCN_HP_GAUGE );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_HP );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	m_Target = target;
	m_Flame = 0;
	m_Player = player;
	m_CurrentHp = target->GetHpGauge();
	// 初期状態
	if( player == 1 ){
//		m_X = 10;
//		m_Y = 23;
		m_X = 0;
		m_Y = 0;
	}else{
//		m_X = 440;
//		m_Y = 23;
		m_X = 400;
		m_Y = 0;
	}
	
	// ブレンド方法指定
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CScnHpGauge::~CScnHpGauge()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CScnHpGauge::Move()
{
	if( m_CurrentHp > m_Target->GetHpGauge() ){
		m_CurrentHp-=50;
	}
	return TRUE;
}

bool CScnHpGauge::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	int baseX, baseY ;

	// 描画 バック赤
	anime = &m_Anime.GetActionData(1)->GetMotionData(1)->m_Image;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
///	m_DispObj->SetBlendColor( 0xffff0000 );
	m_DispObj->SetBlendColor( 0xffffffff );

	if( m_Player == 1 ){
		baseX = m_X + 12;
		baseY = m_Y + 8;
		m_DispObj->SetDestRect( baseX - anime->m_BaseX , baseY - anime->m_BaseY ,
								baseX + ( 315 * m_CurrentHp / 10000) , //m_Target->m_Spec.MAX_HP,
								baseY + 23 );
	}
	else{
		baseX = m_X + 315;
		baseY = m_Y + 8;
		m_DispObj->SetDestRect( baseX + ( (long)texInfo.Width - anime->m_BaseX ),
								baseY - anime->m_BaseY,
								baseX - ( 315 * m_CurrentHp / 10000),//m_Target->m_Spec.MAX_HP,
								baseY + 23	);
	}
////	draw->Draw( m_DispObj );

	// 描画 身
	anime = &m_Anime.GetActionData(1)->GetMotionData(0)->m_Image;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	m_DispObj->SetBlendColor( 0xffffffff );

	if( m_Player == 1 ){
//		baseX = m_X + 12;
//		baseY = m_Y + 8;
		baseX = m_X + 87;
		baseY = m_Y + 32;
//		m_DispObj->SetDestRect( baseX - anime->m_BaseX , baseY - anime->m_BaseY ,
//								baseX + ( 315 * m_Target->GetHpGauge() / 10000) , //m_Target->m_Spec.MAX_HP,
//								baseY + 23 );
		m_DispObj->SetDestRect( baseX + (long)texInfo.Width - ( (long)texInfo.Width * m_Target->GetHpGauge() / 10000),
								baseY - anime->m_BaseY ,
								baseX + (long)texInfo.Width  , //m_Target->m_Spec.MAX_HP,
								baseY + 20 );
	}
	else{
//		baseX = m_X + 338;
//		baseY = m_Y + 8;
		baseX = m_X + 84;
		baseY = m_Y + 32;
//		m_DispObj->SetDestRect( baseX + ( (long)texInfo.Width - anime->m_BaseX ),
//								baseY - anime->m_BaseY,
//								baseX - ( 315 * m_Target->GetHpGauge() / 10000),//m_Target->m_Spec.MAX_HP,
//								baseY + 23	);
		m_DispObj->SetDestRect( baseX ,
								baseY - anime->m_BaseY,
								baseX + ( (long)texInfo.Width * m_Target->GetHpGauge() / 10000),//m_Target->m_Spec.MAX_HP,
								baseY + 20	);
	}
	draw->Draw( m_DispObj );

	// 描画 枠
//	anime = &m_Anime.GetMotionData(0)->m_Image;
//	anime = &m_Anime.GetCurrentMotion()->m_Image;
	anime = &m_Anime.GetActionData(0)->GetMotionData(0)->m_Image;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;

	m_DispObj->SetTexture( tex );
	if( m_Player == 1 ){
		baseX = m_X -5;
		baseY = m_Y;
		m_DispObj->SetDestRect( baseX - anime->m_BaseX , m_Y - anime->m_BaseY ,
								baseX + ( (long)texInfo.Width - anime->m_BaseX ),
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	}
	else{
		baseX = m_X + 31;
		baseY = m_Y;
		m_DispObj->SetDestRect( baseX + ( (long)texInfo.Width - anime->m_BaseX ),
								m_Y - anime->m_BaseY,
								baseX - anime->m_BaseX,
								m_Y + ( (long)texInfo.Height - anime->m_BaseY )	);
	}
	draw->Draw( m_DispObj );

	return true;
}
