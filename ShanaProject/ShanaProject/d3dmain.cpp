#include <windows.h>
#include <d3d9.h>
#include <d3d9types.h>
#include "d3dmain.h"

D3DDISPLAYMODE				d3d_dis_m;
D3DPRESENT_PARAMETERS		d3d_pre_p;
LPDIRECT3D9					lpD3D = NULL;
LPDIRECT3DDEVICE9			lpD3Ddev = NULL;					// Direct3Dデバイスオブジェクト

//-----------------------------------------------------------------------------------------
// DirectGraphicsの終了(オブジェクトの破棄)
//-----------------------------------------------------------------------------------------

bool D3D_END()
{

		RELEASE_3D(lpD3D);
		RELEASE_3D(lpD3Ddev);
		return true;
}

//-----------------------------------------------------------------------------------------
// DirectXの初期化
//-----------------------------------------------------------------------------------------

bool D3Dinit( HWND hwnd, int width, int height, int full )
{
	// Direct3D オブジェクトを作成
	if( NULL == ( lpD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
		// オブジェクト作成失敗
		MessageBox(NULL,"Direct3D の作成に失敗しました。","ERROR MASSAGE",MB_OK | MB_ICONSTOP);
		// 終了する
		return false;
	}

	//メモリ確保
	ZeroMemory(&d3d_pre_p,sizeof(D3DPRESENT_PARAMETERS));
	// 現在の画面モードを取得
	lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3d_dis_m);
	// Direct3D 初期化パラメータの設定
	if (full)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		d3d_pre_p.BackBufferFormat = D3DFMT_R5G6B5;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		d3d_pre_p.BackBufferFormat = d3d_dis_m.Format;
	}
	
	//D3DPRESENT_PARAMETERS構造体の中身の設定
	d3d_pre_p.BackBufferCount = 1;
	d3d_pre_p.BackBufferWidth = width;
	d3d_pre_p.BackBufferHeight = height;
	d3d_pre_p.EnableAutoDepthStencil = TRUE;
	d3d_pre_p.AutoDepthStencilFormat = D3DFMT_D16;
	d3d_pre_p.SwapEffect = D3DSWAPEFFECT_DISCARD;			//他にD3DSWAPEFFECT_COPY_VSYNCなどがある   
	d3d_pre_p.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;		// 垂直信号と同期（高精度）
//	d3d_pre_p.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;// 限界描画
/*	d3dppApp.BackBufferCount		= 1;							// バックバッファの数
	d3dppApp.BackBufferWidth		= w;							// バックバッファの幅
	d3dppApp.BackBufferHeight		= h;							// バックバッファの高
	d3dppApp.BackBufferFormat		= D3DFMT_A8R8G8B8;				// バックバッファの画面モード 
//	d3dppApp.BackBufferFormat		= d3dDisplay.Format;			// バックバッファの画面モード 
	d3dppApp.EnableAutoDepthStencil	= TRUE;							// 深度バッファ有効
	d3dppApp.AutoDepthStencilFormat	= D3DFMT_D16;					// 深度バッファサイズ
	d3dppApp.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER; // バックバッファロックを可能にする
	d3dppApp.MultiSampleQuality		= D3DMULTISAMPLE_NONE;			// マルチサンプリング数(?)
	d3dppApp.MultiSampleType		= D3DMULTISAMPLE_NONE;			// マルチサンプリング数(?)
	d3dppApp.Windowed				= !full;						// ウィンドウモード
	d3dppApp.FullScreen_RefreshRateInHz	= 0;						// リフレッシュレート　ウィンドウモードの場合:0
	d3dppApp.SwapEffect				= D3DSWAPEFFECT_COPY;			// スワッピング方法
//	d3dppApp.PresentationInterval	= D3DPRESENT_INTERVAL_DEFAULT;	// 垂直信号と同期
	d3dppApp.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;		// 垂直信号と同期（高精度）
//	d3dppApp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;// 限界描画
	d3dppApp.hDeviceWindow			= NULL;							// d3d.present時のターゲット（つまり描画先）　0：自動
*/
	if (!full)
	{
		// ウインドウモード
		d3d_pre_p.Windowed =  true ;	//true=ウィンドゥモードで起動 false=フルスクリーンモードで起動
	}
	d3d_pre_p.EnableAutoDepthStencil = 1;	//ture時にはアプリケーションに対する深度バッファを管理＝Zバッファ
	d3d_pre_p.AutoDepthStencilFormat = D3DFMT_D16;
	// プライマリディスプレイドライバしか使わないと思うのでD3DADAPTER_DEFAULT
	// D3DDEVTYPEの種類　1:T&L HALで試行開始
	if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT ,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3d_pre_p,&lpD3Ddev)))
	{
		// 1が失敗、2:HAL(ソフトウェア頂点処理)で試行開始
		if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT ,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3d_pre_p,&lpD3Ddev)))
		{
			// 2が失敗、3:REF で試行開始
			if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT ,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3d_pre_p,&lpD3Ddev)))
			{
				// 結局環境的に駄目
				MessageBox(NULL,"こらいけねぇ、DirectX使って描画できねーってさ。","ERROR MASSAGE",MB_OK | MB_ICONSTOP);
				D3D_END();
				// 終了する
				return false;
			}
		}
	}
	return true;
}
