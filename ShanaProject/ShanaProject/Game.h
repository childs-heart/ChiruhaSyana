#pragma once

#include "CLIB_Util.h"
#include "CLIB_Element.h"
#include "CLIB_DispObj.h"
#include "CLIB_Texture.h"
#include "CLIB_D3DDraw3.h"
#include "CLIB_Input.h"
#include "CLIB_Anime.h"
//#include "CLIB_Movie.h"

#define	MAX_NUM_DISPOBJ		11000
#define	MAX_NUM_TEX_TITLE	10
#define	MAX_NUM_TEX_CHARA	100
#define	MAX_NUM_TEX_SYSTEM	100

class CModeTitle;
class CModeCharaSelect;

class CGame{
private:
	int	m_Mode;
	int m_NextMode;
	CModeTitle *m_ModeTitle;
	CModeCharaSelect *m_ModeCharaSel;

	void initialize();

public:
	CGame();
	~CGame();

	void GameMain();
	void SetMode( int mode );

	// �`��N���X
	CD3DDraw3		m_D3DDraw;
	// �`��I�u�W�F�N�g�O���[�v
	CDispObjGroup	*m_DispObjGroup;
	// �e�N�X�`���[�O���[�v
	CTextureGroupManager	*m_TextureManager;
	// ���b�V���t�@�C���O���[�v
	CXFileGroup		*m_MeshTestGroup;
	// Common�N���X
	CCommonData		*m_CommonMode;
	// �A�j���[�V�����N���X
	CAnimationManager	*m_AnimationManager;
	// �_�C���N�g�C���v�b�g�N���X
	CInput			*m_Input;

};

//extern CGame *Game;
