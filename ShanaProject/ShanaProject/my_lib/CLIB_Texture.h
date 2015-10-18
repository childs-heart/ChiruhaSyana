#pragma	once

#include <d3d9.h>
#include <d3dx9tex.h>

//==============================================================
// �e�N�X�`���[�N���X
//==============================================================
class	CTexture{
private:
protected:
	char				m_Filename[256];	// �摜�t�@�C�����i�K�v�Ȃ������j
	D3DXIMAGE_INFO		m_TexInfo;			// �摜���\����


public:
	LPDIRECT3DTEXTURE9	pD3DTex;			// DirectX�e�N�X�`���[�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_D3DDevice;

	unsigned char		*m_ImageData;		// �摜�f�[�^
	DWORD				m_ImageSize;		// �摜�e��
	DWORD				m_ColorKey;			// �J���[�L�[

	// �R���X�g���N�^���f�X�g���N�^
	CTexture();
	virtual ~CTexture();

	// �摜�t�@�C���ǂݍ���
	bool LoadTexture( char *name , LPDIRECT3DDEVICE9 d3ddevice, int vram_set = 0, RGBQUAD *pal = NULL , DWORD color_key = 0xFF007B8C );
	bool SetPalette( RGBQUAD *pal );

	// �摜���擾
	void GetTextureInfo( D3DXIMAGE_INFO	*texinfo );

	// �T�[�t�F�X�擾
	LPDIRECT3DSURFACE9 GetSurface( );

	// DIRECT3DTEXTURE�p��
	LPDIRECT3DTEXTURE9	TakeTexture();
	bool ReleaseTexture();
};


//==============================================================
// �e�N�X�`���[���X�g�N���X
// �X�N���v�g�N���X�@�P�C���X�^���X���Ɉ���蓖��
//==============================================================
class	CTextureGroup{
private:
	LPDIRECT3DDEVICE9	m_D3DDevice;		// DX �f�o�C�X�I�u�W�F�N�g
	CTexture*			m_CTex;				// �e�N�X�`���[�N���X���X�g

	int					m_Num;				// �e�N�X�`���[�N���X�̐�

public:
	// �R���X�g���N�^���f�X�g���N�^
	CTextureGroup( int num, LPDIRECT3DDEVICE9 d3ddevice );
	virtual ~CTextureGroup();

	// DirectX Graphics �f�o�C�X�I�u�W�F�N�g�Z�b�g
	void SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice );
	// �摜�t�@�C���ǂݍ���
	bool LoadTexture( int num, char *filename,int vram_set = 0, RGBQUAD *pal = NULL, DWORD color_key = 0xFF007B8C );
	// ���X�g���̎w�肵���e�N�X�`���[�N���X�̃|�C���^���擾
	CTexture*	GetTexture( int num );
	// �e�N�X�`���[���N���A
	void	Reset();
};
