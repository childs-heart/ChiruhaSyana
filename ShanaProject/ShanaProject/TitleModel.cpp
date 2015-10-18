/********************/
/* エフェクトテスト	*/
/********************/

#include <math.h>

#include "TitleModel.h"
#include "ShanaProt.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"
#include "CLIB_D3DDraw3.h"

CTitleModel::CTitleModel( CResBattle *game ):CSprite( game )
{
	// 資源調達
	m_Input = game->m_Input ;
	m_Anime.m_AnimeSpec	= game->m_AnimationManager->GetAnimation( ANIME_NO_SYS_TITLE_MODEL);
	m_Tex					= game->m_TextureManager->GetTextureGroup( TEXTURE_NO_SYS_TITLE_REIJI_MAIGO );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();
	m_DispObj->SetXFile( game->m_MeshTestGroup->GetXFile( 0 ) );
	m_DispObj->SetScale( 1 );

//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// 初期状態
	m_X = 400;
	m_Y = 300;
	m_fX = -200;
	m_fY = 100;
	m_fZ = 100;
	m_BaseX = 200;
	m_BaseY = 450;
	m_BaseZ = 100;
	for( int i = 0 ; i < 10 ; i++ ){
		m_ObjX[i]	= m_BaseX;
		m_ObjY[i]	= m_BaseY;
		m_ObjZ[i]	= m_BaseZ;
		m_ObjRange[i]	= 100;
		m_ObjRotX[i]	= 0;
		m_ObjRotY[i]	= 0;
		m_ObjRotZ[i]	= 0;
		m_ObjRotBeginY[i] = 0;
		m_ObjRotXVal[i]	= 0;
		m_ObjRotYVal[i]	= 0;
		m_ObjRotZVal[i]	= 0;
		m_ObjRotBeginYVal[i]	= 0;
	}
	m_ObjRotX[0]	= -80;
	m_ObjRotY[0]	= 0;
	m_ObjRotZ[0]	= 80;
	m_ObjRotBeginY[0]= 0;
	m_ObjRotYVal[0]	= 0;
	m_ObjRotXVal[0]	= 0;
	m_ObjRotZVal[0]	= 0.03;
	m_ObjRotBeginYVal[0]= 0.1;
	m_ObjRotX[1]	= 40;
	m_ObjRotY[1]	= 250;
	m_ObjRotZ[1]	= 160;
	m_ObjRotBeginY[1]= 0;
	m_ObjRotXVal[1]	= 0;
	m_ObjRotYVal[1]	= 0;
	m_ObjRotZVal[1]	= 0.03;
	m_ObjRotBeginYVal[1]= 0.1;
	m_ObjRotX[2]	= 120;
	m_ObjRotY[2]	= 250;
	m_ObjRotZ[2]	= 180;
	m_ObjRotBeginY[2]= 0;
	m_ObjRotXVal[2]	= 0;
	m_ObjRotYVal[2]	= 0;
	m_ObjRotZVal[2]	= 0.03;
	m_ObjRotBeginYVal[2]= 0.1;

	m_ObjRotX[3]	= -10;
	m_ObjRotY[3]	= -10;
	m_ObjRotZVal[3]	= -0.1;
	m_ObjRotX[4]	= 40;
	m_ObjRotY[4]	= 70;
	m_ObjRotZVal[4]	= 0.1;
	m_ObjRotX[5]	= 80;
	m_ObjRotY[5]	= 80;
	m_ObjRotZVal[5]	= -0.1;
	m_ObjRotX[6]	= 20;
	m_ObjRotY[6]	= 30;
	m_ObjRotZVal[6]	= 0.1;
	m_ObjRotX[7]	= 80;
	m_ObjRotY[7]	= 0;
	m_ObjRotZVal[7]	= 0.1;
	m_ObjRange[3]	= 0.6;
	m_ObjRange[4]	= 0.7;
	m_ObjRange[5]	= 0.7;
	m_ObjRange[6]	= 0.9;
	m_ObjRange[7]	= 1.1;

	m_ObjMeshNo[0]	= 0;
	m_ObjMeshNo[1]	= 0;
	m_ObjMeshNo[2]	= 0;
	m_ObjMeshNo[3]	= 2;
	m_ObjMeshNo[4]	= 3;
	m_ObjMeshNo[5]	= 3;
	m_ObjMeshNo[6]	= 2;
	m_ObjMeshNo[7]	= 4;
	rotx = 0;
	roty = 0;
	m_Flame = 0;

	// ブレンド方法指定
	m_DispObj->SetDestBlend(D3DBLEND_ZERO);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);
}

CTitleModel::~CTitleModel()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CTitleModel::Move()
{
	rotx++;
	roty++;
	m_Flame=(m_Flame+1) % 360;
//	m_DispObj->SetRotation( 2, rotx, 3, rotx, 1,rotx );

//	m_Input->UpDateState_Pad();
/*	unsigned long pad1,pad2 ;
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
*/
	// X軸
	for( int i = 0 ; i < 8 ; i++ ){
		m_ObjRotY[i]+=m_ObjRotYVal[i];
		m_ObjRotZ[i]+=m_ObjRotZVal[i];
		m_ObjRotX[i]+=m_ObjRotXVal[i];
		m_ObjRotBeginY[i]+=m_ObjRotBeginYVal[i];
	}
//	m_ObjX[0] = m_ObjRange[0] * sin( D3DXToRadian(m_ObjRotY[0]) ) + m_BaseX;
//	m_ObjZ[0] = m_ObjRange[0] * sin( D3DXToRadian(m_ObjRotY[0]) ) + m_BaseZ;
//	m_ObjY[0] = sqrt((float)(m_ObjZ[0]-m_BaseZ)*(float)(m_ObjZ[0]-m_BaseZ)+
//					(float)(m_ObjY[0]-m_BaseY)*(float)(m_ObjY[0]-m_BaseY)) * sin( D3DXToRadian(m_ObjRotX[0])) + m_BaseY;
//	m_ObjZ[0] = sqrt((float)(m_ObjZ[0]-m_BaseZ)*(float)(m_ObjZ[0]-m_BaseZ)+
//					(float)(m_ObjY[0]-m_BaseY)*(float)(m_ObjY[0]-m_BaseY)) * sin( D3DXToRadian(m_ObjRotX[0])) + m_BaseZ;
//	m_ObjX[0] = (m_ObjX[0] - m_ObjRange[0]) * sin( D3DXToRadian(m_ObjRotZ[0]) ) + m_BaseX;
//	m_ObjY[0] = (m_ObjX[0] - m_ObjRange[0]) * sin( D3DXToRadian(m_ObjRotZ[0]) ) + m_BaseY;

	return TRUE;
}

bool CTitleModel::Draw(CD3DDraw *draw)
{
	CD3DDraw3	*draw3;
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;
	D3DXMATRIX matrix,rol;
	int x,y,z;

	CSprite::Draw();
	StImageData *anime ;

	m_DispObj->SetRotation( 0,0,0,0,0,0,0,0,0,0,0,0);
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 255,255,255,255 ));
	// でっかい輪
	m_DispObj->SetDestBlend(D3DBLEND_ZERO);
	m_DispObj->SetSrcBlend(D3DBLEND_ONE);
	for( int i = 3 ; i < 8 ; i++ ){
		// 描画
		// 画像表示基準点
		anime = &m_Anime.GetCurrentMotion()->m_Image;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// 行列計算
		x = 0;
		y = 0;
		z = 0;
		// 描画
		m_DispObj->SetScale( m_ObjRange[i]*2 );
		m_DispObj->SetXFile( m_Game->m_MeshTestGroup->GetXFile( m_ObjMeshNo[i] ) );
		m_DispObj->SetRotation( 2, m_ObjRotX[i],3,-m_ObjRotY[i],1,-m_ObjRotZ[i]);
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( x+m_BaseX,y+m_BaseY,x+m_BaseX,y+m_BaseY,z+m_BaseZ);
		draw3 = (CD3DDraw3*)(draw);
		draw3->Draw3( m_DispObj, m_fX, m_fY, m_fZ );
	}

	// でっかい物
	for( int i = 0 ; i < 3 ; i++ ){
		m_DispObj->SetScale( 1 );
		// 描画
		// 画像表示基準点
		anime = &m_Anime.GetCurrentMotion()->m_Image;
		tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
		tex->GetTextureInfo( &texInfo ) ;
		// 行列計算
		D3DXMatrixTranslation(&matrix,0,-100,0);
		D3DXMatrixRotationZ(&rol , D3DXToRadian(m_ObjRotZ[i]) );
		D3DXMatrixMultiply(&matrix, &matrix,&rol );
		D3DXMatrixRotationX(&rol , D3DXToRadian(m_ObjRotX[i]) );
		D3DXMatrixMultiply(&matrix, &matrix,&rol);
		D3DXMatrixRotationY(&rol , D3DXToRadian(m_ObjRotY[i]) );
		D3DXMatrixMultiply(&matrix, &matrix,&rol);
		x = 0*matrix.m[0][0] + -100*matrix.m[1][0] + 0*matrix.m[2][0] + 1*matrix.m[3][0];
		y = 0*matrix.m[0][1] + -100*matrix.m[1][1] + 0*matrix.m[2][1] + 1*matrix.m[3][1];
		z = 0*matrix.m[0][2] + -100*matrix.m[1][2] + 0*matrix.m[2][2] + 1*matrix.m[3][2];
		// 描画
		m_DispObj->SetXFile( m_Game->m_MeshTestGroup->GetXFile( 0 ) );
//		m_DispObj->SetRotation( 0,0,0,0,0,0,0,0,0,0,0,0);
		m_DispObj->SetRotation( 0,0,1,m_ObjRotBeginY[i],0,0,
								5, -m_ObjRotX[i],6,m_ObjRotY[i],4,-m_ObjRotZ[i]);
//		m_DispObj->SetRotation( 2, -m_ObjRotX[i],3,m_ObjRotY[i],1,-m_ObjRotZ[i]);
		m_DispObj->SetTexture( tex );
		m_DispObj->SetDestRect( x+m_BaseX,y+m_BaseY,x+m_BaseX,y+m_BaseY,z+m_BaseZ);
		draw3 = (CD3DDraw3*)(draw);
		draw3->Draw3( m_DispObj, m_fX, m_fY, m_fZ );
		m_DispObj->SetRotation( 0,0,1,-m_ObjRotBeginY[i],0,0,
								5, -m_ObjRotX[i],6,m_ObjRotY[i],4,-m_ObjRotZ[i]);
		m_DispObj->SetXFile( m_Game->m_MeshTestGroup->GetXFile( 1 ) );
		draw3->Draw3( m_DispObj, m_fX, m_fY, m_fZ );
	}

// 光
	m_DispObj->SetRotation( 0,0,0,0,0,0,0,0,0,0,0,0);
	// 描画
	// 画像表示基準点
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB( 240,255,255,255 ));
	m_DispObj->SetDestBlend(D3DBLEND_ONE);
	m_DispObj->SetSrcBlend(D3DBLEND_SRCALPHA);
	anime = &m_Anime.GetMotionData(1)->m_Image;
	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;
	// 行列計算
	x = 0;
	y = 0;
	z = 0;
	// 描画
	m_DispObj->SetScale( 1 );
	m_DispObj->SetXFile( NULL );
	m_DispObj->SetRotation( 0,0,0,0,0,0);
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_BaseX - anime->m_BaseX , m_BaseY - anime->m_BaseY ,
							m_BaseX + ( (long)texInfo.Width - anime->m_BaseX ),
							m_BaseY + ( (long)texInfo.Height - anime->m_BaseY ),m_BaseZ );
	draw3 = (CD3DDraw3*)(draw);
	draw3->Draw3( m_DispObj, m_fX, m_fY, m_fZ );
//	draw->Draw( m_DispObj );





//	m_DispObj->SetXFile( m_Game->m_MeshTestGroup->GetXFile( 1 ) );
//	m_DispObj->SetRotation( 0, 0,0,0,1,m_ObjRotY[0] );
//	m_DispObj->SetRotation( 1, 90,2,m_ObjRotY[0]-90,0,0 );
//	m_DispObj->SetRotation( 0, 0,1,-rotx,0,0 );
//	m_DispObj->SetDestRect( m_ObjX[0],m_ObjY[0],m_ObjX[0],m_ObjY[0],m_ObjZ[0]);
//	m_DispObj->SetDestRect( m_X - anime->m_BaseX , m_Y - anime->m_BaseY ,
//							m_X + ( (long)texInfo.Width - anime->m_BaseX ),
//							m_Y + ( (long)texInfo.Height - anime->m_BaseY ) );
//	draw3 = (CD3DDraw3*)(draw);
//	draw3->Draw3( m_DispObj, m_fX, m_fY, m_fZ );
//
	m_DispObj->SetXFile( NULL );
//	m_DispObj->SetRotation( 1, 90,2,m_ObjRotY[0],0,0 );
//	m_DispObj->SetRotation( 1, rotx, 0, 0, 0,0 );
	m_DispObj->SetDestRect( m_fX + 400 - anime->m_BaseX , m_fY + 300- anime->m_BaseY  ,
							m_fX + 400  + ( (long)texInfo.Width - anime->m_BaseX ),
							m_fY + 300  + ( (long)texInfo.Height - anime->m_BaseY ) );
//	draw3 = (CD3DDraw3*)(draw);
//	draw->Draw( m_DispObj );

	return TRUE;
}
