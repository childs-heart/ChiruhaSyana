#include <d3dx9tex.h>
#include "CLIB_Texture.h"
#include "CLIB_D3DMain.h"
#include <stdio.h>

//
//  �e�N�X�`���[�N���X
//

//
//  �֐�: CTEXTURE()
//
//  �ړI: �e�N�X�`���[�N���X�R���X�g���N�^
//
//  �R�����g:
//
CTexture::CTexture()
{
	pD3DTex = NULL;
	m_ImageData = NULL;
}

//
//  �֐�: ~CTEXTURE()
//
//  �ړI: �e�N�X�`���[�N���X�f�X�g���N�^
//
//  �R�����g:
//
CTexture::~CTexture()
{
	if( m_ImageData ){
		delete m_ImageData;
		m_ImageData = NULL;
	}
	RELEASE_3D( pD3DTex );
}

//
//  �֐�: LoadTexture( char * , LPDIRECT3DDEVICE9 , RGBQUAD *pal, DWORD color_key )
//
//  �ړI: �e�N�X�`���[�ǂݍ���
//
//  �p�����[�^:
//		para1�F�t�@�C����
//�@�@�@para2�FD3D�f�o�C�X
//		para3�F�p���b�g�f�[�^�idefault  NULL )
//		para4�F�����F�idefault�@�΂��ۂ��F )
//
//�@�����F
//		�ǂݍ��߂�摜�t�@�C���i .bmp, .jpg, .dds, .png �Ȃǁj
//
bool CTexture::LoadTexture( char *name , LPDIRECT3DDEVICE9 d3ddevice ,int vram, RGBQUAD *pal, DWORD color_key )
{
	HANDLE	hReadFile ;
	DWORD	nFileSize;
	LPDIRECT3DSURFACE9		pSurface = NULL;

	m_D3DDevice = d3ddevice;
	m_ColorKey = color_key;

	RELEASE_3D( pD3DTex );

	// �摜���ǂݍ���
	strcpy( m_Filename, name ) ;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	D3DXGetImageInfoFromFile( m_Filename, &m_TexInfo );

	// �t�@�C���I�[�v�� 
	hReadFile = NULL ;
	hReadFile = CreateFile( m_Filename ,GENERIC_READ,0,NULL,
						OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if( hReadFile == INVALID_HANDLE_VALUE ){
		char a[255];
		sprintf(a,"�t�@�C���Ȃ��A%s",m_Filename);
		MessageBox(NULL,a,"file not found",MB_OK);
		return FALSE;
	}

	// �t�@�C���T�C�Y�擾
	m_ImageSize = GetFileSize( hReadFile , NULL );

	// �̈�m��
	m_ImageData = new unsigned char[ m_ImageSize ] ;

	// �f�[�^�ǂݍ���
	ReadFile( hReadFile , m_ImageData , m_ImageSize , &nFileSize , NULL );
	CloseHandle( hReadFile );

	DWORD res;
/*	if( D3D_OK != ( res = D3DXCreateTextureFromFileInMemoryEx( m_D3DDevice, m_ImageData, m_ImageSize, 0, 0, 0, 0, D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 
		m_ColorKey, NULL, NULL, &pD3DTex ) )){
		delete m_ImageData;
		m_ImageData = NULL;
		return FALSE;
	}
*/

	// �p���b�g�f�[�^���蓖��
	if( pal != NULL ){
		SetPalette( pal );
	}

	// ��̃e�N�X�`���[�쐬
	D3DPOOL pool;
	if( vram == 0 ){
		pool = D3DPOOL_MANAGED;
	}
	else{
		pool = D3DPOOL_DEFAULT;
	}
	if( FAILED( res = d3ddevice->CreateTexture( m_TexInfo.Width, m_TexInfo.Height, 1, 0,//D3DUSAGE_RENDERTARGET,D3DUSAGE_DYNAMIC,
		D3DFMT_A8R8G8B8,pool, &pD3DTex ,NULL))){
		delete m_ImageData;
		m_ImageData = NULL;
		return FALSE ;
	}

	// �e�N�X�`���[�̃T�[�t�F�X�擾
	pD3DTex->GetSurfaceLevel( 0, &pSurface );

	// �e�N�X�`���[�ɉ摜���蓖��
	if( D3D_OK != D3DXLoadSurfaceFromFileInMemory( pSurface, NULL, NULL, m_ImageData, m_ImageSize, NULL, D3DX_DEFAULT, color_key, NULL ) ){
		RELEASE_3D( pSurface );
		delete m_ImageData;
		m_ImageData = NULL;
		return FALSE;
	}
	RELEASE_3D( pSurface );
	delete m_ImageData;
	m_ImageData = NULL;

	return TRUE;
}

//
//  �֐�: SetPalette( RGBQUAD *pal )
//
//  �ړI: �p���b�g�Z�b�g
//
//  �p�����[�^:
//		para1�F�p���b�g�f�[�^
//
//�@�����F
//		�Z�b�g�ł���摜�t�@�C���@.bmp����
//
bool CTexture::SetPalette( RGBQUAD *pal )
{
	BITMAPINFO	*stBmpInfo;
	unsigned char *dst_data ;

	// �p���b�g�㏑��
	stBmpInfo = (BITMAPINFO *)&m_ImageData[sizeof(BITMAPFILEHEADER)];
	dst_data = (unsigned char *)pal;
	for( int i = 0 ; i < stBmpInfo->bmiHeader.biClrImportant ; i++ ){
		stBmpInfo->bmiColors[i].rgbRed   = dst_data[i*3 + 0 ];
		stBmpInfo->bmiColors[i].rgbGreen = dst_data[i*3 + 1 ];
		stBmpInfo->bmiColors[i].rgbBlue  = dst_data[i*3 + 2 ];
	}
	return true;
}

//
//  �֐�: GetTextureInfo( D3DXIMAGE_INFO * )
//
//  �ړI: �e�N�X�`���[�̉摜�����Q�g����
//
//  �p�����[�^:
//		para1�FD3DXIMAGE_INFO�idirectX SDK�Œ�`����Ă���\���́j�̃|�C���^
//
void CTexture::GetTextureInfo( D3DXIMAGE_INFO *inf ){
	memcpy( inf, &m_TexInfo , sizeof( D3DXIMAGE_INFO ));
}


LPDIRECT3DSURFACE9 CTexture::GetSurface( ){

	LPDIRECT3DSURFACE9		pSurface = NULL;
	// �e�N�X�`���[�̃T�[�t�F�X�擾
	pD3DTex->GetSurfaceLevel( 0, &pSurface );

	return pSurface;
}

LPDIRECT3DTEXTURE9 CTexture::TakeTexture(){

	LPDIRECT3DSURFACE9		pSurface = NULL;

/*	// ��̃e�N�X�`���[�쐬
	if( FAILED( m_D3DDevice->CreateTexture( m_TexInfo.Width, m_TexInfo.Height, 1, D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT, &pD3DTex ,NULL)))
		return FALSE ;

	// �e�N�X�`���[�̃T�[�t�F�X�擾
	pD3DTex->GetSurfaceLevel( 0, &pSurface );

	if( D3D_OK != D3DXLoadSurfaceFromFileInMemory( pSurface, NULL, NULL, m_ImageData, m_ImageSize, NULL, D3DX_DEFAULT, m_ColorKey, NULL ) ){
//		delete m_ImageData;
		return FALSE;
	}
*/
	D3DXIMAGE_INFO info;
	if( D3D_OK != D3DXCreateTextureFromFileInMemoryEx( m_D3DDevice, m_ImageData, m_ImageSize, 0, 0, 0, 0, D3DFMT_A8R8G8B8,
											D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 
											m_ColorKey, NULL, NULL, &pD3DTex )){
		return FALSE;
	}

	return pD3DTex;
}

bool CTexture::ReleaseTexture(){
	RELEASE_3D( pD3DTex );
	return true;
}

//
//  �֐�: CTEXTURE_GROUP( int , LPDIRECT3DDEVICE9 )
//
//  �ړI: �R���X�g���N�^
//
//  �p�����[�^:
//		para1�F�e�N�X�`���[�N���X�̐�
//		para2�FD3D�f�o�C�X
//�@�����F
//		D3D�f�o�C�X�́ALoadTexture()�p�ɕK�v
//		NULL����ꂽ�ꍇ�́ALoadTexture()�O��SetD3DDevice()�ŃZ�b�g���Ă����K�v������
//
CTextureGroup::CTextureGroup( int num, LPDIRECT3DDEVICE9 d3ddevice ){
	m_Num	= num ;
	m_CTex  = NULL ;

	m_CTex  = new CTexture[num]() ;
	m_D3DDevice	= d3ddevice ;
}

//
//  �֐�: ~CTEXTURE_GROUP( )
//
//  �ړI: �f�X�g���N�^
//
//  �p�����[�^:
//
CTextureGroup::~CTextureGroup( ){
	if( m_CTex != NULL ){
		delete[] m_CTex;
	}
	m_CTex = NULL;
}

//
//  �֐�: LoadTexture( int num, char *filename )
//
//  �ړI: �e�N�X�`���[�t�@�C���ǂݍ���
//
//  �p�����[�^:
//		para1�F�e�N�X�`���[�N���X�̗v�f�ԍ�
//		para2�F�t�@�C����
//
bool CTextureGroup::LoadTexture( int num, char *filename,int vram_set , RGBQUAD *pal, DWORD color_key )
{
	return m_CTex[num].LoadTexture( filename, m_D3DDevice, vram_set, pal, color_key ) ;
}

//
//  �֐�: Reset( )
//
//  �ړI: �e�N�X�`���[�����Z�b�g
//
void CTextureGroup::Reset( )
{
	if( m_CTex != NULL ){
		delete[] m_CTex;
	}
	m_CTex  = new CTexture[m_Num]() ;
}

//
//  �֐�: SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
//
//  �ړI: d3d�f�o�C�X�Z�b�g
//
//  �p�����[�^:
//		para1�FD3D�f�o�C�X��
//�@�����F
//		�e�N�X�`���[��ǂݍ��܂���O�ɕK�v
//		�R���X�g���N�^�ŁA�f�o�C�X��n���Ă���΁A���̊֐��͌Ă΂Ȃ��ėǂ�
//�@�@�@
void CTextureGroup::SetD3DDevice( LPDIRECT3DDEVICE9 d3ddevice )
{
	m_D3DDevice = d3ddevice ;
}

//
//  �֐�: GetTexture( int num )
//
//  �ړI: �e�X�N�`���[�O���[�v�Ɋi�[����Ă���e�N�X�`���[�N���X���擾����
//
//  �p�����[�^:
//		para1�F�e�N�X�`���[�N���X�̗v�f�ԍ�
//
CTexture* CTextureGroup::GetTexture( int num )
{
	return &m_CTex[num];
}
