#pragma once

#include <d3d9.h>
#include <d3d9types.h>

#define RELEASE_3D(x) 	if(x){x->Release();x=NULL;}

// �v���g�^�C�v
extern	int InitD3D( HWND, int width, int height, int full, HMENU );
extern	int	TermD3D(void);
extern	LPDIRECT3DDEVICE9	GetD3DDevice();

extern	void	ddd();

extern	LPDIRECT3D9				pD3D;
extern	LPDIRECT3DDEVICE9		pD3DDevice;

typedef struct{

	HWND		m_DrawHwnd;			// �`��� �E�B�h�E�n���h��
	HMENU		m_MenuHwnd;			// ���j���[�n���h���i���[�t��ԁj

	int			m_Width;			// ���ƍ���
	int			m_Height;			//

	int			m_WindowMode;		// �E�B���h�E���[�h�@	WINDOW(TRUE) or FULL SCREEN(FALSE)
	int			m_FullScreenOnly;	// �t���X�N���[������	FULL ONLY(TRUE) or WINDOW OK(FALSE)

	int			m_WindowModeChange;
	int			m_DisplayModeChange;
	int			m_FlipActive;

}D3D_MAIN;
extern D3D_MAIN		D3DMain;
