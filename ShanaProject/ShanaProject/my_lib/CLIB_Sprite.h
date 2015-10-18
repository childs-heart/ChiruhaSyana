#pragma once

// �O���Q��
class CResGame;
class CDispObj;
class CDispObjGroup;
class CTextureGroup;

#include "CLIB_Anime.h"
#include "CLIB_Element.h"

typedef struct{
	int m_BaseX ;
	int m_BaseY ;
}ST_SPRITE_ANIME;

class CSprite : public CElement{
protected:
	CResGame		*m_Game;		// 
	CDispObj		*m_DispObj;		
	CDispObjGroup	*m_DispObjGroup;
	CTextureGroup	*m_Tex;			// �e�N�X�`���[�N���X
	CAnime			m_Anime;		// �A�j���[�V�����N���X
	int				m_Dir;

	int m_X;				// X��
	int m_Y;				// Y��
	int m_State;			// ��ԁi���[�N�ϐ��Ƃ��Ďg�p�B�p�r�͎��R�j
	int	m_Flame;			// �t���[�����i���[�N�p�ϐ��Ƃ��Ďg�p�B�p�r�͎��R�j

	int m_AnimeNo;			// �A�j��NO
	int m_AnimeFlame;		// m_AnimeNo�̃A�j����\�������t���[����
	int m_AnimeImage;		// m_AnimeNo�Ŏg���e�N�X�`���[�ԍ�

public:
	CSprite( CResGame *game );
	virtual ~CSprite();

	/************/
	/* �I�[�o�[���C�g�Q
	/************/
	virtual bool Event();							// ���[�U�[������̓��́i�C�x���g�j��t
	virtual bool Move();							// �ړ������i�W�����v�~�����j
	virtual bool Action();							// ���́i�C�x���g�j���e����̓�����{
	virtual bool ActionFinalize();					// ���́i�C�x���g�j���e����̓�����{
	virtual bool Interfere();							// ���蓮��@�q�b�g�m�F�Ȃ�
	virtual bool InterfereFinalize();					// �ŏI���ʁ@�q�b�g���̏�ԕω��ȂǁA�Ō�̏������s��
	virtual bool Draw( CD3DDraw *draw );			// �`�揈�����C���@��{��������Ă�
	virtual bool Draw();							// �`�揈��
	virtual bool DrawFinalize();					// �`�揈���㏈���@Draw�̌�ɌĂ�
//	virtual Draw( CDispObj *dispobj, CTextureGroup *tex); 
	void GetPosition(int *x, int *y);
	void SetPosition(int x, int y);
	void AddPosition(int x, int y);
	int GetState();									// ��Ԃ�Ԃ�
	int GetFlame();									// �t���[������Ԃ�
	CAnime* GetAnime();

	/******************* ���d�p���錾 *********************************************/
	virtual char GetDir();

protected:
	void ChangeState( int state );
	bool Animation( );

private:
	CSprite();
};

