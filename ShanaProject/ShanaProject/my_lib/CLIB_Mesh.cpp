#include <d3d9.h>
#include <d3dx9.h>
#include "CLIB_Mesh.h"
#include "CLIB_D3DMain.h"

LPD3DXBUFFER pD3DXMtrlBuffer;

//
//  関数: CXFile( )
//
//  目的: CXFileクラス　コンストラクタ
//
CXFile::CXFile()
{
	m_Mesh		= NULL;
	m_MaterialBuffer	= NULL;
//	m_MeshMaterials		= NULL;
	m_NumMaterials		= 0;
}

//
//  関数: CXFile( )
//
//  目的: CXFileクラス　デストラクタ
//
CXFile::~CXFile()
{
	RELEASE_3D( m_Mesh );
	RELEASE_3D( m_MaterialBuffer );
//	RELEASE_3D( m_MeshMaterials );
}

//
//  関数: LoadXFile( char *filename, LPDIRECT3DDEVICE9 d3ddevice )
//
//  目的: XFile読みこみ
//
//  パラメータ:
//		para1：D3Dデバイス名
//　メモ：
//		テクスチャーを読み込ませる前に必要
//		コンストラクタで、デバイスを渡していれば、この関数は呼ばなくて良い
//　　　
bool CXFile::LoadXFile( char *filename, LPDIRECT3DDEVICE9 d3ddevice )
{
	if( FAILED( D3DXLoadMeshFromX( filename, D3DXMESH_SYSTEMMEM, 
											d3ddevice, NULL, 
											&m_MaterialBuffer, NULL, &m_NumMaterials, 
											&m_Mesh ) ) ){
		return FALSE;
	}

	return TRUE;
}


//
//  関数: CXFileGroup( int num, LPDIRECT3DDEVICE9 d3ddevice )
//
//  目的: コンストラクタ
//
//  パラメータ:
//		para1：Xファイルクラスの数
//		para2：D3Dデバイス
//　メモ：
//		D3Dデバイスは、LoadXFile()用に必要
//		NULLを入れた場合は、LoadXFile()前にSetD3DDevice()でセットしておく必要がある
//
CXFileGroup::CXFileGroup( int num, LPDIRECT3DDEVICE9 d3ddevice ){
	m_Num	= num ;
	m_CXFile = NULL ;

	m_CXFile  = new CXFile[num]() ;
	m_D3DDevice	= d3ddevice ;
}

//
//  関数: ~CXFileGroup( )
//
//  目的: デストラクタ
//
CXFileGroup::~CXFileGroup( ){
	if( m_CXFile != NULL ){
		delete[] m_CXFile;
	}
	m_CXFile = NULL;
}

//
//  関数: LoadXFile( int num, char *filename )
//
//  目的: XFile読みこみ
//
//  パラメータ:
//		para1：XFileクラスの要素番号
//		para2：ファイル名
//　メモ：
//		Xファイルを読み込ませる前に必要
//		コンストラクタでデバイスを渡していれば、この関数は呼ばなくて良い
//　　　
bool CXFileGroup::LoadXFile( int num, char *filename )
{
	return m_CXFile[num].LoadXFile( filename, m_D3DDevice ) ;
}

//
//  関数: SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
//
//  目的: d3dデバイスセット
//
//  パラメータ:
//		para1：D3Dデバイス名
//　メモ：
//		Xファイルを読み込ませる前に必要
//		コンストラクタでデバイスを渡していれば、この関数は呼ばなくて良い
//　　　
void CXFileGroup::SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
{
	m_D3DDevice = d3ddevice ;
}

//
//  関数: GetXFile( int num )
//
//  目的: XFileクラスグループに格納されているXFileクラスをひとつ取得する
//
//  パラメータ:
//		para1：XFileクラスの要素番号
//
CXFile* CXFileGroup::GetXFile( int num )
{
	return &m_CXFile[num];
}
