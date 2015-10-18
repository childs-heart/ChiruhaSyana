#include <d3dx9tex.h>
#include "CLIB_Texture.h"
#include "CLIB_D3DMain.h"
#include <stdio.h>

//
//  テクスチャークラス
//

//
//  関数: CTEXTURE()
//
//  目的: テクスチャークラスコンストラクタ
//
//  コメント:
//
CTexture::CTexture()
{
	pD3DTex = NULL;
	m_ImageData = NULL;
}

//
//  関数: ~CTEXTURE()
//
//  目的: テクスチャークラスデストラクタ
//
//  コメント:
//
CTexture::~CTexture()
{
	if( m_ImageData ){
		delete m_ImageData;
		m_ImageData = NULL;
	}
	RELEASE_3D( pD3DTex );
}

//
//  関数: LoadTexture( char * , LPDIRECT3DDEVICE9 , RGBQUAD *pal, DWORD color_key )
//
//  目的: テクスチャー読み込み
//
//  パラメータ:
//		para1：ファイル名
//　　　para2：D3Dデバイス
//		para3：パレットデータ（default  NULL )
//		para4：透明色（default　緑っぽい色 )
//
//　メモ：
//		読み込める画像ファイル（ .bmp, .jpg, .dds, .png など）
//
bool CTexture::LoadTexture( char *name , LPDIRECT3DDEVICE9 d3ddevice ,int vram, RGBQUAD *pal, DWORD color_key )
{
	HANDLE	hReadFile ;
	DWORD	nFileSize;
	LPDIRECT3DSURFACE9		pSurface = NULL;

	m_D3DDevice = d3ddevice;
	m_ColorKey = color_key;

	RELEASE_3D( pD3DTex );

	// 画像情報読み込み
	strcpy( m_Filename, name ) ;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	D3DXGetImageInfoFromFile( m_Filename, &m_TexInfo );

	// ファイルオープン 
	hReadFile = NULL ;
	hReadFile = CreateFile( m_Filename ,GENERIC_READ,0,NULL,
						OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if( hReadFile == INVALID_HANDLE_VALUE ){
		char a[255];
		sprintf(a,"ファイルなし、%s",m_Filename);
		MessageBox(NULL,a,"file not found",MB_OK);
		return FALSE;
	}

	// ファイルサイズ取得
	m_ImageSize = GetFileSize( hReadFile , NULL );

	// 領域確保
	m_ImageData = new unsigned char[ m_ImageSize ] ;

	// データ読み込み
	ReadFile( hReadFile , m_ImageData , m_ImageSize , &nFileSize , NULL );
	CloseHandle( hReadFile );

	DWORD res;
/*	if( D3D_OK != ( res = D3DXCreateTextureFromFileInMemoryEx( m_D3DDevice, m_ImageData, m_ImageSize, 0, 0, 0, 0, D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 
		m_ColorKey, NULL, NULL, &pD3DTex ) )){
		delete m_ImageData;
		m_ImageData = NULL;
		return FALSE;
	}
*/

	// パレットデータ割り当て
	if( pal != NULL ){
		SetPalette( pal );
	}

	// 空のテクスチャー作成
	D3DPOOL pool;
	if( vram == 0 ){
		pool = D3DPOOL_MANAGED;
	}
	else{
		pool = D3DPOOL_DEFAULT;
	}
	if( FAILED( res = d3ddevice->CreateTexture( m_TexInfo.Width, m_TexInfo.Height, 1, 0,//D3DUSAGE_RENDERTARGET,D3DUSAGE_DYNAMIC,
		D3DFMT_A8R8G8B8,pool, &pD3DTex ,NULL))){
		delete m_ImageData;
		m_ImageData = NULL;
		return FALSE ;
	}

	// テクスチャーのサーフェス取得
	pD3DTex->GetSurfaceLevel( 0, &pSurface );

	// テクスチャーに画像割り当て
	if( D3D_OK != D3DXLoadSurfaceFromFileInMemory( pSurface, NULL, NULL, m_ImageData, m_ImageSize, NULL, D3DX_DEFAULT, color_key, NULL ) ){
		RELEASE_3D( pSurface );
		delete m_ImageData;
		m_ImageData = NULL;
		return FALSE;
	}
	RELEASE_3D( pSurface );
	delete m_ImageData;
	m_ImageData = NULL;

	return TRUE;
}

//
//  関数: SetPalette( RGBQUAD *pal )
//
//  目的: パレットセット
//
//  パラメータ:
//		para1：パレットデータ
//
//　メモ：
//		セットできる画像ファイル　.bmpだけ
//
bool CTexture::SetPalette( RGBQUAD *pal )
{
	BITMAPINFO	*stBmpInfo;
	unsigned char *dst_data ;

	// パレット上書き
	stBmpInfo = (BITMAPINFO *)&m_ImageData[sizeof(BITMAPFILEHEADER)];
	dst_data = (unsigned char *)pal;
	for( int i = 0 ; i < stBmpInfo->bmiHeader.biClrImportant ; i++ ){
		stBmpInfo->bmiColors[i].rgbRed   = dst_data[i*3 + 0 ];
		stBmpInfo->bmiColors[i].rgbGreen = dst_data[i*3 + 1 ];
		stBmpInfo->bmiColors[i].rgbBlue  = dst_data[i*3 + 2 ];
	}
	return true;
}

//
//  関数: GetTextureInfo( D3DXIMAGE_INFO * )
//
//  目的: テクスチャーの画像情報をゲトする
//
//  パラメータ:
//		para1：D3DXIMAGE_INFO（directX SDKで定義されている構造体）のポインタ
//
void CTexture::GetTextureInfo( D3DXIMAGE_INFO *inf ){
	memcpy( inf, &m_TexInfo , sizeof( D3DXIMAGE_INFO ));
}


LPDIRECT3DSURFACE9 CTexture::GetSurface( ){

	LPDIRECT3DSURFACE9		pSurface = NULL;
	// テクスチャーのサーフェス取得
	pD3DTex->GetSurfaceLevel( 0, &pSurface );

	return pSurface;
}

LPDIRECT3DTEXTURE9 CTexture::TakeTexture(){

	LPDIRECT3DSURFACE9		pSurface = NULL;

/*	// 空のテクスチャー作成
	if( FAILED( m_D3DDevice->CreateTexture( m_TexInfo.Width, m_TexInfo.Height, 1, D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT, &pD3DTex ,NULL)))
		return FALSE ;

	// テクスチャーのサーフェス取得
	pD3DTex->GetSurfaceLevel( 0, &pSurface );

	if( D3D_OK != D3DXLoadSurfaceFromFileInMemory( pSurface, NULL, NULL, m_ImageData, m_ImageSize, NULL, D3DX_DEFAULT, m_ColorKey, NULL ) ){
//		delete m_ImageData;
		return FALSE;
	}
*/
	D3DXIMAGE_INFO info;
	if( D3D_OK != D3DXCreateTextureFromFileInMemoryEx( m_D3DDevice, m_ImageData, m_ImageSize, 0, 0, 0, 0, D3DFMT_A8R8G8B8,
											D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 
											m_ColorKey, NULL, NULL, &pD3DTex )){
		return FALSE;
	}

	return pD3DTex;
}

bool CTexture::ReleaseTexture(){
	RELEASE_3D( pD3DTex );
	return true;
}

//
//  関数: CTEXTURE_GROUP( int , LPDIRECT3DDEVICE9 )
//
//  目的: コンストラクタ
//
//  パラメータ:
//		para1：テクスチャークラスの数
//		para2：D3Dデバイス
//　メモ：
//		D3Dデバイスは、LoadTexture()用に必要
//		NULLを入れた場合は、LoadTexture()前にSetD3DDevice()でセットしておく必要がある
//
CTextureGroup::CTextureGroup( int num, LPDIRECT3DDEVICE9 d3ddevice ){
	m_Num	= num ;
	m_CTex  = NULL ;

	m_CTex  = new CTexture[num]() ;
	m_D3DDevice	= d3ddevice ;
}

//
//  関数: ~CTEXTURE_GROUP( )
//
//  目的: デストラクタ
//
//  パラメータ:
//
CTextureGroup::~CTextureGroup( ){
	if( m_CTex != NULL ){
		delete[] m_CTex;
	}
	m_CTex = NULL;
}

//
//  関数: LoadTexture( int num, char *filename )
//
//  目的: テクスチャーファイル読み込み
//
//  パラメータ:
//		para1：テクスチャークラスの要素番号
//		para2：ファイル名
//
bool CTextureGroup::LoadTexture( int num, char *filename,int vram_set , RGBQUAD *pal, DWORD color_key )
{
	return m_CTex[num].LoadTexture( filename, m_D3DDevice, vram_set, pal, color_key ) ;
}

//
//  関数: Reset( )
//
//  目的: テクスチャーをリセット
//
void CTextureGroup::Reset( )
{
	if( m_CTex != NULL ){
		delete[] m_CTex;
	}
	m_CTex  = new CTexture[m_Num]() ;
}

//
//  関数: SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
//
//  目的: d3dデバイスセット
//
//  パラメータ:
//		para1：D3Dデバイス名
//　メモ：
//		テクスチャーを読み込ませる前に必要
//		コンストラクタで、デバイスを渡していれば、この関数は呼ばなくて良い
//　　　
void CTextureGroup::SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
{
	m_D3DDevice = d3ddevice ;
}

//
//  関数: GetTexture( int num )
//
//  目的: テスクチャーグループに格納されているテクスチャークラスを取得する
//
//  パラメータ:
//		para1：テクスチャークラスの要素番号
//
CTexture* CTextureGroup::GetTexture( int num )
{
	return &m_CTex[num];
}
