/************************/
/* バトル中のメニュー	*/
/************************/

#include "BattleMenu.h"
#include "ModeBattle.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CDataBattleMenu::CDataBattleMenu()
{
	for( int i = 0 ; i < 2 ; i++ ){
		m_AutoAttack[i] = 0;
		m_AutoGuard[i] = 0;
		m_AutoRecover[i] = 0;
		m_GaugeCtrl[i] = 0;
		m_StatusPlayer[i] = 0;
	}
	m_InfoDisp = 0;
}

void CDataBattleMenu::SetValue( int top, int value )
{
	switch( top ){
	case SELECT_TOP_STATUS_1P :
		m_StatusPlayer[0] = value;
		break;
	case SELECT_TOP_STATUS_2P :
		m_StatusPlayer[1] = value;
		break;
	case SELECT_TOP_SP_GAUGE :
		m_GaugeCtrl[0] = value;
		break;
	case SELECT_TOP_AIR_PASSIVE :
		m_AutoRecover[0] = value;
		break;
	case SELECT_TOP_INFORMATION_DISP:
		m_InfoDisp = value;
		break;
	default:
		break;
	}
	return ;
}

int CDataBattleMenu::GetValue( int top )
{
	switch( top ){
	case SELECT_TOP_STATUS_1P :
		return m_StatusPlayer[0];
		break;
	case SELECT_TOP_STATUS_2P :
		return m_StatusPlayer[1];
		break;
	case SELECT_TOP_SP_GAUGE :
		return m_GaugeCtrl[0];
		break;
	case SELECT_TOP_AIR_PASSIVE :
		return m_AutoRecover[0];
		break;
	case SELECT_TOP_INFORMATION_DISP:
		return m_InfoDisp ;
		break;
	default:
		break;
	}
	return 0;
}

CBattleMenu::CBattleMenu( CResBattle *game, CModeBattle *battle_mode, CDataBattleMenu *data, CShanaProt *target ):CSprite( game )
{
	m_Input = game->m_Input ;
	m_Battle = battle_mode;
	m_Data = data;
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_BATTLE_MENU );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_BATTLE_MENU );
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
	m_SelectTop = CDataBattleMenu::SELECT_TOP_STATUS_1P ;

	Setup();
}

CBattleMenu::~CBattleMenu()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );

	for( int i = 0 ; i < CDataBattleMenu::SELECT_TOP_MAX_VALUE ; i++ ){
		if( m_SelectItemImageNo[i] != NULL ){
			delete []m_SelectItemImageNo[i] ;
		}
	}
}

void CBattleMenu::Setup()
{
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_RESET]		= false;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_STATUS_1P]	= true;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_STATUS_2P]	= true;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_AIR_PASSIVE]	= true;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_AUTO_GUARD]	= false;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_SP_GAUGE]	= true;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_INFORMATION_DISP]	= true;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_VIEW_SCREEN]	= false;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_CHANGE_CHAR]	= false;
	m_SelectItemEnable[CDataBattleMenu::SELECT_TOP_EXIT]		= false;

	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_RESET]		= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_STATUS_1P]	= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_STATUS_2P]	= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_AIR_PASSIVE]	= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_AUTO_GUARD]	= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_SP_GAUGE]	= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_INFORMATION_DISP]	= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_VIEW_SCREEN]	= true;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_CHANGE_CHAR]	= false;
	m_SelectButtonEnable[CDataBattleMenu::SELECT_TOP_EXIT]		= true;

	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_RESET]		= 0;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_STATUS_1P]	= 4;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_STATUS_2P]	= 4;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_AIR_PASSIVE]	= 3;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_AUTO_GUARD]	= 0;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_SP_GAUGE]		= 3;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_INFORMATION_DISP]	= 2;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_VIEW_SCREEN]	= 0;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_CHANGE_CHAR]	= 0;
	m_SelectItemMaxValue[CDataBattleMenu::SELECT_TOP_EXIT]			= 0;

	for( int i = 0 ; i < CDataBattleMenu::SELECT_TOP_MAX_VALUE ; i++ ){
		if( m_SelectItemMaxValue[i] != 0 ){
			m_SelectItemImageNo[i] = new int[m_SelectItemMaxValue[i]];
		}
		else{
			m_SelectItemImageNo[i] = NULL ;
		}
	}
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_1P][CDataBattleMenu::STATUS_ITEM_MANUAL] = 11;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_1P][CDataBattleMenu::STATUS_ITEM_STAND] = 12;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_1P][CDataBattleMenu::STATUS_ITEM_CROUCH] = 13;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_1P][CDataBattleMenu::STATUS_ITEM_JUMP] = 14;

	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_2P][CDataBattleMenu::STATUS_ITEM_MANUAL] = 11;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_2P][CDataBattleMenu::STATUS_ITEM_STAND] = 12;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_2P][CDataBattleMenu::STATUS_ITEM_CROUCH] = 13;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_STATUS_2P][CDataBattleMenu::STATUS_ITEM_JUMP] = 14;

	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_AIR_PASSIVE][CDataBattleMenu::PASSIVE_ITEM_NEUTRAL] = 21;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_AIR_PASSIVE][CDataBattleMenu::PASSIVE_ITEM_FRONT] = 22;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_AIR_PASSIVE][CDataBattleMenu::PASSIVE_ITEM_BACK] = 23;

	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_SP_GAUGE][CDataBattleMenu::GAUGE_ITEM_NORMAL] = 31;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_SP_GAUGE][CDataBattleMenu::GAUGE_ITEM_MAX] = 32;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_SP_GAUGE][CDataBattleMenu::GAUGE_ITEM_INFINITY] = 33;

	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_INFORMATION_DISP][CDataBattleMenu::DISP_ITEM_OFF] = 41;
	m_SelectItemImageNo[CDataBattleMenu::SELECT_TOP_INFORMATION_DISP][CDataBattleMenu::DISP_ITEM_ON] = 42;
}

bool CBattleMenu::Event()
{
//	m_Input->UpDateState_Pad();

	return true;
}

bool CBattleMenu::Move()
{
//	m_Input->UpDateState_Pad();
	unsigned long pad1,pad2 ;
	pad1 = m_Input->GetPadData( 0 );
//	pad2 = m_Input->GetPadData( 1 );
	pad1 = m_Input->GetPadData( 1 );
	// メニュー非表示中
	if( m_State == 0 ){
		if( ( ( pad1 & PAD_BUTTON5_ON ) == PAD_BUTTON5_ON ) ){
			m_State = 1;
			m_Battle->BattlePause();
			m_SelectTop = CDataBattleMenu::SELECT_TOP_STATUS_1P ;
		}
		// おまけ、スローモーション
		else if( ( pad1 & PAD_BUTTON8 ) == PAD_BUTTON8 ){
			m_State = 10;
			m_Battle->BattlePause();
		}

	}
	// メニュー表示中
	else if( m_State == 1 ){
		if( ( pad1 & PAD_BUTTON5_ON ) == PAD_BUTTON5_ON ){
			m_State = 0;
			m_Battle->BattleResume();
		}
		else{
			if( ( pad1 & PAD_DOWN_ON ) == PAD_DOWN_ON ){
				m_SelectTop++;
				if( m_SelectTop > (int)CDataBattleMenu::SELECT_TOP_EXIT ){
					m_SelectTop = CDataBattleMenu::SELECT_TOP_EXIT;
				}
			}
			if( ( pad1 & PAD_UP_ON ) == PAD_UP_ON ){
				m_SelectTop--;
				if( m_SelectTop < (int)CDataBattleMenu::SELECT_TOP_STATUS_1P ){
					m_SelectTop = CDataBattleMenu::SELECT_TOP_STATUS_1P;
				}
			}
			if( ( pad1 & PAD_RIGHT_ON ) == PAD_RIGHT_ON ) {
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
			if( ( m_SelectButtonEnable[m_SelectTop] == true ) 
				&& (( pad1 & PAD_BUTTON1_ON ) == PAD_BUTTON1_ON ) ){
				OnButtom( m_SelectTop );
			}
		}
	}
	// スクリーンショット表示中
	else if( m_State == 2 ){
		if( ( pad1 & PAD_BUTTON1_ON ) == PAD_BUTTON1_ON ){
			m_State = 1;
		}
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

	return TRUE;
}

void CBattleMenu::OnButtom( int item )
{
	switch( item ){
	case CDataBattleMenu::SELECT_TOP_VIEW_SCREEN:
		m_State = 2;
		break;
	case CDataBattleMenu::SELECT_TOP_EXIT:
		m_State = 0;
		m_Battle->BattleResume();
		break;
	}
}

/*bool CBattleMenu::FlameResult()
{
	return TRUE;
}
*/
bool CBattleMenu::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	m_DispObj->SetBlendColor( 0xa0ffffff );
	m_DispObj->SetRotation( 1,0,0,0, 0, 0);
	StImageData *anime ;

	if( m_State != 1 ){
		return true;
	}

	// 描画（背景）
	// 画像表示基準点
	anime = &m_Anime.GetMotionData(0)->m_Image ;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 描画（背景）
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( 0, 0, 800, 600 );
	draw->Draw( m_DispObj );

	// 描画（項目）
	// 画像表示基準点
	m_DispObj->SetRotation( 1,0,0,0, 0, 0);
	for( int i = 1 ; i < CDataBattleMenu::SELECT_TOP_MAX_VALUE ; i++ ){
		if( m_SelectTop == i ){
			m_DispObj->SetBlendColor( 0xffffffff );
		}
		else{
			m_DispObj->SetBlendColor( 0xff666666 );
		}
		anime = &m_Anime.GetMotionData(i)->m_Image ;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// 描画（背景）
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( 200 , 50 + 40 * i,
								200 + (long)texInfo.Width, 50 + 40 * i + (long)texInfo.Height );
		draw->Draw( m_DispObj );
	}


	// 描画（選択）
	// 画像表示基準点
	m_DispObj->SetRotation( 1,0,0,0, 0, 0);
	for( int i = 1 ; i < CDataBattleMenu::SELECT_TOP_MAX_VALUE ; i++ ){
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
				m_DispObj->SetDestRect( 500 , 50 + 40 * i,
									500 + (long)texInfo.Width, 50 + 40 * i + (long)texInfo.Height );
				draw->Draw( m_DispObj );
			}
		}
	}

	return true;
}
