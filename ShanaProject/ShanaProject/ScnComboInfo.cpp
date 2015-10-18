/********************/
/* コンボ管理クラス	*/
/********************/

#include "ScnComboInfo.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

CScnComboInfo::CScnComboInfo( CResBattle *game, CShanaProt *target, int player ):CSprite( game )
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_SCN_COMBO_INFO );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_COMBO );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	m_Target = target;
	m_Flame = 0;
	m_Player = player;
	m_Combo = 0;
	m_State = 0;
	// 初期状態
	if( player == 1 ){
		m_X = 600;
		m_Y = 200;
	}else{
		m_X = 200;
		m_Y = 200;
	}
	
	// ブレンド方法指定
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CScnComboInfo::~CScnComboInfo()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CScnComboInfo::InterfereFinalize()
{
	int current = m_Target->GetDamageInfo()->m_ComboCount ;

//	if( m_Combo > current ){
		m_Combo = current ;
//	}
	return TRUE;
}

bool CScnComboInfo::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	int baseX, baseY ;
	int tmp = m_Combo ;
	if( tmp > 1 ){
		for( int i = 1,j = 0 ; (tmp/i)!=0 ; i*=10, j++ ){
			// 描画 数字
			anime = &m_Anime.GetActionData(0)->GetMotionData( (tmp/i)%(i*10) )->m_Image;
			tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
			tex->GetTextureInfo( &texInfo ) ;
			m_DispObj->SetTexture( tex );
			m_DispObj->SetBlendColor( 0xffffffff );

			baseX = m_X - 89*j ;
			baseY = m_Y ;
			m_DispObj->SetDestRect( baseX - anime->m_BaseX , baseY - anime->m_BaseY ,
									baseX + ( (long)texInfo.Width - anime->m_BaseX ),
									baseY + ( (long)texInfo.Height - anime->m_BaseY ) );
			draw->Draw( m_DispObj );
		}

		// ヒット表示
		anime = &m_Anime.GetActionData(0)->GetMotionData( 10 )->m_Image;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		m_DispObj->SetTexture( tex );
		m_DispObj->SetBlendColor( 0xffffffff );

		baseX = m_X + 90 ;
		baseY = m_Y + 7 ;
		m_DispObj->SetDestRect( baseX - anime->m_BaseX , baseY - anime->m_BaseY ,
								baseX + ( (long)texInfo.Width - anime->m_BaseX ),
								baseY + ( (long)texInfo.Height - anime->m_BaseY ) );
		draw->Draw( m_DispObj );
	}

	return true;
}
