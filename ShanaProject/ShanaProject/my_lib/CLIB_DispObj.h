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

// リーフブレンドテンプレート
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
// 表示オブジェクトクラス
//==============================================================
class CDispObj{
friend class CD3DDraw;
friend class CD3DDraw2;
friend class CD3DDraw3;
friend class CDispObjGroup;
private:

	bool		m_Enable;			// 有効フラグ　⇒　CDispObjGroupで使用する

	DWORD		m_Type;				// 種別　enum DISP_TYPE
	DWORD		m_Priority;			// 表示優先度	0:なし	1:高～32767:低

	RECT		m_SrcRect;			// 転送元座標（テスクチャー座標）
	RECT		m_DestRect;			// 転送先座標（スクリーン座標）
	long		m_DestZ;			// 転送先座標Ｚ軸（XFile使用時に活用）
	DWORD		m_Color;			// ディフェーズ色（物体の色）

	int			m_SrcBlend;			// 転送元のブレンド
	int			m_DestBlend;		// 転送先のブレンド

	WORD		m_RotOrderX[2];		// X回転の優先度 0:なし　1:高～3:低
	WORD		m_RotOrderY[2];		// Y回転の優先度 0:なし　1:高～3:低
	WORD		m_RotOrderZ[2];		// Z回転の優先度 0:なし　1:高～3:低
	float		m_RotationX[2];		// X回転度
	float		m_RotationY[2];		// Y回転度
	float		m_RotationZ[2];		// Z回転度

	float		m_Scale;			// 拡大率（XFile使用時のみ有効）

	CTexture*	m_Texture[4];		// テクスチャークラス
	CXFile*		m_XFile;			// XFileクラス
	
	// チェイン時の子クラスを解放
	void	FreeChain();

public:
	bool		m_Visible;			// 表示フラグ　⇒　CD3DDrawクラスで使用する

	CDispObj*	m_Parent;			// チェイン時の親クラス
	CDispObj*	m_Child;			// チェイン時の子クラス

	// コンストラクタ＆デストラクタ
	CDispObj();
	CDispObj( DWORD type );
	virtual ~CDispObj();

	// 初期化
	void	Init( DWORD type );
	// 種別変更
	void	ChangeType( DWORD type );

	// テスクチャークラス・XFileクラスセット
	void	SetTexture( CTexture *tex , char layer = 0 );
	void	SetXFile( CXFile *mesh );

	// ディフェーズ色、ブレンド描画設定
	void	SetBlendColor( DWORD col );
	void	SetSrcBlend( int blend );
	void	SetDestBlend( int blend );

	// 転送元指定
	void	SetSrcRectFromTex( int texNo );
	void	SetSrcRect( RECT *rect );
	void	SetSrcRect( long left, long top, long right, long bottom );
	// 転送先指定
	void	SetDestRect( RECT *rect );
	void	SetDestRect( long left, long top, long right, long bottom );
	void	SetDestRect( long left, long top, long right, long bottom, long z );
	// 拡大率指定
	void	SetScale( float scale );

	// 回転指定
	// 回転の優先度指定
	void	SetRotOrder( char orderX, char orderY, char orderZ );
	// 回転角度指定
	void	SetRotation( float rotX, float rotY, float rotZ );
	// 上２つの関数を合わせたもの
	void	SetRotation( char orderX, float rotX, char orderY, float rotY, char orderZ, float rotZ ); 

	// 多重回転用
	void	SetRotation( char orderX1, float rotX1, char orderY1, float rotY1, char orderZ1, float rot1Z
						, char orderX2, float rotX2, char orderY2, float rotY2, char orderZ2, float rotZ2 ); 

	// Zバッファ指定　Offすると強制的に描画される
	void	ZBufferOn();
	void	ZBufferOff();

	// 表示フラグセット
	void	VisibleOn();
	void	VisibleOff();
};


//==============================================================
// 表示オブジェクトリストクラス
//==============================================================
class	CDispObjGroup{
private:
	int					m_Num;			
	unsigned short		m_WPoint;		
	unsigned short		m_RPoint;		
	unsigned short		m_FreeList;		

public:
	CDispObj*			m_CDisp;		

	// コンストラクタ＆デストラクタ
	CDispObjGroup( int num );		// num:図形クラスの数
	virtual ~CDispObjGroup( ) ;
	
	// 表示オブジェクトクラス割り当て
	CDispObj*	GetDispObj( DWORD type = 0 );
	// 表示オブジェクトクラスの割り当て解放
	void FreeDispObj( CDispObj* disp );

};
