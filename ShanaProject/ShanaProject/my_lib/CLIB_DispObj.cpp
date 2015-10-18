#include <Windows.h>
#include "CLIB_DispObj.h"

LEAF_BLEND	StLeafBlend[12] =
	{{D3DBLEND_ONE,			D3DBLEND_ZERO},
	{D3DBLEND_SRCALPHA,		D3DBLEND_INVSRCALPHA},
	{D3DBLEND_SRCALPHA,		D3DBLEND_INVSRCALPHA},
	{D3DBLEND_ONE,			D3DBLEND_INVSRCALPHA},
	{D3DBLEND_SRCALPHA,		D3DBLEND_ONE},
	{D3DBLEND_SRCALPHA,		D3DBLEND_INVSRCCOLOR},
	{D3DBLEND_DESTCOLOR,	D3DBLEND_SRCCOLOR},
	{D3DBLEND_ZERO,			D3DBLEND_SRCCOLOR},
	{D3DBLEND_SRCALPHA,		D3DBLEND_ONE},
	{D3DBLEND_ZERO,			D3DBLEND_INVSRCCOLOR},
	{D3DBLEND_SRCALPHA,		D3DBLEND_ONE},
	{D3DBLEND_INVDESTCOLOR,	D3DBLEND_INVSRCCOLOR},};

//
//  �֐�: CDispObj( )
//
//  �ړI: �R���X�g���N�^
//
//  �p�����[�^:
//�@�����F
//�@�@�@
CDispObj::CDispObj( )
{
	m_Child = NULL ;
	m_Parent = NULL ;
    m_Enable = FALSE;
	Init( 0 );
}

//
//  �֐�: CDispObj( DWORD type )
//
//  �ړI: �R���X�g���N�^�@�����t��
//
//  �p�����[�^:
//		para1�F����
//�@�����F
//�@�@�@
CDispObj::CDispObj( DWORD type )
{
	m_Child = NULL ;
	m_Parent = NULL ;
    m_Enable = FALSE;
	Init( type );
}

//
//  �֐�: ~CDispObj( )
//
//  �ړI: �f�X�g���N�^
//
//  �p�����[�^:
//�@�����F
//�@�@�@
CDispObj::~CDispObj()
{
}

//
//  �֐�: Init( DWORD type )
//
//  �ړI: �N���X�̃����o������������
//
//  �p�����[�^:
//		para1�F����
//�@�����F
//�@�@�@
void CDispObj::Init( DWORD type )
{
	m_Type = type ;

	m_Visible	= TRUE;

	memset( &m_SrcRect, 0, sizeof(RECT) );
	memset( &m_DestRect, 0, sizeof(RECT) );
	m_SrcBlend	= D3DBLEND_SRCALPHA;
	m_DestBlend	= D3DBLEND_INVSRCALPHA;
	m_RotationX[0] = 0;
	m_RotationY[0] = 0;
	m_RotationZ[0] = 0;
	m_RotOrderX[0] = 0;
	m_RotOrderY[0] = 0;
	m_RotOrderZ[0] = 0;
	m_RotationX[1] = 0;
	m_RotationY[1] = 0;
	m_RotationZ[1] = 0;
	m_RotOrderX[1] = 0;
	m_RotOrderY[1] = 0;
	m_RotOrderZ[1] = 0;
	m_Scale		= 1;
	m_Texture[0]= NULL;
	m_Texture[1]= NULL;
	m_Texture[2]= NULL;
	m_Texture[3]= NULL;
	m_XFile		= NULL;
	m_Color		= 0xFFFFFFFF;

}

//
//  �֐�: SetSrcRect( RECT *rect )
//
//  �ړI: �]�����i�e�N�X�`���[�摜�j���W���Z�b�g
//
//  �p�����[�^:
//		para1�F���W
//�@�����F
//�@�@�@
void CDispObj::SetSrcRect( RECT *rect )
{
	memcpy( &m_SrcRect, rect, sizeof(RECT)) ;
}

//
//  �֐�: SetSrcRectFromTex( int texNo )
//
//  �ړI: �]�����i�e�N�X�`���[�摜�j���W���A�e�N�X�`���[���W�ɂ��킹��
//
//  �p�����[�^:
//		para1�F�e�N�X�`���[�ԍ�
//�@�����F
//�@�@�@
void CDispObj::SetSrcRectFromTex( int texNo )
{
	D3DXIMAGE_INFO	imageInfo;

	if( m_Texture[texNo] != NULL ){
		m_Texture[texNo]->GetTextureInfo( &imageInfo );
		SetSrcRect( 0, 0, imageInfo.Width, imageInfo.Height );
	}

}

//
//  �֐�: SetSrcRect( long left, long top, long right, long bottom )
//
//  �ړI: �]�����i�e�N�X�`���[�摜�j���W���Z�b�g
//
//  �p�����[�^:
//		para1-4�F���W
//�@�����F
//�@�@�@
void CDispObj::SetSrcRect( long left, long top, long right, long bottom )
{
	m_SrcRect.left	= left;
	m_SrcRect.top	= top;
	m_SrcRect.right	= right;
	m_SrcRect.bottom= bottom;
}

//
//  �֐�: SetDestRect( RECT *rect )
//
//  �ړI: �]������W���Z�b�g
//
//  �p�����[�^:
//		para1�F���W
//�@�����F
//�@�@�@LEFT > RIGHT�@�̏ꍇ�͍��E���]�����摜�ɂȂ�
//�@�@�@
void CDispObj::SetDestRect( RECT *rect )
{
	memcpy( &m_DestRect, rect, sizeof(RECT)) ;
}

//
//  �֐�: SetDestRect( long left, long top, long right, long bottom )
//
//  �ړI: �]������W���Z�b�g
//
//  �p�����[�^:
//		para1-4�F���W
//�@�����F
//�@�@�@LEFT > RIGHT�@�̏ꍇ�͍��E���]�����摜�ɂȂ�
//�@�@�@
void CDispObj::SetDestRect( long left, long top, long right, long bottom )
{
	m_DestRect.left		= left;
	m_DestRect.top		= top;
	m_DestRect.right	= right;
	m_DestRect.bottom	= bottom;
	m_DestZ				= 0;
}

//
//  �֐�: SetDestRect( long left, long top, long right, long bottom )
//
//  �ړI: �]������W���Z�b�g
//
//  �p�����[�^:
//		para1-4�F���W
//�@�����F
//�@�@�@LEFT > RIGHT�@�̏ꍇ�͍��E���]�����摜�ɂȂ�
//�@�@�@
void CDispObj::SetDestRect( long left, long top, long right, long bottom, long z )
{
	m_DestRect.left		= left;
	m_DestRect.top		= top;
	m_DestRect.right	= right;
	m_DestRect.bottom	= bottom;
	m_DestZ				= z;
}

//
//  �֐�: SetScale( float scale )
//
//  �ړI: �g�嗦�ݒ�
//
//  �p�����[�^:
//		para1�F�g�嗦
//�@�����F
//		�ꉞX�t�@�C���\���̂ݗL���Ƃ���
//�@�@�@
void CDispObj::SetScale( float scale )
{
	m_Scale = scale ;
}

//
//  �֐�: SetTexture( CTexture *tex, char layer )
//
//  �ړI: �e�N�X�`���[�o�^
//
//  �p�����[�^:
//		para1�F�e�N�X�`���[�N���X
//		para2�F���C���[�ԍ��i���g�p�j�ȗ��\
//�@�����F
//�@�@�@���̂Ƃ���param2�͏ȗ����Ă�������
//�@�@�@
void CDispObj::SetTexture( CTexture *tex, char layer )
{
	m_Texture[layer] = tex;
	SetSrcRectFromTex( layer );
}

//
//  �֐�: SetXFile( CXFile *mesh )
//
//  �ړI: X�t�@�C���o�^
//
//  �p�����[�^:
//		para1�FX�t�@�C���N���X
//�@�����F
//�@�@�@�����ɒl�������Ă���ƁA�\���̍ۂɃ��b�V���\�����s����
//�@�@�@
void CDispObj::SetXFile( CXFile *mesh )
{
	m_XFile = mesh ;
}

//
//  �֐�: SetBlendColor( DWORD col )
//
//  �ړI: �f�B�t�F�[�Y�F�ݒ�
//
//  �p�����[�^:
//		para1�FRGB_COLOR
//�@�����F
//�@�@�@�����̒l�ƃe�N�X�`���[�摜���όv�Z����܂�
//�@�@�@
void CDispObj::SetBlendColor( DWORD col )
{
	m_Color = col ;
}

//
//  �֐�: SetSrcBlend( int blend )
//
//  �ړI: �]�����̃u�����h���@
//
//  �p�����[�^:
//		para1�Fblend
//�@�����F
//�@�@�@
//�@�@�@
void CDispObj::SetSrcBlend( int blend )
{
	m_SrcBlend = blend ;
}

//
//  �֐�: SetDestBlend( int blend )
//
//  �ړI: �]����̃u�����h���@
//
//  �p�����[�^:
//		para1�Fblend
//�@�����F
//�@�@�@
//�@�@�@
void CDispObj::SetDestBlend( int blend )
{
	m_DestBlend = blend ;
}

//
//  �֐�: SetRotOrder( char, char, char )
//
//  �ړI: ��]�̗D�揇����ݒ肷��
//
//  �p�����[�^:
//		para1�F��]���� X
//		para2�F��]���� Y
//		para3�F��]���� Z
//�@�����F
//�@�@�@
void CDispObj::SetRotOrder( char x, char y,char z )
{
	m_RotOrderX[0] = x;
	m_RotOrderY[0] = y;
	m_RotOrderZ[0] = z;
}

//
//  �֐�: SetRotation( WORD, WORD, WORD )
//
//  �ړI: ��]�p�x��ݒ肷��
//
//  �p�����[�^:
//		para1�F��]�p�x X��
//		para2�F��]�p�x Y��
//		para3�F��]�p�x Z��
//�@�����F
//�@�@�@
void CDispObj::SetRotation( float rotX, float rotY, float rotZ )
{
	m_RotationX[0] = rotX;
	m_RotationY[0] = rotY;
	m_RotationZ[0] = rotZ;
}

//
//  �֐�: SetRotation( char, WORD, char, WORD, char, WORD )
//
//  �ړI: ��]�p�x��ݒ肷��
//
//  �p�����[�^:
//		para1_3_5�F��]����
//		para2_4_6�F��]�p�x
//�@�����F
//�@�@�@
void CDispObj::SetRotation( char orderX, float rotX,
							 char orderY, float rotY,
							 char orderZ, float rotZ )
{
	m_RotOrderX[0] = orderX;
	m_RotOrderY[0] = orderY;
	m_RotOrderZ[0] = orderZ;
	m_RotationX[0] = rotX;
	m_RotationY[0] = rotY;
	m_RotationZ[0] = rotZ;
}

//
//  �֐�: SetRotation( char, WORD, char, WORD, char, WORD )
//
//  �ړI: ���d�ŉ�]�p�x��ݒ肷��
//
//  �p�����[�^:
//		para1_3_5�F��]����
//		para2_4_6�F��]�p�x
//		para7_9_11�F��]����
//		para8_10_12�F��]�p�x
//�@�����F
//�@�@�@
void CDispObj::SetRotation( char orderX1, float rotX1,
							 char orderY1, float rotY1,
							 char orderZ1, float rotZ1,
							 char orderX2, float rotX2,
							 char orderY2, float rotY2,
							 char orderZ2, float rotZ2 )
{
	m_RotOrderX[0] = orderX1;
	m_RotOrderY[0] = orderY1;
	m_RotOrderZ[0] = orderZ1;
	m_RotationX[0] = rotX1;
	m_RotationY[0] = rotY1;
	m_RotationZ[0] = rotZ1;

	m_RotOrderX[1] = orderX2;
	m_RotOrderY[1] = orderY2;
	m_RotOrderZ[1] = orderZ2;
	m_RotationX[1] = rotX2;
	m_RotationY[1] = rotY2;
	m_RotationZ[1] = rotZ2;
}

//
//  �֐�: ChangeType( DWORD type )
//
//  �ړI: �����ύX
//
//  �p�����[�^:
//		para1�F����
//�@�����F
//�@�@�@
void CDispObj::ChangeType( DWORD type )
{
	m_Type = type ;
}

//
//  �֐�: VisibleOn( )
//
//  �ړI: �\���L��
//
void CDispObj::VisibleOn()
{
	m_Visible = TRUE;
}

//
//  �֐�: VisibleOff( )
//
//  �ړI: �\������
//�@�@�@
void CDispObj::VisibleOff()
{
	m_Visible = FALSE;
}



//
//  �֐�: FreeChain( )
//
//  �ړI: �e�q�֌W��≏����
//
//  �p�����[�^:
//�@�����F
//�@�@�@
void CDispObj::FreeChain()
{
	if( m_Child ){
		m_Child->FreeChain();
	}
	m_Enable	= FALSE;
	m_Visible	= FALSE;
	m_Parent	= NULL;
	m_Child		= NULL;
}


//
//  �֐�: CDispObjGroup( int num )
//
//  �ړI: �C���X�g���N�^
//
//  �p�����[�^:
//		para1�F�쐬����\���I�u�W�F�N�g�N���X�̐�
//�@�����F
//�@�@�@
CDispObjGroup::CDispObjGroup( int num )
{
	m_Num = num ;
	m_CDisp = NULL ;

	m_CDisp = new CDispObj[m_Num]() ;

	int i;
	for( i=0 ; i<num ; i++ ){
		m_CDisp[i].m_Visible = FALSE ;
	}
}

//
//  �֐�: CDispObjGroup( )
//
//  �ړI: �f�X�g���N�^
//�@�@�@
CDispObjGroup::~CDispObjGroup( )
{
	if( m_CDisp != NULL ){
		delete[] m_CDisp;
	}
	m_CDisp = NULL;
}

//
//  �֐�: GetDispObj( DWORD type )
//
//  �ړI: �O���[�v����A�\���I�u�W�F�N�g�N���X�����蓖�Ă�
//
//  �p�����[�^:
//		para1�F�\���I�u�W�F�N�g�̑���
//�@�����F
//�@�@�@
CDispObj* CDispObjGroup::GetDispObj( DWORD type )
{
	int i = 0;
	while( ( i<m_Num ) && ( m_CDisp[i].m_Enable == TRUE ) ){
		i++;
	}

	if( i == m_Num ){
		return NULL;
	}

    m_CDisp[i].m_Enable = TRUE;
	m_CDisp[i].Init( type );

	return &m_CDisp[i];
}

//
//  �֐�: FreeDispObj( CDispObj* disp )
//
//  �ړI: �\���I�u�W�F�N�g�N���X���J���i���g�p�j����
//
//  �p�����[�^:
//		para1�F�\���I�u�W�F�N�g�N���X
//�@�����F
//�@�@�@
void CDispObjGroup::FreeDispObj( CDispObj* disp )
{
	if( disp->m_Parent ){
		disp->m_Parent->m_Child = NULL ;
	}

	if( disp->m_Child ){
		disp->FreeChain();
	}
	disp->m_Enable	= FALSE;
	disp->m_Visible = FALSE;
}
