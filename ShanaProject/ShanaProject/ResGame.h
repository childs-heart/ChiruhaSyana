#pragma once

// �O���Q��
class CD3DDraw;
class CDispObjGroup;
class CTextureGroupManager;
class CAnimationManager;
class CXFileGroup;
class CCommonData;
class CInput;

class CResGame{
public:
	// �`��N���X
	CD3DDraw		*m_D3DDraw;
	// �`��I�u�W�F�N�g�O���[�v
	CDispObjGroup	*m_DispObjGroup;
	// �e�N�X�`���[�O���[�v
	CTextureGroupManager	*m_TextureManager;
	// �A�j���[�V�����N���X
	CAnimationManager	*m_AnimationManager;
	// ���b�V���t�@�C���O���[�v
	CXFileGroup		*m_MeshTestGroup;
	// Common�N���X
	CCommonData		*m_CommonMode;
	// �_�C���N�g�C���v�b�g�N���X
	CInput			*m_Input;
};
