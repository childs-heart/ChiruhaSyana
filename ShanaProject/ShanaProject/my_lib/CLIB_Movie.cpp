//------------------------------------------------------------------------------
// File: Allocator.cpp
//
// Desc: DirectShow sample code - implementation of the CAllocator class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "CLIB_Movie.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAllocator::CAllocator( IDirect3D9* d3d, IDirect3DDevice9* d3dd)
: m_refCount(1)
,m_D3D(d3d)
,m_D3DDev(d3dd)
{
//    CAutoLock Lock(&m_ObjectLock);
    return ;//m_D3DDev->GetRenderTarget( 0, & m_renderTarget.p );

}

CAllocator::~CAllocator()
{
//    DeleteSurfaces();
}

//IVMRSurfaceAllocator9
HRESULT CAllocator::InitializeDevice( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out][in] */ DWORD *lpNumBuffers)
{
    DWORD dwWidth = 1;
    DWORD dwHeight = 1;
    float fTU = 1.f;
    float fTV = 1.f;

    if( lpNumBuffers == NULL )
    {
        return E_POINTER;
    }

    if( m_lpIVMRSurfAllocNotify == NULL )
    {
        return E_FAIL;
    }

    HRESULT hr = S_OK;

//	lpAllocInfo->dwWidth = dwWidth;
//	lpAllocInfo->dwHeight = dwHeight;

    // NOTE:
    // we need to make sure that we create textures because
    // surfaces can not be textured onto a primitive.
    lpAllocInfo->dwFlags |= VMR9AllocFlag_TextureSurface;

    hr = m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, &m_surfaces );

#if 0
    // If we couldn't create a texture surface and 
    // the format is not an alpha format,
    // then we probably cannot create a texture.
    // So what we need to do is create a private texture
    // and copy the decoded images onto it.
    if(FAILED(hr) && !(lpAllocInfo->dwFlags & VMR9AllocFlag_3DRenderTarget))
    {
        DeleteSurfaces();            

        // is surface YUV ?
        if (lpAllocInfo->Format > '0000') 
        {           
            D3DDISPLAYMODE dm; 
            FAIL_RET( m_D3DDev->GetDisplayMode(NULL,  & dm ) );

            // create the private texture
            FAIL_RET( m_D3DDev->CreateTexture(lpAllocInfo->dwWidth, lpAllocInfo->dwHeight,
                                    1, 
                                    D3DUSAGE_RENDERTARGET, 
                                    dm.Format, 
                                    D3DPOOL_DEFAULT /* default pool - usually video memory */, 
                                    & m_privateTexture.p, NULL ) );
        }

        
        lpAllocInfo->dwFlags &= ~VMR9AllocFlag_TextureSurface;
        lpAllocInfo->dwFlags |= VMR9AllocFlag_OffscreenSurface;

        FAIL_RET( m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, & m_surfaces.at(0) ) );
    }
#endif

    return hr;
}
            
HRESULT CAllocator::TerminateDevice( 
        /* [in] */ DWORD_PTR dwID)
{
//    DeleteSurfaces();
    return S_OK;
}
    
HRESULT CAllocator::GetSurface( 
        /* [in] */ DWORD_PTR dwUserID,
        /* [in] */ DWORD SurfaceIndex,
        /* [in] */ DWORD SurfaceFlags,
        /* [out] */ IDirect3DSurface9 **lplpSurface)
{
    if( lplpSurface == NULL )
    {
        return E_POINTER;
    }

//    CAutoLock Lock(&m_ObjectLock);

    return m_surfaces.CopyTo(lplpSurface) ;
}

void CAllocator::SetSurface( LPDIRECT3DSURFACE9 surface )
{
	m_surfaces.Attach( surface );
}
    
HRESULT CAllocator::AdviseNotify( 
        /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify)
{
//    CAutoLock Lock(&m_ObjectLock);

    HRESULT hr;

    m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;

    HMONITOR hMonitor = m_D3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );
	hr = m_lpIVMRSurfAllocNotify->SetD3DDevice( m_D3DDev, hMonitor );

    return hr;
}

HRESULT CAllocator::StartPresenting( 
    /* [in] */ DWORD_PTR dwUserID)
{
//    CAutoLock Lock(&m_ObjectLock);

    if( m_D3DDev == NULL )
    {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT CAllocator::StopPresenting( 
    /* [in] */ DWORD_PTR dwUserID)
{
    return S_OK;
}

HRESULT CAllocator::PresentImage( 
    /* [in] */ DWORD_PTR dwUserID,
    /* [in] */ VMR9PresentationInfo *lpPresInfo)
{
    HRESULT hr;
//    CAutoLock Lock(&m_ObjectLock);

    // if we are in the middle of the display change
    if( NeedToHandleDisplayChange() )
    {
        // NOTE: this piece of code is left as a user exercise.  
        // The D3DDevice here needs to be switched
        // to the device that is using another adapter
    }

    hr = PresentHelper( lpPresInfo );

#if 0
    // IMPORTANT: device can be lost when user changes the resolution
    // or when (s)he presses Ctrl + Alt + Delete.
    // We need to restore our video memory after that
    if( hr == D3DERR_DEVICELOST)
    {
        if (m_D3DDev->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) 
        {
            DeleteSurfaces();
            FAIL_RET( CreateDevice() );

            HMONITOR hMonitor = m_D3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );

            FAIL_RET( m_lpIVMRSurfAllocNotify->ChangeD3DDevice( m_D3DDev, hMonitor ) );

        }

        hr = S_OK;
    }
#endif

    return hr;
}

HRESULT CAllocator::PresentHelper(VMR9PresentationInfo *lpPresInfo)
{

#if 0
    // parameter validation
    if( lpPresInfo == NULL )
    {
        return E_POINTER;
    }
    else if( lpPresInfo->lpSurf == NULL )
    {
        return E_POINTER;
    }

//    CAutoLock Lock(&m_ObjectLock);
    HRESULT hr;

    m_D3DDev->SetRenderTarget( 0, m_renderTarget );
    // if we created a  private texture
    // blt the decoded image onto the texture.
    if( m_privateTexture != NULL )
    {   
        CComPtr<IDirect3DSurface9> surface;
        FAIL_RET( m_privateTexture->GetSurfaceLevel( 0 , & surface.p ) );

        // copy the full surface onto the texture's surface
        FAIL_RET( m_D3DDev->StretchRect( lpPresInfo->lpSurf, NULL,
                             surface, NULL,
                             D3DTEXF_NONE ) );

        FAIL_RET( m_scene.DrawScene(m_D3DDev, m_privateTexture ) );
    }
    else // this is the case where we have got the textures allocated by VMR
         // all we need to do is to get them from the surface
    {
        CComPtr<IDirect3DTexture9> texture;
        FAIL_RET( lpPresInfo->lpSurf->GetContainer( IID_IDirect3DTexture9, (LPVOID*) & texture.p ) );    
        FAIL_RET( m_scene.DrawScene(m_D3DDev, texture ) );
    }

    FAIL_RET( m_D3DDev->Present( NULL, NULL, NULL, NULL ) );

#endif
    return S_OK;
}

bool CAllocator::NeedToHandleDisplayChange()
{
    if( ! m_lpIVMRSurfAllocNotify )
    {
        return false;
    }

    D3DDEVICE_CREATION_PARAMETERS Parameters;
    if( FAILED( m_D3DDev->GetCreationParameters(&Parameters) ) )
    {
        return false;
    }

    HMONITOR currentMonitor = m_D3D->GetAdapterMonitor( Parameters.AdapterOrdinal );

    HMONITOR hMonitor = m_D3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );

    return hMonitor != currentMonitor;


}


// IUnknown
HRESULT CAllocator::QueryInterface( 
        REFIID riid,
        void** ppvObject)
{
    HRESULT hr = E_NOINTERFACE;

    if( ppvObject == NULL ) {
        hr = E_POINTER;
    } 
    else if( riid == IID_IVMRSurfaceAllocator9 ) {
        *ppvObject = static_cast<IVMRSurfaceAllocator9*>( this );
        AddRef();
        hr = S_OK;
    } 
    else if( riid == IID_IVMRImagePresenter9 ) {
        *ppvObject = static_cast<IVMRImagePresenter9*>( this );
        AddRef();
        hr = S_OK;
    } 
    else if( riid == IID_IUnknown ) {
        *ppvObject = 
            static_cast<IUnknown*>( 
            static_cast<IVMRSurfaceAllocator9*>( this ) );
        AddRef();
        hr = S_OK;    
    }

    return hr;
}

ULONG CAllocator::AddRef()
{
    return InterlockedIncrement(& m_refCount);
}

ULONG CAllocator::Release()
{
    ULONG ret = InterlockedDecrement(& m_refCount);
    if( ret == 0 )
    {
        delete this;
    }

    return ret;
}


CMovie::CMovie( IDirect3D9* d3d, IDirect3DDevice9* d3dd )
:m_D3D(d3d)
,m_D3DDev(d3dd)
{
    CComPtr<IVMRFilterConfig9> filterConfig;
    HRESULT hr;
    
	// フィルタグラフ　インターフェース作成
	if( FAILED( hr = m_graph.CoCreateInstance(CLSID_FilterGraph ) ));

	// VMR用フィルタ　インターフェース作成
    if( FAILED( hr = m_filter.CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER) ));

	// VMRレンダリングコンフィグ　インターフェース取得
	if( FAILED( hr = m_filter->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&filterConfig))));

	// レンダリング方法設定
    if( FAILED( hr = filterConfig->SetRenderingMode( VMR9Mode_Renderless )));

	// レンダリングのミキシング数設定（２にする理由が不明）
    if( FAILED( hr = filterConfig->SetNumberOfStreams(2) ));

	// VMRフィルタにアロケータプレゼンター設定
    if( FAILED( hr = SetAllocatorPresenter( m_filter ) ));

	// フィルタグラフにVMRフィルタを登録
    if( FAILED( hr = m_graph->AddFilter(m_filter, L"Video Mixing Renderer 9") ));

	// フィルタグラフのコントローラー　インターフェース取得
    if( FAILED( hr = m_graph->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&m_mediaControl))));
}

HRESULT CMovie::SetAllocatorPresenter( CComPtr<IBaseFilter> filter )
{
    if( filter == NULL )
    {
        return E_FAIL;
    }

    HRESULT hr;

    CComPtr<IVMRSurfaceAllocatorNotify9> lpIVMRSurfAllocNotify;
    hr = filter->QueryInterface(IID_IVMRSurfaceAllocatorNotify9, reinterpret_cast<void**>(&lpIVMRSurfAllocNotify));

    // create our surface allocator
	m_Allocator = new CAllocator( m_D3D, m_D3DDev );
	m_surfaceAllocator.Attach( m_Allocator );
    if( FAILED( hr ) )
    {
        m_surfaceAllocator = NULL;
        return hr;
    }

    // let the allocator and the notify know about each other
	DWORD_PTR	userId = 0xACDCACDC ;
    hr = lpIVMRSurfAllocNotify->AdviseSurfaceAllocator( userId, m_surfaceAllocator );
    hr = m_surfaceAllocator->AdviseNotify(lpIVMRSurfAllocNotify);
    
    return hr;
}

void CMovie::LoadMovie( LPCWSTR filename , LPDIRECT3DSURFACE9 surface )
{
	m_Allocator->SetSurface( surface );

	// フィルタグラフにファイル読み込み
    HRESULT hr = m_graph->RenderFile( filename, NULL );

    m_mediaControl->Run();
}

