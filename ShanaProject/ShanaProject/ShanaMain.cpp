//-----------------------------------------------------------------------------------------
// TITLE:�V���i�v���W�F�N�g�i��	
// Programmer:T.Ueki T.shimizu							
//															
//-----------------------------------------------------------------------------------------
#include <objbase.h>
#include <windows.h>
#include <stdio.h>
#include "ShanaMain.h"		// ���C���w�b�_�t�@�C��
#include "d3dmain.h"
#include "Game.h"
#include "DsoundMain.h"
#include "FileSave.h"
#include "FileSaveCommon.h"

HWND			win_hwnd;							// �E�B���h�E�̃n���h��
MSG				msg;
HINSTANCE		hInst;								// �C���X�^���X
HINSTANCE		g_hinst;
int end_sw = 0;											// ���C�����[�v�I���Ǘ��ϐ�
int FullS = 0;										// 0:�E�B���h�E���[�h 1:�t���X�N���[�����[�h

CGame		*Game;

void ShowInfoDialog( HINSTANCE , HWND );

//-----------------------------------------------------------------------------------------
// �v���g�^�C�v�錾����
//-----------------------------------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,char *CmdLine,int CmdShow);
LRESULT CALLBACK win_proc(HWND win_hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

//-----------------------------------------------------------------------------------------
// �V�X�e�����C�� - ���t���[���Ă΂��֐��ł�
//-----------------------------------------------------------------------------------------
void sys_main()
{
	// ���C�����[�`���̍ŏ�
	Game->GameMain();
}

//-----------------------------------------------------------------------------------------
// WinMain - WINDOWS�A�v���̍ŏ��Ɏ��s�����ꏊ
//-----------------------------------------------------------------------------------------
int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,char *CmdLine,int CmdShow)
{
	HRESULT hr;

	WNDCLASS winc;

//	hr = CoInitialize(NULL);
//    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	ZeroMemory(&winc,sizeof(WNDCLASS));
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.hCursor = LoadCursor(NULL,IDC_ARROW);
	winc.hInstance = hInst;
	winc.lpfnWndProc = win_proc;
	winc.lpszClassName = "DRBMAIN";
	RegisterClass(&winc);

	char file_path[1024];
	DWORD len;
	//�N���f�B���N�g�����A�t�@�C�����擾
	len = GetModuleFileName(NULL,file_path,1024);
	if(len == 0)
		return	false;

	//�p�X�̕���
	int last=0;
	int i=0;
	while( (i<1024) && (file_path[i]!=NULL) ){
		if( file_path[i] == '\\' )
			last = i;
		i++;
	}
	file_path[last] = NULL;
//	SetCurrentDirectory( file_path );

//	StConfigData keyconfig[2];
	// �ݒ�t�@�C��
	CFileSave	fileSave;
//	fileSave.Open("D:\\child_heart\\program\\ShanaProject\\ShanaProject\\ConfigTool.ini");
	sprintf( file_path, "%s\\ConfigTool.ini\0", file_path );
	fileSave.Open(file_path);
	fileSave.ReadMember(FILE_SAVE_SECTION_DISPLAY,FILE_SAVE_DISPLAY_HEADER_VIEW,(DWORD*)&FullS);
/*	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_UP, &keyconfig[0].m_Dir[0] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_DOWN, &keyconfig[0].m_Dir[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_LEFT, &keyconfig[0].m_Dir[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_RIGHT, &keyconfig[0].m_Dir[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_UP, &keyconfig[1].m_Dir[0] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_DOWN, &keyconfig[1].m_Dir[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_LEFT, &keyconfig[1].m_Dir[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_RIGHT, &keyconfig[1].m_Dir[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_A, &keyconfig[0].m_Button[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_B, &keyconfig[0].m_Button[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_C, &keyconfig[0].m_Button[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_D, &keyconfig[0].m_Button[4] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_START, &keyconfig[0].m_Button[5] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_AB, &keyconfig[0].m_Button[6] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_1PKEY, FILE_SAVE_KEY_HEADER_CD, &keyconfig[0].m_Button[7] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_A, &keyconfig[1].m_Button[1] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_B, &keyconfig[1].m_Button[2] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_C, &keyconfig[1].m_Button[3] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_D, &keyconfig[1].m_Button[4] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_START, &keyconfig[1].m_Button[5] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_AB, &keyconfig[1].m_Button[6] );
	gFileSave.ReadMember(FILE_SAVE_SECTION_2PKEY, FILE_SAVE_KEY_HEADER_CD, &keyconfig[1].m_Button[7] );
*/
	if( FullS == 0 ){
		hr = MessageBox(NULL,"�t���X�N���[�����[�h�ŋN�����܂����H\n�N������ꍇ�́u�͂��v���A�E�B���h�E���[�h�ŋN������ꍇ�́u�������v��I�����Ă��������B","��ʃ��[�h�̑I��",MB_YESNO | MB_ICONQUESTION);
//		hr = 0;//MessageBox(NULL,"�t���X�N���[�����[�h�ŋN�����܂����H\n�N������ꍇ�́u�͂��v���A�E�B���h�E���[�h�ŋN������ꍇ�́u�������v��I�����Ă��������B","��ʃ��[�h�̑I��",MB_YESNO | MB_ICONQUESTION);
		
		if(hr == IDYES)FullS=2;			//�u�͂��v�I�����t���X�N���[�����ʕϐ���1����
		else FullS=1;
	}
	int width,height;

//	FullS=1;
	// �E�C���h�E�̑傫�����v�Z
	FullS--;
	if (FullS)
	{
		// �t���X�N���[�����͂��̂܂܂� OK
		width = W_WIDTH;
		height = W_HEIGHT;
	}
	else
	{
		// �E�C���h�E���̓E�C���h�E�̊O�g�̃T�C�Y���l������
		width = W_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2;
		height = W_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);
	}

	// �E�C���h�E���쐬
	win_hwnd = CreateWindow("DRBMAIN",
							CAPTION,
							WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							width,
							height,
							NULL,
							NULL,
							hInst,
							NULL);

	//DirectX������
	hr = D3Dinit( win_hwnd, W_WIDTH, W_HEIGHT, FullS);
	if FAILED(hr)
	{
		return false;			//�������o���Ȃ�������I��
	}

	// DirectSound������
	// �S�Ă�SE�����o�b�t�@�ɓW�J
	hr = Dsoundinit( win_hwnd );
	if FAILED(hr)
	{
		return false;			//�������o���Ȃ�������I��
	}

	g_hinst=hInst;

	Game = new CGame();
	Game->m_D3DDraw.SetDevice( lpD3Ddev );
	Game->m_D3DDraw.SetCenter( 400,300 );

	ShowWindow( win_hwnd, CmdShow );

	// �C���t�H�E�B���h�E�\��
	if(!FullS){
//		ShowInfoDialog( g_hinst , win_hwnd );
	}

	//���C�����[�v�ŉ񂹉�
	//end_sw��1�̎��ɏI���	
	while (!end_sw)
	{
		// ���b�Z�[�W�����Ă��邩?
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			// ���b�Z�[�W�̏���
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		sys_main();
/*		else
		{
			sys_main();
		}
*/
	}

	delete Game;
	D3D_END();
//    CoUninitialize();
	//�I������
	return false;
}
//-----------------------------------------------------------------------------------------
//	���C���E�B���h�E(NAME:DRBMAIN)�v���V�[�W��
//-----------------------------------------------------------------------------------------
LRESULT CALLBACK win_proc(HWND win_hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{     
	
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		end_sw=1;
		return false;
	}
	return DefWindowProc(win_hwnd,msg,wParam,lParam);

}
