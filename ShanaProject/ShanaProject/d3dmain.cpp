#include <windows.h>
#include <d3d9.h>
#include <d3d9types.h>
#include "d3dmain.h"

D3DDISPLAYMODE				d3d_dis_m;
D3DPRESENT_PARAMETERS		d3d_pre_p;
LPDIRECT3D9					lpD3D = NULL;
LPDIRECT3DDEVICE9			lpD3Ddev = NULL;					// Direct3D�f�o�C�X�I�u�W�F�N�g

//-----------------------------------------------------------------------------------------
// DirectGraphics�̏I��(�I�u�W�F�N�g�̔j��)
//-----------------------------------------------------------------------------------------

bool D3D_END()
{

		RELEASE_3D(lpD3D);
		RELEASE_3D(lpD3Ddev);
		return true;
}

//-----------------------------------------------------------------------------------------
// DirectX�̏�����
//-----------------------------------------------------------------------------------------

bool D3Dinit( HWND hwnd, int width, int height, int full )
{
	// Direct3D �I�u�W�F�N�g���쐬
	if( NULL == ( lpD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) ){
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL,"Direct3D �̍쐬�Ɏ��s���܂����B","ERROR MASSAGE",MB_OK | MB_ICONSTOP);
		// �I������
		return false;
	}

	//�������m��
	ZeroMemory(&d3d_pre_p,sizeof(D3DPRESENT_PARAMETERS));
	// ���݂̉�ʃ��[�h���擾
	lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3d_dis_m);
	// Direct3D �������p�����[�^�̐ݒ�
	if (full)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		d3d_pre_p.BackBufferFormat = D3DFMT_R5G6B5;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		d3d_pre_p.BackBufferFormat = d3d_dis_m.Format;
	}
	
	//D3DPRESENT_PARAMETERS�\���̂̒��g�̐ݒ�
	d3d_pre_p.BackBufferCount = 1;
	d3d_pre_p.BackBufferWidth = width;
	d3d_pre_p.BackBufferHeight = height;
	d3d_pre_p.EnableAutoDepthStencil = TRUE;
	d3d_pre_p.AutoDepthStencilFormat = D3DFMT_D16;
	d3d_pre_p.SwapEffect = D3DSWAPEFFECT_DISCARD;			//����D3DSWAPEFFECT_COPY_VSYNC�Ȃǂ�����   
	d3d_pre_p.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;		// �����M���Ɠ����i�����x�j
//	d3d_pre_p.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;// ���E�`��
/*	d3dppApp.BackBufferCount		= 1;							// �o�b�N�o�b�t�@�̐�
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
*/
	if (!full)
	{
		// �E�C���h�E���[�h
		d3d_pre_p.Windowed =  true ;	//true=�E�B���h�D���[�h�ŋN�� false=�t���X�N���[�����[�h�ŋN��
	}
	d3d_pre_p.EnableAutoDepthStencil = 1;	//ture���ɂ̓A�v���P�[�V�����ɑ΂���[�x�o�b�t�@���Ǘ���Z�o�b�t�@
	d3d_pre_p.AutoDepthStencilFormat = D3DFMT_D16;
	// �v���C�}���f�B�X�v���C�h���C�o�����g��Ȃ��Ǝv���̂�D3DADAPTER_DEFAULT
	// D3DDEVTYPE�̎�ށ@1:T&L HAL�Ŏ��s�J�n
	if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT ,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3d_pre_p,&lpD3Ddev)))
	{
		// 1�����s�A2:HAL(�\�t�g�E�F�A���_����)�Ŏ��s�J�n
		if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT ,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3d_pre_p,&lpD3Ddev)))
		{
			// 2�����s�A3:REF �Ŏ��s�J�n
			if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT ,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3d_pre_p,&lpD3Ddev)))
			{
				// ���Ǌ��I�ɑʖ�
				MessageBox(NULL,"���炢���˂��ADirectX�g���ĕ`��ł��ˁ[���Ă��B","ERROR MASSAGE",MB_OK | MB_ICONSTOP);
				D3D_END();
				// �I������
				return false;
			}
		}
	}
	return true;
}
