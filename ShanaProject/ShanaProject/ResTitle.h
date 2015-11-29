#pragma once
#if 0 //未使用

#include "ResGame.h"

// 前方参照
class CUtlScreen;
//struct StConfigData;

// バトル時に使用するリソースファイル
class CResBattle : public CResGame{
private:
	int		m_ReceivedAttackPlayer;
	CUtlScreen*		m_Screen;
//	StConfigData*	m_ConfigData;
public:
	void	GetScreenPosition( int * x, int * y);
	int		GetDamage(int base_damage, int hit);
	void	NotifyReceivedAttack(int player);
	void	NotifyHittedAttack(int state );
	int		GetReceivedAttackPlayer();
	void	SetUtilScreen( CUtlScreen* screen );

	// Commonクラス
	CCommonData		*m_CommonTitle;
//	CCommonData		*m_CommonChara;
	CCommonData		*m_CommonChara[2];
	CCommonData		*m_CommonSystem;
	CCommonData		*m_CommonSystemFront;
	CCommonData		*m_CommonScene;
	CCommonData		*m_CommonEffect;
	CCommonData		*m_CommonEffectFront;
	CCommonData		*m_CommonBack;
	CCommonData		*m_CommonUtilScreen;

};
#endif
