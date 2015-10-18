/************************/
/* キャラセレクト中のメニュー	*/
/************************/

#include "CharaSelCut.h"
#include "CharaSelBack.h"
#include "ModeCharaSelect.h"
#include "ShanaProt.h"
#include "CharaSelPuchi.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CCharaSelCut::CCharaSelCut( CResBattle *game, CModeCharaSelect *battle_mode,
					CCharaSelPuchi* tar1 ,CCharaSelPuchi* tar2  ):CSprite( game )
{
	m_Input = game->m_Input ;
	m_Battle = battle_mode;
//	m_Data = data;
	// 資源調達
	m_Anime.m_AnimeSpec		= game->m_AnimationManager->GetAnimation( ANIME_NO_CHARA_SELECT_CUTIN );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_CHARA_SELECT_CUTIN );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// ブレンド方法指定
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
	m_Target1 = tar1;
	m_Target2 = tar2;

	m_State = 0;
	m_X = 0;
//	m_SelectTop = CDataTitleMenu::TITLE_TOP_ARCADE;

	Setup();
}

CCharaSelCut::~CCharaSelCut()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

void CCharaSelCut::Setup()
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

bool CCharaSelCut::Event()
{
//	m_Input->UpDateState_Pad();

	return true;
}

bool CCharaSelCut::Move()
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

bool CCharaSelCut::Draw( CD3DDraw *draw )
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
	/* キャラ　1P */
	////////////////
	// 描画（選択）
	// 画像表示基準点
	m_DispObj->SetRotation( 0,0,0,0, 1, 0);
	m_DispObj->SetBlendColor( 0xffffffff );
	anime = &m_Anime.GetMotionData(m_Target1->m_SelectChara)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_DispObj->SetTexture( tex );
	m_DispObj->SetSrcRect( (long)texInfo.Width,0,0,(long)texInfo.Height );
	m_DispObj->SetDestRect( 0 , 0,
							(long)texInfo.Width,
							(long)texInfo.Height );
	draw->Draw( m_DispObj );

	////////////////
	/* キャラ　2P */
	////////////////
	// 描画（選択）
	// 画像表示基準点
	m_DispObj->SetRotation( 0,0,0,0, 1, 0);
	m_DispObj->SetBlendColor( 0xffffffff );
	anime = &m_Anime.GetMotionData(m_Target2->m_SelectChara)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画
	m_DispObj->SetTexture( tex );
	m_DispObj->SetSrcRect( (long)texInfo.Width,0,0,(long)texInfo.Height );
	m_DispObj->SetDestRect( 800 , 0,
							800-(long)texInfo.Width,
							(long)texInfo.Height );
	draw->Draw( m_DispObj );

	return true;
}
