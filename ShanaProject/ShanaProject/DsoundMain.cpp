#include <windows.h>
#include <string.h>
#include "LoadWave.h"
#include "DsoundMain.h"

LPDIRECTSOUND8 lpDS = NULL;
LPDIRECTSOUNDBUFFER lpDSP = NULL;

ST_SBNameArr SBArr[SE_MAX];

// �v���g�^�C�v�錾
LPDIRECTSOUNDBUFFER LoadWave(char *name);
void initSBArr();
void initSBFileList();

//-----------------------------------------------------------------------------------------
// DirectSound�̊J��(�I�u�W�F�N�g�̔j��)
//-----------------------------------------------------------------------------------------

bool DSOUND_END()
{
	int iCount;
	for(iCount = 0;iCount <= SE_MAX;iCount++){
		RELEASE_SOUND(SBArr[iCount].SB_lpDSB);
	}
	RELEASE_SOUND(lpDSP);
	RELEASE_SOUND(lpDS);

	return true;
}

//-----------------------------------------------------------------------------------------
// DirectSound�̏�����
//-----------------------------------------------------------------------------------------

bool Dsoundinit( HWND hwnd )
{	

	// SBArr�̏�����
	initSBArr();

	// DirectSound8 �̍쐬
	if (FAILED(DirectSoundCreate8(NULL,&lpDS,NULL)))
	{
		MessageBox(NULL,"DirectSound �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B","DirectSound�G���[",MB_OK | MB_ICONSTOP);
		return false;
	}

	// DirectSound �̋������x����ݒ�
	if (FAILED(lpDS->SetCooperativeLevel(hwnd,DSSCL_PRIORITY)))
	{
		MessageBox(NULL,"DirectSound �̋������x���̐ݒ�Ɏ��s���܂����B","DirectSound�G���[",MB_OK | MB_ICONSTOP);
		// ����
		SendMessage(hwnd,WM_CLOSE,0,0);
		return false;
	}
	// �v���C�}�� �T�E���h�o�b�t�@�쐬
	DSBUFFERDESC desc;
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSP,NULL)))
	{
		MessageBox(NULL,"�v���C�}���T�E���h�o�b�t�@�̍쐬�Ɏ��s���܂����B","DirectSound�G���[",MB_OK | MB_ICONSTOP);
		// ����
		SendMessage(hwnd,WM_CLOSE,0,0);
		return false;
	}
	//�����܂ł͈��s����OK�̏���

	//SE�̐������Z�J���_���o�b�t�@�Ƀf�[�^�ǂݍ���
	//�ǂݍ��݃t�@�C���������X�g����ǂݍ���

	initSBFileList();
	int nCount;

	for(nCount = 0;nCount <= SE_MAX - 1;nCount++){
		// WAVE �t�@�C���̓ǂݍ���
//		MessageBox(NULL,SBArr[nCount].cSeFileName,"",MB_OK);

		SBArr[nCount].SB_lpDSB = LoadWave(SBArr[nCount].cSeFileName); //���ʉ�
		if (SBArr[nCount].SB_lpDSB == NULL)
		{
			MessageBox(NULL,"�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B","DirectSound�G���[",MB_OK | MB_ICONSTOP);
			// ����
			SendMessage(hwnd,WM_CLOSE,0,0);
			return false;
		}
	}

	return true;
}


//-----------------------------------------------------------------------------------------
// �Z�J���_���o�b�t�@�z��̏����� 
//-----------------------------------------------------------------------------------------
void initSBArr(){
	
	int iCount;
	for(iCount = 0;iCount <= SE_MAX;iCount++){
		SBArr[iCount].SB_lpDSB = NULL; //�Z�J���_���o�b�t�@�̏�����
		//���SE�p�̕�����z������\��
	}

}
//-----------------------------------------------------------------------------------------
// �ǂݍ��݃t�@�C�����̏�����
//-----------------------------------------------------------------------------------------
void initSBFileList(){

	int iCount;
	for(iCount = 0;iCount <= SE_MAX;iCount++){
		strcpy(SBArr[iCount].cSeFileName,"");
		strcpy(SBArr[iCount].cSeFileName,cSEFileName[iCount]);
	}
}


// WAVE �t�@�C���̓ǂݍ��� 
LPDIRECTSOUNDBUFFER LoadWave(char *name)
{
	char *buf;
	UINT readsize;
	WAVEFORMATEX wf;
	LPDIRECTSOUNDBUFFER lpDSB = NULL;
	DSBUFFERDESC desc;
	LPVOID pMem1,pMem2;
	DWORD size1,size2;
	// WAVE �t�@�C�����J��

	if (!YWaveOpen(name))
	{
		return NULL;
	}
	// �������̈�̊m��
	buf = (char *)malloc(m_ckIn.cksize);
	// �ǂݍ���
	ZeroMemory(&wf,sizeof(WAVEFORMATEX));
	if (!YWaveRead(m_ckIn.cksize,buf,&readsize,&wf))
	{
		free(buf);
		return NULL;
	}
	// �T�E���h�o�b�t�@�̍쐬
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	desc.dwBufferBytes = readsize;
	desc.lpwfxFormat = &wf;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSB,NULL)))
	{
		free(buf);
		return NULL;
	}
	// �̈�����b�N
	if (FAILED(lpDSB->Lock(0,readsize,&pMem1,&size1,&pMem2,&size2,0)))
	{
		free(buf);
		return 0;
	}
	// ��������
	memcpy(pMem1,buf,size1);
	if (size2)
	{
		memcpy(pMem2,buf + size1,size2);
	}
	// ���b�N����
	lpDSB->Unlock(pMem1,size1,pMem2,size2);
	free(buf);
	// ����
	YWaveClose();
	return lpDSB;
}
