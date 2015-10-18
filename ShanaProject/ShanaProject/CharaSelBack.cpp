/************************/
/* キャラセレクト中のメニュー	*/
/************************/

#include "CharaSelMenu.h"
#include "CharaSelBack.h"
#include "ModeCharaSelect.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CCharaSelBack::CCharaSelBack( CResBattle *game, CModeCharaSelect *battle_mode ):CSprite( game )
{
	m_Input = game->m_Input ;
	m_Battle = battle_mode;
//	m_Data = data;
	// 資源調達
	m_Anime.m_AnimeSpec		= game->m_AnimationManager->GetAnimation( ANIME_NO_CHARA_SELECT_BACK );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_CHARA_SELECT_BACK );
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
	m_X = 0;
//	m_SelectTop = CDataTitleMenu::TITLE_TOP_ARCADE;

	Setup();
}

CCharaSelBack::~CCharaSelBack()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

void CCharaSelBack::Setup()
{
/*	m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_ARCADE]	= false;
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
*/
}

bool CCharaSelBack::Event()
{
//	m_Input->UpDateState_Pad();

	return true;
}

bool CCharaSelBack::Move()
{
	//	m_Input->UpDateState_Pad();
	unsigned long pad1,pad2 ;
	pad1 = m_Input->GetPadData( 0 ) |  m_Input->GetPadData( 1 );
//	pad2 = m_Input->GetPadData( 1 );

	// メニュー表示中
/*	if( m_State == 0){
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
	}
	else if(m_State == 1 ){
		m_Flame++;
		if( m_Flame == 256 ){
			return FALSE ;
		}
	}
*/
	return TRUE;
}

bool CCharaSelBack::Draw( CD3DDraw *draw )
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
	anime = &m_Anime.GetMotionData(1)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画（背景）
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( 0, 0, 200, 100 );
//	draw->Draw( m_DispObj );

	////////
	/* 帯 */
	////////
	// 描画（選択）
	// 画像表示基準点
	m_DispObj->SetRotation( 0,0,0,0, 1, 20);
	m_DispObj->SetBlendColor( 0xffffffff );
	anime = &m_Anime.GetMotionData(0)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_X = (m_X+1)%800;
	m_DispObj->SetTexture( tex );
	m_DispObj->SetSrcRect( m_X,0,800+(m_X),texInfo.Height);
	m_DispObj->SetDestRect( 0 , 350,
							800,
							350 + (long)texInfo.Height );
	draw->Draw( m_DispObj );

	// ２本目
	m_DispObj->SetRotation( 0,0,0,0, 1,-35);
	m_DispObj->SetSrcRect( 800+(m_X),0,m_X,texInfo.Height);
	m_DispObj->SetDestRect( 0 , 250,
							800,
							250 + (long)texInfo.Height );
	draw->Draw( m_DispObj );

	return true;
}
