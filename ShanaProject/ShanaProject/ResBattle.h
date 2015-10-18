#pragma once

#include "ResGame.h"

// �O���Q��
class CUtlScreen;
class CShanaProt;
//struct StConfigData;

// �o�g�����Ɏg�p���郊�\�[�X�t�@�C��
class CResBattle : public CResGame{
private:
	int		m_ReceivedAttackPlayer;
	CUtlScreen*		m_Screen;
//	StConfigData*	m_ConfigData;
	static CResBattle *m_ResBattle;

public:
	CResBattle();

	void	GetScreenPosition( int * x, int * y);
	int		GetDamage(int base_damage, int hit);
	void	NotifyReceivedAttack(int player);
	void	NotifyHittedAttack(int state );
	int		GetReceivedAttackPlayer();
	void	SetUtilScreen( CUtlScreen* screen );

	static CResBattle*	GetResBattle();

	// Common�N���X
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

	CShanaProt*		m_Player[4];
};
