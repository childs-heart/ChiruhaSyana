#pragma	once

#include <d3dx9tex.h>

//==============================================================
// �w�t�@�C���N���X
//==============================================================
class	CXFile{
friend class CD3DDraw;
friend class CD3DDraw2;
friend class CD3DDraw3;
private:
	LPD3DXMESH		m_Mesh ;					// ���b�V���I�u�W�F�N�g
	D3DMATERIAL9*	m_MeshMaterials ;			// ���b�V���̂Ȃ񂾂���
	LPD3DXBUFFER	m_MaterialBuffer ;			// ���b�V�����̃|�C���g
	DWORD           m_NumMaterials ;			// ���b�V���̐�
public:
	// �R���X�g���N�^���f�X�g���N�^
	CXFile();
	virtual ~CXFile();

	// X�t�@�C���ǂݍ���
	bool LoadXFile( char *filename , LPDIRECT3DDEVICE9 d3ddevice );

};


//==============================================================
// �w�t�@�C�����X�g�N���X
//==============================================================
class	CXFileGroup{
private:
	LPDIRECT3DDEVICE9	m_D3DDevice;		// DX �f�o�C�X�I�u�W�F�N�g
	CXFile*				m_CXFile;			// XFile�N���X���X�g

	int		m_Num;							// XFile�N���X�̐�

public:
	// �R���X�g���N�^���f�X�g���N�^
	CXFileGroup( int num, LPDIRECT3DDEVICE9 d3ddevice );
	virtual ~CXFileGroup();

	// DirectX Graphics �f�o�C�X�I�u�W�F�N�g�Z�b�g
	void SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice );
	// X�t�@�C���ǂݍ���
	bool LoadXFile( int num , char *filename );
	// ���X�g���̎w�肵��X�t�@�C���N���X�̃|�C���^���擾
	CXFile*	GetXFile( int num );
};
