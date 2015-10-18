#include <windows.h>
#include <windowsx.h>
#include <Commdlg.h>
#include <stdio.h>
#include "resource.h"
#include "d3dmain.h"

HWND		HInfoDialog;
HWND		HWndParent;
HINSTANCE	HInstParent;

// プロトタイプ宣言
BOOL CALLBACK InfoDialogProc( HWND , UINT , UINT , LONG ) ;

int	ShowInfoDialog( HINSTANCE hInst, HWND hWndParent ){
	// ブレンドウィンドウ表示
	if (!(HInfoDialog = CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWndParent, InfoDialogProc ))){
		return FALSE ;
	}
	ShowWindow(HInfoDialog,SW_SHOW);

	HWndParent = hWndParent;
	HInstParent = hInst;

	return TRUE;
}

DWORD CPUIDMax    = 0;
DWORD CPUIDExtMax = 0;

char szVenderID[32] = "";
char szCpuName[64] = "";
char szInformation[512] ;

DWORD TypeID     = 0;
DWORD FamilyID   = 0;
DWORD ModelID    = 0;
DWORD SteppingID = 0;

DWORD CPUID_Flag  = 0;
DWORD FPU_Flag    = 0;
DWORD TSC_Flag    = 0;
DWORD MSR_Flag    = 0;
DWORD CMOV_Flag   = 0;
DWORD MMX_Flag    = 0;
DWORD _3DNow_Flag = 0;

DWORD SSE_INT_Flag   = 0;
DWORD SSE_FP_Flag    = 0;
DWORD _3DNowExt_Flag = 0;

DWORD SSE2_Flag    = 0;

DWORD fCpuClock = 0;


void GetCpuID(void)
{
	__asm{
		
		pushfd
		pop eax
		mov ebx, eax
		xor eax, 1<<21
		push eax
		popfd
		pushfd
		pop eax
		cmp eax, ebx
		je exitasm
		mov [CPUID_Flag], 1

		
		xor eax, eax
		cpuid
		mov [CPUIDMax], eax
		mov DWORD PTR [szVenderID+0], ebx
		mov DWORD PTR [szVenderID+4], edx
		mov DWORD PTR [szVenderID+8], ecx
		mov BYTE PTR [szVenderID+12], 0

		
		cmp eax, 1
		jb exitasm
		mov eax, 1
		cpuid

		mov esi, eax
		and esi, 0xf
		mov [SteppingID], esi

		shr eax, 4
		mov esi, eax
		and esi, 0xf
		mov [ModelID], esi

		shr eax, 4
		mov esi, eax
		and esi, 0xf
		mov [FamilyID], esi

		shr eax, 4
		mov esi, eax
		and esi, 0x3
		mov [TypeID], esi


		xor eax, eax
		test edx, 1<<0
		setnz al
		mov [FPU_Flag], eax

		test edx, 1<<4
		setnz al
		mov [TSC_Flag], eax

		test edx, 1<<5
		setnz al
		mov [MSR_Flag], eax

		test edx, 1<<15
		setnz al
		mov [CMOV_Flag], eax

		test edx, 1<<23
		setnz al
		mov [MMX_Flag], eax

		test edx, 1<<25
		setnz al
		mov [SSE_INT_Flag], eax
		mov [SSE_FP_Flag], eax

		test edx, 1<<26
		setnz al
		mov [SSE2_Flag], eax

		
		mov eax, 0x80000000
		cpuid
		mov [CPUIDExtMax], eax

		
		cmp eax, 0x80000001
		jb exitasm
		mov eax, 0x80000001
		cpuid

		xor eax, eax
		test edx, 1<<22
		setnz al
		mov [SSE_INT_Flag], eax

		test edx, 1<<30
		setnz al
		mov [_3DNowExt_Flag], eax

		test edx, 1<<31
		setnz al
		mov [_3DNow_Flag], eax

		
		cmp [CPUIDExtMax], 0x80000004
		jb exitasm
		mov eax, 0x80000002
		cpuid
		mov DWORD PTR [szCpuName+ 0], eax
		mov DWORD PTR [szCpuName+ 4], ebx
		mov DWORD PTR [szCpuName+ 8], ecx
		mov DWORD PTR [szCpuName+12], edx
		mov eax, 0x80000003
		cpuid
		mov DWORD PTR [szCpuName+16], eax
		mov DWORD PTR [szCpuName+20], ebx
		mov DWORD PTR [szCpuName+24], ecx
		mov DWORD PTR [szCpuName+28], edx
		mov eax, 0x80000004
		cpuid
		mov DWORD PTR [szCpuName+32], eax
		mov DWORD PTR [szCpuName+36], ebx
		mov DWORD PTR [szCpuName+40], ecx
		mov DWORD PTR [szCpuName+44], edx
		

	exitasm:
	}
}

void GetCpuClock(void)
{
	DWORD dwCpuClock;
	DWORD dwMsCount;

	if (TSC_Flag == 0)
		return;

	__asm{
		rdtsc
		mov [dwCpuClock], eax
	}

	dwMsCount = timeGetTime();
	while(timeGetTime() - dwMsCount < 500);

	__asm{
		rdtsc
		sub eax, [dwCpuClock]
		mov [dwCpuClock], eax
	}

	fCpuClock = (DWORD)(dwCpuClock/500000.0);
}




void GetSpec( void )
{
	GetCpuID();
	GetCpuClock();

	D3DADAPTER_IDENTIFIER9 identifier;
	lpD3D->GetAdapterIdentifier( 0, D3DENUM_WHQL_LEVEL, &identifier );

	sprintf( szInformation, "-- CPU SPEC --\r\n");
	sprintf( szInformation, "%sVenderID\t：　%s\r\n", szInformation, szVenderID);
	sprintf( szInformation, "%sCpuName\t：　%s\r\n", szInformation, szCpuName);
	sprintf( szInformation, "%sTypeID%d,　　FamilyID %d,　　ModelID %d,　　SteppingID %d\r\n", szInformation, TypeID, FamilyID, ModelID, SteppingID);
	sprintf( szInformation, "%sCpuClock\t：　%dMHz\r\n", szInformation, fCpuClock);

	sprintf( szInformation, "%s\r\n", szInformation );
	sprintf( szInformation, "%s-- GRAPHICS SPEC --\r\n", szInformation );
	sprintf( szInformation, "%sDeviceChipName\t :　%s\r\n", szInformation, identifier.Description );
	sprintf( szInformation, "%sAvailableTextureMemory\t :\r\n\t　%d KBytes/ ", szInformation, lpD3Ddev->GetAvailableTextureMem()/1024 );

/*	sprintf( szInformation, "%sCPUID       %d\r\n", szInformation, CPUID_Flag);		
	sprintf( szInformation, "%sCPUIDMax    %x\r\n", szInformation, CPUIDMax);		
	sprintf( szInformation, "%sCPUIDExtMax %x\r\n", szInformation, CPUIDExtMax);	

	sprintf( szInformation, "%sFPU    %s\r\n", szInformation, szFlag[FPU_Flag]);				
	sprintf( szInformation, "%sTSC    %s\r\n", szInformation, szFlag[TSC_Flag]);				
	sprintf( szInformation, "%sMSR    %s\r\n", szInformation, szFlag[MSR_Flag]);				
	sprintf( szInformation, "%sCMOV   %s\r\n", szInformation, szFlag[CMOV_Flag]);				
	sprintf( szInformation, "%sMMX    %s\r\n", szInformation, szFlag[MMX_Flag]);				
	sprintf( szInformation, "%s3DNow! %s\r\n", szInformation, szFlag[_3DNow_Flag]);			

	sprintf( szInformation, "%sSSE_INT    %s\r\n", szInformation, szFlag[SSE_INT_Flag]);		
	sprintf( szInformation, "%sSSE_FP     %s\r\n", szInformation, szFlag[SSE_FP_Flag]);		
	sprintf( szInformation, "%s3DNow! Ext %s\r\n", szInformation, szFlag[_3DNowExt_Flag]);		
	sprintf( szInformation, "%sFCMOV      %s\r\n", szInformation, szFlag[FPU_Flag & CMOV_Flag]);
*/
} 

BOOL CALLBACK InfoDialogProc( HWND hwnd, UINT wmes, UINT wparam, LONG lparam )
{
	static char info[512];
	switch( wmes ){
		case WM_CREATE:
			break;

		case WM_INITDIALOG:
			GetSpec();
			
			// 表示
			Edit_SetText( GetDlgItem( hwnd, IDC_EDIT1) , szInformation );
		break;


		case WM_COMMAND:
//			switch(LOWORD(wparam)){
//			}
			// 表示
			sprintf( info ,"%s %d KBytes ", szInformation, lpD3Ddev->GetAvailableTextureMem()/1024 );
			Edit_SetText( GetDlgItem( hwnd, IDC_EDIT1) , info );
			break;

		case WM_CLOSE:
			EndDialog( hwnd, TRUE );
			break;

		default:
			return FALSE;
			break;
	}
	return TRUE;
}

