#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;
class CInput;
class CModeCharaSelect;

#include "CLIB_Sprite.h"

class CCharaSelPuchi: public CSprite{
protected:
	CInput*				m_Input;		// �C���v�b�g�N���X
	CModeCharaSelect*	m_Battle ;

/*	bool		m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	bool		m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int*		m_SelectItemImageNo[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int			m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
*/

//	int			m_SelectItem;

	int			m_Player;
public:
	CCharaSelPuchi( CResBattle *game , CModeCharaSelect *battle_mode, int player );

	int			m_SelectChara;
	void	Setup();
	/************/
	/* �I�[�o�[���C�g�Q
	/************/
	bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	bool Move();							// �ړ������i�W�����v�~�����j
//	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
//	virtual bool Result();							// ���蓮��@�q�b�g�m�F�Ȃ�
//	bool FlameResult();						// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
//	virtual bool Draw();							// �`�揈��

protected:
	virtual ~CCharaSelPuchi();
	
};
