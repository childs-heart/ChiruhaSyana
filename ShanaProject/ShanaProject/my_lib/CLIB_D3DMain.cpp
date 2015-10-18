#include "CLIB_D3DMain.h"

// �O���[�o���ϐ�
// DirectX SDK �\����
LPDIRECT3D9				pD3D = NULL;
LPDIRECT3DDEVICE9		pD3DDevice = NULL;
D3DPRESENT_PARAMETERS	d3dppApp;
D3DDISPLAYMODE			d3dDisplay;

// �\����
D3D_MAIN				D3DMain ;

//
//  �֐�: InitD3D()
//
//  �ړI: Direct3D����������
//
//  �R�����g:���s���P�񂾂��Ăяo��
//
int InitD3D( HWND hwnd, int w, int h, int full, HMENU menu ){

	D3DMain.m_DrawHwnd		= hwnd;
	D3DMain.m_Width			= w;
	D3DMain.m_Height		= h;
	D3DMain.m_MenuHwnd		= menu;
	D3DMain.m_WindowMode	= !full;

	// Direct3D�̃I�u�W�F�N�g�쐬
	if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
		MessageBox(NULL,TEXT("Direct3D�I�u�W�F�N�g�̐����Ɏ��s���܂����B[DirectX9�������Ă��Ȃ��H]"),TEXT("�v���I�ȃG���["), MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	// ���݂̉�ʃ��[�h���擾
	if( D3D_OK != (pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3dDisplay))){
		MessageBox(NULL,TEXT("���݂̃f�B�X�v���C���[�h�擾�Ɏ��s���܂����B"),TEXT("�킯�킩��"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// Direct3D�f�o�C�X�쐬
	ZeroMemory(&d3dppApp,sizeof(d3dppApp));

	d3dppApp.BackBufferCount		= 1;							// �o�b�N�o�b�t�@�̐�
	d3dppApp.BackBufferWidth		= w;							// �o�b�N�o�b�t�@�̕�
	d3dppApp.BackBufferHeight		= h;							// �o�b�N�o�b�t�@�̍�
	d3dppApp.BackBufferFormat		= D3DFMT_A8R8G8B8;				// �o�b�N�o�b�t�@�̉�ʃ��[�h 
//	d3dppApp.BackBufferFormat		= d3dDisplay.Format;			// �o�b�N�o�b�t�@�̉�ʃ��[�h 
	d3dppApp.EnableAutoDepthStencil	= TRUE;							// �[�x�o�b�t�@�L��
	d3dppApp.AutoDepthStencilFormat	= D3DFMT_D16;					// �[�x�o�b�t�@�T�C�Y
	d3dppApp.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER; // �o�b�N�o�b�t�@���b�N���\�ɂ���
	d3dppApp.MultiSampleQuality		= D3DMULTISAMPLE_NONE;			// �}���`�T���v�����O��(?)
	d3dppApp.MultiSampleType		= D3DMULTISAMPLE_NONE;			// �}���`�T���v�����O��(?)
	d3dppApp.Windowed				= !full;						// �E�B���h�E���[�h
	d3dppApp.FullScreen_RefreshRateInHz	= 0;						// ���t���b�V�����[�g�@�E�B���h�E���[�h�̏ꍇ:0
	d3dppApp.SwapEffect				= D3DSWAPEFFECT_COPY;			// �X���b�s���O���@
//	d3dppApp.PresentationInterval	= D3DPRESENT_INTERVAL_DEFAULT;	// �����M���Ɠ���
	d3dppApp.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;		// �����M���Ɠ����i�����x�j
//	d3dppApp.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;// ���E�`��
	d3dppApp.hDeviceWindow			= NULL;							// d3d.present���̃^�[�Q�b�g�i�܂�`���j�@0�F����

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
			wsprintf( buf, TEXT("���̃r�f�I�J�[�h�̌��݂̃��[�h�ł̓Q�[�������s�ł��܂���B�t���X�N���[�������܂����H\n[%d]"), D3DCapsStruct.m_DisplayMode[i].RefreshRate );
			if( MessageBox( NULL, buf, TEXT("�₢���킹"), MB_YESNO )==IDNO ){
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
					DebugBox( NULL, TEXT("Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C ������������܂���B") );
					RELEASE_3D(pD3D);
					return FALSE;
				case D3DERR_INVALIDCALL:
					DebugBox( NULL, TEXT("Direct3D�̏������Ɏ��s���܂���[D3DERR_INVALIDCALL]\n���̃O���t�B�b�N�J�[�h�͕K�v�ȋ@�\���T�|�[�g���Ă��Ȃ����A\n���邢��DirectX8�ɑΉ������h���C�o�������Ă��܂���B") );
					RELEASE_3D(pD3D);
					return FALSE;
				case D3DERR_NOTAVAILABLE:
					DebugBox( NULL, TEXT("Direct3D�̏������Ɏ��s���܂���[D3DERR_NOTAVAILABLE]\n���̃O���t�B�b�N�J�[�h�͕K�v�ȋ@�\���T�|�[�g���Ă��Ȃ����A\n���邢��DirectX8�ɑΉ������h���C�o�������Ă��܂���B") );
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
						DebugBox( NULL, TEXT("Direct3D ���������s���̂ɏ\���ȃf�B�X�v���C ������������܂���B") );
						RELEASE_3D(pD3D);
						return FALSE;
					case D3DERR_INVALIDCALL:
						DebugBox( NULL, TEXT("Direct3D�̏������Ɏ��s���܂���[D3DERR_INVALIDCALL]\n���̃O���t�B�b�N�J�[�h�͕K�v�ȋ@�\���T�|�[�g���Ă��Ȃ����A\n���邢��DirectX8�ɑΉ������h���C�o�������Ă��܂���B") );
						RELEASE_3D(pD3D);
						return FALSE;
					case D3DERR_NOTAVAILABLE:
						DebugBox( NULL, TEXT("Direct3D�̏������Ɏ��s���܂���[D3DERR_NOTAVAILABLE]\n���̃O���t�B�b�N�J�[�h�͕K�v�ȋ@�\���T�|�[�g���Ă��Ȃ����A\n���邢��DirectX8�ɑΉ������h���C�o�������Ă��܂���B") );
						RELEASE_3D(pD3D);
						return FALSE;
					}
				}
			}
		}
	}



	if( FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&D3DCapsStruct.m_NowDisplayMode)) ){	
		MessageBox(NULL,TEXT("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂����B[�Ȃɂ䂦�H]"),TEXT("�v���I�ȃG���["), MB_OK | MB_ICONSTOP);
		RELEASE_3D(pD3D);
		return FALSE;
	}
#endif

	return TRUE;
}

//
//  �֐�: TermD3D()
//
//  �ړI: Direct3D�I������
//
//  �R�����g:�v���O�����I�����ɕK���R�[�����Ȃ��Ă͂Ȃ�Ȃ�
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
	// ��ʃN���A
	pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_TARGET , D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	// Begin the scene.
	pD3DDevice->BeginScene();

	// Rendering of scene objects happens here.

	// End the scene.
	pD3DDevice->EndScene();

	// ��ʂɕ\���i�o�b�t�@�X���b�v�j
	pD3DDevice->Present( NULL, NULL, NULL, NULL );
}