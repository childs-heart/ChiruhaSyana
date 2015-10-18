/********************/
/* 背景クラス		*/
/********************/

#include "ScnBackMisago.h"
#include "ScnBack.h"

#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"

#include "UTL_Screen.h"

CScnBackMisago::CScnBackMisago( CResBattle *game , CScnBack *target ):CSprite( game ),m_Target(target)
{
	// 資源調達
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_SCN_BACK_MISAGO );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_STA_RURIDAN );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );
	m_DispObj->SetSrcBlend( D3DBLEND_SRCALPHA);
	m_DispObj->SetDestBlend( D3DBLEND_ONE);

	// 初期状態
	target->GetPosition( &m_X, &m_Y );
	m_Flame = 0;
	m_AddNum = 1;
	m_Anime.ChangeAction(1);

	// ブレンド方法指定
//	m_DispObj->SetDestBlend(D3DBLEND_ONE);
//	m_DispObj->SetSrcBlend(D3DBLEND_ONE);

	// ランダム回転
//	m_DispObj->SetRotation( 0,0,0,0, 1, ( rand()%360 ));
}

CScnBackMisago::~CScnBackMisago()
{
	m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CScnBackMisago::Move()
{

	m_Flame += m_AddNum ;

	if( m_Flame > 100 ){
		m_Flame = 100;
		m_AddNum = -1;
	}
	else if( m_Flame < 0 ){
		m_Flame = 0;
		m_AddNum = 1;
	}
	int blend;
	blend = 0.0045*(m_Flame*m_Flame);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB( blend , 0xff, 0xff, 0xff ) );
	return TRUE;
}

bool CScnBackMisago::Draw( CD3DDraw *draw )
{
//	CD3DDraw2	*draw2 = (CD3DDraw2*)(draw) ;
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;
	m_Target->GetPosition( &m_X, &m_Y );

/*　旧
	ST_IMAGE_DATA *anime ;
	anime = &m_Anime->m_AnimeData[m_AnimeImage] ;
	tex = m_Tex->GetTexture( m_Anime->m_AnimeData[m_AnimeImage].m_TextureNo ) ;
*/
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X + ( (long)texInfo.Width - anime->m_BaseX ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw->Draw( m_DispObj );

//	draw2->Draw2( m_DispObj , m_Flame );

	return TRUE;
}
