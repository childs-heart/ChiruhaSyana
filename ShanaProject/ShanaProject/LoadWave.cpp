// Waveファイルを鳴らすプログラム
// Programmer:T.Ueki

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <dsound.h>
#include "LoadWave.h"

// グローバル変数
WAVEFORMATEX* m_pwfx;
HMMIO m_hmmioIn;
MMCKINFO m_ckIn;
MMCKINFO m_ckInRiff;


// WAVE 閉じる
int YWaveClose()
{
	mmioClose(m_hmmioIn,0);
	return 1;
}

// WAVE Read
int YWaveRead(UINT size,char *data,UINT *read,WAVEFORMATEX *wf)
{
	if (FAILED(YWaveReadFile(m_hmmioIn,size,(BYTE *)data,&m_ckIn,read)))
	{
		return 0;
	}
	// フォーマットのコピー
	if (wf)
	{
		memcpy(wf,m_pwfx,sizeof(WAVEFORMATEX));
	}
	free(m_pwfx);
	return 1;
}

// WAVE Open
int YWaveOpen(char *name)
{
	m_pwfx = NULL;
	if (FAILED(YWaveOpenFile(name,&m_hmmioIn,&m_pwfx,&m_ckInRiff)))
	{
		return 0;
	}
	if (FAILED(YWaveStartDataRead(&m_hmmioIn,&m_ckIn,&m_ckInRiff)))
	{
		return 0;
	}
	return 1;
}

//Waveファイル read
HRESULT YWaveReadFile(HMMIO hmmioIn,UINT cbRead,BYTE* pbDest,MMCKINFO* pckIn, UINT* cbActualRead)
{
	MMIOINFO mmioinfoIn;
	*cbActualRead = 0;
	if (mmioGetInfo(hmmioIn,&mmioinfoIn,0))
	{
		return E_FAIL;
	}
	UINT cbDataIn;
	cbDataIn = cbRead;
	if (cbDataIn > pckIn->cksize) 
	{
		cbDataIn = pckIn->cksize;
	}
	pckIn->cksize -= cbDataIn;
	for (DWORD cT = 0;cT < cbDataIn;cT++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if (mmioAdvance(hmmioIn,&mmioinfoIn,MMIO_READ))
			{
				return E_FAIL;
			}
			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				return E_FAIL;
			}
		}
		*((BYTE *)pbDest + cT) = *((BYTE *)mmioinfoIn.pchNext);
		mmioinfoIn.pchNext++;
	}
	if (mmioSetInfo(hmmioIn,&mmioinfoIn,0))
	{
		return E_FAIL;
	}
	*cbActualRead = cbDataIn;
	return S_OK;
}

// データ読み込み
HRESULT YWaveStartDataRead(HMMIO* phmmioIn,MMCKINFO* pckIn,MMCKINFO* pckInRIFF)
{
	if (-1 == mmioSeek(*phmmioIn,pckInRIFF->dwDataOffset + sizeof(FOURCC),SEEK_SET))
	{
		return E_FAIL;
	}
	pckIn->ckid = mmioFOURCC('d','a','t','a');
	if (mmioDescend(*phmmioIn,pckIn,pckInRIFF,MMIO_FINDCHUNK))
	{
		return E_FAIL;
	}
	return S_OK;
}

//Waveファイルオープン
HRESULT YWaveOpenFile(CHAR* strFileName,HMMIO* phmmioIn,WAVEFORMATEX** ppwfxInfo,MMCKINFO* pckInRIFF)
{
	HRESULT hr;
	HMMIO hmmioIn;
	hmmioIn = NULL;
	if (!(hmmioIn = mmioOpen(strFileName,NULL,MMIO_ALLOCBUF | MMIO_READ)))
	{
		return E_FAIL;
	}
	if (FAILED(hr = YReadMMIO(hmmioIn,pckInRIFF,ppwfxInfo)))
	{
		mmioClose(hmmioIn,0);
		return E_FAIL;
	}
	*phmmioIn = hmmioIn;
	return S_OK;
}

//　MMIO読み込み
HRESULT YReadMMIO(HMMIO hmmioIn,MMCKINFO* pckInRIFF,WAVEFORMATEX **ppwfxInfo)
{
	MMCKINFO ckIn;
	PCMWAVEFORMAT pcmWaveFormat;
	*ppwfxInfo = NULL;
	if (mmioDescend(hmmioIn,pckInRIFF,NULL,0))
	{
		return E_FAIL;
	}
	if ((pckInRIFF->ckid != FOURCC_RIFF) || (pckInRIFF->fccType != mmioFOURCC('W','A','V','E')))
	{
		return E_FAIL;
	}
	ckIn.ckid = mmioFOURCC('f','m','t',' ');
	if (mmioDescend(hmmioIn,&ckIn,pckInRIFF,MMIO_FINDCHUNK))
	{
		return E_FAIL;
	}
	if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
	{
		return E_FAIL;
	}
	if (mmioRead(hmmioIn,(HPSTR)&pcmWaveFormat,sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
	{
		return E_FAIL;
	}
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		if (!(*ppwfxInfo = (WAVEFORMATEX *)malloc(sizeof(WAVEFORMATEX))))
		{
			return E_FAIL;
		}
		memcpy(*ppwfxInfo,&pcmWaveFormat,sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = 0;
	}
	else
	{
		WORD cbExtraBytes;
		cbExtraBytes = 0;
		if (mmioRead(hmmioIn,(CHAR *)&cbExtraBytes,sizeof(WORD)) != sizeof(WORD))
		{
			return E_FAIL;
		}
		*ppwfxInfo = (WAVEFORMATEX *)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
		if (!*ppwfxInfo)
		{
			return E_FAIL;
		}
		memcpy(*ppwfxInfo,&pcmWaveFormat,sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = cbExtraBytes;
		if (mmioRead(hmmioIn,(CHAR *)(((BYTE *) & ((*ppwfxInfo)->cbSize)) + sizeof(WORD)),cbExtraBytes) != cbExtraBytes)
		{
			delete *ppwfxInfo;
			*ppwfxInfo = NULL;
			return E_FAIL;
		}
	}
	if (mmioAscend(hmmioIn,&ckIn,0))
	{
		delete *ppwfxInfo;
		*ppwfxInfo = NULL;
		return E_FAIL;
	}
	return S_OK;
}

