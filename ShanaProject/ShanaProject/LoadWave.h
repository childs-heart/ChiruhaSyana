#ifndef	__LOADWAVE
#define	__LOADWAVE

// DirectSound�@Wave�t�@�C����炷�v���O�����w�b�_
// Programmer:T.Ueki

// �O���[�o���ϐ�
extern WAVEFORMATEX* m_pwfx;
extern HMMIO m_hmmioIn;
extern MMCKINFO m_ckIn;
extern MMCKINFO m_ckInRiff;

// �֐��v���g�^�C�v
int YWaveClose();
int YWaveRead(UINT size,char *data,UINT *read,WAVEFORMATEX *wf);
int YWaveOpen(char *name);
HRESULT YWaveReadFile(HMMIO hmmioIn,UINT cbRead,BYTE* pbDest,MMCKINFO* pckIn, UINT* cbActualRead);
HRESULT YWaveStartDataRead(HMMIO* phmmioIn,MMCKINFO* pckIn,MMCKINFO* pckInRIFF);
HRESULT YWaveOpenFile(CHAR* strFileName,HMMIO* phmmioIn,WAVEFORMATEX** ppwfxInfo,MMCKINFO* pckInRIFF);
HRESULT YReadMMIO(HMMIO hmmioIn,MMCKINFO* pckInRIFF,WAVEFORMATEX **ppwfxInfo);

#endif