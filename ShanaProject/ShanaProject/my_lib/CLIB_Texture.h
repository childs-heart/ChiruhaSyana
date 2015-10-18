#pragma	once

#include <d3d9.h>
#include <d3dx9tex.h>

//==============================================================
// テクスチャークラス
//==============================================================
class	CTexture{
private:
protected:
	char				m_Filename[256];	// 画像ファイル名（必要ないかも）
	D3DXIMAGE_INFO		m_TexInfo;			// 画像情報構造体


public:
	LPDIRECT3DTEXTURE9	pD3DTex;			// DirectXテクスチャーオブジェクト
	LPDIRECT3DDEVICE9 m_D3DDevice;

	unsigned char		*m_ImageData;		// 画像データ
	DWORD				m_ImageSize;		// 画像容量
	DWORD				m_ColorKey;			// カラーキー

	// コンストラクタ＆デストラクタ
	CTexture();
	virtual ~CTexture();

	// 画像ファイル読み込み
	bool LoadTexture( char *name , LPDIRECT3DDEVICE9 d3ddevice, int vram_set = 0, RGBQUAD *pal = NULL , DWORD color_key = 0xFF007B8C );
	bool SetPalette( RGBQUAD *pal );

	// 画像情報取得
	void GetTextureInfo( D3DXIMAGE_INFO	*texinfo );

	// サーフェス取得
	LPDIRECT3DSURFACE9 GetSurface( );

	// DIRECT3DTEXTURE用意
	LPDIRECT3DTEXTURE9	TakeTexture();
	bool ReleaseTexture();
};


//==============================================================
// テクスチャーリストクラス
// スクリプトクラス　１インスタンス毎に一つ割り当て
//==============================================================
class	CTextureGroup{
private:
	LPDIRECT3DDEVICE9	m_D3DDevice;		// DX デバイスオブジェクト
	CTexture*			m_CTex;				// テクスチャークラスリスト

	int					m_Num;				// テクスチャークラスの数

public:
	// コンストラクタ＆デストラクタ
	CTextureGroup( int num, LPDIRECT3DDEVICE9 d3ddevice );
	virtual ~CTextureGroup();

	// DirectX Graphics デバイスオブジェクトセット
	void SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice );
	// 画像ファイル読み込み
	bool LoadTexture( int num, char *filename,int vram_set = 0, RGBQUAD *pal = NULL, DWORD color_key = 0xFF007B8C );
	// リスト内の指定したテクスチャークラスのポインタを取得
	CTexture*	GetTexture( int num );
	// テクスチャーをクリア
	void	Reset();
};
