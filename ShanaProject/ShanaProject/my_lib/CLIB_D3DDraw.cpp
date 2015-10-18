#include "CLIB_D3DDraw.h"
#include "CLIB_DispObj.h"

//
//  関数: SetDevice( LPDIRECT3DDEVICE9 d3ddevice )
//
//  目的: D3Dデバイス登録
//
//  パラメータ:
//		para1：D3Dデバイス
//　メモ：
//　　　
bool CD3DDraw::SetDevice( LPDIRECT3DDEVICE9 d3ddevice)
{
	m_D3DDevice = d3ddevice;
	return TRUE;
}

//
//  関数: GetDevice( )
//
//  目的: D3Dデバイスゲト
//
//  パラメータ:
//　メモ：
//　　　
LPDIRECT3DDEVICE9 CD3DDraw::GetDevice()
{
	return m_D3DDevice;
}

//
//  関数: SetTransrate( )
//
//  目的: 座標変換　射影変換
//　　　
bool CD3DDraw::SetTransrate()
{
	if( m_D3DDevice == NULL ){
		return FALSE;
	}

	//カメラ
	D3DXMATRIX mView,mProj;
	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
//		&D3DXVECTOR3(0.5f,-0.5f,-824.243225f),		// Z座標カメラ画角４０度の場合
		&D3DXVECTOR3(0.5f,-0.5f,-1119.615242f),		// Z座標カメラ画角３０度の場合 メイン
//		&D3DXVECTOR3(0.5f,200.5f,-1900.615242f),		// あそび
		&D3DXVECTOR3(0.5f,-0.5f,0),					// メイン
//		&D3DXVECTOR3(0.5f,200.5f,0),					// 遊び
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)
	);

	// 投影行列の設定
//	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(40), 4.0f/3.0f, 90.0f, 1700.0f);	// ４０度
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(30), 4.0f/3.0f, 90.0f, 2000.0f);	// ３０度メイン
//	D3DXMatrixPerspectiveOffCenterLH(&mProj, -400.0f,400.0f,-300.0f,300.0f,400.0f,1600.0f);
	//行列設定
	m_D3DDevice->SetTransform(D3DTS_VIEW, &mView);
	m_D3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);

	return TRUE;
}

//
//  関数: SetCenter( WORD x, WORD y )
//
//  目的: 画面の中央座標をセットする
//
//  パラメータ:
//		para1：中心座標 X
//		para2：中心座標 Y
//
void CD3DDraw::SetCenter( int x, int y )
{
	m_CenterX = x;
	m_CenterY = y;
}

//
//  関数: Draw( CDispObj* disp )
//
//  目的: 描画実行
//
//  パラメータ:
//		para1：表示オブジェクトクラス
//　　　
bool CD3DDraw::Draw( CDispObj* disp )
{
	//--------------------------------------	
	// 頂点座標セット
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

	// テクスチャ座標セット
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

	// デバイスパラメーターセット
	// Z バッファ有効化->前後関係の計算を正確にしてくれる
	// 両面描画モードの指定
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
	// 座標変換（カメラと投影）
	//--------------------------------------
	SetTransrate( );

	//--------------------------------------	
	// 座標変換（ワールド）
	//--------------------------------------
	D3DXMATRIX mWorld,mTrans,mScale,mRol;
	// 回転
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
	// スケーリング（拡縮）
//	D3DXMatrixTranslation(&mTrans,0,0,0);
	D3DXMatrixScaling( &mScale, disp->m_Scale,disp->m_Scale, disp->m_Scale );
	D3DXMatrixMultiply( &mWorld, &mWorld, &mScale);
	// 移動
	D3DXMatrixTranslation(&mTrans, -m_CenterX + disp->m_DestRect.left + objCenterX ,
									m_CenterY - disp->m_DestRect.top - objCenterY ,
									disp->m_DestZ );
	D3DXMatrixMultiply( &mWorld, &mWorld, &mTrans);
	// 座標セット
	m_D3DDevice->SetTransform(D3DTS_WORLD, &mWorld);

	//--------------------------------------	
	// テクスチャーセット
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
	// ミップマップフィルタ設定( NONE : ドット絵には最適 )
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_NONE);
	m_D3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_NONE);
//	m_D3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP );

	//--------------------------------------	
	// モデルの描画
	//--------------------------------------
	// XFileが割り当てられていたら、そちらを優先
	if( disp->m_XFile != NULL ){
		//--------------------------------------	
		// モデルの描画
		//--------------------------------------
		D3DMATERIAL9	material;
		// マテリアル情報を取り出す
		D3DXMATERIAL*	mD3DXMaterials = (D3DXMATERIAL*)disp->m_XFile->m_MaterialBuffer->GetBufferPointer() ;
		for( DWORD i = 0; i < disp->m_XFile->m_NumMaterials; i++){
			// マテリアルのコピー
			material = mD3DXMaterials[i].MatD3D;
			// マテリアルのセット
//			m_D3DDevice->SetMaterial( &material );
			// 分割されたメッシュの描画
			disp->m_XFile->m_Mesh->DrawSubset( i );
		}
	}
	// 矩形描画
	else{
		m_D3DDevice->SetFVF( FVF_TLVERTEX_3D );
		m_D3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &vb, sizeof(TLVERTEX_3D) );
	}

//	if( disp->m_Texture[0] ){
//		disp->m_Texture[0]->ReleaseTexture();
//	}

	return TRUE;
}
