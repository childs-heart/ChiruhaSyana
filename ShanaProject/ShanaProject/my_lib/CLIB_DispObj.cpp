#include <Windows.h>
#include "CLIB_DispObj.h"

LEAF_BLEND	StLeafBlend[12] =
	{{D3DBLEND_ONE,			D3DBLEND_ZERO},
	{D3DBLEND_SRCALPHA,		D3DBLEND_INVSRCALPHA},
	{D3DBLEND_SRCALPHA,		D3DBLEND_INVSRCALPHA},
	{D3DBLEND_ONE,			D3DBLEND_INVSRCALPHA},
	{D3DBLEND_SRCALPHA,		D3DBLEND_ONE},
	{D3DBLEND_SRCALPHA,		D3DBLEND_INVSRCCOLOR},
	{D3DBLEND_DESTCOLOR,	D3DBLEND_SRCCOLOR},
	{D3DBLEND_ZERO,			D3DBLEND_SRCCOLOR},
	{D3DBLEND_SRCALPHA,		D3DBLEND_ONE},
	{D3DBLEND_ZERO,			D3DBLEND_INVSRCCOLOR},
	{D3DBLEND_SRCALPHA,		D3DBLEND_ONE},
	{D3DBLEND_INVDESTCOLOR,	D3DBLEND_INVSRCCOLOR},};

//
//  関数: CDispObj( )
//
//  目的: コンストラクタ
//
//  パラメータ:
//　メモ：
//　　　
CDispObj::CDispObj( )
{
	m_Child = NULL ;
	m_Parent = NULL ;
    m_Enable = FALSE;
	Init( 0 );
}

//
//  関数: CDispObj( DWORD type )
//
//  目的: コンストラクタ　属性付き
//
//  パラメータ:
//		para1：属性
//　メモ：
//　　　
CDispObj::CDispObj( DWORD type )
{
	m_Child = NULL ;
	m_Parent = NULL ;
    m_Enable = FALSE;
	Init( type );
}

//
//  関数: ~CDispObj( )
//
//  目的: デストラクタ
//
//  パラメータ:
//　メモ：
//　　　
CDispObj::~CDispObj()
{
}

//
//  関数: Init( DWORD type )
//
//  目的: クラスのメンバを初期化する
//
//  パラメータ:
//		para1：属性
//　メモ：
//　　　
void CDispObj::Init( DWORD type )
{
	m_Type = type ;

	m_Visible	= TRUE;

	memset( &m_SrcRect, 0, sizeof(RECT) );
	memset( &m_DestRect, 0, sizeof(RECT) );
	m_SrcBlend	= D3DBLEND_SRCALPHA;
	m_DestBlend	= D3DBLEND_INVSRCALPHA;
	m_RotationX[0] = 0;
	m_RotationY[0] = 0;
	m_RotationZ[0] = 0;
	m_RotOrderX[0] = 0;
	m_RotOrderY[0] = 0;
	m_RotOrderZ[0] = 0;
	m_RotationX[1] = 0;
	m_RotationY[1] = 0;
	m_RotationZ[1] = 0;
	m_RotOrderX[1] = 0;
	m_RotOrderY[1] = 0;
	m_RotOrderZ[1] = 0;
	m_Scale		= 1;
	m_Texture[0]= NULL;
	m_Texture[1]= NULL;
	m_Texture[2]= NULL;
	m_Texture[3]= NULL;
	m_XFile		= NULL;
	m_Color		= 0xFFFFFFFF;

}

//
//  関数: SetSrcRect( RECT *rect )
//
//  目的: 転送元（テクスチャー画像）座標をセット
//
//  パラメータ:
//		para1：座標
//　メモ：
//　　　
void CDispObj::SetSrcRect( RECT *rect )
{
	memcpy( &m_SrcRect, rect, sizeof(RECT)) ;
}

//
//  関数: SetSrcRectFromTex( int texNo )
//
//  目的: 転送元（テクスチャー画像）座標を、テクスチャー座標にあわせる
//
//  パラメータ:
//		para1：テクスチャー番号
//　メモ：
//　　　
void CDispObj::SetSrcRectFromTex( int texNo )
{
	D3DXIMAGE_INFO	imageInfo;

	if( m_Texture[texNo] != NULL ){
		m_Texture[texNo]->GetTextureInfo( &imageInfo );
		SetSrcRect( 0, 0, imageInfo.Width, imageInfo.Height );
	}

}

//
//  関数: SetSrcRect( long left, long top, long right, long bottom )
//
//  目的: 転送元（テクスチャー画像）座標をセット
//
//  パラメータ:
//		para1-4：座標
//　メモ：
//　　　
void CDispObj::SetSrcRect( long left, long top, long right, long bottom )
{
	m_SrcRect.left	= left;
	m_SrcRect.top	= top;
	m_SrcRect.right	= right;
	m_SrcRect.bottom= bottom;
}

//
//  関数: SetDestRect( RECT *rect )
//
//  目的: 転送先座標をセット
//
//  パラメータ:
//		para1：座標
//　メモ：
//　　　LEFT > RIGHT　の場合は左右反転した画像になる
//　　　
void CDispObj::SetDestRect( RECT *rect )
{
	memcpy( &m_DestRect, rect, sizeof(RECT)) ;
}

//
//  関数: SetDestRect( long left, long top, long right, long bottom )
//
//  目的: 転送先座標をセット
//
//  パラメータ:
//		para1-4：座標
//　メモ：
//　　　LEFT > RIGHT　の場合は左右反転した画像になる
//　　　
void CDispObj::SetDestRect( long left, long top, long right, long bottom )
{
	m_DestRect.left		= left;
	m_DestRect.top		= top;
	m_DestRect.right	= right;
	m_DestRect.bottom	= bottom;
	m_DestZ				= 0;
}

//
//  関数: SetDestRect( long left, long top, long right, long bottom )
//
//  目的: 転送先座標をセット
//
//  パラメータ:
//		para1-4：座標
//　メモ：
//　　　LEFT > RIGHT　の場合は左右反転した画像になる
//　　　
void CDispObj::SetDestRect( long left, long top, long right, long bottom, long z )
{
	m_DestRect.left		= left;
	m_DestRect.top		= top;
	m_DestRect.right	= right;
	m_DestRect.bottom	= bottom;
	m_DestZ				= z;
}

//
//  関数: SetScale( float scale )
//
//  目的: 拡大率設定
//
//  パラメータ:
//		para1：拡大率
//　メモ：
//		一応Xファイル表示のみ有効とする
//　　　
void CDispObj::SetScale( float scale )
{
	m_Scale = scale ;
}

//
//  関数: SetTexture( CTexture *tex, char layer )
//
//  目的: テクスチャー登録
//
//  パラメータ:
//		para1：テクスチャークラス
//		para2：レイヤー番号（未使用）省略可能
//　メモ：
//　　　今のところparam2は省略してください
//　　　
void CDispObj::SetTexture( CTexture *tex, char layer )
{
	m_Texture[layer] = tex;
	SetSrcRectFromTex( layer );
}

//
//  関数: SetXFile( CXFile *mesh )
//
//  目的: Xファイル登録
//
//  パラメータ:
//		para1：Xファイルクラス
//　メモ：
//　　　ここに値が入っていると、表示の際にメッシュ表示が行われる
//　　　
void CDispObj::SetXFile( CXFile *mesh )
{
	m_XFile = mesh ;
}

//
//  関数: SetBlendColor( DWORD col )
//
//  目的: ディフェーズ色設定
//
//  パラメータ:
//		para1：RGB_COLOR
//　メモ：
//　　　ここの値とテクスチャー画像が積計算されます
//　　　
void CDispObj::SetBlendColor( DWORD col )
{
	m_Color = col ;
}

//
//  関数: SetSrcBlend( int blend )
//
//  目的: 転送元のブレンド方法
//
//  パラメータ:
//		para1：blend
//　メモ：
//　　　
//　　　
void CDispObj::SetSrcBlend( int blend )
{
	m_SrcBlend = blend ;
}

//
//  関数: SetDestBlend( int blend )
//
//  目的: 転送先のブレンド方法
//
//  パラメータ:
//		para1：blend
//　メモ：
//　　　
//　　　
void CDispObj::SetDestBlend( int blend )
{
	m_DestBlend = blend ;
}

//
//  関数: SetRotOrder( char, char, char )
//
//  目的: 回転の優先順序を設定する
//
//  パラメータ:
//		para1：回転順序 X
//		para2：回転順序 Y
//		para3：回転順序 Z
//　メモ：
//　　　
void CDispObj::SetRotOrder( char x, char y,char z )
{
	m_RotOrderX[0] = x;
	m_RotOrderY[0] = y;
	m_RotOrderZ[0] = z;
}

//
//  関数: SetRotation( WORD, WORD, WORD )
//
//  目的: 回転角度を設定する
//
//  パラメータ:
//		para1：回転角度 X軸
//		para2：回転角度 Y軸
//		para3：回転角度 Z軸
//　メモ：
//　　　
void CDispObj::SetRotation( float rotX, float rotY, float rotZ )
{
	m_RotationX[0] = rotX;
	m_RotationY[0] = rotY;
	m_RotationZ[0] = rotZ;
}

//
//  関数: SetRotation( char, WORD, char, WORD, char, WORD )
//
//  目的: 回転角度を設定する
//
//  パラメータ:
//		para1_3_5：回転順序
//		para2_4_6：回転角度
//　メモ：
//　　　
void CDispObj::SetRotation( char orderX, float rotX,
							 char orderY, float rotY,
							 char orderZ, float rotZ )
{
	m_RotOrderX[0] = orderX;
	m_RotOrderY[0] = orderY;
	m_RotOrderZ[0] = orderZ;
	m_RotationX[0] = rotX;
	m_RotationY[0] = rotY;
	m_RotationZ[0] = rotZ;
}

//
//  関数: SetRotation( char, WORD, char, WORD, char, WORD )
//
//  目的: 多重で回転角度を設定する
//
//  パラメータ:
//		para1_3_5：回転順序
//		para2_4_6：回転角度
//		para7_9_11：回転順序
//		para8_10_12：回転角度
//　メモ：
//　　　
void CDispObj::SetRotation( char orderX1, float rotX1,
							 char orderY1, float rotY1,
							 char orderZ1, float rotZ1,
							 char orderX2, float rotX2,
							 char orderY2, float rotY2,
							 char orderZ2, float rotZ2 )
{
	m_RotOrderX[0] = orderX1;
	m_RotOrderY[0] = orderY1;
	m_RotOrderZ[0] = orderZ1;
	m_RotationX[0] = rotX1;
	m_RotationY[0] = rotY1;
	m_RotationZ[0] = rotZ1;

	m_RotOrderX[1] = orderX2;
	m_RotOrderY[1] = orderY2;
	m_RotOrderZ[1] = orderZ2;
	m_RotationX[1] = rotX2;
	m_RotationY[1] = rotY2;
	m_RotationZ[1] = rotZ2;
}

//
//  関数: ChangeType( DWORD type )
//
//  目的: 属性変更
//
//  パラメータ:
//		para1：属性
//　メモ：
//　　　
void CDispObj::ChangeType( DWORD type )
{
	m_Type = type ;
}

//
//  関数: VisibleOn( )
//
//  目的: 表示有効
//
void CDispObj::VisibleOn()
{
	m_Visible = TRUE;
}

//
//  関数: VisibleOff( )
//
//  目的: 表示無効
//　　　
void CDispObj::VisibleOff()
{
	m_Visible = FALSE;
}



//
//  関数: FreeChain( )
//
//  目的: 親子関係を絶縁する
//
//  パラメータ:
//　メモ：
//　　　
void CDispObj::FreeChain()
{
	if( m_Child ){
		m_Child->FreeChain();
	}
	m_Enable	= FALSE;
	m_Visible	= FALSE;
	m_Parent	= NULL;
	m_Child		= NULL;
}


//
//  関数: CDispObjGroup( int num )
//
//  目的: インストラクタ
//
//  パラメータ:
//		para1：作成する表示オブジェクトクラスの数
//　メモ：
//　　　
CDispObjGroup::CDispObjGroup( int num )
{
	m_Num = num ;
	m_CDisp = NULL ;

	m_CDisp = new CDispObj[m_Num]() ;

	int i;
	for( i=0 ; i<num ; i++ ){
		m_CDisp[i].m_Visible = FALSE ;
	}
}

//
//  関数: CDispObjGroup( )
//
//  目的: デストラクタ
//　　　
CDispObjGroup::~CDispObjGroup( )
{
	if( m_CDisp != NULL ){
		delete[] m_CDisp;
	}
	m_CDisp = NULL;
}

//
//  関数: GetDispObj( DWORD type )
//
//  目的: グループから、表示オブジェクトクラスを割り当てる
//
//  パラメータ:
//		para1：表示オブジェクトの属性
//　メモ：
//　　　
CDispObj* CDispObjGroup::GetDispObj( DWORD type )
{
	int i = 0;
	while( ( i<m_Num ) && ( m_CDisp[i].m_Enable == TRUE ) ){
		i++;
	}

	if( i == m_Num ){
		return NULL;
	}

    m_CDisp[i].m_Enable = TRUE;
	m_CDisp[i].Init( type );

	return &m_CDisp[i];
}

//
//  関数: FreeDispObj( CDispObj* disp )
//
//  目的: 表示オブジェクトクラスを開放（未使用）する
//
//  パラメータ:
//		para1：表示オブジェクトクラス
//　メモ：
//　　　
void CDispObjGroup::FreeDispObj( CDispObj* disp )
{
	if( disp->m_Parent ){
		disp->m_Parent->m_Child = NULL ;
	}

	if( disp->m_Child ){
		disp->FreeChain();
	}
	disp->m_Enable	= FALSE;
	disp->m_Visible = FALSE;
}
