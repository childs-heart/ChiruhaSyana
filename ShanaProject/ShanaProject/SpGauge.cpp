#include "SpGauge.h"
#include "Game.h"
#include "ResGame.h"
#include "CLIB_Element.h"

CSpGauge::CSpGauge( CResGame *game, CShanaProt *target, int player )
:CSprite( game )
{
	m_Game	= game ;
	m_DispObjGroup		= m_Game->m_DispObjGroup;
	m_DispObj			= m_DispObjGroup->GetDispObj();
	m_Anime.m_AnimeSpec	= m_Game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_SCN_SP_GAUGE );
	
	m_Tex				= m_Game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_SP );

	m_DispObj->SetDestBlend( D3DBLEND_ONE );
	m_State = ENUM_SPGAUGE_STATE_GAUGE0;
	m_Target = target;
	m_Player = player;
	m_Flame = 0;
	// ‰Šúó‘Ô
	if( player == 1 ){
		m_X = 0;
		m_Y = 480;
	}else{
		m_X = 800;
		m_Y = 480;
	}
}

CSpGauge::~CSpGauge()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CSpGauge::Move()
{
	int val;
	int state;
	val = m_Target->GetSpGauge();
//	if( val >= ENUM_SPGAUGE_VAL_GAUGE3 ){
//		state = ENUM_SPGAUGE_STATE_GAUGE3;
//	}
	 if( val >= ENUM_SPGAUGE_VAL_GAUGE2 ){
		state = ENUM_SPGAUGE_STATE_GAUGE2;
	}
	else if( val >= ENUM_SPGAUGE_VAL_GAUGE1 ){
		state = ENUM_SPGAUGE_STATE_GAUGE1;
	}
	else{
		state = ENUM_SPGAUGE_STATE_GAUGE0;
	}

	m_Flame++;
	switch( m_State ){
		case ENUM_SPGAUGE_STATE_GAUGE1_IN:
		case ENUM_SPGAUGE_STATE_GAUGE2_IN:
		case ENUM_SPGAUGE_STATE_GAUGE3_IN:
			if( m_Flame > 15 ){
				ChangeState( m_State+1 );
			}
			break;
	}

	switch( state ){
		case ENUM_SPGAUGE_STATE_GAUGE1:
			if( m_State <= ENUM_SPGAUGE_STATE_GAUGE0 ){
				ChangeState( ENUM_SPGAUGE_STATE_GAUGE1_IN );
			}
			break;

		case ENUM_SPGAUGE_STATE_GAUGE2:
			if( m_State <= ENUM_SPGAUGE_STATE_GAUGE1 ){
				ChangeState( ENUM_SPGAUGE_STATE_GAUGE2_IN );
			}
			break;

		case ENUM_SPGAUGE_STATE_GAUGE3:
			if( m_State <= ENUM_SPGAUGE_STATE_GAUGE2 ){
				ChangeState( ENUM_SPGAUGE_STATE_GAUGE3_IN );
			}
			break;
	}


	return TRUE;
}

void CSpGauge::ChangeState( int state )
{
	m_Flame = 0;
	m_State = state;
	m_Anime.ChangeAction( state );

/*	switch( state ){
		case ENUM_SPGAUGE_STATE_GAUGE0:
			m_Anime.ChangeAction( state );
			m_AnimeNo		= 50;
			m_AnimeFlame	= 0;
			m_AnimeImgae	= m_Anime->m_StartAction[m_AnimeNo] ;
			break;

		case ENUM_SPGAUGE_STATE_GAUGE1_IN:
			m_AnimeNo		= 51;
			m_AnimeFlame	= 0;
			m_AnimeImgae	= m_Anime->m_StartAction[m_AnimeNo] ;
			break;

		case ENUM_SPGAUGE_STATE_GAUGE1:
			m_AnimeNo		= 52;
			m_AnimeFlame	= 0;
			m_AnimeImgae	= m_Anime->m_StartAction[m_AnimeNo] ;
			break;

		case ENUM_SPGAUGE_STATE_GAUGE2_IN:
			m_AnimeNo		= 53;
			m_AnimeFlame	= 0;
			m_AnimeImgae	= m_Anime->m_StartAction[m_AnimeNo] ;
			break;

		case ENUM_SPGAUGE_STATE_GAUGE2:
			m_AnimeNo		= 54;
			m_AnimeFlame	= 0;
			m_AnimeImgae	= m_Anime->m_StartAction[m_AnimeNo] ;
			break;

		case ENUM_SPGAUGE_STATE_GAUGE3_IN:
			m_AnimeNo		= 54;
			m_AnimeFlame	= 0;
			m_AnimeImgae	= m_Anime->m_StartAction[m_AnimeNo] ;
			break;

		case ENUM_SPGAUGE_STATE_GAUGE3:
			m_AnimeNo		= 54;
			m_AnimeFlame	= 0;
			m_AnimeImgae	= m_Anime->m_StartAction[m_AnimeNo] ;
			break;
	}
*/
}

bool CSpGauge::Draw( CD3DDraw *draw )
{
	int baseX;
	int baseY;
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// •`‰æi‰Šj
	// ‰æ‘œ•\Ž¦Šî€“_
	StImageData *anime ;
/*
	anime = &m_Anime.GetCurrentMotion()->m_Image;
//	m_X = CUtlScreen::test1;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetDestBlend( D3DBLEND_ONE );
	m_DispObj->SetTexture( tex );
	if( m_Player == 1 ){
		m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
								m_X + ( (long)texInfo.Width - anime->m_BaseX ),
								m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	}
	else{
		m_DispObj->SetDestRect( m_X + ( (long)texInfo.Width - anime->m_BaseX ),
								m_Y - anime->m_BaseY,
								m_X - anime->m_BaseX,
								m_Y + ( (long)texInfo.Height - anime->m_BaseY )	);
	}
	draw->Draw( m_DispObj );
*/
	// •`‰æiƒQ[ƒWj
//	anime = &m_Anime.GetActionData( 5 )->GetMotionData( 1 )->m_Image;
	int sp;
	float dx ;
	sp = m_Target->GetSpGauge();
	if( sp >= 300 ){
		dx = 1.0f;
		anime = &m_Anime.GetActionData( 0 )->GetMotionData( 3 )->m_Image;
	}
	else{
		dx = (float)( sp % 300 ) / 300 ;
		anime = &m_Anime.GetActionData( 0 )->GetMotionData( 2 )->m_Image;
	}

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetDestBlend( D3DBLEND_INVSRCALPHA );
	m_DispObj->SetTexture( tex );
	if( m_Player == 1 ){
		m_DispObj->SetSrcRect( 0, 0, texInfo.Width * dx, texInfo.Height );
		m_DispObj->SetDestRect( 78 - anime->m_BaseX , 568 - anime->m_BaseY ,
								78 + texInfo.Width * dx,
								568 + ( (long)texInfo.Height - anime->m_BaseY ) );
//		m_DispObj->SetDestRect( 50 - anime->m_BaseX , 563 - anime->m_BaseY ,
//								50 + texInfo.Width * dx,
//								563 + ( (long)texInfo.Height - anime->m_BaseY ) );
	}
	else{
		m_DispObj->SetSrcRect( 0, 0, texInfo.Width * dx, texInfo.Height );
		m_DispObj->SetDestRect( 532 + (long)texInfo.Width ,
								568 - anime->m_BaseY,
								532 + texInfo.Width - ( texInfo.Width * dx ),
								568 + ( (long)texInfo.Height - anime->m_BaseY ) );
//		m_DispObj->SetDestRect( 460 + ( (long)texInfo.Width - anime->m_BaseX ),
//								563 - anime->m_BaseY,
//								750 - texInfo.Width * dx,
//								563 + ( (long)texInfo.Height - anime->m_BaseY ) );
	}
	draw->Draw( m_DispObj );

	// •`‰æi˜gj
//	anime = &m_Anime.GetActionData( 5 )->GetMotionData( 0 )->m_Image;
	anime = &m_Anime.GetActionData( 0 )->GetMotionData( 0 )->m_Image;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetDestBlend( D3DBLEND_INVSRCALPHA );
	m_DispObj->SetTexture( tex );
	if( m_Player == 1 ){
		m_DispObj->SetDestRect( -20 - anime->m_BaseX , 500 - anime->m_BaseY ,
								-20 + ( (long)texInfo.Width - anime->m_BaseX ),
								500 + ( (long)texInfo.Height - anime->m_BaseY ) );
//		m_DispObj->SetDestRect( 20 - anime->m_BaseX , 540 - anime->m_BaseY ,
//								20 + ( (long)texInfo.Width - anime->m_BaseX ),
//								540 + ( (long)texInfo.Height - anime->m_BaseY ) );
	}
	else{
		m_DispObj->SetDestRect( 465 + ( (long)texInfo.Width - anime->m_BaseX ),
								500 - anime->m_BaseY,
								465 - anime->m_BaseX,
								500 + ( (long)texInfo.Height - anime->m_BaseY )	);
//		m_DispObj->SetDestRect( 450 + ( (long)texInfo.Width - anime->m_BaseX ),
//								540 - anime->m_BaseY,
//								450 - anime->m_BaseX,
//								540 + ( (long)texInfo.Height - anime->m_BaseY )	);
	}
	draw->Draw( m_DispObj );

	return TRUE;
}

