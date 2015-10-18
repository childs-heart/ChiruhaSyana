#include <d3d9.h>
#include <d3dx9.h>
#include "CLIB_Mesh.h"
#include "CLIB_D3DMain.h"

LPD3DXBUFFER pD3DXMtrlBuffer;

//
//  �֐�: CXFile( )
//
//  �ړI: CXFile�N���X�@�R���X�g���N�^
//
CXFile::CXFile()
{
	m_Mesh		= NULL;
	m_MaterialBuffer	= NULL;
//	m_MeshMaterials		= NULL;
	m_NumMaterials		= 0;
}

//
//  �֐�: CXFile( )
//
//  �ړI: CXFile�N���X�@�f�X�g���N�^
//
CXFile::~CXFile()
{
	RELEASE_3D( m_Mesh );
	RELEASE_3D( m_MaterialBuffer );
//	RELEASE_3D( m_MeshMaterials );
}

//
//  �֐�: LoadXFile( char *filename, LPDIRECT3DDEVICE9 d3ddevice )
//
//  �ړI: XFile�ǂ݂���
//
//  �p�����[�^:
//		para1�FD3D�f�o�C�X��
//�@�����F
//		�e�N�X�`���[��ǂݍ��܂���O�ɕK�v
//		�R���X�g���N�^�ŁA�f�o�C�X��n���Ă���΁A���̊֐��͌Ă΂Ȃ��ėǂ�
//�@�@�@
bool CXFile::LoadXFile( char *filename, LPDIRECT3DDEVICE9 d3ddevice )
{
	if( FAILED( D3DXLoadMeshFromX( filename, D3DXMESH_SYSTEMMEM, 
											d3ddevice, NULL, 
											&m_MaterialBuffer, NULL, &m_NumMaterials, 
											&m_Mesh ) ) ){
		return FALSE;
	}

	return TRUE;
}


//
//  �֐�: CXFileGroup( int num, LPDIRECT3DDEVICE9 d3ddevice )
//
//  �ړI: �R���X�g���N�^
//
//  �p�����[�^:
//		para1�FX�t�@�C���N���X�̐�
//		para2�FD3D�f�o�C�X
//�@�����F
//		D3D�f�o�C�X�́ALoadXFile()�p�ɕK�v
//		NULL����ꂽ�ꍇ�́ALoadXFile()�O��SetD3DDevice()�ŃZ�b�g���Ă����K�v������
//
CXFileGroup::CXFileGroup( int num, LPDIRECT3DDEVICE9 d3ddevice ){
	m_Num	= num ;
	m_CXFile = NULL ;

	m_CXFile  = new CXFile[num]() ;
	m_D3DDevice	= d3ddevice ;
}

//
//  �֐�: ~CXFileGroup( )
//
//  �ړI: �f�X�g���N�^
//
CXFileGroup::~CXFileGroup( ){
	if( m_CXFile != NULL ){
		delete[] m_CXFile;
	}
	m_CXFile = NULL;
}

//
//  �֐�: LoadXFile( int num, char *filename )
//
//  �ړI: XFile�ǂ݂���
//
//  �p�����[�^:
//		para1�FXFile�N���X�̗v�f�ԍ�
//		para2�F�t�@�C����
//�@�����F
//		X�t�@�C����ǂݍ��܂���O�ɕK�v
//		�R���X�g���N�^�Ńf�o�C�X��n���Ă���΁A���̊֐��͌Ă΂Ȃ��ėǂ�
//�@�@�@
bool CXFileGroup::LoadXFile( int num, char *filename )
{
	return m_CXFile[num].LoadXFile( filename, m_D3DDevice ) ;
}

//
//  �֐�: SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
//
//  �ړI: d3d�f�o�C�X�Z�b�g
//
//  �p�����[�^:
//		para1�FD3D�f�o�C�X��
//�@�����F
//		X�t�@�C����ǂݍ��܂���O�ɕK�v
//		�R���X�g���N�^�Ńf�o�C�X��n���Ă���΁A���̊֐��͌Ă΂Ȃ��ėǂ�
//�@�@�@
void CXFileGroup::SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
{
	m_D3DDevice = d3ddevice ;
}

//
//  �֐�: GetXFile( int num )
//
//  �ړI: XFile�N���X�O���[�v�Ɋi�[����Ă���XFile�N���X���ЂƂ擾����
//
//  �p�����[�^:
//		para1�FXFile�N���X�̗v�f�ԍ�
//
CXFile* CXFileGroup::GetXFile( int num )
{
	return &m_CXFile[num];
}
