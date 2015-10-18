#include "Timer.h"
#include "CLIB_Sprite.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"
#include "CLIB_FPS.h"

CTimer::CTimer( CResBattle *game ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TIMER );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TIME );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// 初期状態
	m_X = 400;
	m_Y = 40;
	m_Flame = 0;

	// ブレンド方法指定
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
	m_RotZ[0] = 0;
	m_RotZ[1] = 0;

	// タイマーセット
	m_TimeCount = 99;

	SetTime( 99, true );
}

CTimer::~CTimer()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CTimer::Move()
{

	m_RotZ[0] = m_RotZ[0]+0.1f;
	if( m_RotZ[0] >=360 ) m_RotZ[0] = 0;
	if( m_RotZ[1] <= 0 ){
	    m_RotZ[1] = 360.0f - 0.2f;
	}else{
		m_RotZ[1] -= 0.2f ;
	}

	// 時間
	m_StartTickCount = timeGetTime();

	return TRUE;
}

void CTimer::SetTime( int count, int enable )
{
	m_TimeCount = count ;

	m_StartTickCount = timeGetTime();

}

bool CTimer::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	// 描画
	// 画像表示基準点
	StImageData *anime ;

	// 描画（アウトサークル）
	// 画像表示基準点
	anime = &m_Anime.GetActionData(0)->GetMotionData(0)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_DispObj->SetTexture( tex );
	m_DispObj->SetRotation( 0,0,0,0, 1, m_RotZ[0]);
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X + ( (long)texInfo.Width - anime->m_BaseX ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );

	// 描画（インサークル）
	anime = &m_Anime.GetActionData(1)->GetMotionData(0)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_DispObj->SetTexture( tex );
	m_DispObj->SetRotation( 0,0,0,0, 1, m_RotZ[1]);
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X + ( (long)texInfo.Width - anime->m_BaseX ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );

	// 時間
	int ti = CFps::GetCFps()->GetFPS();
	anime = &m_Anime.GetActionData(2)->GetMotionData(ti/10)->m_Image ;
//	anime = &m_Anime.GetActionData(2)->GetMotionData((m_StartTickCount%100000)/10000)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_DispObj->SetTexture( tex );
	m_DispObj->SetRotation( 0,0,0,0,0,0 );
	m_DispObj->SetDestRect( m_X - 32 - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X - 32 + ( (long)texInfo.Width - anime->m_BaseX ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );
	anime = &m_Anime.GetActionData(2)->GetMotionData(ti%10)->m_Image ;
//	anime = &m_Anime.GetActionData(2)->GetMotionData((m_StartTickCount%10000)/1000)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_DispObj->SetTexture( tex );
	m_DispObj->SetRotation( 0,0,0,0,0,0 );
	m_DispObj->SetDestRect( m_X + 32 - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X + 32 + ( (long)texInfo.Width - anime->m_BaseX ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );


	return TRUE;
}
