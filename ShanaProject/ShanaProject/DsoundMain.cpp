#include <windows.h>
#include <string.h>
#include "LoadWave.h"
#include "DsoundMain.h"

LPDIRECTSOUND8 lpDS = NULL;
LPDIRECTSOUNDBUFFER lpDSP = NULL;

ST_SBNameArr SBArr[SE_MAX];

// プロトタイプ宣言
LPDIRECTSOUNDBUFFER LoadWave(char *name);
void initSBArr();
void initSBFileList();

//-----------------------------------------------------------------------------------------
// DirectSoundの開放(オブジェクトの破棄)
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
// DirectSoundの初期化
//-----------------------------------------------------------------------------------------

bool Dsoundinit( HWND hwnd )
{	

	// SBArrの初期化
	initSBArr();

	// DirectSound8 の作成
	if (FAILED(DirectSoundCreate8(NULL,&lpDS,NULL)))
	{
		MessageBox(NULL,"DirectSound オブジェクトの作成に失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
		return false;
	}

	// DirectSound の協調レベルを設定
	if (FAILED(lpDS->SetCooperativeLevel(hwnd,DSSCL_PRIORITY)))
	{
		MessageBox(NULL,"DirectSound の協調レベルの設定に失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
		// 閉じる
		SendMessage(hwnd,WM_CLOSE,0,0);
		return false;
	}
	// プライマリ サウンドバッファ作成
	DSBUFFERDESC desc;
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSP,NULL)))
	{
		MessageBox(NULL,"プライマリサウンドバッファの作成に失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
		// 閉じる
		SendMessage(hwnd,WM_CLOSE,0,0);
		return false;
	}
	//ここまでは一回行えばOKの処理

	//SEの数だけセカンダリバッファにデータ読み込み
	//読み込みファイル名をリストから読み込む

	initSBFileList();
	int nCount;

	for(nCount = 0;nCount <= SE_MAX - 1;nCount++){
		// WAVE ファイルの読み込み
//		MessageBox(NULL,SBArr[nCount].cSeFileName,"",MB_OK);

		SBArr[nCount].SB_lpDSB = LoadWave(SBArr[nCount].cSeFileName); //効果音
		if (SBArr[nCount].SB_lpDSB == NULL)
		{
			MessageBox(NULL,"ファイルの読み込みに失敗しました。","DirectSoundエラー",MB_OK | MB_ICONSTOP);
			// 閉じる
			SendMessage(hwnd,WM_CLOSE,0,0);
			return false;
		}
	}

	return true;
}


//-----------------------------------------------------------------------------------------
// セカンダリバッファ配列の初期化 
//-----------------------------------------------------------------------------------------
void initSBArr(){
	
	int iCount;
	for(iCount = 0;iCount <= SE_MAX;iCount++){
		SBArr[iCount].SB_lpDSB = NULL; //セカンダリバッファの初期化
		//後でSE用の文字列配列を作る予定
	}

}
//-----------------------------------------------------------------------------------------
// 読み込みファイル名の初期化
//-----------------------------------------------------------------------------------------
void initSBFileList(){

	int iCount;
	for(iCount = 0;iCount <= SE_MAX;iCount++){
		strcpy(SBArr[iCount].cSeFileName,"");
		strcpy(SBArr[iCount].cSeFileName,cSEFileName[iCount]);
	}
}


// WAVE ファイルの読み込み 
LPDIRECTSOUNDBUFFER LoadWave(char *name)
{
	char *buf;
	UINT readsize;
	WAVEFORMATEX wf;
	LPDIRECTSOUNDBUFFER lpDSB = NULL;
	DSBUFFERDESC desc;
	LPVOID pMem1,pMem2;
	DWORD size1,size2;
	// WAVE ファイルを開く

	if (!YWaveOpen(name))
	{
		return NULL;
	}
	// メモリ領域の確保
	buf = (char *)malloc(m_ckIn.cksize);
	// 読み込み
	ZeroMemory(&wf,sizeof(WAVEFORMATEX));
	if (!YWaveRead(m_ckIn.cksize,buf,&readsize,&wf))
	{
		free(buf);
		return NULL;
	}
	// サウンドバッファの作成
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
	// 領域をロック
	if (FAILED(lpDSB->Lock(0,readsize,&pMem1,&size1,&pMem2,&size2,0)))
	{
		free(buf);
		return 0;
	}
	// 書き込み
	memcpy(pMem1,buf,size1);
	if (size2)
	{
		memcpy(pMem2,buf + size1,size2);
	}
	// ロック解除
	lpDSB->Unlock(pMem1,size1,pMem2,size2);
	free(buf);
	// 閉じる
	YWaveClose();
	return lpDSB;
}
