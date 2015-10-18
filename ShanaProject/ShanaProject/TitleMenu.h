#pragma once

// �O���Q��
class CResBattle;
class CShanaProt;
class CInput;
class CModeTitle;

#include "CLIB_Sprite.h"

class CDataTitleMenu{
public:
	enum{
		TITLE_TOP_ARCADE = 0,
		TITLE_TOP_VERSUS,
		TITLE_TOP_TRAINNING,
		TITLE_TOP_OPTION,
		TITLE_TOP_EXIT,
		TITLE_TOP_MAX_VALUE
	};
public:
	CDataTitleMenu();
	void	SetValue( int top, int value );
	int		GetValue( int top );
};

class CTitleMenu: public CSprite{
protected:
	CInput*			m_Input;		// �C���v�b�g�N���X
	CModeTitle*		m_Battle ;
	CShanaProt*		m_Target ;
	CDataTitleMenu* m_Data ;

	bool		m_SelectItemEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	bool		m_SelectButtonEnable[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int*		m_SelectItemImageNo[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;
	int			m_SelectItemMaxValue[CDataTitleMenu::TITLE_TOP_MAX_VALUE] ;

	int			m_SelectTop;
	int			m_SelectItem;

public:
	CTitleMenu( CResBattle *game , CModeTitle *battle_mode );

	void	Setup();
	void	OnButtom( int item );
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
	virtual ~CTitleMenu();
	
};
