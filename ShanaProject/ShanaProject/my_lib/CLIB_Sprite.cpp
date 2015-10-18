
#include "CLIB_Sprite.h"
#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
//#include "CLIB_Element.h"
//#include "CLIB_Texture.h"

CSprite::CSprite( )
{

}

CSprite::CSprite( CResGame *game )
{
	// 資源調達
	m_Game	= game ;
	
	// 継承先で定義するメンバ
	m_Tex		= NULL ;
	m_DispObj	= NULL ;
	m_DispObjGroup = NULL ;

	m_X = 0;
	m_Y = 0;

	m_AnimeNo		= 0;
	m_AnimeFlame	= 0;
	m_AnimeImage	= 0 ;

	m_State = 0;
	m_Flame = 0;
}

CSprite::~CSprite()
{
	if( m_DispObjGroup != NULL ){
		m_DispObjGroup->FreeDispObj( m_DispObj );
	}
}

bool CSprite::Move()
{
	return TRUE;
}

bool CSprite::Action()
{
	return TRUE;
}

bool CSprite::ActionFinalize()
{
	return TRUE;
}

bool CSprite::Event()
{
	return TRUE;
}

bool CSprite::Interfere()
{
	return TRUE;
}

void CSprite::ChangeState( int state )
{
}

bool CSprite::Animation( )
{
	// フレーム経過
	m_Anime.StepFlame( 1 );

	return TRUE;
}

bool CSprite::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image;

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

	return TRUE;
}

bool CSprite::InterfereFinalize( )
{
	// アニメーション行うときは、こいつを実行
//	Animation( );

//	m_DispObj->SetBlendColor(0);
	return TRUE;
}

bool CSprite::Draw( )
{
	return TRUE;
}

bool CSprite::DrawFinalize( )
{
	// アニメーション行うときは、こいつを実行
	Animation( );

//	m_DispObj->SetBlendColor(0);
	return TRUE;
}

int CSprite::GetState()
{
	return m_State;
}

void CSprite::GetPosition(int *x, int *y)
{
	*x = this->m_X;
	*y = this->m_Y;
}

void CSprite::SetPosition(int x, int y)
{
	m_X = x;
	m_Y = y;
}

void CSprite::AddPosition(int x, int y)
{
	m_X += x;
	m_Y += y;
}

CAnime* CSprite::GetAnime()
{
	return &m_Anime;
}

char CSprite::GetDir()
{
	return m_Dir;
}

int CSprite::GetFlame()
{
	return m_Flame;
}

