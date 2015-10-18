/************************/
/* キャラセレクト中のメニュー	*/
/************************/

#include "CharaSelPuchi.h"
#include "CharaSelBack.h"
#include "ModeCharaSelect.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CCharaSelPuchi::CCharaSelPuchi( CResBattle *game, CModeCharaSelect *battle_mode, int player ):CSprite( game )
{
	m_Input = game->m_Input ;
	m_Battle = battle_mode ;
//	m_Data = data;
	// 資源調達
	m_Anime.m_AnimeSpec		= game->m_AnimationManager->GetAnimation( ANIME_NO_CHARA_SELECT_PUCHI );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_CHARA_SELECT_PUCHI);
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
	m_Player				= player ;
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// ブレンド方法指定
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
	m_State = 0;
//	m_SelectTop = CDataTitleMenu::TITLE_TOP_ARCADE;

	m_Anime.ChangeAction(player);
	m_X = player*230;
	m_SelectChara = player ;
	m_Dir = (player == 0)?-1:1;

	Setup();
}

CCharaSelPuchi::~CCharaSelPuchi()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

void CCharaSelPuchi::Setup()
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

bool CCharaSelPuchi::Event()
{
//	m_Input->UpDateState_Pad();

	return true;
}

bool CCharaSelPuchi::Move()
{
	m_Input->UpDateState_Pad();
	unsigned long pad ;
	pad = m_Input->GetPadData( m_Player );
//	pad2 = m_Input->GetPadData( 1 );

	// メニュー表示中
	if( ( pad & PAD_RIGHT_ON ) == PAD_RIGHT_ON ){
		if( m_SelectChara < 1 ){
			m_SelectChara++;
			m_Anime.ChangeAction(m_SelectChara);
		}
	}
	if( ( pad & PAD_LEFT_ON ) == PAD_LEFT_ON ){
		if( m_SelectChara > 0 ){
			m_SelectChara--;
			m_Anime.ChangeAction(m_SelectChara);
		}
	}
	if( ( pad & PAD_BUTTON1_ON ) == PAD_BUTTON1_ON ){
		m_Battle->DecideChara( m_Player, m_SelectChara );
		m_Battle->SetMode(7);
	}
	return TRUE;
}

bool CCharaSelPuchi::Draw( CD3DDraw *draw )
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

	m_DispObj->SetDestBlend(D3DBLEND_INVSRCALPHA);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);

	////////////////
	/* キャラ　   */
	////////////////
	// 描画（選択）
	// 画像表示基準点
	m_DispObj->SetRotation( 0,0,0,0, 1, 0);
	m_DispObj->SetBlendColor( 0xffffffff );
	anime = &m_Anime.GetCurrentMotion()->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_DispObj->SetTexture( tex );
//	if( m_Player == 0 ){
		m_DispObj->SetSrcRect( (long)texInfo.Width,0,0,(long)texInfo.Height );
//	}
//	else{
		m_DispObj->SetSrcRect( 0,0,(long)texInfo.Width,(long)texInfo.Height );
//	}
	m_DispObj->SetDestRect( 290 + ( -anime->m_BaseX ) * m_Dir + m_SelectChara * 220 ,
										480 + ( -anime->m_BaseY ),
										290 + ( (long)texInfo.Width - anime->m_BaseX ) * m_Dir + m_SelectChara * 220,
										480 + ( (long)texInfo.Height - anime->m_BaseY ) );
/*	m_DispObj->SetDestRect( 200 + m_SelectChara * 230, 350,
							200 + m_SelectChara * 230+(long)texInfo.Width,
							350+(long)texInfo.Height );
*/	draw->Draw( m_DispObj );

	return true;
}
