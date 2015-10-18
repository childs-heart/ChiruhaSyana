#pragma once

// �O���Q��
class CResBattle;
class CCharaSelPuchi;
class CInput;
class CModeCharaSelect;

#include "CLIB_Sprite.h"

class CCharaSelCut: public CSprite{
protected:
	CInput*				m_Input;		// �C���v�b�g�N���X
	CModeCharaSelect*	m_Battle ;
	CCharaSelPuchi*		m_Target1 ;
	CCharaSelPuchi*		m_Target2 ;

/*	bool		m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	bool		m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int*		m_SelectItemImageNo[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int			m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;

	int			m_SelectTop;
	int			m_SelectItem;
*/
public:
	CCharaSelCut( CResBattle *game , CModeCharaSelect *battle_mode,
					CCharaSelPuchi* tar1 ,CCharaSelPuchi* tar2 );

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
	virtual ~CCharaSelCut();
	
};
