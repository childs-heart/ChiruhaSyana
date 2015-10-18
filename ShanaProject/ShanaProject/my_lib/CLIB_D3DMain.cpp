#include "CLIB_D3DMain.h"

// グローバル変数
// DirectX SDK 構造体
LPDIRECT3D9				pD3D = NULL;
LPDIRECT3DDEVICE9		pD3DDevice = NULL;
D3DPRESENT_PARAMETERS	d3dppApp;
D3DDISPLAYMODE			d3dDisplay;

// 構造体
D3D_MAIN				D3DMain ;

//
//  関数: InitD3D()
//
//  目的: Direct3D初期化処理
//
//  コメント:実行中１回だけ呼び出す
//
int InitD3D( HWND hwnd, int w, int h, int full, HMENU menu ){

	D3DMain.m_DrawHwnd		= hwnd;
	D3DMain.m_Width			= w;
	D3DMain.m_Height		= h;
	D3DMain.m_MenuHwnd		= menu;
	D3DMain.m_WindowMode	= !full;

	// Direct3Dのオブジェクト作成
	if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
		MessageBox(NULL,TEXT("Direct3Dオブジェクトの生成に失敗しました。[DirectX9が入っていない？]"),TEXT("致命的なエラー"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	// 現在の画面モードを取得
	if( D3D_OK != (pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3dDisplay))){
		MessageBox(NULL,TEXT("現在のディスプレイモード取得に失敗しました。"),TEXT("わけわかめ"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// Direct3Dデバイス作成
	ZeroMemory(&d3dppApp,sizeof(d3dppApp));

	d3dppApp.BackBufferCount		= 1;							// バックバッファの数
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

	HRESULT	ret;
	ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
	if( FAILED(ret) ){	
		ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
		if( FAILED(ret) ){	
			D3DMain.m_FullScreenOnly = TRUE;
			return FALSE;
		}
	}
#if 0
	if(D3DMain.m_FullScreenOnly==TRUE){
		RELEASE_3D(pD3DDevice);

		D3DMain.m_WindowMode = FALSE;
		ZeroMemory(&d3dppApp,sizeof(d3dppApp));
		for(i=0;i<D3DCapsStruct.m_DisplayModeNum;i++){
			if( D3DCapsStruct.m_DisplayMode[i].Width  == 800 && D3DCapsStruct.m_DisplayMode[i].Height == 600 ){
				switch( D3DCapsStruct.m_DisplayMode[i].Format ){
					case D3DFMT_R5G6B5:		case D3DFMT_X1R5G5B5:
					case D3DFMT_A1R5G5B5:	case D3DFMT_A4R4G4B4:
					case D3DFMT_X4R4G4B4:
						D3DCapsStruct.m_FullModeNum=i;

						d3dppApp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
						d3dppApp.Windowed = D3DMain.m_WindowMode;		
						d3dppApp.SwapEffect = FULL_FLIP;		
						d3dppApp.BackBufferFormat = D3DCapsStruct.m_DisplayMode[i].Format;	
						d3dppApp.BackBufferCount = 1;
						d3dppApp.BackBufferWidth  = WinWidth;
						d3dppApp.BackBufferHeight = WinHeight;



						break;
				}
			}
			if(d3dppApp.SwapEffect) break;
		}
		if(!full){
			wsprintf( buf, TEXT("このビデオカードの現在のモードではゲームを実行できません。フルスクリーン化しますか？\n[%d]"), D3DCapsStruct.m_DisplayMode[i].RefreshRate );
			if( MessageBox( NULL, buf, TEXT("問い合わせ"), MB_YESNO )==IDNO ){
				RELEASE_3D(pD3D);
				return FALSE;
			}
		}

		ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
		if( FAILED(ret) ){	
			ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
			if( FAILED(ret) ){	
				switch(ret){
				default:
				case D3DERR_OUTOFVIDEOMEMORY:
					DebugBox( NULL, TEXT("Direct3D が処理を行うのに十分なディスプレイ メモリがありません。") );
					RELEASE_3D(pD3D);
					return FALSE;
				case D3DERR_INVALIDCALL:
					DebugBox( NULL, TEXT("Direct3Dの初期化に失敗しました[D3DERR_INVALIDCALL]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。") );
					RELEASE_3D(pD3D);
					return FALSE;
				case D3DERR_NOTAVAILABLE:
					DebugBox( NULL, TEXT("Direct3Dの初期化に失敗しました[D3DERR_NOTAVAILABLE]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。") );
					RELEASE_3D(pD3D);
					return FALSE;
				}
			}
		}
	}else{
		if(D3DMain.m_WindowMode){	
		}else{
			RELEASE_3D(pD3DDevice);
			ZeroMemory(&d3dppApp,sizeof(d3dppApp));

	
			d3dppApp.SwapEffect = FULL_FLIP;
	
	
			d3dppApp.BackBufferCount = 1;
			d3dppApp.BackBufferWidth  = WinWidth;
			d3dppApp.BackBufferHeight = WinHeight;

		
			d3dppApp.Windowed = FALSE;							
			d3dppApp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;


			if(DrawSetting.full_16bit){
				d3dppApp.BackBufferFormat=D3DFMT_UNKNOWN;
				for(i=0;i<D3DCapsStruct.m_DisplayModeNum;i++){
					if( D3DCapsStruct.m_DisplayMode[i].Width  == 800 && D3DCapsStruct.m_DisplayMode[i].Height == 600 ){
						switch( D3DCapsStruct.m_DisplayMode[i].Format ){
							case D3DFMT_R5G6B5:		case D3DFMT_X1R5G5B5:
							case D3DFMT_A1R5G5B5:	case D3DFMT_A4R4G4B4:
							case D3DFMT_X4R4G4B4:
								D3DCapsStruct.m_FullModeNum=i;
								d3dppApp.BackBufferFormat = D3DCapsStruct.m_DisplayMode[i].Format;	
								break;
						}
					}
					if(d3dppApp.BackBufferFormat!=D3DFMT_UNKNOWN) break;
				}
			}else{
				d3dppApp.BackBufferFormat = D3DCapsStruct.m_NowDisplayMode.Format;
			}

			ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
			if( FAILED(ret) ){	
				ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dppApp,&pD3DDevice);
				if( FAILED(ret) ){	
					switch(ret){
					default:
					case D3DERR_OUTOFVIDEOMEMORY:
						DebugBox( NULL, TEXT("Direct3D が処理を行うのに十分なディスプレイ メモリがありません。") );
						RELEASE_3D(pD3D);
						return FALSE;
					case D3DERR_INVALIDCALL:
						DebugBox( NULL, TEXT("Direct3Dの初期化に失敗しました[D3DERR_INVALIDCALL]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。") );
						RELEASE_3D(pD3D);
						return FALSE;
					case D3DERR_NOTAVAILABLE:
						DebugBox( NULL, TEXT("Direct3Dの初期化に失敗しました[D3DERR_NOTAVAILABLE]\nこのグラフィックカードは必要な機能をサポートしていないか、\nあるいはDirectX8に対応したドライバが入っていません。") );
						RELEASE_3D(pD3D);
						return FALSE;
					}
				}
			}
		}
	}



	if( FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&D3DCapsStruct.m_NowDisplayMode)) ){	
		MessageBox(NULL,TEXT("ディスプレイモードの取得に失敗しました。[なにゆえ？]"),TEXT("致命的なエラー"), MB_OK | MB_ICONSTOP);
		RELEASE_3D(pD3D);
		return FALSE;
	}
#endif

	return TRUE;
}

//
//  関数: TermD3D()
//
//  目的: Direct3D終了処理
//
//  コメント:プログラム終了時に必ずコールしなくてはならない
//
int TermD3D(void)
{

	RELEASE_3D(pD3DDevice);
	RELEASE_3D(pD3D);

	return TRUE;
}

LPDIRECT3DDEVICE9	GetD3DDevice()
{
	return pD3DDevice;
}

void ddd(){
	// 画面クリア
	pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_TARGET , D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	// Begin the scene.
	pD3DDevice->BeginScene();

	// Rendering of scene objects happens here.

	// End the scene.
	pD3DDevice->EndScene();

	// 画面に表示（バッファスワップ）
	pD3DDevice->Present( NULL, NULL, NULL, NULL );
}