//-----------------------------------------------------------------------------------------
// �萔
//-----------------------------------------------------------------------------------------
// �d���C���N���[�h�̉��
#ifndef __D3DMAIN
#define __D3DMAIN

#include <windows.h>
#include <d3d9.h>

#define RELEASE_3D(x) 	if(x){x->Release();x=NULL;}

extern bool D3D_END();
extern bool D3Dinit( HWND hwnd, int width, int height, int full );

extern LPDIRECT3D9			lpD3D;
extern LPDIRECT3DDEVICE9	lpD3Ddev;			// Direct3D�f�o�C�X�I�u�W�F�N�g

#endif
