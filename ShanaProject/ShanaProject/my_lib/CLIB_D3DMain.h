#pragma once

#include <d3d9.h>
#include <d3d9types.h>

#define RELEASE_3D(x) 	if(x){x->Release();x=NULL;}

// プロトタイプ
extern	int InitD3D( HWND, int width, int height, int full, HMENU );
extern	int	TermD3D(void);
extern	LPDIRECT3DDEVICE9	GetD3DDevice();

extern	void	ddd();

extern	LPDIRECT3D9				pD3D;
extern	LPDIRECT3DDEVICE9		pD3DDevice;

typedef struct{

	HWND		m_DrawHwnd;			// 描画先 ウィドウハンドル
	HMENU		m_MenuHwnd;			// メニューハンドル（リーフ定番）

	int			m_Width;			// 幅と高さ
	int			m_Height;			//

	int			m_WindowMode;		// ウィンドウモード　	WINDOW(TRUE) or FULL SCREEN(FALSE)
	int			m_FullScreenOnly;	// フルスクリーンだけ	FULL ONLY(TRUE) or WINDOW OK(FALSE)

	int			m_WindowModeChange;
	int			m_DisplayModeChange;
	int			m_FlipActive;

}D3D_MAIN;
extern D3D_MAIN		D3DMain;
