/************************/
/* バトル中のメニュー	*/
/************************/

#include "TitleMenu.h"
#include "ModeTitle.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CDataTitleMenu::CDataTitleMenu()
{
//	m_InfoDisp = 0;
}

void CDataTitleMenu::SetValue( int top, int value )
{
	switch( top ){
	default:
		break;
	}
	return ;
}

int CDataTitleMenu::GetValue( int top )
{
	switch( top ){
	default:
		break;
	}
	return 0;
}

CTitleMenu::CTitleMenu( CResBattle *game, CModeTitle *battle_mode ):CSprite( game )
{
	m_Input = game->m_Input ;
	m_Battle = battle_mode;
//	m_Data = data;
	// 資源調達
	m_Anime.m_AnimeSpec		= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_MENU );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_MENU );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// ブレンド方法指定
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
	m_State = 0;
	m_SelectTop = CDataTitleMenu::TITLE_TOP_ARCADE;

	Setup();
}

CTitleMenu::~CTitleMenu()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );

	for( int i = 0 ; i < CDataTitleMenu::TITLE_TOP_MAX_VALUE ; i++ ){
		if( m_SelectItemImageNo[i] != NULL ){
			delete m_SelectItemImageNo[i] ;
		}
	}
}

void CTitleMenu::Setup()
{
	m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_ARCADE]	= false;
	m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_VERSUS]	= false;
	m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_TRAINNING]	= false;
	m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_OPTION]	= false;
	m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_EXIT]		= false;

	m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_ARCADE]		= false;
	m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_VERSUS]		= false;
	m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_TRAINNING]	= true;
	m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_OPTION]		= false;
	m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_EXIT]		= true;

	m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_ARCADE]		= 0;
	m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_VERSUS]		= 0;
	m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_TRAINNING]	= 0;
	m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_OPTION]		= 0;
	m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_EXIT]		= 0;

	for( int i = 0 ; i < CDataTitleMenu::TITLE_TOP_MAX_VALUE ; i++ ){
		if( m_SelectItemMaxValue[i] != 0 ){
			m_SelectItemImageNo[i] = new int[m_SelectItemMaxValue[i]];
		}
		else{
			m_SelectItemImageNo[i] = NULL ;
		}
	}
}

bool CTitleMenu::Event()
{
//	m_Input->UpDateState_Pad();

	return true;
}

bool CTitleMenu::Move()
{
	//	m_Input->UpDateState_Pad();
	unsigned long pad1,pad2 ;
	pad1 = m_Input->GetPadData( 0 ) |  m_Input->GetPadData( 1 );
//	pad2 = m_Input->GetPadData( 1 );

	// メニュー表示中
	if( m_State == 0){
		if( ( pad1 & PAD_DOWN_ON ) == PAD_DOWN_ON ){
			m_SelectTop++;
			if( m_SelectTop > (int)CDataTitleMenu::TITLE_TOP_EXIT ){
				m_SelectTop = CDataTitleMenu::TITLE_TOP_EXIT ;
			}
		}
		if( ( pad1 & PAD_UP_ON ) == PAD_UP_ON ){
			m_SelectTop--;
			if( m_SelectTop < (int)CDataTitleMenu::TITLE_TOP_ARCADE ){
				m_SelectTop = CDataTitleMenu::TITLE_TOP_ARCADE;
			}
		}
	/*	if( ( pad1 & PAD_RIGHT_ON ) == PAD_RIGHT_ON ) {
			m_SelectItem = m_Data->GetValue( m_SelectTop );
			m_SelectItem++;
			if( m_SelectItem >= m_SelectItemMaxValue[ m_SelectTop ] ){
				m_SelectItem = m_SelectItemMaxValue[ m_SelectTop ] - 1;
			}
			m_Data->SetValue( m_SelectTop, m_SelectItem );
		}
		if( ( pad1 & PAD_LEFT_ON ) == PAD_LEFT_ON ) {
			m_SelectItem = m_Data->GetValue( m_SelectTop );
			if( m_SelectItem > 0 ){
				m_SelectItem--;
			}
			m_Data->SetValue( m_SelectTop, m_SelectItem );
		}
	*/
		if( ( m_SelectButtonEnable[m_SelectTop] == true ) 
			&& (( pad1 & PAD_BUTTON1_ON ) == PAD_BUTTON1_ON ) ){
			OnButtom( m_SelectTop );
		}
		// おまけ　スローモーション
		else if( m_State == 10 ){
			m_Flame ++;
			if( m_Flame > 10 ){
	//			if( ( pad1 & PAD_BUTTON7 ) != PAD_BUTTON7 ){
					m_State = 0;
					m_Battle->BattleResume();
	//			}
				m_Flame = 0;
			}
		}
	}
	else if(m_State == 1 ){
		m_Flame++;
		if( m_Flame == 256 ){
			return FALSE ;
		}
	}

	return TRUE;
}

void CTitleMenu::OnButtom( int item )
{
	switch( item ){
	case CDataTitleMenu::TITLE_TOP_ARCADE:
		m_State = 1;
		m_Flame = 0;
//		m_Battle->BattleResume();
		break;
	case CDataTitleMenu::TITLE_TOP_TRAINNING:
		m_State = 2;
		m_Flame = 0;
		m_Battle->BattleResume();
		break;
	}
}


bool CTitleMenu::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	m_DispObj->SetBlendColor( 0xa0ffffff );
	m_DispObj->SetRotation( 1,0,0,0, 0, 0);
	StImageData *anime ;

//	if( m_State = 0 ){
//		return true;
//	}

	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
	// 描画（背景）
	// 画像表示基準点
	anime = &m_Anime.GetMotionData(0)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画（背景）
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( 0, 0, 800, 600 );
//	draw->Draw( m_DispObj );

	// 描画（項目）
	// 画像表示基準点
	m_DispObj->SetRotation( 1,0,0,0, 0, 0);
	for( int i = 0 ; i < CDataTitleMenu::TITLE_TOP_MAX_VALUE ; i++ ){
		if( m_SelectTop == i ){
			m_DispObj->SetBlendColor( 0xffffffff );
			anime = &m_Anime.GetMotionData(i+5)->m_Image ;
		}
		else{
			m_DispObj->SetBlendColor( 0xff666666 );
			anime = &m_Anime.GetMotionData(i)->m_Image ;
		}
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// 描画（背景）
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( 400 - anime->m_BaseX , 350 - anime->m_BaseY + 40 * i,
								400 + (long)texInfo.Width - anime->m_BaseX,
								350 + 40 * i + (long)texInfo.Height - anime->m_BaseY );
		draw->Draw( m_DispObj );
	}

	// 描画（選択）
	// 画像表示基準点
	m_DispObj->SetRotation( 1,0,0,0, 0, 0);
	for( int i = 0 ; i < CDataTitleMenu::TITLE_TOP_MAX_VALUE ; i++ ){
		if( m_SelectItemEnable[i] == true ){
			if( m_SelectTop == i ){
				m_DispObj->SetBlendColor( 0xffffffff );
			}
			else{
				m_DispObj->SetBlendColor( 0xff666666 );
			}
			if( m_SelectItemEnable[i] == true ){
				anime = &m_Anime.GetMotionData( m_SelectItemImageNo[i][m_Data->GetValue(i)])->m_Image ;
				tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
				tex->GetTextureInfo( &texInfo ) ;
				// 描画（背景）
				m_DispObj->SetTexture( tex );
				m_DispObj->SetDestRect( 400 - anime->m_BaseX , 350 - anime->m_BaseY + 40 * i,
										400 + (long)texInfo.Width - anime->m_BaseX,
										350 + 40 * i + (long)texInfo.Height - anime->m_BaseY );
				draw->Draw( m_DispObj );
			}
		}
	}

	// 描画（コピーライト）
	// 画像表示基準点
	m_DispObj->SetBlendColor( 0xffffffff );
	m_DispObj->SetRotation( 0,0,0,0, 0, 0);
	anime = &m_Anime.GetMotionData(10)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( 400 - anime->m_BaseX , 572 - anime->m_BaseY,
							400 + (long)texInfo.Width - anime->m_BaseX,
							572 + (long)texInfo.Height - anime->m_BaseY );
	draw->Draw( m_DispObj );

	// 描画（コピーライト）
	// 画像表示基準点
	m_DispObj->SetRotation( 0,0,0,0, 0, 0);
	anime = &m_Anime.GetMotionData(11)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( 763 - anime->m_BaseX , 572 - anime->m_BaseY,
							763 + (long)texInfo.Width - anime->m_BaseX,
							572 + (long)texInfo.Height - anime->m_BaseY );
	draw->Draw( m_DispObj );

	// 暗幕
	if( m_State == 1 ){
		m_DispObj->SetDestBlend(D3DBLEND_INVSRCALPHA);
		m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
		anime = &m_Anime.GetMotionData(12)->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		m_DispObj->SetBlendColor( D3DCOLOR_ARGB( m_Flame,255,255,255 ));
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( 0,0,800,600 );
		draw->Draw( m_DispObj );
	}

	return true;
}
