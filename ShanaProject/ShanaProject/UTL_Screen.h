#pragma once

#include "CLIB_Element.h"

// 前方参照
class CSprite;
class CShanaProt;

class CUtlScreen : public CElement{

public:
	static int DISTANCE ;		// スクロール実行範囲　距離
	static int test1,test2;

	CUtlScreen( CShanaProt* target1, CShanaProt* target2 );
	virtual ~CUtlScreen();

	// 画面系
	void GetBase( int *x , int *y );
	void GetWorld( int *width , int *hight );
	void GetScreen( int *width , int *hight );

	// 
	virtual bool Move();
	virtual bool Draw( CD3DDraw *draw );	// 描画処理はじめ　⇒　オフセットセット
	virtual bool Draw( );					// 描画処理終わり　⇒　オフセットリカバー

	// 画面効果
	void Vibration();
	void SetVibration(int state);

	static int	m_X;
	static int m_Y;
	int m_VibrationFlame;
	int m_VibrationX;
	int m_VibrationY;

private:
	int m_WorldWidth;
	int m_WorldHight;

	int m_ScreenWidth;
	int m_ScreenHight;

	CShanaProt*	m_Target1;
	CShanaProt*	m_Target2;

	CD3DDraw *m_Draw; 
	CUtlScreen( );
};
