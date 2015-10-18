#include "CLIB_D3DDraw3.h"
#include "CLIB_DispObj.h"

//
//  �֐�: Draw2( CDispObj* disp )
//
//  �ړI: �`����s
//
//  �p�����[�^:
//		para1�F�\���I�u�W�F�N�g�N���X
//�@�@�@
bool CD3DDraw3::Draw3( CDispObj* disp, float x, float y, float z )
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
	D3DLIGHT9	light;

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

	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type	= D3DLIGHT_POINT;
	light.Diffuse.a = light.Diffuse.r = light.Diffuse.b = light.Diffuse.g = 0.7f;
//	light.Diffuse.r = 164.0f/255;
//	light.Diffuse.g = 180.0f/255;
//	light.Diffuse.b = 230.0f/255;

	light.Specular.a = light.Specular.r = light.Specular.b = light.Specular.g = 1.0f;
	light.Ambient.a = light.Ambient.r = light.Ambient.b = light.Ambient.g = 1.0f;
	light.Position.x = x;
	light.Position.y = -y;
	light.Position.z = z;
	light.Range = 400.0f;//FLT_MAX * 1;
	light.Attenuation0 = 1.0f;
	
/*	light.Type	= D3DLIGHT_DIRECTIONAL;
	light.Diffuse.a = light.Diffuse.r = light.Diffuse.b = light.Diffuse.g = 1.0f;
	D3DXVECTOR3 vecdir;
	vecdir = D3DXVECTOR3( -5.0f,-5.0f,-10.0f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecdir);
//	light.Specular.a = light.Specular.r = light.Specular.b = light.Specular.g = 0.5f;
//	light.Ambient.a = light.Ambient.r = light.Ambient.b = light.Ambient.g = 0.5f;
//	light.Position.x = light.Position.y = 0.5f;
//	light.Position.z = 0.0f;
//	light.Range = FLT_MAX * 10000;
//	light.Attenuation0 = 0.01f;
*/
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
	m_D3DDevice->SetRenderState( D3DRS_ZENABLE	, D3DZB_TRUE );
	m_D3DDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE );
	if( disp->m_XFile == NULL ){
//		m_D3DDevice->SetRenderState( D3DRS_ZENABLE	, D3DZB_FALSE );
	m_D3DDevice->SetRenderState( D3DRS_ZENABLE	, D3DZB_TRUE );
		m_D3DDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	}
	m_D3DDevice->SetRenderState( D3DRS_LIGHTING	, FALSE );
	if( disp->m_XFile != NULL ){
		m_D3DDevice->SetRenderState( D3DRS_LIGHTING	, TRUE );
	}
	m_D3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_D3DDevice->SetRenderState( D3DRS_SRCBLEND	, disp->m_SrcBlend );
	m_D3DDevice->SetRenderState( D3DRS_DESTBLEND, disp->m_DestBlend );
	m_D3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_D3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// �ǉ�����
//	m_D3DDevice->SetRenderState( D3DRS_ALPHAREF, param1 );				// �ǉ�����
//	m_D3DDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_LESSEQUAL );	// �ǉ�����
//	m_D3DDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );// �ǉ�����

	//--------------------------------------	
	// ���W�ϊ��i�J�����Ɠ��e�j
	//--------------------------------------
	SetTransrate( );

	//--------------------------------------	
	// ���W�ϊ��i���[���h�j
	//--------------------------------------
	D3DXMATRIX mWorld,mTrans,mScale,mRol,mTmp;
	// ��]
	D3DXMatrixIdentity( &mWorld );
	for( int i = 1 ; i < 4 ; i++ ){
		D3DXMatrixIdentity( &mTmp );
		if( disp->m_RotOrderX[0] == i ){
			D3DXMatrixRotationX(&mRol , D3DXToRadian(disp->m_RotationX[0]) );
//			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol);
			D3DXMatrixMultiply(&mTmp, &mTmp,&mRol);
		}
		if( disp->m_RotOrderY[0] == i ){
			D3DXMatrixRotationY(&mRol , D3DXToRadian(disp->m_RotationY[0]) );
//			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol);
			D3DXMatrixMultiply(&mTmp, &mTmp,&mRol);
		}
		if( disp->m_RotOrderZ[0] == i ){
			D3DXMatrixRotationZ(&mRol , D3DXToRadian(disp->m_RotationZ[0]) );
//			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol );
			D3DXMatrixMultiply(&mTmp, &mTmp,&mRol);
		}
		D3DXMatrixMultiply(&mWorld, &mWorld,&mTmp );
	}
	// ���d��]
	for( int i = 4 ; i < 7 ; i++ ){
		D3DXMatrixIdentity( &mTmp );
		if( disp->m_RotOrderX[1] == i ){
			D3DXMatrixRotationX(&mRol , D3DXToRadian(disp->m_RotationX[1]) );
//			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol);
			D3DXMatrixMultiply(&mTmp, &mTmp,&mRol);
		}
		if( disp->m_RotOrderY[1] == i ){
			D3DXMatrixRotationY(&mRol , D3DXToRadian(disp->m_RotationY[1]) );
//			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol);
			D3DXMatrixMultiply(&mTmp, &mTmp,&mRol);
		}
		if( disp->m_RotOrderZ[1] == i ){
			D3DXMatrixRotationZ(&mRol , D3DXToRadian(disp->m_RotationZ[1]) );
//			D3DXMatrixMultiply(&mWorld, &mWorld,&mRol );
			D3DXMatrixMultiply(&mTmp, &mTmp,&mRol);
		}
		D3DXMatrixMultiply(&mWorld, &mWorld,&mTmp );
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
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	D3DTOP_MODULATE);
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		m_D3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	}
	// �~�b�v�}�b�v�t�B���^�ݒ�( NONE : �h�b�g�G�ɂ͍œK )
//	m_D3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);
//	m_D3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_NONE);
//	m_D3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_NONE);
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	//--------------------------------------
	// ���C�e�B���O
	//--------------------------------------
	m_D3DDevice->SetLight(0, &light);
	m_D3DDevice->LightEnable(0, true); 

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
			material.Diffuse.a = 1.0f;
//			material.Diffuse.r = 115.0f/255;
//			material.Diffuse.g = 115.0f/255;
//			material.Diffuse.b = 60.0f/255;
			material.Diffuse.r = 80.0f/255;
			material.Diffuse.g = 80.0f/255;
			material.Diffuse.b = 115.0f/255;
			material.Ambient.a = 1.0f;
			material.Ambient.r = 10.0f/255;
			material.Ambient.g = 10.0f/255;
			material.Ambient.b = 25.0f/255;
			material.Specular.a = 1.0f;
			material.Specular.r = 1.0f;
			material.Specular.g = 1.0f;
			material.Specular.b = 1.0f;
			// �}�e���A���̃Z�b�g
			m_D3DDevice->SetMaterial( &material );
			// �������ꂽ���b�V���̕`��
			disp->m_XFile->m_Mesh->DrawSubset( i );
		}
	}
	// ��`�`��
	else{
		m_D3DDevice->SetFVF( FVF_TLVERTEX_3D );
		m_D3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vb, sizeof(TLVERTEX_3D) );
	}

	m_D3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE);
	return TRUE;
}
