#pragma	once

#include <d3dx9tex.h>

//==============================================================
// Ｘファイルクラス
//==============================================================
class	CXFile{
friend class CD3DDraw;
friend class CD3DDraw2;
friend class CD3DDraw3;
private:
	LPD3DXMESH		m_Mesh ;					// メッシュオブジェクト
	D3DMATERIAL9*	m_MeshMaterials ;			// メッシュのなんだっけ
	LPD3DXBUFFER	m_MaterialBuffer ;			// メッシュ情報のポイント
	DWORD           m_NumMaterials ;			// メッシュの数
public:
	// コンストラクタ＆デストラクタ
	CXFile();
	virtual ~CXFile();

	// Xファイル読み込み
	bool LoadXFile( char *filename , LPDIRECT3DDEVICE9 d3ddevice );

};


//==============================================================
// Ｘファイルリストクラス
//==============================================================
class	CXFileGroup{
private:
	LPDIRECT3DDEVICE9	m_D3DDevice;		// DX デバイスオブジェクト
	CXFile*				m_CXFile;			// XFileクラスリスト

	int		m_Num;							// XFileクラスの数

public:
	// コンストラクタ＆デストラクタ
	CXFileGroup( int num, LPDIRECT3DDEVICE9 d3ddevice );
	virtual ~CXFileGroup();

	// DirectX Graphics デバイスオブジェクトセット
	void SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice );
	// Xファイル読み込み
	bool LoadXFile( int num , char *filename );
	// リスト内の指定したXファイルクラスのポインタを取得
	CXFile*	GetXFile( int num );
};
