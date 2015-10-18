#ifndef	__LOADWAVE
#define	__LOADWAVE

// DirectSound　Waveファイルを鳴らすプログラムヘッダ
// Programmer:T.Ueki

// グローバル変数
extern WAVEFORMATEX* m_pwfx;
extern HMMIO m_hmmioIn;
extern MMCKINFO m_ckIn;
extern MMCKINFO m_ckInRiff;

// 関数プロトタイプ
int YWaveClose();
int YWaveRead(UINT size,char *data,UINT *read,WAVEFORMATEX *wf);
int YWaveOpen(char *name);
HRESULT YWaveReadFile(HMMIO hmmioIn,UINT cbRead,BYTE* pbDest,MMCKINFO* pckIn, UINT* cbActualRead);
HRESULT YWaveStartDataRead(HMMIO* phmmioIn,MMCKINFO* pckIn,MMCKINFO* pckInRIFF);
HRESULT YWaveOpenFile(CHAR* strFileName,HMMIO* phmmioIn,WAVEFORMATEX** ppwfxInfo,MMCKINFO* pckInRIFF);
HRESULT YReadMMIO(HMMIO hmmioIn,MMCKINFO* pckInRIFF,WAVEFORMATEX **ppwfxInfo);

#endif