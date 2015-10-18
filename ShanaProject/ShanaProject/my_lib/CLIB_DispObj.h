#pragma once

//#include <d3dx9tex.h>
#include <d3d9.h>
#include "CLIB_Texture.h"
#include "CLIB_Mesh.h"

enum DISP_TYPE{		
	DISP_TYPE_SPRITE	= 0x00000000,
	DISP_TYPE_XFILE		= 0x00000001,
	DISP_MASK_TYPE		= 0x000000FF
};

// ���[�t�u�����h�e���v���[�g
enum DISP_LEAF_BLEND{
	BLEND_NONE = 0,
	BLEND_ALPHA,
	BLEND_PIX_FADE,
	BLEND_ALPHA2,
	BLEND_ADD,
	BLEND_SCREEN,
	BLEND_HARDLIGHT,
	BLEND_MUL,
	BLEND_SUB,
	BLEND_REVMUL,
	BLEND_REVSUB,
	BLEND_EXCLUDE
};

typedef struct{
	int		srcBlend;
	int		destBlend;
}LEAF_BLEND;

//==============================================================
// �\���I�u�W�F�N�g�N���X
//==============================================================
class CDispObj{
friend class CD3DDraw;
friend class CD3DDraw2;
friend class CD3DDraw3;
friend class CDispObjGroup;
private:

	bool		m_Enable;			// �L���t���O�@�ˁ@CDispObjGroup�Ŏg�p����

	DWORD		m_Type;				// ��ʁ@enum DISP_TYPE
	DWORD		m_Priority;			// �\���D��x	0:�Ȃ�	1:���`32767:��

	RECT		m_SrcRect;			// �]�������W�i�e�X�N�`���[���W�j
	RECT		m_DestRect;			// �]������W�i�X�N���[�����W�j
	long		m_DestZ;			// �]������W�y���iXFile�g�p���Ɋ��p�j
	DWORD		m_Color;			// �f�B�t�F�[�Y�F�i���̂̐F�j

	int			m_SrcBlend;			// �]�����̃u�����h
	int			m_DestBlend;		// �]����̃u�����h

	WORD		m_RotOrderX[2];		// X��]�̗D��x 0:�Ȃ��@1:���`3:��
	WORD		m_RotOrderY[2];		// Y��]�̗D��x 0:�Ȃ��@1:���`3:��
	WORD		m_RotOrderZ[2];		// Z��]�̗D��x 0:�Ȃ��@1:���`3:��
	float		m_RotationX[2];		// X��]�x
	float		m_RotationY[2];		// Y��]�x
	float		m_RotationZ[2];		// Z��]�x

	float		m_Scale;			// �g�嗦�iXFile�g�p���̂ݗL���j

	CTexture*	m_Texture[4];		// �e�N�X�`���[�N���X
	CXFile*		m_XFile;			// XFile�N���X
	
	// �`�F�C�����̎q�N���X�����
	void	FreeChain();

public:
	bool		m_Visible;			// �\���t���O�@�ˁ@CD3DDraw�N���X�Ŏg�p����

	CDispObj*	m_Parent;			// �`�F�C�����̐e�N���X
	CDispObj*	m_Child;			// �`�F�C�����̎q�N���X

	// �R���X�g���N�^���f�X�g���N�^
	CDispObj();
	CDispObj( DWORD type );
	virtual ~CDispObj();

	// ������
	void	Init( DWORD type );
	// ��ʕύX
	void	ChangeType( DWORD type );

	// �e�X�N�`���[�N���X�EXFile�N���X�Z�b�g
	void	SetTexture( CTexture *tex , char layer = 0 );
	void	SetXFile( CXFile *mesh );

	// �f�B�t�F�[�Y�F�A�u�����h�`��ݒ�
	void	SetBlendColor( DWORD col );
	void	SetSrcBlend( int blend );
	void	SetDestBlend( int blend );

	// �]�����w��
	void	SetSrcRectFromTex( int texNo );
	void	SetSrcRect( RECT *rect );
	void	SetSrcRect( long left, long top, long right, long bottom );
	// �]����w��
	void	SetDestRect( RECT *rect );
	void	SetDestRect( long left, long top, long right, long bottom );
	void	SetDestRect( long left, long top, long right, long bottom, long z );
	// �g�嗦�w��
	void	SetScale( float scale );

	// ��]�w��
	// ��]�̗D��x�w��
	void	SetRotOrder( char orderX, char orderY, char orderZ );
	// ��]�p�x�w��
	void	SetRotation( float rotX, float rotY, float rotZ );
	// ��Q�̊֐������킹������
	void	SetRotation( char orderX, float rotX, char orderY, float rotY, char orderZ, float rotZ ); 

	// ���d��]�p
	void	SetRotation( char orderX1, float rotX1, char orderY1, float rotY1, char orderZ1, float rot1Z
						, char orderX2, float rotX2, char orderY2, float rotY2, char orderZ2, float rotZ2 ); 

	// Z�o�b�t�@�w��@Off����Ƌ����I�ɕ`�悳���
	void	ZBufferOn();
	void	ZBufferOff();

	// �\���t���O�Z�b�g
	void	VisibleOn();
	void	VisibleOff();
};


//==============================================================
// �\���I�u�W�F�N�g���X�g�N���X
//==============================================================
class	CDispObjGroup{
private:
	int					m_Num;			
	unsigned short		m_WPoint;		
	unsigned short		m_RPoint;		
	unsigned short		m_FreeList;		

public:
	CDispObj*			m_CDisp;		

	// �R���X�g���N�^���f�X�g���N�^
	CDispObjGroup( int num );		// num:�}�`�N���X�̐�
	virtual ~CDispObjGroup( ) ;
	
	// �\���I�u�W�F�N�g�N���X���蓖��
	CDispObj*	GetDispObj( DWORD type = 0 );
	// �\���I�u�W�F�N�g�N���X�̊��蓖�ĉ��
	void FreeDispObj( CDispObj* disp );

};
