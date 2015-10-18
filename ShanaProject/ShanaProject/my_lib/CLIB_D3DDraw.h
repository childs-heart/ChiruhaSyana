#pragma once
#include "CLIB_DispObj.h"
#include <d3d9.h>
#include <d3d9types.h>

///////////////////////////
// ���_�o�b�t�@�\����
// �K���Ƀt�H�[�}�b�g�T��
// ���W�ϊ��ς݁@�e�N�X�`���[��
typedef	struct
{
	float		x,y,z;
	float		rhw;
	D3DCOLOR	color;
	D3DCOLOR	specular;
	float		tu,tv;
}TLVERTEX;
#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_SPECULAR)

// ���W�ϊ��ς݁@�e�N�X�`���[���i�Q���j
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

// ���W�ϊ��ς݁@�e�N�X�`���[�Ȃ�
typedef struct
{
	float		x,y,z;
	float		rhw;
	D3DCOLOR	color;

}TLVERTEX_NOTEX;
#define	FVF_TLVERTEX_NOTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// �e�N�X�`���[��
typedef struct 
{
	float		x,y,z;
	D3DCOLOR	color;
	float		tu,tv;
}TLVERTEX_3D;
#define	FVF_TLVERTEX_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �e�N�X�`���[���i�Q���j
typedef struct 
{
	float		x,y,z;
	D3DCOLOR	color;
	float		tu0,tv0;
	float		tu1,tv1;
}TLVERTEX2_3D;
#define	FVF_TLVERTEX2_3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEX2)


//==============================================================
// �`��N���X
//==============================================================
class CD3DDraw{
public:
	// DirectX Graphics�I�u�W�F�N�g
	LPDIRECT3D9			m_D3D;
	LPDIRECT3DDEVICE9	m_D3DDevice;

	CDispObj*			m_Disp;			// �}�`�N���X�i�K�v�Ȃ������j

	int	m_CenterX;					// �X�N���[���Z���^�[ X���W
	int	m_CenterY;					// �X�N���[���Z���^�[ Y���W

	// �`�掞�Ɏg���֐�
	void SetVertex( );					// ���_���Z�b�g�i�������j				
	bool SetTransrate( );				// ���W�ϊ����s

public:
	// �`��J�n
	void DrawBegin();
	bool Draw( CDispObj* disp );
	void DrawEnd();
	// DirectX Graphics �f�o�C�X�I�u�W�F�N�g�Z�b�g���Q�b�g
	bool SetDevice( LPDIRECT3DDEVICE9 d3ddevice );
	LPDIRECT3DDEVICE9 GetDevice();

	// �X�N���[���Z���^�[���W�Z�b�g
	void SetCenter( int x, int y );
};
