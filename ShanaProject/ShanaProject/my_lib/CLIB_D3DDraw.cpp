#include "CLIB_D3DDraw.h"
#include "CLIB_DispObj.h"

//
//  �֐�: SetDevice( LPDIRECT3DDEVICE9 d3ddevice )
//
//  �ړI: D3D�f�o�C�X�o�^
//
//  �p�����[�^:
//		para1�FD3D�f�o�C�X
//�@�����F
//�@�@�@
bool CD3DDraw::SetDevice( LPDIRECT3DDEVICE9 d3ddevice)
{
	m_D3DDevice = d3ddevice;
	return TRUE;
}

//
//  �֐�: GetDevice( )
//
//  �ړI: D3D�f�o�C�X�Q�g
//
//  �p�����[�^:
//�@�����F
//�@�@�@
LPDIRECT3DDEVICE9 CD3DDraw::GetDevice()
{
	return m_D3DDevice;
}

//
//  �֐�: SetTransrate( )
//
//  �ړI: ���W�ϊ��@�ˉe�ϊ�
//�@�@�@
bool CD3DDraw::SetTransrate()
{
	if( m_D3DDevice == NULL ){
		return FALSE;
	}

	//�J����
	D3DXMATRIX mView,mProj;
	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
//		&D3DXVECTOR3(0.5f,-0.5f,-824.243225f),		// Z���W�J������p�S�O�x�̏ꍇ
		&D3DXVECTOR3(0.5f,-0.5f,-1119.615242f),		// Z���W�J������p�R�O�x�̏ꍇ ���C��
//		&D3DXVECTOR3(0.5f,200.5f,-1900.615242f),		// ������
		&D3DXVECTOR3(0.5f,-0.5f,0),					// ���C��
//		&D3DXVECTOR3(0.5f,200.5f,0),					// �V��
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)
	);

	// ���e�s��̐ݒ�
//	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(40), 4.0f/3.0f, 90.0f, 1700.0f);	// �S�O�x
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(30), 4.0f/3.0f, 90.0f, 2000.0f);	// �R�O�x���C��
//	D3DXMatrixPerspectiveOffCenterLH(&mProj, -400.0f,400.0f,-300.0f,300.0f,400.0f,1600.0f);
	//�s��ݒ�
	m_D3DDevice->SetTransform(D3DTS_VIEW, &mView);
	m_D3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	return TRUE;
}

//
//  �֐�: SetCenter( WORD x, WORD y )
//
//  �ړI: ��ʂ̒������W���Z�b�g����
//
//  �p�����[�^:
//		para1�F���S���W X
//		para2�F���S���W Y
//
void CD3DDraw::SetCenter( int x, int y )
{
	m_CenterX = x;
	m_CenterY = y;
}

//
//  �֐�: Draw( CDispObj* disp )
//
//  �ړI: �`����s
//
//  �p�����[�^:
//		para1�F�\���I�u�W�F�N�g�N���X
//�@�@�@
bool CD3DDraw::Draw( CDispObj* disp )
{
	//--------------------------------------	
	// ���_���W�Z�b�g
	//--------------------------------------
	TLVERTEX_3D	vb[4];
	float	top;
	float	bottom;
	float	left;
	float	right;
	float	topTx;
	float	bottomTx;
	float	leftTx;
	float	rightTx;
	long	objCenterX;
	long	objCenterY;
	long	tmpX;
	long	tmpY;

	D3DXIMAGE_INFO	imageInfo;

	objCenterX	= disp->m_DestRect.right - disp->m_DestRect.left;
	tmpX		= ( objCenterX & 0x01 ? 1 : 0 );
	objCenterX	= objCenterX >> 1;
	objCenterY	= disp->m_DestRect.bottom - disp->m_DestRect.top;
	tmpY		= ( objCenterY & 0x01 ? 1 : 0 );
	objCenterY	= objCenterY >> 1;

	left		= (float)-objCenterX;
	right		= (float)objCenterX + tmpX; 
	top			= (float)objCenterY;
	bottom		= (float)-objCenterY - tmpY;

	// �e�N�X�`�����W�Z�b�g
	if( NULL != disp->m_Texture[0]){
		disp->m_Texture[0]->GetTextureInfo( &imageInfo );
		leftTx		= (float)disp->m_SrcRect.left / imageInfo.Width ;
		rightTx		= (float)disp->m_SrcRect.right / imageInfo.Width ;
		topTx		= (float)disp->m_SrcRect.top / imageInfo.Height ;
		bottomTx	= (float)disp->m_SrcRect.bottom / imageInfo.Height ;
	}
	else{
		leftTx		= 0.0f;
		rightTx		= 1.0f;
		topTx		= 0.0f;
		bottomTx	= 1.0f;
	}

	vb[0].x = left;					vb[0].y = top;
	vb[1].x = right;				vb[1].y = top;
	vb[2].x = left;					vb[2].y = bottom;
	vb[3].x = right;				vb[3].y = bottom;
	vb[0].z = 0.0f;					vb[1].z = 0.0f ;
	vb[2].z = 0.0f;					vb[3].z = 0.0f ;
//	vb[0].z = (float)disp->m_DestZ;	vb[1].z = (float)disp->m_DestZ ;
//	vb[2].z = (float)disp->m_DestZ;	vb[3].z = (float)disp->m_DestZ ;
	vb[0].color = disp->m_Color ;	vb[1].color = disp->m_Color ;
	vb[2].color = disp->m_Color ;	vb[3].color = disp->m_Color ;
	vb[0].tu = leftTx;				vb[0].tv = topTx;
	vb[1].tu = rightTx;				vb[1].tv = topTx;
	vb[2].tu = leftTx;				vb[2].tv = bottomTx;
	vb[3].tu = rightTx;				vb[3].tv = bottomTx;

	// �f�o�C�X�p�����[�^�[�Z�b�g
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����
	// ���ʕ`�惂�[�h�̎w��
    m_D3DDevice->SetRenderState( D3DRS_CULLMODE	, D3DCULL_NONE );
//	m_D3DDevice->SetRenderState( D3DRS_ZENABLE	, D3DZB_TRUE );
	m_D3DDevice->SetRenderState( D3DRS_ZENABLE	, D3DZB_FALSE );
	m_D3DDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	m_D3DDevice->SetRenderState( D3DRS_LIGHTING	, FALSE );
	m_D3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_D3DDevice->SetRenderState( D3DRS_SRCBLEND	, disp->m_SrcBlend );
	m_D3DDevice->SetRenderState( D3DRS_DESTBLEND, disp->m_DestBlend );
//	m_D3DDevice->SetRenderState( D3DRS_WRAP0, D3DWRAPCOORD_0);


	//--------------------------------------	
	// ���W�ϊ��i�J�����Ɠ��e�j
	//--------------------------------------
	SetTransrate( );

	//--------------------------------------	
	// ���W�ϊ��i���[���h�j
	//--------------------------------------
	D3DXMATRIX mWorld,mTrans,mScale,mRol;
	// ��]
	D3DXMatrixIdentity( &mWorld );
	for( int i = 1 ; i < 4 ; i++ ){
		if( disp->m_RotOrderX[0] == i ){
			D3DXMatrixRotationX(&mRol , D3DXToRadian(disp->m_RotationX[0]) );
			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol);
		}
		else if( disp->m_RotOrderY[0] == i ){
			D3DXMatrixRotationY(&mRol , D3DXToRadian(disp->m_RotationY[0]) );
			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol);
		}
		else if( disp->m_RotOrderZ[0] == i ){
			D3DXMatrixRotationZ(&mRol , D3DXToRadian(disp->m_RotationZ[0]) );
			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol );
		}
	}
	// �X�P�[�����O�i�g�k�j
//	D3DXMatrixTranslation(&mTrans,0,0,0);
	D3DXMatrixScaling( &mScale, disp->m_Scale,disp->m_Scale, disp->m_Scale );
	D3DXMatrixMultiply( &mWorld, &mWorld, &mScale);
	// �ړ�
	D3DXMatrixTranslation(&mTrans, -m_CenterX + disp->m_DestRect.left + objCenterX ,
									m_CenterY - disp->m_DestRect.top - objCenterY ,
									disp->m_DestZ );
	D3DXMatrixMultiply( &mWorld, &mWorld, &mTrans);
	// ���W�Z�b�g
	m_D3DDevice->SetTransform(D3DTS_WORLD, &mWorld);

	//--------------------------------------	
	// �e�N�X�`���[�Z�b�g
	//--------------------------------------
	if( disp->m_Texture[0] ){
		m_D3DDevice->SetTexture( 0, disp->m_Texture[0]->pD3DTex );
//		m_D3DDevice->SetTexture( 0, disp->m_Texture[0]->TakeTexture() );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE);
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	}
	// �~�b�v�}�b�v�t�B���^�ݒ�( NONE : �h�b�g�G�ɂ͍œK )
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_NONE);
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_NONE);
//	m_D3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP );

	//--------------------------------------	
	// ���f���̕`��
	//--------------------------------------
	// XFile�����蓖�Ă��Ă�����A�������D��
	if( disp->m_XFile != NULL ){
		//--------------------------------------	
		// ���f���̕`��
		//--------------------------------------
		D3DMATERIAL9	material;
		// �}�e���A���������o��
		D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)disp->m_XFile->m_MaterialBuffer->GetBufferPointer() ;
		for( DWORD i = 0; i < disp->m_XFile->m_NumMaterials; i++){
			// �}�e���A���̃R�s�[
			material = mD3DXMaterials[i].MatD3D;
			// �}�e���A���̃Z�b�g
//			m_D3DDevice->SetMaterial( &material );
			// �������ꂽ���b�V���̕`��
			disp->m_XFile->m_Mesh->DrawSubset( i );
		}
	}
	// ��`�`��
	else{
		m_D3DDevice->SetFVF( FVF_TLVERTEX_3D );
		m_D3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vb, sizeof(TLVERTEX_3D) );
	}

//	if( disp->m_Texture[0] ){
//		disp->m_Texture[0]->ReleaseTexture();
//	}

	return TRUE;
}
