/********************/
/* エフェクトテスト	*/
/********************/

#include "TestX.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"
#include "CLIB_D3DDraw3.h"

CTestX::CTestX( CResBattle *game ):CSprite( game )
{
	// 資源調達
	m_Input = game->m_Input ;
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_EFF_X );
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_BACK_WHITE );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
	game->m_MeshTestGroup->LoadXFile( 0, "asm_r.x" );
	game->m_MeshTestGroup->LoadXFile( 1, "asm_l.x" );
	game->m_MeshTestGroup->LoadXFile( 2, "testX2.x" );
	m_DispObj->SetXFile( game->m_MeshTestGroup->GetXFile( 0 ) );
	m_DispObj->SetScale( 1 );

/*	m_Anime.m_AnimeSpec->CreateAction( 0, 10 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 0, 0, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 1, 1, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 2, 2, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 3, 3, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 4, 4, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 5, 5, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 6, 6, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 7, 7, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 8, 8, 4, 320, 240 );
	m_Anime.m_AnimeSpec->GetActionData( 0 )->SetMotionData( 9, 9, 0, 320, 240 );
*/
	//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// 初期状態
	m_X = 400;
	m_Y = 300;
	m_fX = 0;
	m_fY = 0;
	m_fZ = 0;
	rotx = 0;
	roty = 0;
	m_Flame = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ZERO);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);
}

CTestX::~CTestX()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CTestX::Move()
{
	rotx++;
	roty++;
//	m_DispObj->SetRotation( 2, rotx, 3, rotx, 1,rotx );

//	m_Input->UpDateState_Pad();
	unsigned long pad1,pad2 ;
	pad1 = m_Input->GetPadData( 1 );
	pad2 = m_Input->GetPadData( 1 );
	// メニュー非表示中
	if( ( pad1 & PAD_DOWN ) == PAD_DOWN ){
		m_fY ++;
	}
	if( ( pad1 & PAD_UP ) == PAD_UP ){
		m_fY --;
	}
	if( ( pad1 & PAD_LEFT ) == PAD_LEFT ){
		m_fX --;
	}
	if( ( pad1 & PAD_RIGHT ) == PAD_RIGHT ){
		m_fX ++;
	}
	if( ( pad1 & PAD_BUTTON1 ) == PAD_BUTTON1 ){
		m_fZ --;
	}
	if( ( pad1 & PAD_BUTTON2 ) == PAD_BUTTON2 ){
		m_fZ ++;
	}

	return TRUE;
}

bool CTestX::Draw(CD3DDraw *draw)
{
	CD3DDraw3	*draw3;
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;

	m_DispObj->SetXFile( m_Game->m_MeshTestGroup->GetXFile( 0 ) );
	m_DispObj->SetRotation( 0, 0,1,rotx,0,0 );
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y ,
							m_X,
							m_Y);
	draw3 = (CD3DDraw3*)(draw);
	draw3->Draw3( m_DispObj, m_fX, m_fY, m_fZ );
//
	m_DispObj->SetXFile( m_Game->m_MeshTestGroup->GetXFile( 1 ) );
	m_DispObj->SetRotation( 0, 0,1,-rotx,0,0 );
	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
							m_X + ( (long)texInfo.Width - anime->m_BaseX ),
							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
	draw3 = (CD3DDraw3*)(draw);
	draw3->Draw3( m_DispObj, m_fX, m_fY, m_fZ );
//
	m_DispObj->SetXFile( NULL );
	m_DispObj->SetRotation( 1, rotx, 0, 0, 0,0 );
	m_DispObj->SetDestRect( m_fX + 400 - anime->m_BaseX , m_fY + 300- anime->m_BaseY  ,
							m_fX + 400  + ( (long)texInfo.Width - anime->m_BaseX ),
							m_fY + 300  + ( (long)texInfo.Height - anime->m_BaseY ) );
//	draw3 = (CD3DDraw3*)(draw);
	draw->Draw( m_DispObj );

	return TRUE;
}
