/********************/
/* エフェクトテスト	*/
/********************/

#include "CChaRibbon.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"
#include "ResBattle.h"

//#include "EffTest.h"
//#include "EffShanaOpt.h"
#include "EffHit008.h"
//#include "EffHit002.h"
//#include "EffHit003.h"
//#include "EffHit004.h"
#include "EffHit005.h"
//#include "EffHit006.h"
//#include "EffHit007.h"
#include "EffGuard001.h"
//#include "EffAction01.h"
//#include "EffAction02.h"

CChaRibbon::CChaRibbon( CResBattle *game, CShanaProt *target, CCommonData *common ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_RIBBON );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_EFF_SHA802_1 );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

/*	m_Anime.m_AnimeSpec->CreateAction( 0, 10 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 0, 0, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 1, 1, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 2, 2, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 3, 3, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 4, 4, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 5, 5, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 6, 6, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 7, 7, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 8, 8, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 9, 9, 0, 320, 240 );
*/
	//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_Dir = -target->getDir();
	m_X += m_Dir * 100;
	m_Y -= 100;
	m_Flame = 0;
	m_Hitted = 0;
	m_ResBattle = game;
	m_Common = common;
	m_Target = target->GetTarget() ;
	m_Anime.ChangeAction(0,0);

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,255,255,255) );
	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CChaRibbon::~CChaRibbon()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CChaRibbon::Move()
{
	m_Flame++;
	m_X += m_Dir * 9;
	if( m_X < -60 ){
		return FALSE ;
	}
	else if( m_X > 1660 ){
		return FALSE ;
	}
	if( m_Hitted == 1 ){
		return FALSE ;
	}
	return TRUE;
}

bool CChaRibbon::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image ;

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;

	// 描画
//	m_DispObj->SetRotation( 1,-90,0,0, 0, 0);
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X - anime->m_BaseX * m_Dir , m_Y - anime->m_BaseY ,
							m_X + ( ((long)texInfo.Width - anime->m_BaseX) * m_Dir ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );

	draw->Draw( m_DispObj );

	return TRUE;
}

bool CChaRibbon::Interfere()
{
	// キャラクター移動
//	Transfer();

	// 相手がいる場合の処理がここから開始
	////////////////////
	if( m_Target == NULL ){
		return true;
	}

	// 当たり判定
	if( m_Anime.IsAttackEnabled() && m_Target->IsCollisioned( this ) ){	// 相手に攻撃あたってる？
		HitAttack();
	}

	return true;
}

void CChaRibbon::HitAttack()
{
	m_Anime.AttackHit();		// 名前変えよう・・・

	m_Hitted=1;
	if( m_Target->ReceiveAttack( this , &m_Anime ) == 0 ){
		////////////
		// エフェクト処理
		new(m_ResBattle->m_CommonEffectFront) CEffHit008( m_ResBattle, m_Target );
		new(m_ResBattle->m_CommonEffectFront) CEffHit005( m_ResBattle, m_Target );
	}
	else{
		////////////
		// エフェクト処理
//		switch( m_State ){
//			case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
			new(m_ResBattle->m_CommonEffectFront) CEffGuard001( m_ResBattle, m_Target );
//			break;
//		}
	}
}
