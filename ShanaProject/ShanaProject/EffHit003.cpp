/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>
#include "EffHit003.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CEffHit003::CEffHit003( CResBattle *game, CShanaProt *target ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_HIT_003 );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_BACK_WHITE );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime.m_AnimeSpec, 94 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 94 );

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_X -= (rand()%30);
	m_Y -= 70+(rand()%50);
	m_Flame = 0;
	m_FlagGround = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	m_DispObj->SetBlendColor( 0xffFFFFFF );

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));

	for( int i = 0 ; i < 5 ; i++ ){
		m_HistoryX[i] = m_X;
		m_HistoryY[i] = m_Y;
	}
	StartAir( ((rand()%7)+3)*target->getDir(), 1+(rand()%5), 0, 0.15f );
//	StartAir( ((rand()%20)+3)*target->getDir(), 1+(rand()%20), 0, 0.15f );
	m_Life = 30+rand()%30;
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(255,200,0,0) );

	DoAir();
}

CEffHit003::~CEffHit003()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffHit003::Move()
{
	// 10フレ経過で終了
	m_Flame++;
	if( m_Flame == m_Life ){
		return FALSE ;
	}

	for( int i = 4 ; i > 0 ; i-- ){
		m_HistoryX[i] = m_HistoryX[i-1];
		m_HistoryY[i] = m_HistoryY[i-1];
	}
	m_HistoryX[0] = m_X;
	m_HistoryY[0] = m_Y;

	DoAir();
	if( m_Y > 500 ){
		m_Y = 500;
		m_FlagGround = 1;
		for( int i = 0 ; i < 5 ; i++ ){
			m_HistoryX[i] = m_X;
			m_HistoryY[i] = m_Y;
		}
		EndAir();
	}
	return TRUE;
}

bool CEffHit003::Draw( CD3DDraw *draw )
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

	int arg;

	arg = m_FlagGround==0?3:2;		// 奇跡のながさ

	float subX,subY,subXY;
	subX = m_HistoryX[arg] - m_X;
	subY = m_HistoryY[arg] - m_Y;
	subXY = sqrt( subX*subX + subY*subY );
	int centerX;
	centerX = ( m_HistoryX[arg] + m_X )/2;
	// 描画
	m_DispObj->SetRotation( 0,0,0,0, 1, atan2( subX, subY ) * (57.29583)+180 );
	m_DispObj->SetTexture( tex );

	m_DispObj->SetDestRect( m_X - 1 ,
							m_Y - subXY/2 ,
							m_X + 1 ,
							m_Y + subXY/2 ) ;

	draw->Draw( m_DispObj );

	return TRUE;
}


// ジャンプ開始
void CEffHit003::StartAir( float vec_x, float vec_y, int op1, float gravity )
{
	m_AirVector[0]	= vec_x;
	m_AirVector[1]	= vec_y;
	m_AirBase[0]	= m_X;
	m_AirBase[1]	= m_Y;
	m_AirTime		= op1;
	m_AirGravity	= gravity;
}

// ジャンプ着地
void CEffHit003::EndAir()
{
	StartAir( m_AirVector[0], m_AirVector[1], 0, m_AirGravity );
}

// 空中動作
void CEffHit003::DoAir()
{
	m_AirTime++ ;
	m_Y = m_AirBase[1] - ( m_AirVector[1] * m_AirTime - ( m_AirGravity * ( m_AirTime * m_AirTime) ) );// m_Vector[ENUM_VECTOR_UP];
//	m_AirIncrease = m_AirVector[1] - m_AirGravity * 2 * m_AirTime;
	m_X += m_AirVector[0];
}
