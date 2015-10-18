#pragma once
#include "CLIB_DispObj.h"
#include <d3d9.h>
#include <d3d9types.h>

///////////////////////////
// 頂点バッファ構造体
// 適当にフォーマット５種
// 座標変換済み　テクスチャーつき
typedef	struct
{
	float		x,y,z;
	float		rhw;
	D3DCOLOR	color;
	D3DCOLOR	specular;
	float		tu,tv;
}TLVERTEX;
#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_SPECULAR)

// 座標変換済み　テクスチャーつき（２枚）
typedef struct
{
	float		x,y,z;
	float		rhw;
	D3DCOLOR	color;
	D3DCOLOR	specular;
	float		tu0,tv0;
	float		tu1,tv1;
}TLVERTEX2;
#define	FVF_TLVERTEX2 (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2 | D3DFVF_SPECULAR)

// 座標変換済み　テクスチャーなし
typedef struct
{
	float		x,y,z;
	float		rhw;
	D3DCOLOR	color;

}TLVERTEX_NOTEX;
#define	FVF_TLVERTEX_NOTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// テクスチャーつき
typedef struct 
{
	float		x,y,z;
	D3DCOLOR	color;
	float		tu,tv;
}TLVERTEX_3D;
#define	FVF_TLVERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// テクスチャーつき（２枚）
typedef struct 
{
	float		x,y,z;
	D3DCOLOR	color;
	float		tu0,tv0;
	float		tu1,tv1;
}TLVERTEX2_3D;
#define	FVF_TLVERTEX2_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2)


//==============================================================
// 描画クラス
//==============================================================
class CD3DDraw{
public:
	// DirectX Graphicsオブジェクト
	LPDIRECT3D9			m_D3D;
	LPDIRECT3DDEVICE9	m_D3DDevice;

	CDispObj*			m_Disp;			// 図形クラス（必要ないかも）

	int	m_CenterX;					// スクリーンセンター X座標
	int	m_CenterY;					// スクリーンセンター Y座標

	// 描画時に使う関数
	void SetVertex( );					// 頂点をセット（未実装）				
	bool SetTransrate( );				// 座標変換実行

public:
	// 描画開始
	void DrawBegin();
	bool Draw( CDispObj* disp );
	void DrawEnd();
	// DirectX Graphics デバイスオブジェクトセット＆ゲット
	bool SetDevice( LPDIRECT3DDEVICE9 d3ddevice );
	LPDIRECT3DDEVICE9 GetDevice();

	// スクリーンセンター座標セット
	void SetCenter( int x, int y );
};
