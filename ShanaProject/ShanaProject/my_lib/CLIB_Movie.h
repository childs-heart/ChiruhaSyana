#pragma once

// Windows Header Files:
#include <objbase.h>
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <comdef.h>
#include <atlbase.h>
#include <commdlg.h>
#include <tchar.h>

// DirectShow Header Files
#include <dshow.h>
#include <d3d9.h>
#include <vmr9.h>

#include <dshow.h>

#pragma warning(push, 2)
#include <vector>
#pragma warning(pop)
using namespace std;

class CAllocator  : public  IVMRSurfaceAllocator9, 
                            IVMRImagePresenter9
{
public:
    CAllocator( IDirect3D9* d3d , IDirect3DDevice9* d3dd );
	
	void SetSurface( LPDIRECT3DSURFACE9 surface );
    virtual ~CAllocator();

    // IVMRSurfaceAllocator9
    virtual HRESULT STDMETHODCALLTYPE InitializeDevice( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out][in] */ DWORD *lpNumBuffers);
            
    virtual HRESULT STDMETHODCALLTYPE TerminateDevice( 
        /* [in] */ DWORD_PTR dwID);
    
    virtual HRESULT STDMETHODCALLTYPE GetSurface( 
        /* [in] */ DWORD_PTR dwUserID,
        /* [in] */ DWORD SurfaceIndex,
        /* [in] */ DWORD SurfaceFlags,
        /* [out] */ IDirect3DSurface9 **lplpSurface);
    
    virtual HRESULT STDMETHODCALLTYPE AdviseNotify( 
        /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify);

    // IVMRImagePresenter9
    virtual HRESULT STDMETHODCALLTYPE StartPresenting( 
        /* [in] */ DWORD_PTR dwUserID);
    
    virtual HRESULT STDMETHODCALLTYPE StopPresenting( 
        /* [in] */ DWORD_PTR dwUserID);
    
    virtual HRESULT STDMETHODCALLTYPE PresentImage( 
        /* [in] */ DWORD_PTR dwUserID,
        /* [in] */ VMR9PresentationInfo *lpPresInfo);
    
    // IUnknown
    virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        REFIID riid,
        void** ppvObject);

    virtual ULONG STDMETHODCALLTYPE AddRef();
    virtual ULONG STDMETHODCALLTYPE Release();

protected:
    HRESULT CreateDevice();

    // a helper function to erase every surface in the vector
//    void DeleteSurfaces();

    bool NeedToHandleDisplayChange();

    // This function is here so we can catch the loss of surfaces.
    // All the functions are using the FAIL_RET macro so that they exit
    // with the last error code.  When this returns with the surface lost
    // error code we can restore the surfaces.
    HRESULT PresentHelper(VMR9PresentationInfo *lpPresInfo);

private:
	// 引数なしのインスタンス作成を不許可
	CAllocator();

	// needed to make this a thread safe object
//    CCritSec    m_ObjectLock;
    HWND        m_window;
    long        m_refCount;

    CComPtr<IDirect3D9>                     m_D3D;
    CComPtr<IDirect3DDevice9>               m_D3DDev;
    CComPtr<IVMRSurfaceAllocatorNotify9>    m_lpIVMRSurfAllocNotify;
    CComPtr<IDirect3DSurface9>				m_surfaces;
    CComPtr<IDirect3DSurface9>              m_renderTarget;
    CComPtr<IDirect3DTexture9>              m_privateTexture;
};

class CMovie{
public:
    CMovie( IDirect3D9* d3d , IDirect3DDevice9* d3dd );
	HRESULT SetAllocatorPresenter( CComPtr<IBaseFilter> filter );
	void LoadMovie( LPCWSTR filename, LPDIRECT3DSURFACE9 surface );

private:
	CAllocator*								m_Allocator;

    CComPtr<IDirect3D9>                     m_D3D;
    CComPtr<IDirect3DDevice9>               m_D3DDev;
	// DirectShow interfaces
	CComPtr<IGraphBuilder>					m_graph;
	CComPtr<IBaseFilter>					m_filter;
	CComPtr<IMediaControl>				    m_mediaControl;
	CComPtr<IVMRSurfaceAllocator9>			m_surfaceAllocator;
};
