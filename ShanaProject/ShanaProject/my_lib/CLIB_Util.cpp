#include "CLIB_Util.h"

//==============================================================
// テクスチャーリストクラス管理
//==============================================================
CTextureGroupManager::CTextureGroupManager( LPDIRECT3DDEVICE9 d3ddevice )
{
	m_texGroup = new CTextureGroup*[101];
	for( int i = 0 ; i < 101 ; i++ ){
		m_texGroup[i] = new CTextureGroup( 300, d3ddevice );
	}
}

CTextureGroupManager::~CTextureGroupManager()
{
	for( int i = 0 ; i < 101 ; i++ ){
		delete m_texGroup[i];
	}
	delete []m_texGroup;
}

//
//  関数: GetTextureNo( int GROUP_NO )
//
//  目的: テクスチャーグループ番号取得
//
//  パラメータ:
//　　　　para1:テクスチャーグループ番号
//　メモ：
//　　　
int CTextureGroupManager::GetTextureNo( int no )
{
	return no;

/*	switch( no ){
		case TEXTUREGROUP_CHARACTOR:
			return 0;
			break;

		case 100:
			return 10;
			break;

		case 99:
			return 11;
			break;

		case 98:
			return 12;
			break;

		case 97:
			return 13;
			break;

		case 96:
			return 14;
			break;

		case 95:
			return 19;
			break;

		case 94:
			return 9;
			break;

		case 93:
			return 18;
			break;

		default:
			return no;
			break;
	}
*/

}

//
//  関数: GetTextureGroup( int GROUP_NO )
//
//  目的: テクスチャーグループ取得
//
//  パラメータ:
//　　　　para1:テクスチャーグループ番号
//　メモ：
//　　　
CTextureGroup* CTextureGroupManager::GetTextureGroup( int no )
{
	return m_texGroup[ GetTextureNo(no) ];
}

//
//  関数: SetupTextureGroup( CTextureGroup* tex, int CHARA_NO )
//
//  目的: テクスチャーファイル読み込み
//
//  パラメータ:
//　　　　para1:読み込み先　テクスチャーグループ
//　　　　para2:読み込み種別番号
//　メモ：
//　　　
void CTextureGroupManager::SetupTextureGroup( CTextureGroup* tex, int no, int param1 )
{
	tex->Reset();
	// パラメータ有効時に使うもの
	HANDLE	hReadFile ;
	DWORD	nFileSize ;
	RGBQUAD	stPalette[256];
	RGBQUAD *stPaletteTemp;

	switch( no ){
		case TEXTURE_NO_WIL:
		stPaletteTemp = NULL;
		if( param1 == 1 ){
			hReadFile = NULL ;
			hReadFile = CreateFile( "shana2p.act" ,GENERIC_READ,0,NULL,
								OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if( hReadFile == INVALID_HANDLE_VALUE ){
				MessageBox(NULL,"ファイルなし　パレット","file not found",MB_OK);
				stPaletteTemp = NULL;
			}
			else{
				for( int i = 0 ; i < 255 ; i++ ){
					// データ読み込み
					ReadFile( hReadFile , &stPalette[i] , sizeof( RGBQUAD ) , &nFileSize , NULL );
				}
				CloseHandle( hReadFile );
				stPaletteTemp = stPalette ;
			}
		}
		// nutral
		tex->LoadTexture( 0, "Dot_Wil_105_001.bmp", 0 );
		tex->LoadTexture( 1, "Dot_Wil_105_002.bmp", 0 );
		tex->LoadTexture( 2, "Dot_Wil_105_003.bmp", 0 );
		tex->LoadTexture( 3, "Dot_Wil_105_004.bmp", 0 );
		tex->LoadTexture( 4, "Dot_Wil_105_005.bmp", 0 );
		tex->LoadTexture( 5, "Dot_Wil_105_006.bmp", 0 );
		tex->LoadTexture( 6, "Dot_Wil_105_007.bmp", 0 );
		tex->LoadTexture( 7, "Dot_Wil_105_008.bmp", 0 );

		// WALK for
		tex->LoadTexture( 15, "Dot_Wil_301_001.bmp", 0 );
		tex->LoadTexture( 16, "Dot_Wil_301_002.bmp", 0 );
		tex->LoadTexture( 17, "Dot_Wil_301_003.bmp", 0 );
		tex->LoadTexture( 18, "Dot_Wil_301_004.bmp", 0 );
		tex->LoadTexture( 19, "Dot_Wil_301_005.bmp", 0 );
		tex->LoadTexture( 20, "Dot_Wil_301_006.bmp", 0 );
		tex->LoadTexture( 21, "Dot_Wil_301_007.bmp", 0 );
		tex->LoadTexture( 22, "Dot_Wil_301_008.bmp", 0 );

		// WALK back
		tex->LoadTexture( 23, "Dot_Wil_302_001.bmp", 0 );
		tex->LoadTexture( 24, "Dot_Wil_302_002.bmp", 0 );
		tex->LoadTexture( 25, "Dot_Wil_302_003.bmp", 0 );
		tex->LoadTexture( 26, "Dot_Wil_302_004.bmp", 0 );
		tex->LoadTexture( 27, "Dot_Wil_302_005.bmp", 0 );
		tex->LoadTexture( 28, "Dot_Wil_302_006.bmp", 0 );
		tex->LoadTexture( 29, "Dot_Wil_302_007.bmp", 0 );
		tex->LoadTexture( 30, "Dot_Wil_302_008.bmp", 0 );

		// DUSH back
		tex->LoadTexture( 31, "Dot_Wil_304_001.bmp", 0 );
		tex->LoadTexture( 32, "Dot_Wil_304_002.bmp", 0 );
		tex->LoadTexture( 33, "Dot_Wil_304_003.bmp", 0 );
		tex->LoadTexture( 34, "Dot_Wil_304_004.bmp", 0 );

		// JUMP
		tex->LoadTexture( 35, "Dot_Wil_306_001.bmp", 0 );
		tex->LoadTexture( 36, "Dot_Wil_306_002.bmp", 0 );
		tex->LoadTexture( 37, "Dot_Wil_306_003.bmp", 0 );
		tex->LoadTexture( 38, "Dot_Wil_306_004.bmp", 0 );
		tex->LoadTexture( 39, "Dot_Wil_306_005.bmp", 0 );
		tex->LoadTexture( 40, "Dot_Wil_306_006.bmp", 0 );
		tex->LoadTexture( 41, "Dot_Wil_306_007.bmp", 0 );
		tex->LoadTexture( 42, "Dot_Wil_306_008.bmp", 0 );

		// JUMP back-turn
		tex->LoadTexture( 43, "Dot_Wil_307_001.bmp", 0 );
		tex->LoadTexture( 44, "Dot_Wil_307_002.bmp", 0 );
		tex->LoadTexture( 45, "Dot_Wil_307_003.bmp", 0 );
		tex->LoadTexture( 46, "Dot_Wil_307_004.bmp", 0 );
		tex->LoadTexture( 47, "Dot_Wil_307_005.bmp", 0 );
		tex->LoadTexture( 48, "Dot_Wil_307_006.bmp", 0 );

		// JUMP DUSH for
		tex->LoadTexture( 50, "Dot_Wil_308_001.bmp", 0 );
		tex->LoadTexture( 51, "Dot_Wil_308_002.bmp", 0 );
		tex->LoadTexture( 52, "Dot_Wil_308_003.bmp", 0 );

		// Attack LOW
		tex->LoadTexture( 53, "Dot_Wil_406_001.bmp", 0 );
		tex->LoadTexture( 54, "Dot_Wil_406_002.bmp", 0 );

		// Attack HIGH (for+HIGH)
		tex->LoadTexture( 56, "Dot_Wil_401_001.bmp", 0 );
		tex->LoadTexture( 57, "Dot_Wil_401_002.bmp", 0 );
		tex->LoadTexture( 58, "Dot_Wil_401_003.bmp", 0 );
		tex->LoadTexture( 59, "Dot_Wil_401_004.bmp", 0 );
		tex->LoadTexture( 60, "Dot_Wil_401_005.bmp", 0 );
		tex->LoadTexture( 61, "Dot_Wil_401_006.bmp", 0 );
		tex->LoadTexture( 62, "Dot_Wil_401_007.bmp", 0 );
		tex->LoadTexture( 63, "Dot_Wil_401_008.bmp", 0 );
		tex->LoadTexture( 64, "Dot_Wil_401_009.bmp", 0 );
		tex->LoadTexture( 65, "Dot_Wil_401_010.bmp", 0 );
		tex->LoadTexture( 66, "Dot_Wil_401_011.bmp", 0 );
		tex->LoadTexture( 67, "Dot_Wil_401_012.bmp", 0 );
		tex->LoadTexture( 68, "Dot_Wil_401_013.bmp", 0 );
		tex->LoadTexture( 69, "Dot_Wil_401_014.bmp", 0 );
		tex->LoadTexture( 70, "Dot_Wil_401_015.bmp", 0 );

		// Attack HIGH
		tex->LoadTexture( 71, "Dot_Wil_405_001.bmp", 0 );
		tex->LoadTexture( 72, "Dot_Wil_405_002.bmp", 0 );
		tex->LoadTexture( 73, "Dot_Wil_405_003.bmp", 0 );
		tex->LoadTexture( 74, "Dot_Wil_405_004.bmp", 0 );
		tex->LoadTexture( 75, "Dot_Wil_405_005.bmp", 0 );
		tex->LoadTexture( 76, "Dot_Wil_405_006.bmp", 0 );

		// Damage
		tex->LoadTexture( 78, "Dot_Wil_206_001.bmp", 0 );
		tex->LoadTexture( 79, "Dot_Wil_206_002.bmp", 0 );

		// Crouch
		tex->LoadTexture( 80, "Dot_Wil_104_001.bmp", 0 );
		tex->LoadTexture( 81, "Dot_Wil_104_002.bmp", 0 );
		tex->LoadTexture( 82, "Dot_Wil_104_003.bmp", 0 );
		tex->LoadTexture( 83, "Dot_Wil_104_004.bmp", 0 );

		// JUMP-DUSH-for

		// JUMP-DUSH-back
		tex->LoadTexture( 85, "Dot_Wil_309_001.bmp", 0 );
		tex->LoadTexture( 86, "Dot_Wil_309_002.bmp", 0 );
		tex->LoadTexture( 87, "Dot_Wil_309_003.bmp", 0 );

		// damage down
		tex->LoadTexture( 88, "Dot_Wil_207_001.bmp", 0 );
		tex->LoadTexture( 89, "Dot_Wil_207_002.bmp", 0 );

		// Crouch-Attack low
		tex->LoadTexture( 90, "Dot_Wil_433_1.bmp", 0 );
		tex->LoadTexture( 91, "Dot_Wil_433_2.bmp", 0 );
		
		// Crouch-damage
		tex->LoadTexture( 92, "Dot_Wil_211_001.bmp", 0 );
		tex->LoadTexture( 93, "Dot_Wil_211_002.bmp", 0 );
		
		// DUSH-for
		tex->LoadTexture( 94, "Dot_Wil_303_001.bmp", 0 );
		tex->LoadTexture( 95, "Dot_Wil_303_002.bmp", 0 );
		tex->LoadTexture( 96, "Dot_Wil_303_003.bmp", 0 );
		tex->LoadTexture( 97, "Dot_Wil_303_004.bmp", 0 );
		tex->LoadTexture( 98, "Dot_Wil_303_005.bmp", 0 );
		tex->LoadTexture( 99, "Dot_Wil_303_006.bmp", 0 );
		
		// damage aerial down
		tex->LoadTexture( 100, "Dot_Wil_203_001.bmp", 0 );
		tex->LoadTexture( 101, "Dot_Wil_203_002.bmp", 0 );
		tex->LoadTexture( 102, "Dot_Wil_204_001.bmp", 0 );
		tex->LoadTexture( 103, "Dot_Wil_204_002.bmp", 0 );
		tex->LoadTexture( 104, "Dot_Wil_204_003.bmp", 0 );
		tex->LoadTexture( 105, "Dot_Wil_204_004.bmp", 0 );

		// blow down
		tex->LoadTexture( 107, "Dot_Wil_202_001.bmp", 0 );
		tex->LoadTexture( 108, "Dot_Wil_202_002.bmp", 0 );

		// recover
		tex->LoadTexture( 110, "Dot_Wil_208_001.bmp", 0 );
		tex->LoadTexture( 111, "Dot_Wil_208_002.bmp", 0 );
		tex->LoadTexture( 112, "Dot_Wil_208_003.bmp", 0 );
		tex->LoadTexture( 113, "Dot_Wil_208_004.bmp", 0 );
		tex->LoadTexture( 114, "Dot_Wil_208_005.bmp", 0 );

		// throw
		tex->LoadTexture( 115, "Dot_Wil_413_001.bmp", 0 );
		tex->LoadTexture( 116, "Dot_Wil_413_002.bmp", 0 );
		tex->LoadTexture( 117, "Dot_Wil_413_003.bmp", 0 );
		tex->LoadTexture( 118, "Dot_Wil_413_004.bmp", 0 );
		tex->LoadTexture( 119, "Dot_Wil_413_005.bmp", 0 );
		tex->LoadTexture( 120, "Dot_Wil_413_006.bmp", 0 );
		tex->LoadTexture( 121, "Dot_Wil_413_007.bmp", 0 );

		// damage aerial up
		tex->LoadTexture( 122, "Dot_Wil_203_001.bmp", 0 );
		tex->LoadTexture( 123, "Dot_Wil_203_002.bmp", 0 );

		// crouch attack low
		tex->LoadTexture( 124, "Dot_Wil_433_1.bmp", 0 );
		tex->LoadTexture( 125, "Dot_Wil_433_2.bmp", 0 );

		// Damage down
//		tex->LoadTexture( 126, "Dot_Wil_207_001.bmp", 0 );
	//	tex->LoadTexture( 127, "Dot_Wil_207_002.bmp", 0 );

		// Damage Wall
		tex->LoadTexture( 128, "Dot_Wil_201_001.bmp", 0 );

		// jump attack high
		tex->LoadTexture( 130, "Dot_Wil_420_001.bmp", 0 );
		tex->LoadTexture( 131, "Dot_Wil_420_002.bmp", 0 );
		tex->LoadTexture( 132, "Dot_Wil_420_003.bmp", 0 );
		tex->LoadTexture( 133, "Dot_Wil_420_004.bmp", 0 );
		tex->LoadTexture( 134, "Dot_Wil_420_005.bmp", 0 );

		// crouch attack mid
		tex->LoadTexture( 140, "Dot_Wil_434_001.bmp", 0 );
		tex->LoadTexture( 141, "Dot_Wil_434_002.bmp", 0 );
		tex->LoadTexture( 142, "Dot_Wil_434_003.bmp", 0 );
		tex->LoadTexture( 143, "Dot_Wil_434_004.bmp", 0 );
		tex->LoadTexture( 144, "Dot_Wil_434_005.bmp", 0 );
		tex->LoadTexture( 145, "Dot_Wil_434_006.bmp", 0 );
		tex->LoadTexture( 146, "Dot_Wil_434_007.bmp", 0 );

		// jump attack low 
		tex->LoadTexture( 147, "Dot_Wil_419_001.bmp", 0 );
		tex->LoadTexture( 148, "Dot_Wil_419_002.bmp", 0 );
		tex->LoadTexture( 149, "Dot_Wil_419_003.bmp", 0 );

		// special 1
		tex->LoadTexture( 151, "Dot_Wil_801_001.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 152, "Dot_Wil_801_002.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 153, "Dot_Wil_801_003.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 154, "Dot_Wil_801_004.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 155, "Dot_Wil_801_005.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 156, "Dot_Wil_801_006.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 157, "Dot_Wil_801_007.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 158, "Dot_Wil_801_008.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 159, "Dot_Wil_801_009.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 160, "Dot_Wil_801_010.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 161, "Dot_Wil_801_011.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 162, "Dot_Wil_801_012.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 163, "Dot_Wil_801_013.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 164, "Dot_Wil_801_014.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 165, "Dot_Wil_801_015.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 166, "Dot_Wil_801_016.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 167, "Dot_Wil_801_017.bmp", 0, stPaletteTemp );
//		break;

		// damage down
//		tex->LoadTexture(170, "Dot_Wil_207_001.bmp", 0, stPaletteTemp);
//		tex->LoadTexture(171, "Dot_Wil_207_002.bmp", 0, stPaletteTemp);

		// attackl low
//		tex->LoadTexture(175, "Dot_Wil_406_001.bmp", 0, stPaletteTemp);
//		tex->LoadTexture(176, "Dot_Wil_406_002.bmp", 0, stPaletteTemp);
//		break;

		// attackl mid
		tex->LoadTexture(180, "Dot_Wil_407_001.bmp", 0, stPaletteTemp);
		tex->LoadTexture(181, "Dot_Wil_407_002.bmp", 0, stPaletteTemp);
		tex->LoadTexture(182, "Dot_Wil_407_003.bmp", 0, stPaletteTemp);
		tex->LoadTexture(183, "Dot_Wil_407_004.bmp", 0, stPaletteTemp);
		tex->LoadTexture(184, "Dot_Wil_407_005.bmp", 0, stPaletteTemp);
//		break;

		// attackl jump high
		tex->LoadTexture(185, "Dot_Wil_418_001.bmp", 0, stPaletteTemp);
		tex->LoadTexture(186, "Dot_Wil_418_002.bmp", 0, stPaletteTemp);
		tex->LoadTexture(187, "Dot_Wil_418_003.bmp", 0, stPaletteTemp);
		tex->LoadTexture(188, "Dot_Wil_418_004.bmp", 0, stPaletteTemp);
		tex->LoadTexture(189, "Dot_Wil_418_005.bmp", 0, stPaletteTemp);
		tex->LoadTexture(190, "Dot_Wil_418_006.bmp", 0, stPaletteTemp);
		tex->LoadTexture(191, "Dot_Wil_418_007.bmp", 0, stPaletteTemp);
		tex->LoadTexture(192, "Dot_Wil_418_008.bmp", 0, stPaletteTemp);
		tex->LoadTexture(193, "Dot_Wil_418_009.bmp", 0, stPaletteTemp);
		tex->LoadTexture(194, "Dot_Wil_418_010.bmp", 0, stPaletteTemp);
		tex->LoadTexture(195, "Dot_Wil_418_011.bmp", 0, stPaletteTemp);
		tex->LoadTexture(196, "Dot_Wil_418_012.bmp", 0, stPaletteTemp);
//		break;

		// throw miss
		tex->LoadTexture(198, "Dot_Wil_431_001.bmp", 0, stPaletteTemp);
		tex->LoadTexture(199, "Dot_Wil_431_002.bmp", 0, stPaletteTemp);
//		break;

		// guard
		tex->LoadTexture(200, "Dot_Wil_501_001.bmp", 0, stPaletteTemp);
		tex->LoadTexture(201, "Dot_Wil_501_002.bmp", 0, stPaletteTemp);
//		break;

		// air guard
		tex->LoadTexture(203, "Dot_Wil_502_001.bmp", 0, stPaletteTemp);
		tex->LoadTexture(204, "Dot_Wil_502_002.bmp", 0, stPaletteTemp);
//		break;

		// crounch guard
		tex->LoadTexture(206, "Dot_Wil_503_001.bmp", 0, stPaletteTemp);
		tex->LoadTexture(207, "Dot_Wil_503_002.bmp", 0, stPaletteTemp);
//		break;

		// special 2
		tex->LoadTexture(210, "Dot_Wil_802_001.bmp", 0, stPaletteTemp);
		tex->LoadTexture(211, "Dot_Wil_802_002.bmp", 0, stPaletteTemp);
		tex->LoadTexture(212, "Dot_Wil_802_003.bmp", 0, stPaletteTemp);
		tex->LoadTexture(213, "Dot_Wil_802_004.bmp", 0, stPaletteTemp);
		tex->LoadTexture(214, "Dot_Wil_802_005.bmp", 0, stPaletteTemp);
		tex->LoadTexture(215, "Dot_Wil_802_006.bmp", 0, stPaletteTemp);
		tex->LoadTexture(216, "Dot_Wil_802_007.bmp", 0, stPaletteTemp);
		tex->LoadTexture(217, "Dot_Wil_802_008.bmp", 0, stPaletteTemp);
		tex->LoadTexture(218, "Dot_Wil_802_009.bmp", 0, stPaletteTemp);
		tex->LoadTexture(219, "Dot_Wil_802_010.bmp", 0, stPaletteTemp);
		break;

		case TEXTURE_NO_SHANA:
		stPaletteTemp = NULL;
		if( param1 == 1 ){
			hReadFile = NULL ;
			hReadFile = CreateFile( "shana2p.act" ,GENERIC_READ,0,NULL,
								OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if( hReadFile == INVALID_HANDLE_VALUE ){
				MessageBox(NULL,"ファイルなし　パレット","file not found",MB_OK);
				stPaletteTemp = NULL;
			}
			else{
		for( int i = 0 ; i < 255 ; i++ ){
					// データ読み込み
					ReadFile( hReadFile , &stPalette[i] , sizeof( RGBQUAD ) , &nFileSize , NULL );
				}
				CloseHandle( hReadFile );
				stPaletteTemp = stPalette ;
			}
		}

		tex->LoadTexture( 0, "Dot_Sya_001_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 1, "Dot_Sya_001_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 2, "Dot_Sya_001_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 3, "Dot_Sya_001_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 4, "Dot_Sya_001_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 5, "Dot_Sya_001_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 6, "Dot_Sya_001_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 7, "Dot_Sya_022_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 8, "Dot_Sya_022_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 9, "Dot_Sya_022_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 10, "Dot_Sya_022_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 11, "Dot_Sya_002_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 12, "Dot_Sya_002_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 13, "Dot_Sya_002_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 14, "Dot_Sya_002_04.bmp", 0, stPaletteTemp );
		// ATTACK HIGH
		tex->LoadTexture( 15, "Dot_Sya_004_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 16, "Dot_Sya_004_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 17, "Dot_Sya_004_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 18, "Dot_Sya_004_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 19, "Dot_Sya_004_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 20, "Dot_Sya_004_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 21, "Dot_Sya_004_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 22, "Dot_Sya_004_08.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 23, "Dot_Sya_004_09.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 24, "Dot_Sya_004_10.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 25, "Dot_Sya_004_11.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 26, "Dot_Sya_005_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 27, "Dot_Sya_005_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 28, "Dot_Sya_005_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 29, "Dot_Sya_005_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 30, "Dot_Sya_005_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 31, "Dot_Sya_005_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 32, "Dot_Sya_005_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 33, "Dot_Sya_005_08.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 40, "Dot_Sya_035_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 41, "Dot_Sya_035_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 42, "Dot_Sya_035_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 43, "Dot_Sya_035_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 44, "Dot_Sya_035_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 45, "Dot_Sya_035_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 46, "Dot_Sya_035_07.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 47, "Dot_Sya_999_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 48, "Dot_Sya_999_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 49, "Dot_Sya_999_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 50, "Dot_Sya_999_04.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 51, "Dot_Sya_037_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 52, "Dot_Sya_037_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 53, "Dot_Sya_037_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 54, "Dot_Sya_037_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 55, "Dot_Sya_037_05.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 56, "Dot_Sya_038_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 57, "Dot_Sya_038_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 58, "Dot_Sya_038_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 59, "Dot_Sya_038_04.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 60, "Dot_Sya_433_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 61, "Dot_Sya_433_02.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 62, "Dot_Sya_418_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 63, "Dot_Sya_418_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 64, "Dot_Sya_418_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 65, "Dot_Sya_418_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 66, "Dot_Sya_418_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 67, "Dot_Sya_418_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 68, "Dot_Sya_418_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 69, "Dot_Sya_418_08.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 70, "Dot_Sya_418_09.bmp", 0, stPaletteTemp );

//		tex->LoadTexture( 71, "Dot_Sya_039_01.bmp", 0, stPaletteTemp );
//		tex->LoadTexture( 72, "Dot_Sya_039_02.bmp", 0, stPaletteTemp );
//		tex->LoadTexture( 73, "Dot_Sya_039_03.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 74, "Dot_Sya_040_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 75, "Dot_Sya_040_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 76, "Dot_Sya_040_03.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 77, "Dot_Sya_045_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 78, "Dot_Sya_045_02.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 79, "Dot_Sya_211_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 80, "Dot_Sya_211_02.bmp", 0, stPaletteTemp );

		// mid
		tex->LoadTexture( 81, "Dot_Sya_407_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 82, "Dot_Sya_407_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 83, "Dot_Sya_407_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 84, "Dot_Sya_407_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 85, "Dot_Sya_407_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 86, "Dot_Sya_407_06.bmp", 0, stPaletteTemp );
//		tex->LoadTexture( 87, "Dot_Sya_003_07.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 88, "Dot_Sya_434_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 89, "Dot_Sya_434_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 90, "Dot_Sya_434_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 91, "Dot_Sya_434_04.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 100, "Dot_Sya_419_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 101, "Dot_Sya_419_02.bmp", 0, stPaletteTemp );

		tex->LoadTexture( 102, "Dot_Sya_420_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 103, "Dot_Sya_420_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 104, "Dot_Sya_420_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 105, "Dot_Sya_420_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 106, "Dot_Sya_420_05.bmp", 0, stPaletteTemp );
		// damage aerial
		tex->LoadTexture( 110, "Dot_Sya_203_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 111, "Dot_Sya_203_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 112, "Dot_Sya_204_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 113, "Dot_Sya_204_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 114, "Dot_Sya_204_03.bmp", 0, stPaletteTemp );
		// down
		tex->LoadTexture( 115, "Dot_Sya_601_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 116, "Dot_Sya_601_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 117, "Dot_Sya_601_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 118, "Dot_Sya_601_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 119, "Dot_Sya_601_05.bmp", 0, stPaletteTemp );

		// crouch attack high
		tex->LoadTexture( 120, "Dot_Sya_432_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 121, "Dot_Sya_432_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 122, "Dot_Sya_432_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 123, "Dot_Sya_432_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 124, "Dot_Sya_432_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 125, "Dot_Sya_432_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 126, "Dot_Sya_432_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 127, "Dot_Sya_432_08.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 128, "Dot_Sya_432_09.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 129, "Dot_Sya_432_10.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 130, "Dot_Sya_432_11.bmp", 0, stPaletteTemp );

		// guard
		tex->LoadTexture( 131, "Dot_Sya_032_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 132, "Dot_Sya_032_02.bmp", 0, stPaletteTemp );
		// crouch guard
		tex->LoadTexture( 133, "Dot_Sya_048_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 134, "Dot_Sya_048_02.bmp", 0, stPaletteTemp );
		// jump guard
		tex->LoadTexture( 135, "Dot_Sya_050_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 136, "Dot_Sya_050_02.bmp", 0, stPaletteTemp );

		// air damage
		tex->LoadTexture( 140, "Dot_Sya_210_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 141, "Dot_Sya_210_02.bmp", 0, stPaletteTemp );

		// big damage
		tex->LoadTexture( 145, "Dot_Sya_202_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 146, "Dot_Sya_202_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 147, "Dot_Sya_202_03.bmp", 0, stPaletteTemp );

		// special 1
		tex->LoadTexture( 150, "Dot_Sya_801_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 151, "Dot_Sya_801_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 152, "Dot_Sya_801_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 153, "Dot_Sya_801_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 154, "Dot_Sya_801_05.bmp", 0, stPaletteTemp );

		// jump dush
		tex->LoadTexture( 155, "Dot_Sya_308_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 156, "Dot_Sya_308_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 157, "Dot_Sya_308_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 158, "Dot_Sya_308_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 159, "Dot_Sya_308_05.bmp", 0, stPaletteTemp );

		// throw
		tex->LoadTexture( 160, "Dot_Sya_414_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 161, "Dot_Sya_414_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 162, "Dot_Sya_414_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 163, "Dot_Sya_414_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 164, "Dot_Sya_414_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 165, "Dot_Sya_414_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 166, "Dot_Sya_414_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 167, "Dot_Sya_414_08.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 168, "Dot_Sya_414_09.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 169, "Dot_Sya_414_10.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 170, "Dot_Sya_414_11.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 171, "Dot_Sya_414_12.bmp", 0, stPaletteTemp );

		// throw miss
		tex->LoadTexture( 173, "Dot_Sya_413_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 174, "Dot_Sya_413_02.bmp", 0, stPaletteTemp );

		// jump ex
		tex->LoadTexture( 175, "Dot_Sya_421_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 176, "Dot_Sya_421_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 177, "Dot_Sya_421_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 178, "Dot_Sya_421_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 179, "Dot_Sya_421_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 180, "Dot_Sya_421_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 181, "Dot_Sya_421_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 182, "Dot_Sya_421_08.bmp", 0, stPaletteTemp );

		// get up
		tex->LoadTexture( 185, "Dot_Sya_602_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 186, "Dot_Sya_602_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 187, "Dot_Sya_602_03.bmp", 0, stPaletteTemp );

		// special 2
		tex->LoadTexture( 190, "Dot_Sya_802_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 191, "Dot_Sya_802_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 192, "Dot_Sya_802_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 193, "Dot_Sya_802_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 194, "Dot_Sya_802_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 195, "Dot_Sya_802_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 196, "Dot_Sya_802_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 197, "Dot_Sya_802_08.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 198, "Dot_Sya_802_09.bmp", 0, stPaletteTemp );

		// special 3
		tex->LoadTexture( 200, "Dot_Sya_803_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 201, "Dot_Sya_803_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 202, "Dot_Sya_803_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 203, "Dot_Sya_803_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 204, "Dot_Sya_803_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 205, "Dot_Sya_803_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 206, "Dot_Sya_803_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 207, "Dot_Sya_803_08.bmp", 0, stPaletteTemp );

		// blow down
		tex->LoadTexture( 210, "Dot_Sya_202_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 211, "Dot_Sya_202_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 212, "Dot_Sya_202_03.bmp", 0, stPaletteTemp );

		// wall bound
		tex->LoadTexture( 214, "Dot_Sya_201_01.bmp", 0, stPaletteTemp );

		// recover
		tex->LoadTexture( 220, "Dot_Sya_208_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 221, "Dot_Sya_208_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 222, "Dot_Sya_208_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 223, "Dot_Sya_208_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 224, "Dot_Sya_208_05.bmp", 0, stPaletteTemp );

		// crouch ex
		tex->LoadTexture( 230, "Dot_Sya_017_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 231, "Dot_Sya_017_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 232, "Dot_Sya_017_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 233, "Dot_Sya_017_04.bmp", 0, stPaletteTemp );

		// s.p 
		tex->LoadTexture( 240, "Dot_Sya_903_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 241, "Dot_Sya_903_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 242, "Dot_Sya_903_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 243, "Dot_Sya_903_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 244, "Dot_Sya_903_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 245, "Dot_Sya_903_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 246, "Dot_Sya_903_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 247, "Dot_Sya_903_08.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 248, "Dot_Sya_903_09.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 249, "Dot_Sya_903_10.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 250, "Dot_Sya_903_11.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 251, "Dot_Sya_903_12.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 252, "Dot_Sya_903_13.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 253, "Dot_Sya_903_14.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 254, "Dot_Sya_903_15.bmp", 0, stPaletteTemp );

		// crouch
		tex->LoadTexture( 255, "Dot_Sya_030_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 256, "Dot_Sya_030_02.bmp", 0, stPaletteTemp );

		// midle 
		tex->LoadTexture( 260, "Dot_Sya_003_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 261, "Dot_Sya_003_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 262, "Dot_Sya_003_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 263, "Dot_Sya_003_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 264, "Dot_Sya_003_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 265, "Dot_Sya_003_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 266, "Dot_Sya_003_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 267, "Dot_Sya_003_04.bmp", 0, stPaletteTemp );

		break;

	case TEXTURE_NO_EFF_GUARD_CANCEL:
	// 
		tex->LoadTexture( 0, "GuardCancel1_0001.png", 1 );
		tex->LoadTexture( 1, "GuardCancel1_0002.png", 1 );
		tex->LoadTexture( 2, "GuardCancel1_0003.png", 1 );
		tex->LoadTexture( 3, "GuardCancel1_0004.png", 1 );
		tex->LoadTexture( 4, "GuardCancel1_0005.png", 1 );
		tex->LoadTexture( 5, "GuardCancel1_0006.png", 1 );
		tex->LoadTexture( 6, "GuardCancel1_0007.png", 1 );
		tex->LoadTexture( 7, "GuardCancel1_0008.png", 1 );
		tex->LoadTexture( 8, "GuardCancel1_0009.png", 1 );
		tex->LoadTexture( 9, "GuardCancel1_0010.png", 1 );
		tex->LoadTexture( 10, "GuardCancel1_0010.png", 1 );
		tex->LoadTexture( 11, "GuardCancel1_0011.png", 1 );
		tex->LoadTexture( 12, "GuardCancel1_0012.png", 1 );
		tex->LoadTexture( 13, "GuardCancel1_0013.png", 1 );
		tex->LoadTexture( 14, "GuardCancel1_0014.png", 1 );
		tex->LoadTexture( 15, "GuardCancel1_0015.png", 1 );
		tex->LoadTexture( 16, "GuardCancel1_0016.png", 1 );
		tex->LoadTexture( 17, "GuardCancel1_0017.png", 1 );
		tex->LoadTexture( 18, "GuardCancel1_0018.png", 1 );
		tex->LoadTexture( 19, "GuardCancel1_0019.png", 1 );
		tex->LoadTexture( 20, "GuardCancel1_0020.png", 1 );
		tex->LoadTexture( 21, "GuardCancel1_0021.png", 1 );
		tex->LoadTexture( 22, "GuardCancel1_0022.png", 1 );
		tex->LoadTexture( 23, "GuardCancel1_0023.png", 1 );
		tex->LoadTexture( 24, "GuardCancel1_0024.png", 1 );
		tex->LoadTexture( 25, "GuardCancel1_0025.png", 1 );
		tex->LoadTexture( 26, "GuardCancel1_0026.png", 1 );
		tex->LoadTexture( 27, "GuardCancel1_0027.png", 1 );
		tex->LoadTexture( 28, "GuardCancel1_0028.png", 1 );
		tex->LoadTexture( 29, "GuardCancel1_0029.png", 1 );
		tex->LoadTexture( 30, "GuardCancel1_0030.png", 1 );
		tex->LoadTexture( 31, "GuardCancel1_0031.png", 1 );
		tex->LoadTexture( 32, "GuardCancel1_0032.png", 1 );
		tex->LoadTexture( 33, "GuardCancel1_0033.png", 1 );
		tex->LoadTexture( 34, "GuardCancel1_0034.png", 1 );
		tex->LoadTexture( 35, "GuardCancel1_0035.png", 1 );
		tex->LoadTexture( 36, "GuardCancel1_0036.png", 1 );
		tex->LoadTexture( 37, "GuardCancel1_0037.png", 1 );
		tex->LoadTexture( 38, "GuardCancel1_0038.png", 1 );
		tex->LoadTexture( 39, "GuardCancel1_0039.png", 1 );
		tex->LoadTexture( 40, "GuardCancel1_0040.png", 1 );
		tex->LoadTexture( 41, "GuardCancel1_0041.png", 1 );
		tex->LoadTexture( 42, "GuardCancel1_0042.png", 1 );
		tex->LoadTexture( 43, "GuardCancel1_0043.png", 1 );
		tex->LoadTexture( 44, "GuardCancel1_0044.png", 1 );
		tex->LoadTexture( 45, "GuardCancel1_0045.png", 1 );
		break;

	case TEXTURE_NO_SYS_TIME:
		tex->LoadTexture( 0, "自在式_TIME_nontime_out.png" );
		tex->LoadTexture( 1, "自在式_TIME_nontime_in.png" );
		tex->LoadTexture( 2, "タイムフォント0.png" );
		tex->LoadTexture( 3, "タイムフォント1.png" );
		tex->LoadTexture( 4, "タイムフォント2.png" );
		tex->LoadTexture( 5, "タイムフォント3.png" );
		tex->LoadTexture( 6, "タイムフォント4.png" );
		tex->LoadTexture( 7, "タイムフォント5.png" );
		tex->LoadTexture( 8, "タイムフォント6.png" );
		tex->LoadTexture( 9, "タイムフォント7.png" );
		tex->LoadTexture( 10, "タイムフォント8.png" );
		tex->LoadTexture( 11, "タイムフォント9.png" );
		tex->LoadTexture( 12, "frame_p_gauge_center.png" );
		break;

	case TEXTURE_NO_STA_RURIDAN:
		tex->LoadTexture( 0, "玻璃壇.jpg" ,1);
		tex->LoadTexture( 1, "玻璃壇光.jpg" ,1);
		break;

	case TEXTURE_NO_SYS_HP:
//		tex->LoadTexture( 0, "体力ゲージ枠.png", 0, NULL, 0xFF000000 );
//		tex->LoadTexture( 1, "体力ゲージ身.png", 0, NULL, 0xFF000000 );
//		tex->LoadTexture( 2, "back_white.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 0, "frame_p_gauge_side.png", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 1, "p_gauge_normal.png", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 2, "p_gauge_empty.png", 0, NULL, 0xFF000000 );
		break;

	case TEXTURE_NO_SYS_SP:
		tex->LoadTexture(  0, "frame_s_gauge.png", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  1, "s_gauge_empty.png", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  2, "s_gauge_normal.png", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  3, "s_gauge_full.png", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  5, "SystemGra_001_01.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  6, "SystemGra_001_02.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  7, "SystemGra_001_03.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  8, "SystemGra_001_04.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture(  9, "SystemGra_001_05.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 10, "SystemGra_002_01.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 11, "SystemGra_002_02.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 12, "SystemGra_002_03.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 13, "SystemGra_002_04.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 14, "SystemGra_002_05.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 15, "SystemGra_003_01.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 16, "SystemGra_003_02.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 17, "SystemGra_003_03.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 18, "SystemGra_003_04.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 19, "SystemGra_003_05.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 20, "SystemGra_004_01.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 21, "SystemGra_004_02.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 22, "SystemGra_004_03.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 23, "SystemGra_004_04.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 24, "SystemGra_004_05.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 25, "SystemGra_005_01.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 26, "SystemGra_005_02.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 27, "SystemGra_005_03.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 28, "SystemGra_005_04.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 29, "SystemGra_005_05.bmp", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 30, "存在ゲージ枠.png", 0, NULL, 0xFF000000 );
		tex->LoadTexture( 31, "存在ゲージ身.png", 0, NULL, 0xFF000000 );
		break;

	case TEXTURE_NO_SYS_BATTLE_MENU:
		tex->LoadTexture( 0, "back_black.PNG", 0, NULL, 0x00000000 );
		tex->LoadTexture( 1, "BattleMenuItem1.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 2, "BattleMenuItem2.PNG", 0, NULL, 0xff000000 );
//		tex->LoadTexture( 3, "BattleMenuItem2.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 4, "BattleMenuItem4.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 5, "BattleMenuItem5.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 6, "BattleMenuItem6.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 7, "BattleMenuItem7.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 8, "BattleMenuItem8.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 9, "BattleMenuItem9.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 10, "BattleMenuItem10.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 11, "BattleMenuItem1_1.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 12, "BattleMenuItem1_2.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 13, "BattleMenuItem1_3.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 14, "BattleMenuItem1_4.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 21, "BattleMenuItem5_1.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 22, "BattleMenuItem5_2.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 23, "BattleMenuItem5_3.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 31, "BattleMenuItem6_1.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 32, "BattleMenuItem6_2.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 33, "BattleMenuItem6_3.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 41, "BattleMenuItem7_1.PNG", 0, NULL, 0xff000000 );
		tex->LoadTexture( 42, "BattleMenuItem7_2.PNG", 0, NULL, 0xff000000 );
		break;

	case TEXTURE_NO_EFF_HIT_ZAN1:
	// 
		tex->LoadTexture( 0, "ZAN.png" );
		tex->LoadTexture( 1, "Hit0002.png" );
		tex->LoadTexture( 2, "Hit0003.png" );
		tex->LoadTexture( 3, "Hit0004.png" );
		tex->LoadTexture( 4, "Hit0005.png" );
		tex->LoadTexture( 5, "Hit0006.png" );
		break;

	case TEXTURE_NO_SYS_COMBO:
		tex->LoadTexture( 0, "combo_font_a_0.png" );
		tex->LoadTexture( 1, "combo_font_a_1.png" );
		tex->LoadTexture( 2, "combo_font_a_2.png" );
		tex->LoadTexture( 3, "combo_font_a_3.png" );
		tex->LoadTexture( 4, "combo_font_a_4.png" );
		tex->LoadTexture( 5, "combo_font_a_5.png" );
		tex->LoadTexture( 6, "combo_font_a_6.png" );
		tex->LoadTexture( 7, "combo_font_a_7.png" );
		tex->LoadTexture( 8, "combo_font_a_8.png" );
		tex->LoadTexture( 9, "combo_font_a_9.png" );
		tex->LoadTexture( 10, "combo_font_hit.png" );
		break;

	case TEXTURE_NO_EFF_SHA802_1:
		tex->LoadTexture( 0, "shana_802_eff_0001.png" );
		tex->LoadTexture( 1, "shana_802_eff_0002.png" );
		tex->LoadTexture( 2, "shana_802_eff_0003.png" );
		tex->LoadTexture( 3, "shana_802_eff_0004.png" );
		tex->LoadTexture( 4, "shana_802_eff_0005.png" );
		tex->LoadTexture( 5, "shana_802_eff_0006.png" );
		break;

	case TEXTURE_NO_EFF_SYOUGEKI:
		tex->LoadTexture( 0, "syougekiha.png" );
		break;

	case TEXTURE_NO_SYS_BACK_WHITE:
		tex->LoadTexture( 0, "back_white.bmp" );
		break;

	case TEXTURE_NO_EFF_SHA308:
		tex->LoadTexture( 0, "shana_308_eff001.png" );
		tex->LoadTexture( 1, "shana_308_eff002.png" );
		tex->LoadTexture( 2, "shana_308_eff003.png" );
		tex->LoadTexture( 3, "shana_308_eff004.png" );
		tex->LoadTexture( 4, "shana_308_eff005.png" );
		tex->LoadTexture( 5, "shana_308_eff006.png" );
		tex->LoadTexture( 6, "shana_308_eff007.png" );
		tex->LoadTexture( 7, "shana_308_eff008.png" );
		tex->LoadTexture( 10, "shana_308_eff101.png" );
		tex->LoadTexture( 11, "shana_308_eff102.png" );
		tex->LoadTexture( 12, "shana_308_eff103.png" );
		tex->LoadTexture( 13, "shana_308_eff104.png" );
		tex->LoadTexture( 14, "shana_308_eff105.png" );
		tex->LoadTexture( 15, "shana_308_eff106.png" );
		tex->LoadTexture( 16, "shana_308_eff107.png" );
		tex->LoadTexture( 17, "shana_308_eff108.png" );
		break;

	case TEXTURE_NO_EFF_HIT_ZAN2:
		tex->LoadTexture( 0, "ZAN02.png" );
		break;

	case TEXTURE_NO_EFF_GUARD:
		tex->LoadTexture( 0, "Guard10100q.bmp" );
		break;

	case TEXTURE_NO_EFF_TAIKUUTI:
		tex->LoadTexture( 0, "空対地EF3-.png" );
		break;

	case TEXTURE_NO_EFF_SHA303_1:
		tex->LoadTexture( 0, "shana_303_eff001.png" );
		tex->LoadTexture( 1, "shana_303_eff002.png" );
		tex->LoadTexture( 2, "shana_303_eff003.png" );
		tex->LoadTexture( 3, "shana_303_eff004.png" );
		tex->LoadTexture( 4, "shana_303_eff005.png" );
		tex->LoadTexture( 5, "shana_303_eff006.png" );
		tex->LoadTexture( 6, "shana_303_eff007.png" );
		tex->LoadTexture( 7, "shana_303_eff008.png" );
		tex->LoadTexture( 8, "shana_303_eff009.png" );
		tex->LoadTexture( 9, "shana_303_eff010.png" );
		tex->LoadTexture( 10, "shana_303_eff011.png" );
		tex->LoadTexture( 11, "shana_303_eff012.png" );
		tex->LoadTexture( 12, "shana_303_eff013.png" );
		tex->LoadTexture( 13, "shana_303_eff014.png" );
		tex->LoadTexture( 15, "shana_303_eff101.png" );
		tex->LoadTexture( 16, "shana_303_eff102.png" );
		tex->LoadTexture( 17, "shana_303_eff103.png" );
		tex->LoadTexture( 18, "shana_303_eff104.png" );
		tex->LoadTexture( 19, "shana_303_eff105.png" );
		tex->LoadTexture( 20, "shana_303_eff106.png" );
		tex->LoadTexture( 21, "shana_303_eff107.png" );
		tex->LoadTexture( 22, "shana_303_eff108.png" );
		tex->LoadTexture( 23, "shana_303_eff109.png" );
		tex->LoadTexture( 24, "shana_303_eff110.png" );
		tex->LoadTexture( 25, "shana_303_eff111.png" );
		tex->LoadTexture( 26, "shana_303_eff112.png" );
		tex->LoadTexture( 27, "shana_303_eff113.png" );
		tex->LoadTexture( 28, "shana_303_eff114.png" );
		break;

	case TEXTURE_NO_EFF_SHA_AIRDASH_FRONT:
		tex->LoadTexture( 0, "ef_Airdash_front.png" );
		tex->LoadTexture( 1, "ef_Airdash_front_back.png" );
	break;

	case TEXTURE_NO_EFF_SHA408:
		tex->LoadTexture( 0, "shana_408_eff001.png" );
		tex->LoadTexture( 1, "shana_408_eff002.png" );
		tex->LoadTexture( 2, "shana_408_eff003.png" );
		tex->LoadTexture( 3, "shana_408_eff004.png" );
		tex->LoadTexture( 4, "shana_408_eff005.png" );
		tex->LoadTexture( 5, "shana_408_eff006.png" );
		tex->LoadTexture( 6, "shana_408_eff007.png" );
	break;

	case TEXTURE_NO_EFF_JUMP_LANDING:
		tex->LoadTexture( 0, "Jump_landing0009q.bmp" );
		tex->LoadTexture( 1, "Jump_landing0010q.bmp" );
		tex->LoadTexture( 2, "Jump_landing0012q.bmp" );
		tex->LoadTexture( 3, "Jump_landing0013q.bmp" );
		tex->LoadTexture( 4, "Jump_landing0014q.bmp" );
		tex->LoadTexture( 5, "Jump_landing0015q.bmp" );
		tex->LoadTexture( 6, "Jump_landing0016q.bmp" );
		tex->LoadTexture( 7, "Jump_landing0017q.bmp" );
		tex->LoadTexture( 8, "Jump_landing0018q.bmp" );
		tex->LoadTexture( 9, "Jump_landing0019q.bmp" );
		tex->LoadTexture( 10, "Jump_landing0020q.bmp" );
	break;

	case TEXTURE_NO_EFF_SHA802_2:
		tex->LoadTexture( 0, "shana_802_eff_02_0001.png" );
		tex->LoadTexture( 1, "shana_802_eff_02_0002.png" );
		tex->LoadTexture( 2, "shana_802_eff_02_0003.png" );
		tex->LoadTexture( 3, "shana_802_eff_02_0004.png" );
		tex->LoadTexture( 4, "shana_802_eff_02_0005.png" );
		tex->LoadTexture( 5, "shana_802_eff_02_0006.png" );
		tex->LoadTexture( 6, "shana_802_eff_02_0007.png" );
		tex->LoadTexture( 7, "shana_802_eff_02_0008.png" );
		tex->LoadTexture( 8, "shana_802_eff_02_0009.png" );
		tex->LoadTexture( 9, "shana_802_eff_02_0010.png" );
		tex->LoadTexture( 10, "shana_802_eff_02_0011.png" );
		tex->LoadTexture( 11, "shana_802_eff_02_0012.png" );
		tex->LoadTexture( 12, "shana_802_eff_02_0013.png" );
		tex->LoadTexture( 13, "shana_802_eff_02_0014.png" );
		tex->LoadTexture( 14, "shana_802_eff_02_0015.png" );
		tex->LoadTexture( 15, "shana_802_eff_02_0016.png" );
		tex->LoadTexture( 16, "shana_802_eff_02_0017.png" );
		tex->LoadTexture( 17, "shana_802_eff_02_0018.png" );
		tex->LoadTexture( 18, "shana_802_eff_02_0019.png" );
		tex->LoadTexture( 19, "shana_802_eff_02_0020.png" );
		tex->LoadTexture( 20, "shana_802_eff_02_0021.png" );
		tex->LoadTexture( 21, "shana_802_eff_02_0022.png" );
		tex->LoadTexture( 22, "shana_802_eff_02_0023.png" );
		tex->LoadTexture( 23, "shana_802_eff_02_0024.png" );
		tex->LoadTexture( 24, "shana_802_eff_02_0025.png" );
		tex->LoadTexture( 25, "shana_802_eff_02_0026.png" );
		tex->LoadTexture( 26, "shana_802_eff_02_0027.png" );
		tex->LoadTexture( 27, "shana_802_eff_02_0028.png" );
		tex->LoadTexture( 28, "shana_802_eff_02_0029.png" );
		tex->LoadTexture( 29, "shana_802_eff_02_0030.png" );
	break;

	case TEXTURE_NO_EFF_SHA303_2:
		tex->LoadTexture( 0, "shana_303_eff_001.png" );
		tex->LoadTexture( 1, "shana_303_eff_002.png" );
		tex->LoadTexture( 2, "shana_303_eff_003.png" );
		tex->LoadTexture( 3, "shana_303_eff_004.png" );
	break;

	case TEXTURE_NO_EFF_HIT_UPPER:
		tex->LoadTexture( 0, "hit_Upper_0001.png" );
		tex->LoadTexture( 1, "hit_Upper_0002.png" );
		tex->LoadTexture( 2, "hit_Upper_0003.png" );
		tex->LoadTexture( 3, "hit_Upper_0004.png" );
		tex->LoadTexture( 4, "hit_Upper_0005.png" );
		tex->LoadTexture( 5, "hit_Upper_0006.png" );
	break;

	case TEXTURE_NO_EFF_HIT_LINE:
		tex->LoadTexture( 0, "hit_line_0001.png" );
	break;

	// タイトル画面
	case TEXTURE_NO_SYS_TITLE_ZAN:
		tex->LoadTexture( 0, "zan.bmp" );
	break;

	case TEXTURE_NO_SYS_TITLE_ZAN_ANIIME:
		tex->LoadTexture( 0, "title_zan_anime_0001.png" );
		tex->LoadTexture( 1, "title_zan_anime_0002.png" );
		tex->LoadTexture( 2, "title_zan_anime_0003.png" );
		tex->LoadTexture( 3, "title_zan_anime_0004.png" );
		tex->LoadTexture( 4, "title_zan_anime_0005.png" );
		tex->LoadTexture( 5, "title_zan_anime_0006.png" );
		tex->LoadTexture( 6, "title_zan_anime_0007.png" );
		tex->LoadTexture( 7, "title_zan_anime_0008.png" );
		tex->LoadTexture( 8, "title_zan_anime_0009.png" );
		tex->LoadTexture( 9, "title_zan_anime_0010.png" );
		tex->LoadTexture( 10, "title_zan_anime_0011.png" );
		tex->LoadTexture( 11, "title_zan_anime_0012.png" );
		tex->LoadTexture( 12, "title_zan_anime_0013.png" );
		tex->LoadTexture( 13, "title_zan_anime_0014.png" );
		tex->LoadTexture( 14, "title_zan_anime_0015.png" );
		tex->LoadTexture( 15, "title_zan_anime_0016.png" );
		tex->LoadTexture( 16, "zan.bmp" );
		tex->LoadTexture( 17, "Title.png" );
		tex->LoadTexture( 18, "back_white.bmp" );
		tex->LoadTexture( 19, "TitleB.png" );
	break;

	case TEXTURE_NO_SYS_CHILD_LOGO:
		tex->LoadTexture( 0, "Flash.png" );
		tex->LoadTexture( 1, "TitleB.png" );
		tex->LoadTexture( 2, "Chilha_Logo_b.png" );
	break;

	case TEXTURE_NO_SYS_TITLE_MENU:
		tex->LoadTexture( 0, "ARCADE_a.png" );
		tex->LoadTexture( 1, "VERSUS_a.png" );
		tex->LoadTexture( 2, "TRAINING_a.png" );
		tex->LoadTexture( 3, "OPTION_a.png" );
		tex->LoadTexture( 4, "EXIT_a.png" );
		tex->LoadTexture( 5, "ARCADE_b.png" );
		tex->LoadTexture( 6, "VERSUS_b.png" );
		tex->LoadTexture( 7, "TRAINING_b.png" );
		tex->LoadTexture( 8, "OPTION_b.png" );
		tex->LoadTexture( 9, "EXIT_b.png" );
		tex->LoadTexture( 10, "COPYRIGHT.png" );
		tex->LoadTexture( 11, "VER.png" );
		tex->LoadTexture( 12, "back_black.PNG" );
	break;

	case TEXTURE_NO_SYS_TITLE_REIJI_MAIGO:
		tex->LoadTexture( 0, "back_white.bmp" );
		tex->LoadTexture( 1, "REIJI-MAIGO_Grow.png" );
	break;

	case TEXTURE_NO_CHARA_SELECT_MENU:
		tex->LoadTexture( 0, "CharaSel_Shana.bmp" );
		tex->LoadTexture( 1, "CharaSel_Will.bmp" );
	break;

	case TEXTURE_NO_CHARA_SELECT_BACK:
		tex->LoadTexture( 0, "obi.bmp" );
		tex->LoadTexture( 1, "SelectChar_Sya001_01.bmp" );
		tex->LoadTexture( 2, "SelectChar_Wil001_01.bmp" );
	break;

	case TEXTURE_NO_CHARA_SELECT_CUTIN:
		tex->LoadTexture( 0, "SelectChar_Sya001_01.png",0,0 );
		tex->LoadTexture( 1, "SelectChar_Wil001_01.png",0,0 );
	break;

	case TEXTURE_NO_CHARA_SELECT_PUCHI:
		stPaletteTemp = NULL;
		if( param1 == 1 ){
			hReadFile = NULL ;
			hReadFile = CreateFile( "shana2p.act" ,GENERIC_READ,0,NULL,
								OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if( hReadFile == INVALID_HANDLE_VALUE ){
				MessageBox(NULL,"ファイルなし　パレット","file not found",MB_OK);
				stPaletteTemp = NULL;
			}
			else{
		for( int i = 0 ; i < 255 ; i++ ){
					// データ読み込み
					ReadFile( hReadFile , &stPalette[i] , sizeof( RGBQUAD ) , &nFileSize , NULL );
				}
				CloseHandle( hReadFile );
				stPaletteTemp = stPalette ;
			}
		}

		tex->LoadTexture( 0, "Dot_Sya_001_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 1, "Dot_Sya_001_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 2, "Dot_Sya_001_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 3, "Dot_Sya_001_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 4, "Dot_Sya_001_05.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 5, "Dot_Sya_001_06.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 6, "Dot_Sya_001_07.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 7, "Dot_Sya_022_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 8, "Dot_Sya_022_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 9, "Dot_Sya_022_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 10, "Dot_Sya_022_04.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 11, "Dot_Sya_002_01.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 12, "Dot_Sya_002_02.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 13, "Dot_Sya_002_03.bmp", 0, stPaletteTemp );
		tex->LoadTexture( 14, "Dot_Sya_002_04.bmp", 0, stPaletteTemp );

		stPaletteTemp = NULL;
		if( param1 == 1 ){
			hReadFile = NULL ;
			hReadFile = CreateFile( "shana2p.act" ,GENERIC_READ,0,NULL,
								OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if( hReadFile == INVALID_HANDLE_VALUE ){
				MessageBox(NULL,"ファイルなし　パレット","file not found",MB_OK);
				stPaletteTemp = NULL;
			}
			else{
				for( int i = 0 ; i < 255 ; i++ ){
					// データ読み込み
					ReadFile( hReadFile , &stPalette[i] , sizeof( RGBQUAD ) , &nFileSize , NULL );
				}
				CloseHandle( hReadFile );
				stPaletteTemp = stPalette ;
			}
		}
		// nutral
		tex->LoadTexture( 10, "Dot_Wil_105_001.bmp", 0 );
		tex->LoadTexture( 11, "Dot_Wil_105_002.bmp", 0 );
		tex->LoadTexture( 12, "Dot_Wil_105_003.bmp", 0 );
		tex->LoadTexture( 13, "Dot_Wil_105_004.bmp", 0 );
		tex->LoadTexture( 14, "Dot_Wil_105_005.bmp", 0 );
		tex->LoadTexture( 15, "Dot_Wil_105_006.bmp", 0 );
		tex->LoadTexture( 16, "Dot_Wil_105_007.bmp", 0 );
		tex->LoadTexture( 17, "Dot_Wil_105_008.bmp", 0 );
		break;
	}
}


//==============================================================
// アニメーションクラス管理
//==============================================================
CAnimationManager::CAnimationManager( )
{
	m_animeGroup	= new CAnimeSpec[101];
}

CAnimationManager::~CAnimationManager()
{
	delete []m_animeGroup;
//	delete m_animeGroup;
}

//
//  関数: GetAnimationNo( int GROUP_NO )
//
//  目的: アニメーションクラス番号取得
//
//  パラメータ:
//　　　　para1:アニメーションクラス番号
//　メモ：
//　　　
int CAnimationManager::GetAnimationNo( int no )
{
	return no;
/*	switch( no ){
		case TEXTUREGROUP_CHARACTOR:
			return 0;
			break;
		case 100:
			return 10;
			break;

		case 99:
			return 9;
			break;

		case 98:
			return 8;
			break;

		case 97:
			return 7;
			break;

		case 96:
			return 6;
			break;

		case 95:
			return 19;
			break;

		case 94:
			return 5;
			break;

		case 93:
			return 18;
			break;

		default :
			return no;
			break;
	}
*/
}

//
//  関数: GetAnimation( int GROUP_NO )
//
//  目的: アニメーションクラス取得
//
//  パラメータ:
//　　　　para1:アニメーションクラス番号
//　メモ：
//　　　
CAnimeSpec* CAnimationManager::GetAnimation( int no )
{
	return &m_animeGroup[ GetAnimationNo(no) ];
}

//
//  関数: SetupAnimation( CAnime* anime, int CHARA_NO )
//
//  目的: アニメーションファイル読み込み
//
//  パラメータ:
//　　　　para1:読み込み先　アニメーションクラス
//　　　　para2:読み込み種別番号
//　メモ：
//　　　
void CAnimationManager::SetupAnimation( CAnimeSpec* anime, int no )
{
	int tmpx;
	int tmpy;

	int temp;
	switch( no ){
	case ANIME_NO_WIL:
		temp = DOT_WILL_ANIME_NUTRAL ;
		anime->CreateAction( temp, 8 );
		anime->GetActionData( temp )->SetMotionData( 0, 0, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 1, 1, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 2, 2, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 3, 3, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 4, 4, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 5, 5, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 6, 6, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 7, 7, 6, 90, 109 );
		anime->GetActionData( temp )->SetWoundData( 0, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 1, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 2, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 3, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 4, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 5, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 6, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 7, 0, -13, -70, 17, 0 );

		// walk_forward
		temp = DOT_WILL_ANIME_WALK_FORWARD;
		anime->CreateAction( temp, 8 );
		anime->GetActionData( temp )->SetMotionData( 0,15, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 1,16, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 2,17, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 3,18, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 4,19, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 5,20, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 6,21, 6, 90, 109 );
		anime->GetActionData( temp )->SetMotionData( 7,22, 6, 90, 109 );
		anime->GetActionData( temp )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 2, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 3, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 4, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 5, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 6, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 7, 0, -13, -50, 17, 0 );

		// walk_back
		temp = DOT_WILL_ANIME_WALK_BACK;
		anime->CreateAction( temp, 8 );
		anime->GetActionData( temp )->SetMotionData( 0, 23, 6, 90, 164 );
		anime->GetActionData( temp )->SetMotionData( 1, 24, 6, 90, 164 );
		anime->GetActionData( temp )->SetMotionData( 2, 25, 6, 90, 164 );
		anime->GetActionData( temp )->SetMotionData( 3, 26, 6, 90, 164 );
		anime->GetActionData( temp )->SetMotionData( 4, 27, 6, 90, 164 );
		anime->GetActionData( temp )->SetMotionData( 5, 28, 6, 90, 164 );
		anime->GetActionData( temp )->SetMotionData( 6, 29, 6, 90, 164 );
		anime->GetActionData( temp )->SetMotionData( 7, 30, 6, 90, 164 );
		anime->GetActionData( temp )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 2, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 3, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 4, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 5, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 6, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 7, 0, -13, -50, 17, 0 );

		// JUMP
		temp = DOT_WILL_ANIME_JUMP;
		anime->CreateAction( DOT_WILL_ANIME_JUMP, 1 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP )->SetMotionData( 0, 35, 1, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->CreateAction( DOT_WILL_ANIME_JUMP + 1, 2 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 1 )->SetMotionData( 0, 36, 2, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 1 )->SetMotionData( 1, 37, 2, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 1 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 1 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->CreateAction( DOT_WILL_ANIME_JUMP + 2 , 2 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 2 )->SetMotionData( 0, 38, 2, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 2 )->SetMotionData( 1, 39, 0, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 2 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 2 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->CreateAction( DOT_WILL_ANIME_JUMP + 3, 2 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 3 )->SetMotionData( 0, 40, 2, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 3 )->SetMotionData( 1, 41, 2, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 3 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 3 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->CreateAction( DOT_WILL_ANIME_JUMP + 4 , 1 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 4 )->SetMotionData( 0, 42, 1, 73, 116 );
		anime->GetActionData( DOT_WILL_ANIME_JUMP + 4 )->SetWoundData( 0, 0, -13, -50, 17, 0 );

		// BACK JUMP
		temp = DOT_WILL_ANIME_BACK_JUMP;
		anime->CreateAction( temp, 1 );
		anime->GetActionData( temp )->SetMotionData( 0, 35, 1, 73, 116 );
		anime->GetActionData( temp )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->CreateAction( temp + 1, 5 );
		anime->GetActionData( temp + 1 )->SetMotionData( 0, 47, 5, 83, 104 );
		anime->GetActionData( temp + 1 )->SetMotionData( 1, 43, 5, 83, 104 );
		anime->GetActionData( temp + 1 )->SetMotionData( 2, 44, 5, 83, 104 );
		anime->GetActionData( temp + 1 )->SetMotionData( 3, 45, 5, 83, 104 );
		anime->GetActionData( temp + 1 )->SetMotionData( 4, 46, 0, 83, 104 );
		anime->GetActionData( temp + 1 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp + 1 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp + 1 )->SetWoundData( 2, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp + 1 )->SetWoundData( 3, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp + 1 )->SetWoundData( 4, 0, -13, -50, 17, 0 );
		anime->CreateAction( temp + 2 , 2 );
		anime->GetActionData( temp + 2 )->SetMotionData( 0, 47, 2, 83, 104 );
		anime->GetActionData( temp + 2 )->SetMotionData( 1, 48, 2, 83, 104 );
		anime->GetActionData( temp + 2 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( temp + 2 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->CreateAction( temp + 3 , 1 );
		anime->GetActionData( temp + 3 )->SetMotionData( 0, 42, 1, 73, 116 );
		anime->GetActionData( temp + 3 )->SetWoundData( 0, 0, -13, -50, 17, 0 );

		// JUMP DUSH for
		temp = DOT_WILL_ANIME_JUMP_DUSH_FORWARD;
		anime->CreateAction( temp, 1 );
		anime->GetActionData( temp )->SetMotionData( 0, 50, 0, 56, 115 );
		temp = DOT_WILL_ANIME_JUMP_DUSH_FORWARD1;
		anime->CreateAction( temp , 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 51, 3, 56, 115 );
		anime->GetActionData( temp )->SetMotionData( 1, 52, 3, 56, 115 );

		// ATTACK LOW
		temp = DOT_WILL_ANIME_ATTACK_LOW;
		anime->CreateAction( temp, 3 );
		anime->GetActionData( temp )->SetMotionData( 0, 53, 3, 87, 110 );
		anime->GetActionData( temp )->SetMotionData( 1, 54, 3, 87, 110 );
		anime->GetActionData( temp )->SetMotionData( 2, 53, 3, 87, 110 );

		// DUSH back
		temp = DOT_WILL_ANIME_DUSH_BACK;
		anime->CreateAction( temp, 4 );
		anime->GetActionData( temp )->SetMotionData( 0, 31, 3, 62, 107 );
		anime->GetActionData( temp )->SetMotionData( 1, 32, 3, 62, 107 );
		anime->GetActionData( temp )->SetMotionData( 2, 33, 3, 62, 107 );
		anime->GetActionData( temp )->SetMotionData( 3, 34, 3, 62, 107 );

/*		// DOT_SHA002.(ATTACK_LOW)
		anime->CreateAction( 5, 7 );
		anime->GetActionData( 5 )->SetMotionData( 0, 35, 3, 84, 110 );
		anime->GetActionData( 5 )->SetMotionData( 1, 36, 3, 84, 110 );
		anime->GetActionData( 5 )->SetMotionData( 2, 37, 3, 84, 110 );
		anime->GetActionData( 5 )->SetMotionData( 3, 38, 3, 84, 110 );
		anime->GetActionData( 5 )->SetMotionData( 0, 39, 3, 84, 110 );
		anime->GetActionData( 5 )->SetMotionData( 1, 40, 3, 84, 110 );
		anime->GetActionData( 5 )->SetMotionData( 2, 41, 3, 84, 110 );

		// DOT_SHA002.(ATTACK_LOW)
/*		anime->CreateAction( 6, 3 );
		anime->GetActionData( 6 )->SetMotionData( 0, 42, 3, 52, 116 );
		anime->GetActionData( 6 )->SetMotionData( 1, 43, 3, 52, 116 );
		anime->GetActionData( 6 )->SetMotionData( 2, 44, 3, 52, 116 );

		// DOT_SHA002.(ATTACK_LOW)
		anime->CreateAction( 7, 3 );
		anime->GetActionData( 7 )->SetMotionData( 0, 45, 3, 62, 109 );
		anime->GetActionData( 7 )->SetMotionData( 1, 46, 3, 62, 109 );
		anime->GetActionData( 7 )->SetMotionData( 2, 47, 3, 62, 109 );

		// DOT_SHA002.(ATTACK_LOW)
		anime->CreateAction( 8, 15 );
		anime->GetActionData( 8 )->SetMotionData( 0, 45, 3, 62, 109 );
		anime->GetActionData( 8 )->SetMotionData( 1, 46, 3, 62, 109 );
		anime->GetActionData( 8 )->SetMotionData( 2, 47, 3, 62, 109 );
*/
		// 
        temp = DOT_WILL_ANIME_ATTACK_EX;
		anime->CreateAction( temp, 15 );
		anime->GetActionData( temp )->SetMotionData( 0, 56, 5, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 1, 57, 4, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 2, 58, 4, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 3, 59, 4, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 4, 60, 2, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 5, 61, 2, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 6, 62, 2, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 7, 63, 3, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 8, 64, 4, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 9, 65, 5, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 10, 66, 4, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 11, 67, 4, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 12, 68, 4, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 13, 69, 3, 126, 132 );
		anime->GetActionData( temp )->SetMotionData( 14, 70, 3, 126, 132 );
		anime->GetActionData( temp )->SetAttackData( 6, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( temp )->SetAttackData( 7, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( temp )->SetAttackData( 8, 0, -120, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( temp )->SetAttackData( 9, 0, -120, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( temp )->SetAttackData( 10, 0, -100, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( temp )->SetAttackSpec( 6, 100, 0, ENUM_ATTACK_TYPE_RESET  );
		anime->GetActionData( temp )->SetAttackSpec( 7, 100, 0, ENUM_ATTACK_TYPE_RESET  );
		anime->GetActionData( temp )->SetAttackSpec( 8, 100, 0, ENUM_ATTACK_TYPE_RESET  );
		anime->GetActionData( temp )->SetAttackSpec( 9, 100, 0, ENUM_ATTACK_TYPE_RESET  );
		anime->GetActionData( temp )->SetAttackSpec( 10, 100, 0, ENUM_ATTACK_TYPE_RESET  );

		// AttackHIGH
		temp = DOT_WILL_ANIME_ATTACK_HIGH;
		anime->CreateAction( temp, 6 );
		anime->GetActionData( temp )->SetMotionData( 0, 71, 4, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 1, 72, 3, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 2, 73, 2, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 3, 74, 3, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 4, 75, 4, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 5, 76, 5, 121, 113 );
		anime->GetActionData( temp )->SetAttackData( 2, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( temp )->SetAttackData( 3, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( temp )->SetAttackSpec( 2, 100, 0, 0  );
		anime->GetActionData( temp )->SetAttackSpec( 3, 100, 0, 0  );

		// Damage up
        temp = DOT_WILL_ANIME_DAMAGE;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 78, 2, 93, 109 );
		anime->GetActionData( temp )->SetMotionData( 1, 79, 0, 93, 109 );
		anime->GetActionData( temp )->SetWoundData( 0, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 1, 0, -13, -70, 17, 0 );

		// Damage down
        temp = DOT_WILL_ANIME_DAMAGE_DOWN;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 126, 30, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 0, 127, 30, 121, 113 );

		// CROUCH 
		temp = DOT_WILL_ANIME_CROUCH;
		anime->CreateAction( temp, 4 );
		anime->GetActionData( temp )->SetMotionData( 0, 80, 3, 86, 113 );
		anime->GetActionData( temp )->SetMotionData( 1, 81, 3, 86, 113 );
		anime->GetActionData( temp )->SetMotionData( 2, 82, 3, 86, 113 );
		anime->GetActionData( temp )->SetMotionData( 3, 83, 0, 86, 113 );

		// JUMP-DUSH back
		temp = DOT_WILL_ANIME_JUMP_DUSH_BACK;
		anime->CreateAction( temp, 3 );
		anime->GetActionData( temp )->SetMotionData( 0, 85, 3, 63, 111 );
		anime->GetActionData( temp )->SetMotionData( 1, 86, 3, 63, 111 );
		anime->GetActionData( temp )->SetMotionData( 2, 87, 0, 63, 111 );

		// ??? back
//		temp = DOT_WILL_ANIME_HATENA;
///		anime->CreateAction( temp, 2 );
//		anime->GetActionData( temp )->SetMotionData( 0, 88, 3, 63, 111 );
//		anime->GetActionData( temp )->SetMotionData( 1, 89, 3, 63, 111 );

		// crouch_attack_low
		temp = DOT_WILL_ANIME_CROUCH_ATTACK_LOW;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 90, 3, 83, 111 );
		anime->GetActionData( temp )->SetMotionData( 1, 91, 3, 83, 111 );
		
		anime->GetActionData(temp)->SetWoundData(0, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(1, 0, -30, -100, 30, 0);

		anime->GetActionData(temp)->SetAttackData(0, 0, -40, -40, -30, -30, ENUM_ATTACK_PROPERTY_LOW);
		anime->GetActionData(temp)->SetAttackData(1, 0, -40, -40, -30, -30, ENUM_ATTACK_PROPERTY_LOW);

		anime->GetActionData(temp)->SetAttackSpec(0, 100, 0, ENUM_ATTACK_TYPE_RESET);
		anime->GetActionData(temp)->SetAttackSpec(1, 100, 0, ENUM_ATTACK_TYPE_RESET);

		// crouch_damage
		temp = DOT_WILL_ANIME_CROUCH_DAMAGE;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 92, 3, 85, 111 );
		anime->GetActionData( temp )->SetMotionData( 1, 93, 3, 86, 111 );

		// DUSH
		temp = DOT_WILL_ANIME_DUSH_FORWARD;
		anime->CreateAction( temp, 6 );
		anime->GetActionData( temp )->SetMotionData( 0, 94, 5, 72, 111 );
		anime->GetActionData( temp )->SetMotionData( 1, 95, 5, 72, 111 );
		anime->GetActionData( temp )->SetMotionData( 2, 96, 5, 72, 111 );
		anime->GetActionData( temp )->SetMotionData( 3, 97, 5, 72, 111 );
		anime->GetActionData( temp )->SetMotionData( 4, 98, 5, 72, 111 );
		anime->GetActionData( temp )->SetMotionData( 5, 99, 5, 72, 111 );

		// damage aerial down
		temp = DOT_WILL_ANIME_DAMAGE_AERIAL_DOWN;
		anime->CreateAction( temp, 6 );
		anime->GetActionData( temp )->SetMotionData( 0, 100, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 1, 101, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 2, 102, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 3, 103, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 4, 104, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 5, 105, 0, 89, 75 );

		// damage blow down
		temp = DOT_WILL_ANIME_DAMAGE_BLOW_DOWN;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 107, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 1, 108, 3, 89, 75 );

		// recover
		temp = DOT_WILL_ANIME_RECOVER;
		anime->CreateAction( temp, 5 );
		anime->GetActionData( temp )->SetMotionData( 0, 110, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 1, 111, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 2, 112, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 3, 113, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 4, 114, 3, 89, 75 );

		// throw
		temp = DOT_WILL_ANIME_THROW;
		anime->CreateAction( temp, 7 );
		anime->GetActionData( temp )->SetMotionData( 0, 115, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 1, 116, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 2, 117, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 3, 118, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 4, 119, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 5, 120, 3, 89, 75 );
		anime->GetActionData( temp )->SetMotionData( 6, 121, 3, 89, 75 );

		// damage aerial up
		temp = 	DOT_WILL_ANIME_DAMAGE_AERIAL_UP;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 122, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 1, 123, 3, 84, 110 );

		// crouch attack low
		temp = DOT_WILL_ANIME_CROUCH_ATTACK_LOW;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData( 0, 124, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 1, 125, 3, 84, 110 );

		// Damage wall
        temp = DOT_WILL_ANIME_DAMAGE_WALL;
		anime->CreateAction( temp, 1 );
		anime->GetActionData( temp )->SetMotionData( 0, 128, 30, 121, 113 );

		// Jump Attack Middle
        temp = DOT_WILL_ANIME_JUMP_ATTACK_MID;
		anime->CreateAction( temp, 5 );
		anime->GetActionData( temp )->SetMotionData( 0, 130, 4, 118, 136 );
		anime->GetActionData( temp )->SetMotionData( 1, 131, 2, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 2, 132, 4, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 3, 133, 4, 121, 113 );
		anime->GetActionData( temp )->SetMotionData( 4, 134, 4, 121, 113 );
		// 食らい判定
		anime->GetActionData(temp)->SetWoundData(0, 0, -30, -80, 30, 30);
		anime->GetActionData(temp)->SetWoundData(1, 0, -30, -80, 30, 30);
		anime->GetActionData(temp)->SetWoundData(2, 0, -30, -80, 30, 30);
		anime->GetActionData(temp)->SetWoundData(3, 0, -30, -80, 30, 30);
		anime->GetActionData(temp)->SetWoundData(4, 0, -30, -80, 30, 30);
		// 攻撃判定
		anime->GetActionData(temp)->SetAttackData(1, 0, -10, -60, 0, -30, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(1, 1, -40, -70, -20, -50, ENUM_ATTACK_PROPERTY_HIGH);

		anime->GetActionData(temp)->SetAttackData(2, 0, -20, -60, 0, -30, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(2, 1, -40, -70, -20, -40, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(2, 2, -60, -80, -40, -50, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(2, 3, -90, -100, -60, -60, ENUM_ATTACK_PROPERTY_HIGH);

		anime->GetActionData(temp)->SetAttackData(3, 0, -20, -60, 0, -30, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(3, 1, -40, -70, -20, -40, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(3, 2, -60, -80, -40, -50, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(3, 3, -90, -100, -60, -60, ENUM_ATTACK_PROPERTY_HIGH);
		// ダメージなど
		anime->GetActionData(temp)->SetAttackSpec(1, 300, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(2, 300, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(3, 450, 0, 0);



		// crouch attack mid
		temp = DOT_WILL_ANIME_CROUCH_ATTACK_MID;
		anime->CreateAction( temp, 7 );
		anime->GetActionData( temp )->SetMotionData( 0, 140, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 1, 141, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 2, 142, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 3, 143, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 4, 144, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 5, 145, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 6, 146, 3, 84, 110 );
		// 食らい判定
		anime->GetActionData(temp)->SetWoundData(0, 0, -25, -70, 20, 0);
		anime->GetActionData(temp)->SetWoundData(1, 0, -25, -70, 20, 0);
		anime->GetActionData(temp)->SetWoundData(2, 0, -35, -70, 10, 0);
		anime->GetActionData(temp)->SetWoundData(3, 0, -45, -70, 0, 0);
		anime->GetActionData(temp)->SetWoundData(3, 1, -75, -40, -5, -30);
		anime->GetActionData(temp)->SetWoundData(4, 0, -45, -70, 0, 0);
		anime->GetActionData(temp)->SetWoundData(4, 0, -75, -43, -5, -33);
		anime->GetActionData(temp)->SetWoundData(5, 0, -35, -70, 10, 0);
		anime->GetActionData(temp)->SetWoundData(5, 1, -75, -43, -5, -33);
		anime->GetActionData(temp)->SetWoundData(6, 0, -25, -70, 20, 0);
		// 攻撃判定
		anime->GetActionData(temp)->SetAttackData(3, 0, -75, -40, -10, -30, ENUM_ATTACK_PROPERTY_MIDDLE);
		anime->GetActionData(temp)->SetAttackData(4, 0, -75, -43, -10, -33, ENUM_ATTACK_PROPERTY_MIDDLE);
		// ダメージなど
		anime->GetActionData(temp)->SetAttackSpec(3, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(4, 100, 0, 0);

		// jump attack low
		temp = DOT_WILL_ANIME_JUMP_ATTACK_LOW;
		anime->CreateAction( temp, 3 );
		anime->GetActionData( temp )->SetMotionData( 0, 147, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 1, 148, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 2, 149, 3, 84, 110 );
		// 食らい判定
		anime->GetActionData(temp)->SetWoundData(0, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(1, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(2, 0, -30, -100, 30, 0);
		// 攻撃判定
		anime->GetActionData(temp)->SetAttackData(0, 0, -78, -50, -24, -42, ENUM_ATTACK_PROPERTY_LOW);
		anime->GetActionData(temp)->SetAttackData(1, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_LOW);
		anime->GetActionData(temp)->SetAttackData(2, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_LOW);
		// ダメージなど
		anime->GetActionData(temp)->SetAttackSpec(0, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(1, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(2, 100, 0, 0);


		// special 1
		temp = DOT_WILL_ANIME_SPECIAL1;
		anime->CreateAction( temp, 17 );
		anime->GetActionData( temp )->SetMotionData( 0, 151, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 1, 152, 3, 84, 110);
		anime->GetActionData( temp )->SetMotionData( 2, 153, 3, 84, 110);
		anime->GetActionData( temp )->SetMotionData( 3, 154, 3, 84, 110);
		anime->GetActionData( temp )->SetMotionData( 4, 155, 3, 84, 110);
		anime->GetActionData( temp )->SetMotionData( 5, 156, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 6, 157, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 7, 158, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 8, 159, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 9, 160, 3, 84, 110);
		anime->GetActionData( temp )->SetMotionData(10, 161, 3, 84, 110);
		anime->GetActionData( temp )->SetMotionData(11, 162, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(12, 163, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(13, 164, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(14, 165, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(15, 166, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(16, 167, 3, 84, 110 );

		// ATTACK MID
		temp = DOT_WILL_ANIME_ATTACK_MID;
		anime->CreateAction( temp, 5 );
		anime->GetActionData( temp )->SetMotionData(0, 180, 3, 87, 113);
		anime->GetActionData( temp )->SetMotionData(1, 181, 3, 87, 113);
		anime->GetActionData( temp )->SetMotionData(2, 182, 3, 87, 113);
		anime->GetActionData( temp )->SetMotionData(3, 183, 3, 87, 113);
		anime->GetActionData( temp )->SetMotionData(4, 184, 3, 87, 113);

		// JUMP ATTACK HIGH
		temp = DOT_WILL_ANIME_JUMP_ATTACK_HIGH;
		anime->CreateAction( temp, 12 );

		anime->GetActionData(temp)->SetMotionData(0, 185, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(1, 186, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(2, 187, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(3, 188, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(4, 189, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(5, 190, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(6, 191, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(7, 192, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(8, 193, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(9, 194, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(10, 195, 3, 84, 110);
		anime->GetActionData(temp)->SetMotionData(11, 196, 3, 84, 110);
		// 食らい判定
		anime->GetActionData(temp)->SetWoundData(0, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(1, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(2, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(3, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(4, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(5, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(6, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(7, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(8, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(9, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(10, 0, -30, -100, 30, 0);
		anime->GetActionData(temp)->SetWoundData(11, 0, -30, -100, 30, 0);
		// 攻撃判定
		anime->GetActionData(temp)->SetAttackData(3, 0, -78, -50, -24, -42, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(4, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(5, 0, 0, 0, -80, 100, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(6, 0, 0, 0, -80, 100, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(7, 0, 50, 0, -30, 100, ENUM_ATTACK_PROPERTY_HIGH);
		anime->GetActionData(temp)->SetAttackData(8, 0, -78, -64, -24, -42, ENUM_ATTACK_PROPERTY_HIGH);
		// ダメージなど
		anime->GetActionData(temp)->SetAttackSpec(3, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(4, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(5, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(6, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(7, 100, 0, 0);
		anime->GetActionData(temp)->SetAttackSpec(8, 100, 0, 0);

		// THROW MISS
		temp = DOT_WILL_ANIME_THROW_MISS;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData(0, 198, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(1, 199, 3, 84, 110);

		// GUARD
		temp = DOT_WILL_ANIME_GUARD;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData(0, 200, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(1, 201, 3, 84, 110);

		// AIR GUARD
		temp = DOT_WILL_ANIME_AIR_GUARD;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData(0, 203, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(1, 204, 3, 84, 110);

		// CROUCH GUARD
		temp = DOT_WILL_ANIME_CROUCH_GUARD;
		anime->CreateAction( temp, 2 );
		anime->GetActionData( temp )->SetMotionData(0, 206, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData(1, 207, 3, 84, 110);

		// special 2
		temp = DOT_WILL_ANIME_SPECIAL2;
		anime->CreateAction( temp, 10 );
		anime->GetActionData( temp )->SetMotionData( 0, 210, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 1, 211, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 2, 212, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 3, 213, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 4, 214, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 5, 215, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 6, 216, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 7, 217, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 8, 218, 3, 84, 110 );
		anime->GetActionData( temp )->SetMotionData( 9, 219, 3, 84, 110 );

#if 0
		anime->GetActionData( 4 )->SetWoundDataAbs( 0, 0, 18, 25, 65, 107 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 1, 0, 17, 26, 69, 108 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 2, 0, 13, 23, 69, 109 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 3, 0, 28, 25, 72, 109 );
//		anime->GetActionData( 4 )->SetAttackData( 0, 0, -30, -50, 30, 50 );
//		anime->GetActionData( 4 )->SetAttackData( 1, 0, -30, -50, 30, 50 );
		anime->GetActionData( 4 )->SetAttackData( 2, 0, -40, -50, 0, 0, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( 4 )->SetAttackSpec( 2, 100, 0, 0 );
//		anime->GetActionData( 4 )->SetAttackData( 3, 0, -30, -50, 30, 50 );

		{
			// ATTACK_HIGH
			anime->CreateAction( 4, 11 );
			anime->GetActionData( 4 )->SetMotionData( 0, 15, 4, 54, 115 );
			anime->GetActionData( 4 )->SetMotionData( 1, 16, 4, 54, 115 );
			anime->GetActionData( 4 )->SetMotionData( 2, 17, 4, 54, 115 );
			anime->GetActionData( 4 )->SetMotionData( 3, 18, 4, 54, 115 );
			anime->GetActionData( 4 )->SetMotionData( 4, 19, 4, 54, 115 );
			anime->GetActionData( 4 )->SetMotionData( 5, 20, 4, 76, 115 );
			anime->GetActionData( 4 )->SetMotionData( 6, 21, 4, 122, 115 );
			anime->GetActionData( 4 )->SetMotionData( 7, 22, 6, 122, 115 );
			anime->GetActionData( 4 )->SetMotionData( 8, 23, 6, 122, 115 );
			anime->GetActionData( 4 )->SetMotionData( 9, 24, 12, 122, 115 );
			anime->GetActionData( 4 )->SetMotionData( 10, 25, 0, 98, 115 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 0, 0, 22, 32, 78, 119 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 1, 0, 25, 33, 70, 118 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 2, 0, 30, 32, 35+30, +86+32 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 3, 0, 31, 32, 31+31, +85+32 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 4, 0, 26, 34, 32+26, +83+34 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 5, 0, 37, 34, 36+37, +82+34 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 6, 0, 58, 43, 58+58, +76+43 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 7, 0, 59, 44, 58+59, +74+44 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 8, 0, 60, 44, 57+60, +74+44 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 9, 0, 60, 44, 56+60, +75+44 );
			anime->GetActionData( 4 )->SetWoundDataAbs( 10, 0, 48, 41, 48+60, +44+80 );
			anime->GetActionData( 4 )->SetAttackData( 6, 0, -120, -100, -30, 0, ENUM_ATTACK_PROPERTY_HIGH );
			anime->GetActionData( 4 )->SetAttackSpec( 6, 1000, 0, 0 );

			// ATTACK_EX
			anime->CreateAction( 5, 8 );
			anime->GetActionData( 5 )->SetMotionData( 0, 26, 4, 62, 120 );
			anime->GetActionData( 5 )->SetMotionData( 1, 27, 4, 62, 120 );
			anime->GetActionData( 5 )->SetMotionData( 2, 28, 4, 62, 120 );
			anime->GetActionData( 5 )->SetMotionData( 3, 29, 4, 62, 120 );
			anime->GetActionData( 5 )->SetMotionData( 4, 30, 4, 67, 120 );
			anime->GetActionData( 5 )->SetMotionData( 5, 30, 4, 67, 120 );
			anime->GetActionData( 5 )->SetMotionData( 6, 32, 4, 67, 120 );
			anime->GetActionData( 5 )->SetMotionData( 7, 33, 0, 67, 120 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 0, 0, 40, 41, 47+40, 84+41 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 1, 0, 30, 35, 65+30, 89+35 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 2, 0, 31, 33, 68+31, 90+33 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 3, 0, 31, 34, 66+31, 86+34 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 4, 0, 40, 35, 51+40, 84+35 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 5, 0, 40, 35, 51+40, 84+35 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 6, 0, 51, 37, 45+51, 85+37 );
			anime->GetActionData( 5 )->SetWoundDataAbs( 7, 0, 49, 38, 43+49, 85+38 );
			anime->GetActionData( 5 )->SetAttackData( 6, 0, -50, -100, -00, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
			anime->GetActionData( 4 )->SetAttackSpec( 6, 300, 0, 0 );
		
			anime->CreateAction( 6, 1 );
			anime->GetActionData( 6 )->SetMotionData( 0, 40, 1, 34, 112 );
			anime->GetActionData( 6 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
			anime->CreateAction( 7, 2 );
			anime->GetActionData( 7 )->SetMotionData( 0, 41, 2, 34, 124 );
			anime->GetActionData( 7 )->SetMotionData( 1, 42, 2, 34, 124 );
			anime->GetActionData( 7 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
			anime->GetActionData( 7 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
			anime->CreateAction( 8, 1 );
			anime->GetActionData( 8 )->SetMotionData( 0, 43, 1, 34, 124 );
			anime->GetActionData( 8 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
			anime->CreateAction( 9, 2 );
			anime->GetActionData( 9 )->SetMotionData( 0, 44, 2, 34, 124 );
			anime->GetActionData( 9 )->SetMotionData( 1, 45, 2, 34, 124 );
			anime->GetActionData( 9 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
			anime->GetActionData( 9 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
			anime->CreateAction( 10, 1 );
			anime->GetActionData( 10 )->SetMotionData( 0, 46, 1, 34, 124 );
			anime->GetActionData( 10 )->SetWoundData( 0, 0, -13, -50, 17, 0 );

			anime->CreateAction( 11, 4 );
			anime->GetActionData( 11 )->SetMotionData( 0, 47, 4, 46, 112 );
			anime->GetActionData( 11 )->SetMotionData( 1, 48, 4, 41, 112 );
			anime->GetActionData( 11 )->SetMotionData( 2, 49, 4, 41, 112 );
			anime->GetActionData( 11 )->SetMotionData( 3, 50, 0, 41, 112 );
			anime->GetActionData( 11 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
			anime->GetActionData( 11 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
			anime->GetActionData( 11 )->SetWoundData( 2, 0, -13, -50, 17, 0 );
			anime->GetActionData( 11 )->SetWoundData( 3, 0, -13, -50, 17, 0 );

			// forward dush
			anime->CreateAction( 12, 2 );
			anime->GetActionData( 12 )->SetMotionData( 0, 51, 3, 56, 116 );
			anime->GetActionData( 12 )->SetMotionData( 1, 52, 4, 87, 116 );
			anime->GetActionData( 12 )->SetWoundDataAbs( 0, 0, 33, 40, 41+33, 79+40 );
			anime->GetActionData( 12 )->SetWoundDataAbs( 1, 0, 60, 55, 51+60, 64+55 );
	//		anime->GetActionData( 12 )->SetMotionData( 2, 53, 4, 87, 116 );
	//		anime->GetActionData( 12 )->SetMotionData( 3, 54, 2, 87, 116 );
	//		anime->GetActionData( 12 )->SetMotionData( 4, 55, 0, 56, 116 );
	// ********************番号スキップ
			anime->CreateAction( 45, 2 );
			anime->GetActionData( 45 )->SetMotionData( 0, 53, 3, 87, 116 );
			anime->GetActionData( 45 )->SetMotionData( 1, 54, 3, 87, 116 );
			anime->GetActionData( 45 )->SetWoundDataAbs( 0, 0, 47, 42, 60+47, 75+42 );
			anime->GetActionData( 45 )->SetWoundDataAbs( 1, 0, 46, 43, 61+46, 74+43 );
			anime->CreateAction( 46, 1 );
			anime->GetActionData( 46 )->SetMotionData( 0, 55, 3, 56, 116 );
			anime->GetActionData( 46 )->SetWoundDataAbs( 0, 0, 36, 40, 38+36, 78+40 );

			// back dush
			anime->CreateAction( 13, 4 );
			anime->GetActionData( 13 )->SetMotionData( 0, 56, 2, 50, 117 );
			anime->GetActionData( 13 )->SetMotionData( 1, 57, 3, 50, 117 );
			anime->GetActionData( 13 )->SetMotionData( 2, 58, 3, 50, 117 );
			anime->GetActionData( 13 )->SetMotionData( 3, 59, 0, 50, 117 );
			anime->GetActionData( 13 )->SetWoundDataAbs( 0, 0, 32, 36, 39+32, 84+36 );
			anime->GetActionData( 13 )->SetWoundDataAbs( 1, 0, 33, 36, 43+33, 84+36 );
			anime->GetActionData( 13 )->SetWoundDataAbs( 2, 0, 33, 36, 43+33, 84+36 );
			anime->GetActionData( 13 )->SetWoundDataAbs( 3, 0, 34, 37, 45+34, 84+37 );

			// CROUCH_LOW
			anime->CreateAction( 14, 2 );
			anime->GetActionData( 14 )->SetMotionData( 0, 60, 3, 51, 112 );
			anime->GetActionData( 14 )->SetMotionData( 1, 61, 3, 51, 112 );
			anime->GetActionData( 14 )->SetWoundDataAbs( 0, 0, 40, 52, 30+40, 61+52 );
			anime->GetActionData( 14 )->SetWoundDataAbs( 0, 1, 27, 93, 17+27, 21+93 );
			anime->GetActionData( 14 )->SetWoundDataAbs( 1, 0, 42, 51, 30+40, 62+52 );
			anime->GetActionData( 14 )->SetWoundDataAbs( 1, 1, 19, 94, 28+19, 20+94 );
			anime->GetActionData( 14 )->SetAttackData( 1, 0, -33, -40, -0, 0, ENUM_ATTACK_PROPERTY_LOW );
			anime->GetActionData( 14 )->SetAttackSpec( 1, 100, 0, 0 );

			// DOT_SHA418.(JUMP HIGH)
			anime->CreateAction( 15, 9 );
			anime->GetActionData( 15 )->SetMotionData( 0, 62, 4, 115, 143 );
			anime->GetActionData( 15 )->SetMotionData( 1, 63, 5, 115, 143 );
			anime->GetActionData( 15 )->SetMotionData( 2, 64, 2, 67, 122 );
			anime->GetActionData( 15 )->SetMotionData( 3, 65, 2, 67, 122 );
			anime->GetActionData( 15 )->SetMotionData( 4, 66, 2, 67, 122 );
			anime->GetActionData( 15 )->SetMotionData( 5, 67, 2, 87, 126 );
			anime->GetActionData( 15 )->SetMotionData( 6, 68, 2, 87, 126 );
			anime->GetActionData( 15 )->SetMotionData( 7, 69, 5, 87, 126 );
			anime->GetActionData( 15 )->SetMotionData( 8, 70, 0, 87, 126 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 0, 0, 106, 53, 31+106 ,92+53 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 1, 0, 100, 52, 30+100 ,92+52 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 2, 0,  58, 29, 43+58  ,90+29 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 3, 0,  59, 30, 45+59  ,87+30 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 4, 0,  58, 29, 30+58  ,95+29 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 5, 0,  63, 43, 39+63  ,86+43 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 6, 0,  62, 51, 45+62  ,67+51 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 7, 0,  62, 51, 45+62  ,67+51 );
			anime->GetActionData( 15 )->SetWoundDataAbs( 8, 0,  66, 41, 41+66  ,87+41 );
			anime->GetActionData( 15 )->SetAttackData( 5, 0, 54, -90, -60, -127, ENUM_ATTACK_PROPERTY_JUMP );
			anime->GetActionData( 15 )->SetAttackData( 6, 0, -86, -4, -19, -102, ENUM_ATTACK_PROPERTY_JUMP );
			anime->GetActionData( 15 )->SetAttackSpec( 5, 500, 0, 0 );
			anime->GetActionData( 15 )->SetAttackSpec( 6, 500, 0, 0 );
	/* matsu motion
			anime->SetAnimeData( 62, 62, 5, 119, 143 );
			anime->SetAnimeData( 63, 63, 6, 119, 143 );
			anime->SetAnimeData( 64, 64, 6, 66, 118 );
			anime->SetAnimeData( 65, 65, 6, 45, 111 );
			anime->SetAnimeData( 66, 66, 6, 45, 111 );
			anime->SetAnimeData( 67, 67, 3, 87, 126 );
			anime->SetAnimeData( 68, 68, 3, 87, 126 );
			anime->SetAnimeData( 69, 69, 1, 87, 126 );
			anime->SetAnimeData( 70, 70, 0, 87, 126 );
	*/
			anime->CreateAction( 16, 5 );
			anime->GetActionData( 16 )->SetMotionData( 0, 155, 3, 44, 118 );
			anime->GetActionData( 16 )->SetMotionData( 1, 156, 3, 44, 118 );
			anime->GetActionData( 16 )->SetMotionData( 2, 157, 3, 69, 95 );
			anime->GetActionData( 16 )->SetMotionData( 3, 158, 0, 69, 95 );
			anime->GetActionData( 16 )->SetMotionData( 4, 159, 0, 44, 118 );

			// DOT_SHA_040.(JUMP_BACK_DUSH)
			anime->CreateAction( 17, 3 );
			anime->GetActionData( 17 )->SetMotionData( 0, 74, 3, 44, 114 );
			anime->GetActionData( 17 )->SetMotionData( 1, 75, 4, 44, 114 );
			anime->GetActionData( 17 )->SetMotionData( 2, 76, 0, 44, 114 );
			anime->GetActionData( 17 )->SetWoundDataAbs( 0, 0, 23, 32, 37+23, 83+32 );
			anime->GetActionData( 17 )->SetWoundDataAbs( 1, 0, 25, 32, 35+25, 83+32 );
			anime->GetActionData( 17 )->SetWoundDataAbs( 2, 0, 24, 31, 36+24, 85+31 );

			// damage
			anime->CreateAction( 18, 2 );
			anime->GetActionData( 18 )->SetMotionData( 0, 77, 5, 53, 95 );
			anime->GetActionData( 18 )->SetMotionData( 1, 78, 0, 53, 95 );
			anime->GetActionData( 18 )->SetWoundDataAbs( 0, 0, 45, 22, 81, 97 );
			anime->GetActionData( 18 )->SetWoundDataAbs( 1, 0, 45, 22, 81, 97 );

			// damage
			anime->CreateAction( 19, 2 );
			anime->GetActionData( 19 )->SetMotionData( 0, 79, 5, 90, 114 );
			anime->GetActionData( 19 )->SetMotionData( 1, 80, 0, 90, 114 );

			// DOT_SYA003->407.(MID)
			anime->CreateAction( 20, 6 );
			anime->GetActionData( 20 )->SetMotionData( 0, 81, 2, 36, 79 );
			anime->GetActionData( 20 )->SetMotionData( 1, 82, 3, 86, 79 );
			anime->GetActionData( 20 )->SetMotionData( 2, 83, 3, 50, 76 );
			anime->GetActionData( 20 )->SetMotionData( 3, 84, 20, 50, 75 );
			anime->GetActionData( 20 )->SetMotionData( 4, 85, 3, 43, 87 );
			anime->GetActionData( 20 )->SetMotionData( 5, 86, 0, 35, 87 );
	//		anime->GetActionData( 20 )->SetMotionData( 6, 87, 0, 82, 114 );
			anime->GetActionData( 20 )->SetAttackData( 3, 0, -74, -100, -22, 0, ENUM_ATTACK_PROPERTY_HIGH );
			anime->GetActionData( 20 )->SetAttackSpec( 3, 300, 0, 0 );

			// DOT_SYA434.(CROUCH_MID)
			anime->CreateAction( 21, 4 );
			anime->GetActionData( 21 )->SetMotionData( 0, 88, 5, 97, 114 );
			anime->GetActionData( 21 )->SetMotionData( 1, 89, 5, 97, 114 );
			anime->GetActionData( 21 )->SetMotionData( 2, 90, 5, 97, 114 );
			anime->GetActionData( 21 )->SetMotionData( 3, 91, 0, 97, 114 );
			anime->GetActionData( 21 )->SetWoundDataAbs( 0, 0, 81, 52, 36+81, 65+52 );
			anime->GetActionData( 21 )->SetWoundDataAbs( 1, 0, 81, 51, 35+81, 66+51 );
			anime->GetActionData( 21 )->SetWoundDataAbs( 2, 0, 81, 52, 36+81, 65+52 );
			anime->GetActionData( 21 )->SetWoundDataAbs( 2, 1, 71, 75, 14+71, 14+75 );
			anime->GetActionData( 21 )->SetWoundDataAbs( 3, 0, 81, 52, 37+81, 65+52 );
			anime->GetActionData( 21 )->SetWoundDataAbs( 3, 1, 69, 74, 14+69, 14+74 );
			anime->GetActionData( 21 )->SetAttackData( 2, 0, -78, -30, -25, 0, ENUM_ATTACK_PROPERTY_LOW );
			anime->GetActionData( 21 )->SetAttackSpec( 2, 300, 0, 0 );

			// DOT_SYA419.(JUMP_LOW)
			anime->CreateAction( 22, 3 );
			anime->GetActionData( 22 )->SetMotionData( 0,101, 3, 44, 124 );
			anime->GetActionData( 22 )->SetMotionData( 1,101, 10, 44, 124 );
			anime->GetActionData( 22 )->SetMotionData( 2,100, 0, 44, 124 );
	//		anime->GetActionData( 22 )->SetAttackData( 0, 0, -45, -20, 0, 0 );
			anime->GetActionData( 22)->SetWoundDataAbs( 0, 0,  35, 36, 47+35  ,47+36 );
			anime->GetActionData( 22)->SetWoundDataAbs( 0, 1,   4, 79,  45+4  ,30+79 );
			anime->GetActionData( 22)->SetWoundDataAbs( 1, 0,  35, 36, 47+35  ,47+36 );
			anime->GetActionData( 22)->SetWoundDataAbs( 1, 1,   4, 79,  45+4  ,30+79 );
			anime->GetActionData( 22)->SetWoundDataAbs( 2, 0,  41, 30, 34+41  ,56+30 );
			anime->GetActionData( 22)->SetWoundDataAbs( 2, 1,  20, 83, 40+20  ,36+83 );
			anime->GetActionData( 22 )->SetAttackData( 1, 0, -45, -20, 0, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
			anime->GetActionData( 22 )->SetAttackSpec( 1, 100, 0, 0 );

			// DOT_SYA420.(JUMP_MID)
			anime->CreateAction( 23, 5 );
			anime->GetActionData( 23 )->SetMotionData( 0,102, 3, 70, 125 );
			anime->GetActionData( 23 )->SetMotionData( 1,103, 4, 70, 125 );
			anime->GetActionData( 23 )->SetMotionData( 2,104, 4, 70, 125 );
	//		anime->GetActionData( 23 )->SetAttackData( 2,0, -60, -52, -24, -32, ENUM_ATTACK_PROPERTY_JUMP );
			anime->GetActionData( 23 )->SetMotionData( 3,105, 4, 70, 125 );
			anime->GetActionData( 23 )->SetMotionData( 4,106, 0, 70, 125 );
			anime->GetActionData( 23)->SetWoundDataAbs( 0, 0, 55, 35, 33+55 ,93+35 );
			anime->GetActionData( 23)->SetWoundDataAbs( 1, 0, 47, 36, 47+47 ,93+36 );
			anime->GetActionData( 23)->SetWoundDataAbs( 2, 0, 52, 35, 43+52 ,90+35 );
			anime->GetActionData( 23)->SetWoundDataAbs( 2, 1, 12, 80, 43+12 ,13+80 );
			anime->GetActionData( 23)->SetWoundDataAbs( 3, 0, 52, 35, 43+52 ,90+35 );
			anime->GetActionData( 23)->SetWoundDataAbs( 3, 1, 14, 73, 42+14 ,17+73 );
			anime->GetActionData( 23)->SetWoundDataAbs( 4, 0, 49, 35, 35+49 ,93+35 );
			anime->GetActionData( 23 )->SetAttackData( 3,0, -60, -52, -24, -32, ENUM_ATTACK_PROPERTY_JUMP );
			anime->GetActionData( 23 )->SetAttackSpec( 3, 300, 0, 0 );

			// DOT_SYA203.(AERIAL_DAMAGE 1)
			anime->CreateAction( 24, 1 );
			anime->GetActionData( 24 )->SetMotionData( 0,110, 0, 71, 126 );
			anime->GetActionData( 24 )->SetWoundDataAbs( 0, 0, 61, 46, 38+61, 86+46 );
			anime->GetActionData( 24 )->SetWoundDataAbs( 0, 1, 41, 57, 76+41, 26+57 );
			// DOT_SYA203.(AERIAL_DAMAGE 2)
			anime->CreateAction( 25, 1 );
			anime->GetActionData( 25 )->SetMotionData( 0,111, 0, 71, 126 );
			anime->GetActionData( 25 )->SetWoundDataAbs( 0, 0, 40, 57, 78+40, 33+57 );
			anime->GetActionData( 25 )->SetWoundDataAbs( 0, 1, 66, 87, 63+66, 36+87 );
			// DOT_SYA204.(AERIAL_DAMAGE 3)
			anime->CreateAction( 26, 1 );
			anime->GetActionData( 26 )->SetMotionData( 0,112, 0, 71, 126 );
			anime->GetActionData( 26 )->SetWoundDataAbs( 0, 0, 52, 47, 44+52, 18+47 );
			anime->GetActionData( 26 )->SetWoundDataAbs( 0, 1, 78, 61, 53+78, 54+61 );
			// DOT_SYA204.(AERIAL_DAMAGE 4)
			anime->CreateAction( 27, 2 );
			anime->GetActionData( 27 )->SetMotionData( 0,113, 3, 71, 126 );
			anime->GetActionData( 27 )->SetMotionData( 1,114, 3, 71, 126 );
			anime->GetActionData( 27 )->SetWoundDataAbs( 0, 0, 59, 33, 42+59, 32+33 );
			anime->GetActionData( 27 )->SetWoundDataAbs( 0, 1, 82, 62, 47+82, 55+62 );
			anime->GetActionData( 27 )->SetWoundDataAbs( 1, 0, 59, 33, 42+59, 32+33 );
			anime->GetActionData( 27 )->SetWoundDataAbs( 1, 1, 82, 62, 47+82, 55+62 );

			// DOT_SYA601.(DOWN)
			anime->CreateAction( 28, 5 );
			anime->GetActionData( 28 )->SetMotionData( 0,115, 3, 71, 126 );
			anime->GetActionData( 28 )->SetMotionData( 1,116, 3, 71, 126 );
			anime->GetActionData( 28 )->SetMotionData( 2,117, 3, 71, 126 );
			anime->GetActionData( 28 )->SetMotionData( 3,118, 3, 71, 126 );
			anime->GetActionData( 28 )->SetMotionData( 4,119, 0, 71, 126 );
			anime->GetActionData( 28 )->SetWoundDataAbs( 0, 0, 53, 58, 33+53, 42+58 );
			anime->GetActionData( 28 )->SetWoundDataAbs( 0, 1, 64, 90, 52+64, 36+90 );
			anime->GetActionData( 28 )->SetWoundDataAbs( 1, 0, 34, 79, 81+34, 47+79 );
			anime->GetActionData( 28 )->SetWoundDataAbs( 2, 0, 32, 83, 84+32, 46+83 );
			anime->GetActionData( 28 )->SetWoundDataAbs( 3, 0, 32, 83, 84+32, 46+83 );
			anime->GetActionData( 28 )->SetWoundDataAbs( 4, 0, 34,115, 85+34, 17+115 );
			anime->GetActionData( 28 )->SetWoundDataAbs( 4, 1, 51, 91, 66+51, 28+91 );

			// DOT_SYA432.(CROUCH ATTACK HIGH)
			anime->CreateAction( 29, 11 );
			anime->GetActionData( 29 )->SetMotionData( 0,120, 10, 108, 144 );
			anime->GetActionData( 29 )->SetMotionData( 1,121, 3, 108, 144 );
			anime->GetActionData( 29 )->SetMotionData( 2,122, 3, 101, 123 );
			anime->GetActionData( 29 )->SetMotionData( 3,123, 3, 101, 123 );
			anime->GetActionData( 29 )->SetMotionData( 4,124, 5, 101, 123 );
			anime->GetActionData( 29 )->SetMotionData( 5,125, 5, 101, 123 );
			anime->GetActionData( 29 )->SetMotionData( 6,126, 5, 101, 123 );
			anime->GetActionData( 29 )->SetMotionData( 7,127, 5, 101, 123 );
			anime->GetActionData( 29 )->SetMotionData( 8,128, 5, 43, 122 );
			anime->GetActionData( 29 )->SetMotionData( 9,129, 5, 43, 122 );
			anime->GetActionData( 29 )->SetMotionData( 10,130, 0, 43, 122 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 0, 0, 88, 79, 43+88, 68+79 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 1, 0, 87, 78, 43+87, 68+78 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 2, 0, 85, 47, 30+85, 77+47 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 3, 0, 85, 47, 30+85, 77+47 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 4, 0, 85, 47, 30+85, 77+47 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 5, 0, 85, 47, 30+85, 77+47 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 6, 0, 85, 47, 30+85, 77+47 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 7, 0, 85, 54, 44+85, 70+54 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 8, 0, 25, 60, 36+25, 64+60 );
			anime->GetActionData( 29 )->SetWoundDataAbs( 9, 0, 25, 60, 36+25, 64+60 );
			anime->GetActionData( 29 )->SetWoundDataAbs(10, 0, 25, 60, 36+25, 64+60 );
			anime->GetActionData( 29 )->SetAttackData( 2, 0, -64, -77, 0, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
			anime->GetActionData( 29 )->SetAttackSpec( 2, 600, 0, 0 );

			// DOT_SYA032.(STAND_GUARD)
			anime->CreateAction( 30, 2 );
			anime->GetActionData( 30 )->SetMotionData( 0,131, 8, 60, 115 );
			anime->GetActionData( 30 )->SetMotionData( 1,132, 0, 60, 115 );
			anime->GetActionData( 30 )->SetWoundDataAbs( 0, 0, 41, 34, 32+41, 82+34 );
			anime->GetActionData( 30 )->SetWoundDataAbs( 0, 1, 70, 79, 43+70, 13+79 );
			anime->GetActionData( 30 )->SetWoundDataAbs( 1, 0, 41, 32, 37+41, 84+32 );
			anime->GetActionData( 30 )->SetWoundDataAbs( 1, 1, 73, 78, 55+73, 9+78 );
			anime->CreateAction( 31, 1 );
			anime->GetActionData( 31 )->SetMotionData( 0,132, 0, 60, 115 );
			anime->GetActionData( 31 )->SetWoundDataAbs( 0, 0, 41, 32, 37+41, 84+32 );
			anime->GetActionData( 31 )->SetWoundDataAbs( 0, 1, 73, 78, 55+73, 9+78 );
			// DOT_SYA048.(CROUCH_GUARD)
			// ＊＊絵が逆
			anime->CreateAction( 32, 2 );
			anime->GetActionData( 32 )->SetMotionData( 0,133, 2, 93, 115 );
			anime->GetActionData( 32 )->SetMotionData( 1,134, 0, 93, 115 );
			anime->GetActionData( 32 )->SetWoundDataAbs( 0, 0, 80, 52, 34+80, 66+52 );
			anime->GetActionData( 32 )->SetWoundDataAbs( 0, 1, 22, 84, 65+22, 13+84 );
			anime->GetActionData( 32 )->SetWoundDataAbs( 1, 0, 76, 40, 38+76, 78+40 );
			anime->GetActionData( 32 )->SetWoundDataAbs( 1, 1, 41, 62, 46+41, 55+62 );

			// DOT_SYA210.(JUMP_DAMAGE)
			anime->CreateAction( 33, 2 );
			anime->GetActionData( 33 )->SetMotionData( 0,140, 3, 50, 112 );
			anime->GetActionData( 33 )->SetMotionData( 1,141, 0, 50, 112 );
			anime->GetActionData( 33 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
			anime->GetActionData( 33 )->SetWoundData( 1, 0, -13, -50, 17, 0 );

			// DOT_SYA050.(JUMP_GUARD)
			anime->CreateAction( 34, 2 );
			anime->GetActionData( 34 )->SetMotionData( 0,135, 3, 60, 116 );
			anime->GetActionData( 34 )->SetMotionData( 1,136, 3, 60, 116 );
			anime->GetActionData( 34 )->SetWoundDataAbs( 0, 0, 47, 33, 31+47, 93+33 );
			anime->GetActionData( 34 )->SetWoundDataAbs( 1, 0, 47, 33, 31+47, 93+33 );

			// DOT_SYA202.(BIG_DAMAGE)
			anime->CreateAction( 35, 3 );
			anime->GetActionData( 35 )->SetMotionData( 0,135, 3, 38, 64 );
			anime->GetActionData( 35 )->SetMotionData( 1,136, 3, 38, 64 );
			anime->GetActionData( 35 )->SetMotionData( 2,137, 3, 38, 64 );

			// DOT_SYA602.(GET_UP)
			anime->CreateAction( 36, 3 );
			anime->GetActionData( 36 )->SetMotionData( 0,185, 5, 71, 126 );
			anime->GetActionData( 36 )->SetMotionData( 1,186, 5, 71, 126 );
			anime->GetActionData( 36 )->SetMotionData( 2,187, 0, 71, 126 );

			// DOT_SYA202.(BLOW DOWN)
			anime->CreateAction( 40, 3 );
			anime->GetActionData( 40 )->SetMotionData( 0,210, 3, 68, 85 );
			anime->GetActionData( 40 )->SetMotionData( 1,211, 3, 68, 85 );
			anime->GetActionData( 40 )->SetMotionData( 2,212, 3, 68, 85 );

			// DOT_SYA201.(WALL BOUND)
			anime->CreateAction( 41, 1 );
			anime->GetActionData( 41 )->SetMotionData( 0,214, 3, 68, 85 );

			// DOT_SYA208.(RECOVER)
			anime->CreateAction( 42, 5 );
			anime->GetActionData( 42 )->SetMotionData( 0,220, 3, 100, 98 );
			anime->GetActionData( 42 )->SetMotionData( 1,221, 3, 100, 98 );
			anime->GetActionData( 42 )->SetMotionData( 2,222, 3, 100, 98 );
			anime->GetActionData( 42 )->SetMotionData( 3,223, 3, 100, 98 );
			anime->GetActionData( 42 )->SetMotionData( 4,224, 0, 100, 98 );

			// DOT_SYA414.(THROW)
			anime->CreateAction( 50, 1 );
			anime->GetActionData( 50 )->SetMotionData( 0,160, 0, 71, 106 );
			anime->GetActionData( 50 )->SetWoundDataAbs( 0, 0, 22, 30, 54+22, 42+30 );
			anime->GetActionData( 50 )->SetWoundDataAbs( 0, 1, 57, 71, 44+57, 37+71 );
			anime->CreateAction( 51, 8 );
			anime->GetActionData( 51 )->SetMotionData( 0,161, 3, 71, 106 );
			anime->GetActionData( 51 )->SetMotionData( 1,162, 3, 71, 106 );
			anime->GetActionData( 51 )->SetMotionData( 2,163, 3, 71, 106 );
			anime->GetActionData( 51 )->SetMotionData( 3,164, 3, 71, 106 );
			anime->GetActionData( 51 )->SetMotionData( 4,165, 3, 106, 109 );
			anime->GetActionData( 51 )->SetMotionData( 5,166, 3, 106, 109 );
			anime->GetActionData( 51 )->SetMotionData( 6,167, 3, 106, 109 );
			anime->GetActionData( 51 )->SetMotionData( 7,168, 0, 106, 109 );
			anime->CreateAction( 52, 3 );
			anime->GetActionData( 52 )->SetMotionData( 0,169, 3, 106, 109 );
			anime->GetActionData( 52 )->SetMotionData( 1,170, 3, 47, 109 );
			anime->GetActionData( 52 )->SetMotionData( 2,171, 3, 47, 109 );

			// DOT_SYA413.(MISS THROW)
			anime->CreateAction( 53, 2 );
			anime->GetActionData( 53 )->SetMotionData( 0,173, 5, 94, 113 );
			anime->GetActionData( 53 )->SetMotionData( 1,174, 0, 94, 113 );
			anime->GetActionData( 53 )->SetWoundDataAbs( 0, 0, 41, 43, 54+41, 38+43 );
			anime->GetActionData( 53 )->SetWoundDataAbs( 0, 1, 80, 79, 39+80, 36+79 );
			anime->GetActionData( 53 )->SetWoundDataAbs( 1, 0, 33, 45, 56+33, 38+45 );
			anime->GetActionData( 53 )->SetWoundDataAbs( 1, 1, 74, 80, 42+74, 36+80 );

			// DOT_SYA421.(JUMP ATTACK EX)
			anime->CreateAction( 55, 8 );
			anime->GetActionData( 55 )->SetMotionData( 0,175, 10, 93, 115 );
			anime->GetActionData( 55 )->SetMotionData( 1,176, 3, 93, 122 );
			anime->GetActionData( 55 )->SetMotionData( 2,177, 3, 93, 129 );
			anime->GetActionData( 55 )->SetMotionData( 3,178, 3, 93, 136 );
			anime->GetActionData( 55 )->SetMotionData( 4,179, 3, 93, 143 );
			anime->GetActionData( 55 )->SetMotionData( 5,180, 3, 93, 150 );
			anime->GetActionData( 55 )->SetMotionData( 6,181, 3, 93, 157 );
			anime->GetActionData( 55 )->SetMotionData( 7,182, 0, 93, 164 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 0, 0, 82, 29, 34+82 ,88+29 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 1, 0, 76, 58, 53+76 ,37+58 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 1, 1,105, 93,27+105 ,19+93 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 2, 0, 85, 77, 52+85 ,38+77 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 3, 0, 83, 82, 52+83 ,57+82 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 4, 0, 84, 77, 25+84 ,48+77 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 4, 1,110,106,31+111 ,27+106 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 5, 0, 76,111, 67+76 ,26+111 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 5, 1,114, 93,30+114 ,23+93 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 6, 0, 86, 76, 38+86 ,86+76 );
			anime->GetActionData( 55 )->SetWoundDataAbs( 7, 0, 78, 73, 34+82 ,95+29 );
			anime->GetActionData( 55 )->SetAttackData( 3, 0, -36, -98, 0, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
			anime->GetActionData( 55 )->SetAttackData( 3, 1, -27, 0, 62, 62, ENUM_ATTACK_PROPERTY_MIDDLE );
			anime->GetActionData( 55 )->SetAttackSpec( 3, 600, 0, 0 );

			// DOT_SYA203.2(AERIAL_DAMAGE 1)
			anime->CreateAction( 56, 1 );
			anime->GetActionData( 56 )->SetMotionData( 0,111, 0, 71, 126 );
			// DOT_SYA203.2(AERIAL_DAMAGE 2)
			anime->CreateAction( 57, 1 );
			anime->GetActionData( 57 )->SetMotionData( 0,112, 0, 71, 126 );
			// DOT_SYA204.2(AERIAL_DAMAGE 3)
			anime->CreateAction( 58, 2 );
			anime->GetActionData( 58 )->SetMotionData( 0,113, 3, 71, 126 );
			anime->GetActionData( 58 )->SetMotionData( 1,114, 3, 71, 126 );

			// DOT_SYA801.(SPECIAL1)
			anime->CreateAction( 60, 4 );
			anime->GetActionData( 60 )->SetMotionData( 0,150, 5, 55, 100 );
			anime->GetActionData( 60 )->SetMotionData( 1,151, 5, 55, 100 );
			anime->GetActionData( 60 )->SetMotionData( 2,152, 3, 55, 105 );
			anime->GetActionData( 60 )->SetMotionData( 3,153, 0, 55, 105 );
			anime->GetActionData( 60 )->SetWoundDataAbs( 0, 0, 39, 33, 33+39 ,75+33 );
			anime->GetActionData( 60 )->SetWoundDataAbs( 1, 0, 32, 39, 39+32 ,63+39 );
			anime->GetActionData( 60 )->SetWoundDataAbs( 2, 0, 16, 95, 42+16 ,39+95 );
			anime->GetActionData( 60 )->SetWoundDataAbs( 2, 1, 58, 66, 35+58 ,57+66 );
			anime->GetActionData( 60 )->SetWoundDataAbs( 3, 0, 16, 95, 42+16 ,39+95 );
			anime->GetActionData( 60 )->SetWoundDataAbs( 3, 1, 58, 66, 35+58 ,57+66 );
			anime->GetActionData( 60 )->SetAttackDataAbs( 3, 0, 16, 95, 42+16 ,39+95 );
			anime->GetActionData( 60 )->SetAttackDataAbs( 3, 1, 58, 66, 35+58 ,57+66 );
			anime->GetActionData( 60 )->SetAttackSpec( 3, 400, 0, 0 );
			anime->CreateAction( 61, 1 );
			anime->GetActionData( 61 )->SetMotionData( 0,154, 0, 40, 115 );
			anime->GetActionData( 61 )->SetWoundDataAbs( 0, 0, 18, 46, 42+18 ,71+46 );

			// DOT_SYA802.(SPECIAL2)
			anime->CreateAction( 63, 9 );
			anime->GetActionData( 63 )->SetMotionData( 0,190, 5, 55, 114 );
			anime->GetActionData( 63 )->SetMotionData( 1,191, 5, 55, 114 );
			anime->GetActionData( 63 )->SetMotionData( 2,192, 7, 55, 114 );
			anime->GetActionData( 63 )->SetMotionData( 3,193, 7, 55, 114 );
			anime->GetActionData( 63 )->SetMotionData( 4,194, 7, 55, 114 );
			anime->GetActionData( 63 )->SetMotionData( 5,195, 7, 55, 114 );
			anime->GetActionData( 63 )->SetMotionData( 6,196, 7, 55, 114 );
			anime->GetActionData( 63 )->SetMotionData( 7,197, 7, 53, 111 );
			anime->GetActionData( 63 )->SetMotionData( 8,198, 0, 53, 111 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 0, 0, 36, 36, 40+36 ,81+36 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 1, 0, 36, 37, 37+36 ,81+37 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 1, 1, 21, 66, 28+21 ,16+66 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 2, 0, 36, 35, 40+36 ,82+35 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 2, 1, 15, 53, 30+15 ,20+53 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 3, 0, 36, 35, 40+36 ,82+35 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 3, 1, 15, 53, 30+15 ,20+53 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 4, 0, 36, 35, 40+36 ,82+35 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 4, 1, 15, 53, 30+15 ,20+53 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 5, 0, 36, 35, 40+36 ,82+35 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 5, 1, 15, 53, 30+15 ,20+53 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 6, 0, 37, 37, 35+37 ,80+37 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 6, 1, 21, 65, 27+21 ,16+65 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 7, 0, 35, 32, 36+35 ,83+32 );
			anime->GetActionData( 63 )->SetWoundDataAbs( 8, 0, 35, 32, 36+35 ,83+32 );

			// DOT_SYA803.(SPECIAL3)
			anime->CreateAction( 65, 8 );
			anime->GetActionData( 65 )->SetMotionData( 0,200, 10, 129, 142 );
			anime->GetActionData( 65 )->SetMotionData( 1,201, 3, 129, 142 );
			anime->GetActionData( 65 )->SetMotionData( 2,202, 1, 129, 142 );
			anime->GetActionData( 65 )->SetMotionData( 3,203, 1, 129, 142 );
			anime->GetActionData( 65 )->SetMotionData( 4,204, 1, 129, 142 );
			anime->GetActionData( 65 )->SetMotionData( 5,205, 3, 129, 142 );
			anime->GetActionData( 65 )->SetMotionData( 6,206, 3, 129, 142 );
			anime->GetActionData( 65 )->SetMotionData( 7,207, 0, 129, 142 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 0, 0,113, 62, 34+113 ,87+62 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 1, 0,101, 59, 51+101 ,49+59 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 1, 1,113,104, 28+113 ,45+104 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 2, 0,108, 63, 41+108 ,39+63 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 2, 1, 87, 90, 31+87  ,12+90 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 2, 2,118,102, 30+118 ,49+102 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 3, 0,106, 64, 45+106 ,55+64 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 3, 1,118,114, 29+118 ,35+114 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 4, 0,108, 67, 44+108 ,56+67 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 4, 1,121,119, 19+121 ,27+119 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 5, 0,106, 66, 47+106 ,53+66 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 5, 1,111,117, 35+111 ,29+117 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 6, 0,111, 65, 37+111 ,83+65 );
			anime->GetActionData( 65 )->SetWoundDataAbs( 7, 0,102, 56, 31+102 ,88+56 );

			// DOT_SYA017.1(CROUCH_EX 1)
			anime->CreateAction( 66, 1 );
			anime->GetActionData( 66 )->SetMotionData( 0,230, 0, 48, 107 );
			anime->GetActionData( 66 )->SetWoundDataAbs( 0,0, 27, 35, 40+27, 76+35 );
			// DOT_SYA017.2(CROUCH_EX 2)
			anime->CreateAction( 67, 2 );
			anime->GetActionData( 67 )->SetMotionData( 0,231, 3, 48, 107 );
			anime->GetActionData( 67 )->SetMotionData( 1,232, 3, 48, 107 );
			anime->GetActionData( 67 )->SetWoundDataAbs( 0, 0, 10, 44, 72+10, 69+44 );
			anime->GetActionData( 67 )->SetWoundDataAbs( 1, 0, 10, 44, 72+10, 69+44 );
			anime->GetActionData( 67 )->SetAttackData( 0, 0, -38, 4, 3, -19, ENUM_ATTACK_PROPERTY_LOW );
			anime->GetActionData( 67 )->SetAttackData( 1, 0, -38, 4, 3, -19, ENUM_ATTACK_PROPERTY_LOW );
			anime->GetActionData( 67 )->SetAttackSpec( 0, 100, 0, 0 );
			anime->GetActionData( 67 )->SetAttackSpec( 1, 100, 0, 0 );
			// DOT_SYA017.3(CROUCH_EX 3)
			anime->CreateAction( 68, 1 );
			anime->GetActionData( 68 )->SetMotionData( 0,233, 3, 48, 107 );
			anime->GetActionData( 68 )->SetWoundDataAbs( 0, 0, 26, 36, 46+26, 75+36 );

			// 以降てすつ
	/*		anime->CreateAction( 50, 5 );
			anime->GetActionData( 50 )->SetMotionData( 0, 0, 4, 0, 0 );
			anime->GetActionData( 50 )->SetMotionData( 1, 1, 4, 0, 0 );
			anime->GetActionData( 50 )->SetMotionData( 2, 2, 4, 0, 0 );
			anime->GetActionData( 50 )->SetMotionData( 3, 3, 4, 0, 0 );
			anime->GetActionData( 50 )->SetMotionData( 4, 4, 4, 0, 0 );
			anime->CreateAction( 51, 5 );
			anime->GetActionData( 51 )->SetMotionData( 0, 5, 4, 0, 0 );
			anime->GetActionData( 51 )->SetMotionData( 1, 6, 4, 0, 0 );
			anime->GetActionData( 51 )->SetMotionData( 2, 7, 4, 0, 0 );
			anime->GetActionData( 51 )->SetMotionData( 3, 8, 4, 0, 0 );
			anime->GetActionData( 51 )->SetMotionData( 4, 9, 4, 0, 0 );
			anime->CreateAction( 52, 5 );
			anime->GetActionData( 52 )->SetMotionData( 0, 10, 4, 0, 0 );
			anime->GetActionData( 52 )->SetMotionData( 1, 11, 4, 0, 0 );
			anime->GetActionData( 52 )->SetMotionData( 2, 12, 4, 0, 0 );
			anime->GetActionData( 52 )->SetMotionData( 3, 13, 4, 0, 0 );
			anime->GetActionData( 52 )->SetMotionData( 4, 14, 4, 0, 0 );
			anime->CreateAction( 53, 5 )
			anime->GetActionData( 53 )->SetMotionData( 0, 15, 4, 0, 0 );
			anime->GetActionData( 53 )->SetMotionData( 1, 16, 4, 0, 0 );
			anime->GetActionData( 53 )->SetMotionData( 2, 17, 4, 0, 0 );
			anime->GetActionData( 53 )->SetMotionData( 3, 18, 4, 0, 0 );
			anime->GetActionData( 53 )->SetMotionData( 4, 19, 4, 0, 0 );
			anime->CreateAction( 54, 5 );
			anime->GetActionData( 54 )->SetMotionData( 0, 20, 4, 0, 0 );
			anime->GetActionData( 54 )->SetMotionData( 1, 21, 4, 0, 0 );
			anime->GetActionData( 54 )->SetMotionData( 2, 22, 4, 0, 0 );
			anime->GetActionData( 54 )->SetMotionData( 3, 23, 4, 0, 0 );
			anime->GetActionData( 54 )->SetMotionData( 4, 24, 4, 0, 0 );

			anime->CreateAction( 60, 10 );
			anime->GetActionData( 60 )->SetMotionData( 0, 0, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 1, 1, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 2, 2, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 3, 3, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 4, 4, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 5, 5, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 6, 6, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 7, 7, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 8, 8, 4, 0, 0 );
			anime->GetActionData( 60 )->SetMotionData( 9, 9, 4, 0, 0 );
*/
}
#endif

	break;

	case ANIME_NO_SHANA:
		temp = DOT_SYA_ANIME_NUTRAL ;
		anime->CreateAction( temp, 7 );
		anime->GetActionData( temp )->SetMotionData( 0, 0, 6, 34, 124 );
		anime->GetActionData( temp )->SetMotionData( 1, 1, 6, 34, 124 );
		anime->GetActionData( temp )->SetMotionData( 2, 2, 6, 34, 124 );
		anime->GetActionData( temp )->SetMotionData( 3, 3, 6, 34, 124 );
		anime->GetActionData( temp )->SetMotionData( 4, 4, 6, 34, 124 );
		anime->GetActionData( temp )->SetMotionData( 5, 5, 6, 34, 124 );
		anime->GetActionData( temp )->SetMotionData( 6, 6, 6, 34, 124 );
		anime->GetActionData( temp )->SetWoundData( 0, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 1, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 2, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 3, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 4, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 5, 0, -13, -70, 17, 0 );
		anime->GetActionData( temp )->SetWoundData( 6, 0, -13, -70, 17, 0 );

        // walk_forward
		anime->CreateAction( 1, 6 );
		anime->GetActionData( 1 )->SetMotionData( 0, 7, 6, 34, 124 );
		anime->GetActionData( 1 )->SetMotionData( 1, 8, 6, 34, 124 );
		anime->GetActionData( 1 )->SetMotionData( 2, 9, 6, 34, 124 );
		anime->GetActionData( 1 )->SetMotionData( 3,10, 6, 34, 124 );
		anime->GetActionData( 1 )->SetMotionData( 4, 9, 6, 34, 124 );
		anime->GetActionData( 1 )->SetMotionData( 5, 8, 6, 34, 124 );
		anime->GetActionData( 1 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( 1 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->GetActionData( 1 )->SetWoundData( 2, 0, -13, -50, 17, 0 );
		anime->GetActionData( 1 )->SetWoundData( 3, 0, -13, -50, 17, 0 );
		anime->GetActionData( 1 )->SetWoundData( 4, 0, -13, -50, 17, 0 );
		anime->GetActionData( 1 )->SetWoundData( 5, 0, -13, -50, 17, 0 );

        // walk_back
		anime->CreateAction( 2, 6 );
		anime->GetActionData( 2 )->SetMotionData( 0, 7, 6, 34, 124 );
		anime->GetActionData( 2 )->SetMotionData( 1, 8, 6, 34, 124 );
		anime->GetActionData( 2 )->SetMotionData( 2, 9, 6, 34, 124 );
		anime->GetActionData( 2 )->SetMotionData( 3,10, 6, 34, 124 );
		anime->GetActionData( 2 )->SetMotionData( 4, 9, 6, 34, 124 );
		anime->GetActionData( 2 )->SetMotionData( 5, 8, 6, 34, 124 );
		anime->GetActionData( 2 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( 2 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->GetActionData( 2 )->SetWoundData( 2, 0, -13, -50, 17, 0 );
		anime->GetActionData( 2 )->SetWoundData( 3, 0, -13, -50, 17, 0 );
		anime->GetActionData( 2 )->SetWoundData( 4, 0, -13, -50, 17, 0 );
		anime->GetActionData( 2 )->SetWoundData( 5, 0, -13, -50, 17, 0 );

        // DOT_SHA002.(ATTACK_LOW)
		anime->CreateAction( 3, 4 );
		anime->GetActionData( 3 )->SetMotionData( 0, 11, 3, 45, 106 );
		anime->GetActionData( 3 )->SetMotionData( 1, 12, 3, 45, 106 );
		anime->GetActionData( 3 )->SetMotionData( 2, 13, 3, 51, 106 );
		anime->GetActionData( 3 )->SetMotionData( 3, 14, 3, 51, 106 );
		anime->GetActionData( 3 )->SetWoundDataAbs( 0, 0, 18, 25, 65, 107 );
		anime->GetActionData( 3 )->SetWoundDataAbs( 1, 0, 17, 26, 69, 108 );
		anime->GetActionData( 3 )->SetWoundDataAbs( 2, 0, 13, 23, 69, 109 );
		anime->GetActionData( 3 )->SetWoundDataAbs( 3, 0, 28, 25, 72, 109 );
//		anime->GetActionData( 3 )->SetAttackData( 0, 0, -30, -50, 30, 50 );
//		anime->GetActionData( 3 )->SetAttackData( 1, 0, -30, -50, 30, 50 );
		anime->GetActionData( 3 )->SetAttackData( 2, 0, -40, -50, 0, 0, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( 3 )->SetAttackSpec( 2, 100, 0, 0 );
//		anime->GetActionData( 3 )->SetAttackData( 3, 0, -30, -50, 30, 50 );

		// ATTACK_HIGH
		anime->CreateAction( 4, 11 );
		anime->GetActionData( 4 )->SetMotionData( 0, 15, 4, 54, 115 );
		anime->GetActionData( 4 )->SetMotionData( 1, 16, 4, 54, 115 );
		anime->GetActionData( 4 )->SetMotionData( 2, 17, 4, 54, 115 );
		anime->GetActionData( 4 )->SetMotionData( 3, 18, 4, 54, 115 );
		anime->GetActionData( 4 )->SetMotionData( 4, 19, 4, 54, 115 );
		anime->GetActionData( 4 )->SetMotionData( 5, 20, 4, 76, 115 );
		anime->GetActionData( 4 )->SetMotionData( 6, 21, 4, 122, 115 );
		anime->GetActionData( 4 )->SetMotionData( 7, 22, 6, 122, 115 );
		anime->GetActionData( 4 )->SetMotionData( 8, 23, 6, 122, 115 );
		anime->GetActionData( 4 )->SetMotionData( 9, 24, 12, 122, 115 );
		anime->GetActionData( 4 )->SetMotionData( 10, 25, 0, 98, 115 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 0, 0, 22, 32, 78, 119 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 1, 0, 25, 33, 70, 118 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 2, 0, 30, 32, 35+30, +86+32 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 3, 0, 31, 32, 31+31, +85+32 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 4, 0, 26, 34, 32+26, +83+34 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 5, 0, 37, 34, 36+37, +82+34 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 6, 0, 58, 43, 58+58, +76+43 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 7, 0, 59, 44, 58+59, +74+44 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 8, 0, 60, 44, 57+60, +74+44 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 9, 0, 60, 44, 56+60, +75+44 );
		anime->GetActionData( 4 )->SetWoundDataAbs( 10, 0, 48, 41, 48+60, +44+80 );
		anime->GetActionData( 4 )->SetAttackData( 6, 0, -120, -100, -30, 0, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( 4 )->SetAttackSpec( 6, 1000, 0, 0 );

		// ATTACK_EX
		anime->CreateAction( 5, 8 );
		anime->GetActionData( 5 )->SetMotionData( 0, 26, 4, 62, 120 );
		anime->GetActionData( 5 )->SetMotionData( 1, 27, 4, 62, 120 );
		anime->GetActionData( 5 )->SetMotionData( 2, 28, 4, 62, 120 );
		anime->GetActionData( 5 )->SetMotionData( 3, 29, 4, 62, 120 );
		anime->GetActionData( 5 )->SetMotionData( 4, 30, 4, 67, 120 );
		anime->GetActionData( 5 )->SetMotionData( 5, 30, 4, 67, 120 );
		anime->GetActionData( 5 )->SetMotionData( 6, 32, 4, 67, 120 );
		anime->GetActionData( 5 )->SetMotionData( 7, 33, 0, 67, 120 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 0, 0, 40, 41, 47+40, 84+41 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 1, 0, 30, 35, 65+30, 89+35 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 2, 0, 31, 33, 68+31, 90+33 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 3, 0, 31, 34, 66+31, 86+34 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 4, 0, 40, 35, 51+40, 84+35 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 5, 0, 40, 35, 51+40, 84+35 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 6, 0, 51, 37, 45+51, 85+37 );
		anime->GetActionData( 5 )->SetWoundDataAbs( 7, 0, 49, 38, 43+49, 85+38 );
		anime->GetActionData( 5 )->SetAttackData( 6, 0, -50, -100, -00, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
		anime->GetActionData( 5 )->SetAttackSpec( 6, 300, 0, 0 );
	
		anime->CreateAction( 6, 1 );
		anime->GetActionData( 6 )->SetMotionData( 0, 40, 1, 34, 112 );
		anime->GetActionData( 6 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->CreateAction( 7, 2 );
		anime->GetActionData( 7 )->SetMotionData( 0, 41, 2, 34, 124 );
		anime->GetActionData( 7 )->SetMotionData( 1, 42, 2, 34, 124 );
		anime->GetActionData( 7 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( 7 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->CreateAction( 8, 1 );
		anime->GetActionData( 8 )->SetMotionData( 0, 43, 1, 34, 124 );
		anime->GetActionData( 8 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->CreateAction( 9, 2 );
		anime->GetActionData( 9 )->SetMotionData( 0, 44, 2, 34, 124 );
		anime->GetActionData( 9 )->SetMotionData( 1, 45, 2, 34, 124 );
		anime->GetActionData( 9 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( 9 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->CreateAction( 10, 1 );
		anime->GetActionData( 10 )->SetMotionData( 0, 46, 1, 34, 124 );
		anime->GetActionData( 10 )->SetWoundData( 0, 0, -13, -50, 17, 0 );

		anime->CreateAction( 11, 4 );
		anime->GetActionData( 11 )->SetMotionData( 0, 47, 4, 46, 112 );
		anime->GetActionData( 11 )->SetMotionData( 1, 48, 4, 41, 112 );
		anime->GetActionData( 11 )->SetMotionData( 2, 49, 4, 41, 112 );
		anime->GetActionData( 11 )->SetMotionData( 3, 50, 0, 41, 112 );
		anime->GetActionData( 11 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( 11 )->SetWoundData( 1, 0, -13, -50, 17, 0 );
		anime->GetActionData( 11 )->SetWoundData( 2, 0, -13, -50, 17, 0 );
		anime->GetActionData( 11 )->SetWoundData( 3, 0, -13, -50, 17, 0 );

		// forward dush
		anime->CreateAction( 12, 2 );
		anime->GetActionData( 12 )->SetMotionData( 0, 51, 3, 56, 116 );
		anime->GetActionData( 12 )->SetMotionData( 1, 52, 4, 87, 116 );
		anime->GetActionData( 12 )->SetWoundDataAbs( 0, 0, 33, 40, 41+33, 79+40 );
		anime->GetActionData( 12 )->SetWoundDataAbs( 1, 0, 60, 55, 51+60, 64+55 );
//		anime->GetActionData( 12 )->SetMotionData( 2, 53, 4, 87, 116 );
//		anime->GetActionData( 12 )->SetMotionData( 3, 54, 2, 87, 116 );
//		anime->GetActionData( 12 )->SetMotionData( 4, 55, 0, 56, 116 );
// ********************番号スキップ
		anime->CreateAction( 45, 2 );
		anime->GetActionData( 45 )->SetMotionData( 0, 53, 3, 87, 116 );
		anime->GetActionData( 45 )->SetMotionData( 1, 54, 3, 87, 116 );
		anime->GetActionData( 45 )->SetWoundDataAbs( 0, 0, 47, 42, 60+47, 75+42 );
		anime->GetActionData( 45 )->SetWoundDataAbs( 1, 0, 46, 43, 61+46, 74+43 );
		anime->CreateAction( 46, 1 );
		anime->GetActionData( 46 )->SetMotionData( 0, 55, 3, 56, 116 );
		anime->GetActionData( 46 )->SetWoundDataAbs( 0, 0, 36, 40, 38+36, 78+40 );

		// back dush
		anime->CreateAction( 13, 4 );
		anime->GetActionData( 13 )->SetMotionData( 0, 56, 2, 50, 117 );
		anime->GetActionData( 13 )->SetMotionData( 1, 57, 3, 50, 117 );
		anime->GetActionData( 13 )->SetMotionData( 2, 58, 3, 50, 117 );
		anime->GetActionData( 13 )->SetMotionData( 3, 59, 0, 50, 117 );
		anime->GetActionData( 13 )->SetWoundDataAbs( 0, 0, 32, 36, 39+32, 84+36 );
		anime->GetActionData( 13 )->SetWoundDataAbs( 1, 0, 33, 36, 43+33, 84+36 );
		anime->GetActionData( 13 )->SetWoundDataAbs( 2, 0, 33, 36, 43+33, 84+36 );
		anime->GetActionData( 13 )->SetWoundDataAbs( 3, 0, 34, 37, 45+34, 84+37 );

		// CROUCH_LOW
		anime->CreateAction( 14, 2 );
		anime->GetActionData( 14 )->SetMotionData( 0, 60, 3, 51, 112 );
		anime->GetActionData( 14 )->SetMotionData( 1, 61, 3, 51, 112 );
		anime->GetActionData( 14 )->SetWoundDataAbs( 0, 0, 40, 52, 30+40, 61+52 );
		anime->GetActionData( 14 )->SetWoundDataAbs( 0, 1, 27, 93, 17+27, 21+93 );
		anime->GetActionData( 14 )->SetWoundDataAbs( 1, 0, 42, 51, 30+40, 62+52 );
		anime->GetActionData( 14 )->SetWoundDataAbs( 1, 1, 19, 94, 28+19, 20+94 );
		anime->GetActionData( 14 )->SetAttackData( 1, 0, -33, -40, -0, 0, ENUM_ATTACK_PROPERTY_LOW );
		anime->GetActionData( 14 )->SetAttackSpec( 1, 100, 0, 0 );

		// DOT_SHA418.(JUMP HIGH)
		anime->CreateAction( 15, 9 );
		anime->GetActionData( 15 )->SetMotionData( 0, 62, 4, 115, 143 );
		anime->GetActionData( 15 )->SetMotionData( 1, 63, 5, 115, 143 );
		anime->GetActionData( 15 )->SetMotionData( 2, 64, 2, 67, 122 );
		anime->GetActionData( 15 )->SetMotionData( 3, 65, 2, 67, 122 );
		anime->GetActionData( 15 )->SetMotionData( 4, 66, 2, 67, 122 );
		anime->GetActionData( 15 )->SetMotionData( 5, 67, 2, 87, 126 );
		anime->GetActionData( 15 )->SetMotionData( 6, 68, 2, 87, 126 );
		anime->GetActionData( 15 )->SetMotionData( 7, 69, 5, 87, 126 );
		anime->GetActionData( 15 )->SetMotionData( 8, 70, 0, 87, 126 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 0, 0, 106, 53, 31+106 ,92+53 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 1, 0, 100, 52, 30+100 ,92+52 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 2, 0,  58, 29, 43+58  ,90+29 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 3, 0,  59, 30, 45+59  ,87+30 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 4, 0,  58, 29, 30+58  ,95+29 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 5, 0,  63, 43, 39+63  ,86+43 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 6, 0,  62, 51, 45+62  ,67+51 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 7, 0,  62, 51, 45+62  ,67+51 );
		anime->GetActionData( 15 )->SetWoundDataAbs( 8, 0,  66, 41, 41+66  ,87+41 );
		anime->GetActionData( 15 )->SetAttackData( 5, 0, 54, -90, -60, -127, ENUM_ATTACK_PROPERTY_JUMP );
		anime->GetActionData( 15 )->SetAttackData( 6, 0, -86, -4, -19, -102, ENUM_ATTACK_PROPERTY_JUMP );
		anime->GetActionData( 15 )->SetAttackSpec( 5, 500, 0, 0 );
		anime->GetActionData( 15 )->SetAttackSpec( 6, 500, 0, 0 );
/* matsu motion
		anime->SetAnimeData( 62, 62, 5, 119, 143 );
		anime->SetAnimeData( 63, 63, 6, 119, 143 );
		anime->SetAnimeData( 64, 64, 6, 66, 118 );
		anime->SetAnimeData( 65, 65, 6, 45, 111 );
		anime->SetAnimeData( 66, 66, 6, 45, 111 );
		anime->SetAnimeData( 67, 67, 3, 87, 126 );
		anime->SetAnimeData( 68, 68, 3, 87, 126 );
		anime->SetAnimeData( 69, 69, 1, 87, 126 );
		anime->SetAnimeData( 70, 70, 0, 87, 126 );
*/
		anime->CreateAction( 16, 5 );
		anime->GetActionData( 16 )->SetMotionData( 0, 155, 3, 44, 118 );
		anime->GetActionData( 16 )->SetMotionData( 1, 156, 3, 44, 118 );
		anime->GetActionData( 16 )->SetMotionData( 2, 157, 3, 69, 95 );
		anime->GetActionData( 16 )->SetMotionData( 3, 158, 0, 69, 95 );
		anime->GetActionData( 16 )->SetMotionData( 4, 159, 0, 44, 118 );

		// DOT_SHA_040.(JUMP_BACK_DUSH)
		anime->CreateAction( 17, 3 );
		anime->GetActionData( 17 )->SetMotionData( 0, 74, 3, 44, 114 );
		anime->GetActionData( 17 )->SetMotionData( 1, 75, 4, 44, 114 );
		anime->GetActionData( 17 )->SetMotionData( 2, 76, 0, 44, 114 );
		anime->GetActionData( 17 )->SetWoundDataAbs( 0, 0, 23, 32, 37+23, 83+32 );
		anime->GetActionData( 17 )->SetWoundDataAbs( 1, 0, 25, 32, 35+25, 83+32 );
		anime->GetActionData( 17 )->SetWoundDataAbs( 2, 0, 24, 31, 36+24, 85+31 );

		// damage
		anime->CreateAction( 18, 2 );
		anime->GetActionData( 18 )->SetMotionData( 0, 77, 5, 53, 95 );
		anime->GetActionData( 18 )->SetMotionData( 1, 78, 0, 53, 95 );
		anime->GetActionData( 18 )->SetWoundDataAbs( 0, 0, 45, 22, 81, 97 );
		anime->GetActionData( 18 )->SetWoundDataAbs( 1, 0, 45, 22, 81, 97 );

		// damage
		anime->CreateAction( 19, 2 );
		anime->GetActionData( 19 )->SetMotionData( 0, 79, 5, 90, 114 );
		anime->GetActionData( 19 )->SetMotionData( 1, 80, 0, 90, 114 );

		// DOT_SYA003->407.(MID)
		anime->CreateAction( 20, 6 );
		anime->GetActionData( 20 )->SetMotionData( 0, 81, 2, 36, 79 );
		anime->GetActionData( 20 )->SetMotionData( 1, 82, 3, 86, 79 );
		anime->GetActionData( 20 )->SetMotionData( 2, 83, 3, 50, 76 );
		anime->GetActionData( 20 )->SetMotionData( 3, 84, 20, 50, 75 );
		anime->GetActionData( 20 )->SetMotionData( 4, 85, 3, 43, 87 );
		anime->GetActionData( 20 )->SetMotionData( 5, 86, 0, 35, 87 );
//		anime->GetActionData( 20 )->SetMotionData( 6, 87, 0, 82, 114 );
		anime->GetActionData( 20 )->SetAttackData( 3, 0, -74, -100, -22, 0, ENUM_ATTACK_PROPERTY_HIGH );
		anime->GetActionData( 20 )->SetAttackSpec( 3, 300, 0, 0 );

		// DOT_SYA434.(CROUCH_MID)
		anime->CreateAction( 21, 4 );
		anime->GetActionData( 21 )->SetMotionData( 0, 88, 5, 97, 114 );
		anime->GetActionData( 21 )->SetMotionData( 1, 89, 5, 97, 114 );
		anime->GetActionData( 21 )->SetMotionData( 2, 90, 5, 97, 114 );
		anime->GetActionData( 21 )->SetMotionData( 3, 91, 0, 97, 114 );
		anime->GetActionData( 21 )->SetWoundDataAbs( 0, 0, 81, 52, 36+81, 65+52 );
		anime->GetActionData( 21 )->SetWoundDataAbs( 1, 0, 81, 51, 35+81, 66+51 );
		anime->GetActionData( 21 )->SetWoundDataAbs( 2, 0, 81, 52, 36+81, 65+52 );
		anime->GetActionData( 21 )->SetWoundDataAbs( 2, 1, 71, 75, 14+71, 14+75 );
		anime->GetActionData( 21 )->SetWoundDataAbs( 3, 0, 81, 52, 37+81, 65+52 );
		anime->GetActionData( 21 )->SetWoundDataAbs( 3, 1, 69, 74, 14+69, 14+74 );
		anime->GetActionData( 21 )->SetAttackData( 2, 0, -78, -30, -25, 0, ENUM_ATTACK_PROPERTY_LOW );
		anime->GetActionData( 21 )->SetAttackSpec( 2, 300, 0, 0 );

		// DOT_SYA419.(JUMP_LOW)
		anime->CreateAction( 22, 3 );
		anime->GetActionData( 22 )->SetMotionData( 0,101, 3, 44, 124 );
		anime->GetActionData( 22 )->SetMotionData( 1,101, 10, 44, 124 );
		anime->GetActionData( 22 )->SetMotionData( 2,100, 0, 44, 124 );
//		anime->GetActionData( 22 )->SetAttackData( 0, 0, -45, -20, 0, 0 );
		anime->GetActionData( 22)->SetWoundDataAbs( 0, 0,  35, 36, 47+35  ,47+36 );
		anime->GetActionData( 22)->SetWoundDataAbs( 0, 1,   4, 79,  45+4  ,30+79 );
		anime->GetActionData( 22)->SetWoundDataAbs( 1, 0,  35, 36, 47+35  ,47+36 );
		anime->GetActionData( 22)->SetWoundDataAbs( 1, 1,   4, 79,  45+4  ,30+79 );
		anime->GetActionData( 22)->SetWoundDataAbs( 2, 0,  41, 30, 34+41  ,56+30 );
		anime->GetActionData( 22)->SetWoundDataAbs( 2, 1,  20, 83, 40+20  ,36+83 );
		anime->GetActionData( 22 )->SetAttackData( 1, 0, -45, -20, 0, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
		anime->GetActionData( 22 )->SetAttackSpec( 1, 100, 0, 0 );

		// DOT_SYA420.(JUMP_MID)
		anime->CreateAction( 23, 5 );
		anime->GetActionData( 23 )->SetMotionData( 0,102, 3, 70, 125 );
		anime->GetActionData( 23 )->SetMotionData( 1,103, 4, 70, 125 );
		anime->GetActionData( 23 )->SetMotionData( 2,104, 4, 70, 125 );
//		anime->GetActionData( 23 )->SetAttackData( 2,0, -60, -52, -24, -32, ENUM_ATTACK_PROPERTY_JUMP );
		anime->GetActionData( 23 )->SetMotionData( 3,105, 4, 70, 125 );
		anime->GetActionData( 23 )->SetMotionData( 4,106, 0, 70, 125 );
		anime->GetActionData( 23)->SetWoundDataAbs( 0, 0, 55, 35, 33+55 ,93+35 );
		anime->GetActionData( 23)->SetWoundDataAbs( 1, 0, 47, 36, 47+47 ,93+36 );
		anime->GetActionData( 23)->SetWoundDataAbs( 2, 0, 52, 35, 43+52 ,90+35 );
		anime->GetActionData( 23)->SetWoundDataAbs( 2, 1, 12, 80, 43+12 ,13+80 );
		anime->GetActionData( 23)->SetWoundDataAbs( 3, 0, 52, 35, 43+52 ,90+35 );
		anime->GetActionData( 23)->SetWoundDataAbs( 3, 1, 14, 73, 42+14 ,17+73 );
		anime->GetActionData( 23)->SetWoundDataAbs( 4, 0, 49, 35, 35+49 ,93+35 );
		anime->GetActionData( 23 )->SetAttackData( 3,0, -60, -52, -24, -32, ENUM_ATTACK_PROPERTY_JUMP );
		anime->GetActionData( 23 )->SetAttackSpec( 3, 300, 0, 0 );

		// DOT_SYA203.(AERIAL_DAMAGE 1)
		anime->CreateAction( 24, 1 );
		anime->GetActionData( 24 )->SetMotionData( 0,110, 0, 71, 126 );
		anime->GetActionData( 24 )->SetWoundDataAbs( 0, 0, 61, 46, 38+61, 86+46 );
		anime->GetActionData( 24 )->SetWoundDataAbs( 0, 1, 41, 57, 76+41, 26+57 );
		// DOT_SYA203.(AERIAL_DAMAGE 2)
		anime->CreateAction( 25, 1 );
		anime->GetActionData( 25 )->SetMotionData( 0,111, 0, 71, 126 );
		anime->GetActionData( 25 )->SetWoundDataAbs( 0, 0, 40, 57, 78+40, 33+57 );
		anime->GetActionData( 25 )->SetWoundDataAbs( 0, 1, 66, 87, 63+66, 36+87 );
		// DOT_SYA204.(AERIAL_DAMAGE 3)
		anime->CreateAction( 26, 1 );
		anime->GetActionData( 26 )->SetMotionData( 0,112, 0, 71, 126 );
		anime->GetActionData( 26 )->SetWoundDataAbs( 0, 0, 52, 47, 44+52, 18+47 );
		anime->GetActionData( 26 )->SetWoundDataAbs( 0, 1, 78, 61, 53+78, 54+61 );
		// DOT_SYA204.(AERIAL_DAMAGE 4)
		anime->CreateAction( 27, 2 );
		anime->GetActionData( 27 )->SetMotionData( 0,113, 3, 71, 126 );
		anime->GetActionData( 27 )->SetMotionData( 1,114, 3, 71, 126 );
		anime->GetActionData( 27 )->SetWoundDataAbs( 0, 0, 59, 33, 42+59, 32+33 );
		anime->GetActionData( 27 )->SetWoundDataAbs( 0, 1, 82, 62, 47+82, 55+62 );
		anime->GetActionData( 27 )->SetWoundDataAbs( 1, 0, 59, 33, 42+59, 32+33 );
		anime->GetActionData( 27 )->SetWoundDataAbs( 1, 1, 82, 62, 47+82, 55+62 );

		// DOT_SYA601.(DOWN)
		anime->CreateAction( 28, 5 );
		anime->GetActionData( 28 )->SetMotionData( 0,115, 3, 71, 126 );
		anime->GetActionData( 28 )->SetMotionData( 1,116, 3, 71, 126 );
		anime->GetActionData( 28 )->SetMotionData( 2,117, 3, 71, 126 );
		anime->GetActionData( 28 )->SetMotionData( 3,118, 3, 71, 126 );
		anime->GetActionData( 28 )->SetMotionData( 4,119, 0, 71, 126 );
		anime->GetActionData( 28 )->SetWoundDataAbs( 0, 0, 53, 58, 33+53, 42+58 );
		anime->GetActionData( 28 )->SetWoundDataAbs( 0, 1, 64, 90, 52+64, 36+90 );
		anime->GetActionData( 28 )->SetWoundDataAbs( 1, 0, 34, 79, 81+34, 47+79 );
		anime->GetActionData( 28 )->SetWoundDataAbs( 2, 0, 32, 83, 84+32, 46+83 );
		anime->GetActionData( 28 )->SetWoundDataAbs( 3, 0, 32, 83, 84+32, 46+83 );
		anime->GetActionData( 28 )->SetWoundDataAbs( 4, 0, 34,115, 85+34, 17+115 );
		anime->GetActionData( 28 )->SetWoundDataAbs( 4, 1, 51, 91, 66+51, 28+91 );

		// DOT_SYA432.(CROUCH ATTACK HIGH)
		anime->CreateAction( 29, 11 );
		anime->GetActionData( 29 )->SetMotionData( 0,120, 10, 108, 144 );
		anime->GetActionData( 29 )->SetMotionData( 1,121, 3, 108, 144 );
		anime->GetActionData( 29 )->SetMotionData( 2,122, 3, 101, 123 );
		anime->GetActionData( 29 )->SetMotionData( 3,123, 3, 101, 123 );
		anime->GetActionData( 29 )->SetMotionData( 4,124, 5, 101, 123 );
		anime->GetActionData( 29 )->SetMotionData( 5,125, 5, 101, 123 );
		anime->GetActionData( 29 )->SetMotionData( 6,126, 5, 101, 123 );
		anime->GetActionData( 29 )->SetMotionData( 7,127, 5, 101, 123 );
		anime->GetActionData( 29 )->SetMotionData( 8,128, 5, 43, 122 );
		anime->GetActionData( 29 )->SetMotionData( 9,129, 5, 43, 122 );
		anime->GetActionData( 29 )->SetMotionData( 10,130, 0, 43, 122 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 0, 0, 88, 79, 43+88, 68+79 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 1, 0, 87, 78, 43+87, 68+78 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 2, 0, 85, 47, 30+85, 77+47 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 3, 0, 85, 47, 30+85, 77+47 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 4, 0, 85, 47, 30+85, 77+47 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 5, 0, 85, 47, 30+85, 77+47 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 6, 0, 85, 47, 30+85, 77+47 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 7, 0, 85, 54, 44+85, 70+54 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 8, 0, 25, 60, 36+25, 64+60 );
		anime->GetActionData( 29 )->SetWoundDataAbs( 9, 0, 25, 60, 36+25, 64+60 );
		anime->GetActionData( 29 )->SetWoundDataAbs(10, 0, 25, 60, 36+25, 64+60 );
		anime->GetActionData( 29 )->SetAttackData( 2, 0, -64, -77, 0, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
		anime->GetActionData( 29 )->SetAttackSpec( 2, 600, 0, 0 );

		// DOT_SYA032.(STAND_GUARD)
		anime->CreateAction( 30, 2 );
		anime->GetActionData( 30 )->SetMotionData( 0,131, 8, 60, 115 );
		anime->GetActionData( 30 )->SetMotionData( 1,132, 0, 60, 115 );
		anime->GetActionData( 30 )->SetWoundDataAbs( 0, 0, 41, 34, 32+41, 82+34 );
		anime->GetActionData( 30 )->SetWoundDataAbs( 0, 1, 70, 79, 43+70, 13+79 );
		anime->GetActionData( 30 )->SetWoundDataAbs( 1, 0, 41, 32, 37+41, 84+32 );
		anime->GetActionData( 30 )->SetWoundDataAbs( 1, 1, 73, 78, 55+73, 9+78 );
		anime->CreateAction( 31, 1 );
		anime->GetActionData( 31 )->SetMotionData( 0,132, 0, 60, 115 );
		anime->GetActionData( 31 )->SetWoundDataAbs( 0, 0, 41, 32, 37+41, 84+32 );
		anime->GetActionData( 31 )->SetWoundDataAbs( 0, 1, 73, 78, 55+73, 9+78 );
		// DOT_SYA048.(CROUCH_GUARD)
		// ＊＊絵が逆
		anime->CreateAction( 32, 2 );
		anime->GetActionData( 32 )->SetMotionData( 0,133, 2, 93, 115 );
		anime->GetActionData( 32 )->SetMotionData( 1,134, 0, 93, 115 );
		anime->GetActionData( 32 )->SetWoundDataAbs( 0, 0, 80, 52, 34+80, 66+52 );
		anime->GetActionData( 32 )->SetWoundDataAbs( 0, 1, 22, 84, 65+22, 13+84 );
		anime->GetActionData( 32 )->SetWoundDataAbs( 1, 0, 76, 40, 38+76, 78+40 );
		anime->GetActionData( 32 )->SetWoundDataAbs( 1, 1, 41, 62, 46+41, 55+62 );

		// DOT_SYA210.(JUMP_DAMAGE)
		anime->CreateAction( 33, 2 );
		anime->GetActionData( 33 )->SetMotionData( 0,140, 3, 50, 112 );
		anime->GetActionData( 33 )->SetMotionData( 1,141, 0, 50, 112 );
		anime->GetActionData( 33 )->SetWoundData( 0, 0, -13, -50, 17, 0 );
		anime->GetActionData( 33 )->SetWoundData( 1, 0, -13, -50, 17, 0 );

		// DOT_SYA050.(JUMP_GUARD)
		anime->CreateAction( 34, 2 );
		anime->GetActionData( 34 )->SetMotionData( 0,135, 3, 60, 116 );
		anime->GetActionData( 34 )->SetMotionData( 1,136, 3, 60, 116 );
		anime->GetActionData( 34 )->SetWoundDataAbs( 0, 0, 47, 33, 31+47, 93+33 );
		anime->GetActionData( 34 )->SetWoundDataAbs( 1, 0, 47, 33, 31+47, 93+33 );

		// DOT_SYA202.(BIG_DAMAGE)
		anime->CreateAction( 35, 3 );
		anime->GetActionData( 35 )->SetMotionData( 0,135, 3, 38, 64 );
		anime->GetActionData( 35 )->SetMotionData( 1,136, 3, 38, 64 );
		anime->GetActionData( 35 )->SetMotionData( 2,137, 3, 38, 64 );

		// DOT_SYA602.(GET_UP)
		anime->CreateAction( 36, 3 );
		anime->GetActionData( 36 )->SetMotionData( 0,185, 5, 71, 126 );
		anime->GetActionData( 36 )->SetMotionData( 1,186, 5, 71, 126 );
		anime->GetActionData( 36 )->SetMotionData( 2,187, 0, 71, 126 );

		// DOT_SYA202.(BLOW DOWN)
		anime->CreateAction( 40, 3 );
		anime->GetActionData( 40 )->SetMotionData( 0,210, 3, 68, 85 );
		anime->GetActionData( 40 )->SetMotionData( 1,211, 3, 68, 85 );
		anime->GetActionData( 40 )->SetMotionData( 2,212, 3, 68, 85 );

		// DOT_SYA201.(WALL BOUND)
		anime->CreateAction( 41, 1 );
		anime->GetActionData( 41 )->SetMotionData( 0,214, 3, 68, 85 );

		// DOT_SYA208.(RECOVER)
		anime->CreateAction( 42, 5 );
		anime->GetActionData( 42 )->SetMotionData( 0,220, 3, 100, 98 );
		anime->GetActionData( 42 )->SetMotionData( 1,221, 3, 100, 98 );
		anime->GetActionData( 42 )->SetMotionData( 2,222, 3, 100, 98 );
		anime->GetActionData( 42 )->SetMotionData( 3,223, 3, 100, 98 );
		anime->GetActionData( 42 )->SetMotionData( 4,224, 0, 100, 98 );

		// DOT_SYA414.(THROW)
		anime->CreateAction( 50, 1 );
		anime->GetActionData( 50 )->SetMotionData( 0,160, 0, 71, 106 );
		anime->GetActionData( 50 )->SetWoundDataAbs( 0, 0, 22, 30, 54+22, 42+30 );
		anime->GetActionData( 50 )->SetWoundDataAbs( 0, 1, 57, 71, 44+57, 37+71 );
		anime->CreateAction( 51, 8 );
		anime->GetActionData( 51 )->SetMotionData( 0,161, 3, 71, 106 );
		anime->GetActionData( 51 )->SetMotionData( 1,162, 3, 71, 106 );
		anime->GetActionData( 51 )->SetMotionData( 2,163, 3, 71, 106 );
		anime->GetActionData( 51 )->SetMotionData( 3,164, 3, 71, 106 );
		anime->GetActionData( 51 )->SetMotionData( 4,165, 3, 106, 109 );
		anime->GetActionData( 51 )->SetMotionData( 5,166, 3, 106, 109 );
		anime->GetActionData( 51 )->SetMotionData( 6,167, 3, 106, 109 );
		anime->GetActionData( 51 )->SetMotionData( 7,168, 0, 106, 109 );
		anime->CreateAction( 52, 3 );
		anime->GetActionData( 52 )->SetMotionData( 0,169, 3, 106, 109 );
		anime->GetActionData( 52 )->SetMotionData( 1,170, 3, 47, 109 );
		anime->GetActionData( 52 )->SetMotionData( 2,171, 3, 47, 109 );

		// DOT_SYA413.(MISS THROW)
		anime->CreateAction( 53, 2 );
		anime->GetActionData( 53 )->SetMotionData( 0,173, 5, 94, 113 );
		anime->GetActionData( 53 )->SetMotionData( 1,174, 0, 94, 113 );
		anime->GetActionData( 53 )->SetWoundDataAbs( 0, 0, 41, 43, 54+41, 38+43 );
		anime->GetActionData( 53 )->SetWoundDataAbs( 0, 1, 80, 79, 39+80, 36+79 );
		anime->GetActionData( 53 )->SetWoundDataAbs( 1, 0, 33, 45, 56+33, 38+45 );
		anime->GetActionData( 53 )->SetWoundDataAbs( 1, 1, 74, 80, 42+74, 36+80 );

		// DOT_SYA421.(JUMP ATTACK EX)
		anime->CreateAction( 55, 8 );
		anime->GetActionData( 55 )->SetMotionData( 0,175, 10, 93, 115 );
		anime->GetActionData( 55 )->SetMotionData( 1,176, 3, 93, 122 );
		anime->GetActionData( 55 )->SetMotionData( 2,177, 3, 93, 129 );
		anime->GetActionData( 55 )->SetMotionData( 3,178, 3, 93, 136 );
		anime->GetActionData( 55 )->SetMotionData( 4,179, 3, 93, 143 );
		anime->GetActionData( 55 )->SetMotionData( 5,180, 3, 93, 150 );
		anime->GetActionData( 55 )->SetMotionData( 6,181, 3, 93, 157 );
		anime->GetActionData( 55 )->SetMotionData( 7,182, 0, 93, 164 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 0, 0, 82, 29, 34+82 ,88+29 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 1, 0, 76, 58, 53+76 ,37+58 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 1, 1,105, 93,27+105 ,19+93 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 2, 0, 85, 77, 52+85 ,38+77 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 3, 0, 83, 82, 52+83 ,57+82 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 4, 0, 84, 77, 25+84 ,48+77 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 4, 1,110,106,31+111 ,27+106 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 5, 0, 76,111, 67+76 ,26+111 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 5, 1,114, 93,30+114 ,23+93 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 6, 0, 86, 76, 38+86 ,86+76 );
		anime->GetActionData( 55 )->SetWoundDataAbs( 7, 0, 78, 73, 34+82 ,95+29 );
		anime->GetActionData( 55 )->SetAttackData( 3, 0, -36, -98, 0, 0, ENUM_ATTACK_PROPERTY_MIDDLE );
		anime->GetActionData( 55 )->SetAttackData( 3, 1, -27, 0, 62, 62, ENUM_ATTACK_PROPERTY_MIDDLE );
		anime->GetActionData( 55 )->SetAttackSpec( 3, 600, 0, 0 );

		// DOT_SYA203.2(AERIAL_DAMAGE 1)
		anime->CreateAction( 56, 1 );
		anime->GetActionData( 56 )->SetMotionData( 0,111, 0, 71, 126 );
		// DOT_SYA203.2(AERIAL_DAMAGE 2)
		anime->CreateAction( 57, 1 );
		anime->GetActionData( 57 )->SetMotionData( 0,112, 0, 71, 126 );
		// DOT_SYA204.2(AERIAL_DAMAGE 3)
		anime->CreateAction( 58, 2 );
		anime->GetActionData( 58 )->SetMotionData( 0,113, 3, 71, 126 );
		anime->GetActionData( 58 )->SetMotionData( 1,114, 3, 71, 126 );

		// DOT_SYA801.(SPECIAL1)
		anime->CreateAction( 60, 4 );
		anime->GetActionData( 60 )->SetMotionData( 0,150, 5, 55, 100 );
		anime->GetActionData( 60 )->SetMotionData( 1,151, 5, 55, 100 );
		anime->GetActionData( 60 )->SetMotionData( 2,152, 3, 55, 105 );
		anime->GetActionData( 60 )->SetMotionData( 3,153, 0, 55, 105 );
		anime->GetActionData( 60 )->SetWoundDataAbs( 0, 0, 39, 33, 33+39 ,75+33 );
		anime->GetActionData( 60 )->SetWoundDataAbs( 1, 0, 32, 39, 39+32 ,63+39 );
		anime->GetActionData( 60 )->SetWoundDataAbs( 2, 0, 16, 95, 42+16 ,39+95 );
		anime->GetActionData( 60 )->SetWoundDataAbs( 2, 1, 58, 66, 35+58 ,57+66 );
		anime->GetActionData( 60 )->SetWoundDataAbs( 3, 0, 16, 95, 42+16 ,39+95 );
		anime->GetActionData( 60 )->SetWoundDataAbs( 3, 1, 58, 66, 35+58 ,57+66 );
		anime->GetActionData( 60 )->SetAttackDataAbs( 3, 0, 16, 95, 42+16 ,39+95 );
		anime->GetActionData( 60 )->SetAttackDataAbs( 3, 1, 58, 66, 35+58 ,57+66 );
		anime->GetActionData( 60 )->SetAttackSpec( 3, 400, 0, 0 );
		anime->CreateAction( 61, 1 );
		anime->GetActionData( 61 )->SetMotionData( 0,154, 0, 40, 115 );
		anime->GetActionData( 61 )->SetWoundDataAbs( 0, 0, 18, 46, 42+18 ,71+46 );

		// DOT_SYA802.(SPECIAL2)
		anime->CreateAction( 63, 9 );
		anime->GetActionData( 63 )->SetMotionData( 0,190, 5, 55, 114 );
		anime->GetActionData( 63 )->SetMotionData( 1,191, 5, 55, 114 );
		anime->GetActionData( 63 )->SetMotionData( 2,192, 7, 55, 114 );
		anime->GetActionData( 63 )->SetMotionData( 3,193, 7, 55, 114 );
		anime->GetActionData( 63 )->SetMotionData( 4,194, 7, 55, 114 );
		anime->GetActionData( 63 )->SetMotionData( 5,195, 7, 55, 114 );
		anime->GetActionData( 63 )->SetMotionData( 6,196, 7, 55, 114 );
		anime->GetActionData( 63 )->SetMotionData( 7,197, 7, 53, 111 );
		anime->GetActionData( 63 )->SetMotionData( 8,198, 0, 53, 111 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 0, 0, 36, 36, 40+36 ,81+36 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 1, 0, 36, 37, 37+36 ,81+37 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 1, 1, 21, 66, 28+21 ,16+66 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 2, 0, 36, 35, 40+36 ,82+35 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 2, 1, 15, 53, 30+15 ,20+53 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 3, 0, 36, 35, 40+36 ,82+35 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 3, 1, 15, 53, 30+15 ,20+53 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 4, 0, 36, 35, 40+36 ,82+35 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 4, 1, 15, 53, 30+15 ,20+53 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 5, 0, 36, 35, 40+36 ,82+35 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 5, 1, 15, 53, 30+15 ,20+53 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 6, 0, 37, 37, 35+37 ,80+37 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 6, 1, 21, 65, 27+21 ,16+65 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 7, 0, 35, 32, 36+35 ,83+32 );
		anime->GetActionData( 63 )->SetWoundDataAbs( 8, 0, 35, 32, 36+35 ,83+32 );

		// DOT_SYA803.(SPECIAL3)
		anime->CreateAction( 65, 8 );
		anime->GetActionData( 65 )->SetMotionData( 0,200, 10, 129, 142 );
		anime->GetActionData( 65 )->SetMotionData( 1,201, 3, 129, 142 );
		anime->GetActionData( 65 )->SetMotionData( 2,202, 1, 129, 142 );
		anime->GetActionData( 65 )->SetMotionData( 3,203, 1, 129, 142 );
		anime->GetActionData( 65 )->SetMotionData( 4,204, 1, 129, 142 );
		anime->GetActionData( 65 )->SetMotionData( 5,205, 3, 129, 142 );
		anime->GetActionData( 65 )->SetMotionData( 6,206, 3, 129, 142 );
		anime->GetActionData( 65 )->SetMotionData( 7,207, 0, 129, 142 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 0, 0,113, 62, 34+113 ,87+62 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 1, 0,101, 59, 51+101 ,49+59 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 1, 1,113,104, 28+113 ,45+104 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 2, 0,108, 63, 41+108 ,39+63 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 2, 1, 87, 90, 31+87  ,12+90 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 2, 2,118,102, 30+118 ,49+102 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 3, 0,106, 64, 45+106 ,55+64 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 3, 1,118,114, 29+118 ,35+114 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 4, 0,108, 67, 44+108 ,56+67 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 4, 1,121,119, 19+121 ,27+119 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 5, 0,106, 66, 47+106 ,53+66 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 5, 1,111,117, 35+111 ,29+117 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 6, 0,111, 65, 37+111 ,83+65 );
		anime->GetActionData( 65 )->SetWoundDataAbs( 7, 0,102, 56, 31+102 ,88+56 );

		// DOT_SYA017.1(CROUCH_EX 1)
		anime->CreateAction( 66, 1 );
		anime->GetActionData( 66 )->SetMotionData( 0,230, 0, 48, 107 );
		anime->GetActionData( 66 )->SetWoundDataAbs( 0,0, 27, 35, 40+27, 76+35 );
		// DOT_SYA017.2(CROUCH_EX 2)
		anime->CreateAction( 67, 2 );
		anime->GetActionData( 67 )->SetMotionData( 0,231, 3, 48, 107 );
		anime->GetActionData( 67 )->SetMotionData( 1,232, 3, 48, 107 );
		anime->GetActionData( 67 )->SetWoundDataAbs( 0, 0, 10, 44, 72+10, 69+44 );
		anime->GetActionData( 67 )->SetWoundDataAbs( 1, 0, 10, 44, 72+10, 69+44 );
		anime->GetActionData( 67 )->SetAttackData( 0, 0, -38, 4, 3, -19, ENUM_ATTACK_PROPERTY_LOW );
		anime->GetActionData( 67 )->SetAttackData( 1, 0, -38, 4, 3, -19, ENUM_ATTACK_PROPERTY_LOW );
		anime->GetActionData( 67 )->SetAttackSpec( 0, 100, 0, 0 );
		anime->GetActionData( 67 )->SetAttackSpec( 1, 100, 0, 0 );
		// DOT_SYA017.3(CROUCH_EX 3)
		anime->CreateAction( 68, 1 );
		anime->GetActionData( 68 )->SetMotionData( 0,233, 3, 48, 107 );
		anime->GetActionData( 68 )->SetWoundDataAbs( 0, 0, 26, 36, 46+26, 75+36 );

		// DOT_SYA003(crouch 003)
		anime->CreateAction( 70, 7 );
		anime->GetActionData( 70 )->SetMotionData( 0,230, 0, 48, 107 );
		anime->GetActionData( 70 )->SetMotionData( 1,230, 0, 48, 107 );
		anime->GetActionData( 70 )->SetMotionData( 2,230, 0, 48, 107 );
		anime->GetActionData( 70 )->SetMotionData( 3,230, 0, 48, 107 );
		anime->GetActionData( 70 )->SetMotionData( 4,230, 0, 48, 107 );
		anime->GetActionData( 70 )->SetMotionData( 5,230, 0, 48, 107 );
		anime->GetActionData( 70 )->SetMotionData( 6,230, 0, 48, 107 );
		anime->GetActionData( 70 )->SetWoundDataAbs( 5,0, 27, 35, 40+27, 76+35 );

		// 以降てすつ
/*		anime->CreateAction( 50, 5 );
		anime->GetActionData( 50 )->SetMotionData( 0, 0, 4, 0, 0 );
		anime->GetActionData( 50 )->SetMotionData( 1, 1, 4, 0, 0 );
		anime->GetActionData( 50 )->SetMotionData( 2, 2, 4, 0, 0 );
		anime->GetActionData( 50 )->SetMotionData( 3, 3, 4, 0, 0 );
		anime->GetActionData( 50 )->SetMotionData( 4, 4, 4, 0, 0 );
		anime->CreateAction( 51, 5 );
		anime->GetActionData( 51 )->SetMotionData( 0, 5, 4, 0, 0 );
		anime->GetActionData( 51 )->SetMotionData( 1, 6, 4, 0, 0 );
		anime->GetActionData( 51 )->SetMotionData( 2, 7, 4, 0, 0 );
		anime->GetActionData( 51 )->SetMotionData( 3, 8, 4, 0, 0 );
		anime->GetActionData( 51 )->SetMotionData( 4, 9, 4, 0, 0 );
		anime->CreateAction( 52, 5 );
		anime->GetActionData( 52 )->SetMotionData( 0, 10, 4, 0, 0 );
		anime->GetActionData( 52 )->SetMotionData( 1, 11, 4, 0, 0 );
		anime->GetActionData( 52 )->SetMotionData( 2, 12, 4, 0, 0 );
		anime->GetActionData( 52 )->SetMotionData( 3, 13, 4, 0, 0 );
		anime->GetActionData( 52 )->SetMotionData( 4, 14, 4, 0, 0 );
		anime->CreateAction( 53, 5 )
		anime->GetActionData( 53 )->SetMotionData( 0, 15, 4, 0, 0 );
		anime->GetActionData( 53 )->SetMotionData( 1, 16, 4, 0, 0 );
		anime->GetActionData( 53 )->SetMotionData( 2, 17, 4, 0, 0 );
		anime->GetActionData( 53 )->SetMotionData( 3, 18, 4, 0, 0 );
		anime->GetActionData( 53 )->SetMotionData( 4, 19, 4, 0, 0 );
		anime->CreateAction( 54, 5 );
		anime->GetActionData( 54 )->SetMotionData( 0, 20, 4, 0, 0 );
		anime->GetActionData( 54 )->SetMotionData( 1, 21, 4, 0, 0 );
		anime->GetActionData( 54 )->SetMotionData( 2, 22, 4, 0, 0 );
		anime->GetActionData( 54 )->SetMotionData( 3, 23, 4, 0, 0 );
		anime->GetActionData( 54 )->SetMotionData( 4, 24, 4, 0, 0 );

		anime->CreateAction( 60, 10 );
		anime->GetActionData( 60 )->SetMotionData( 0, 0, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 1, 1, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 2, 2, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 3, 3, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 4, 4, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 5, 5, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 6, 6, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 7, 7, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 8, 8, 4, 0, 0 );
		anime->GetActionData( 60 )->SetMotionData( 9, 9, 4, 0, 0 );
*/

		break;

	case ANIME_NO_EFF_SHANA_OPT:
	case ANIME_NO_EFF_SHANA_OPT_PARTS:
	case ANIME_NO_EFF_TEST:
		anime->CreateAction( 0, 46 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 7, 7, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 8, 8, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 9, 9, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 10, 10, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 11, 11, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 12, 12, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 13, 13, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 14, 14, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 15, 15, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 16, 16, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 17, 17, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 18, 18, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 19, 19, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 20, 20, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 21, 21, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 22, 22, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 23, 23, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 24, 24, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 25, 25, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 26, 26, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 27, 27, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 28, 28, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 29, 29, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 30, 30, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 31, 31, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 32, 32, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 33, 33, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 34, 34, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 35, 35, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 36, 36, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 37, 37, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 38, 38, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 39, 39, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 40, 40, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 41, 41, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 42, 42, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 43, 43, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 44, 44, 1, 320, 240 );
		anime->GetActionData( 0 )->SetMotionData( 45, 45, 1, 320, 240 );
		break;

	case ANIME_NO_SYS_TIMER:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 100, 100 );
		anime->CreateAction( 1, 1 );
		anime->GetActionData( 1 )->SetMotionData( 0, 1, 0, 100, 100 );
		anime->CreateAction( 2, 10 );
		anime->GetActionData( 2 )->SetMotionData( 0, 2, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 1, 3, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 2, 4, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 3, 5, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 4, 6, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 5, 7, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 6, 8, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 7, 9, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 8, 10, 0, 32, 32 );
		anime->GetActionData( 2 )->SetMotionData( 9, 11, 0, 32, 32 );
		anime->CreateAction( 3, 1 );
		anime->GetActionData( 3 )->SetMotionData( 0, 12, 0, 86, 66 );
		break;

	case ANIME_NO_SYS_SCN_BACK:
	case ANIME_NO_SYS_SCN_BACK_MISAGO:
	case ANIME_NO_SYS_LOGO_2:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->CreateAction( 1, 1 );
		anime->GetActionData( 1 )->SetMotionData( 0, 1, 0, 0, 0 );
		break;

	case ANIME_NO_SYS_SCN_HP_GAUGE:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->CreateAction( 1, 2 );
		anime->GetActionData( 1 )->SetMotionData( 0, 1, 0, 0, 0 );
		anime->GetActionData( 1 )->SetMotionData( 1, 2, 0, 0, 0 );
		break;

	case ANIME_NO_SYS_SCN_SP_GAUGE:
		anime->CreateAction( 0, 4 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 0, 0, 0 );
		anime->CreateAction( 1, 5 );
		anime->GetActionData( 1 )->SetMotionData( 0, 5, 3, 90, 90 );
		anime->GetActionData( 1 )->SetMotionData( 1, 6, 3, 90, 90 );
		anime->GetActionData( 1 )->SetMotionData( 2, 7, 3, 90, 90 );
		anime->GetActionData( 1 )->SetMotionData( 3, 8, 3, 90, 90 );
		anime->GetActionData( 1 )->SetMotionData( 4, 9, 3, 90, 90 );
		anime->CreateAction( 2, 5 );
		anime->GetActionData( 2 )->SetMotionData( 0,10, 3, 90, 90 );
		anime->GetActionData( 2 )->SetMotionData( 1,12, 3, 90, 90 );
		anime->GetActionData( 2 )->SetMotionData( 2,12, 3, 90, 90 );
		anime->GetActionData( 2 )->SetMotionData( 3,13, 3, 90, 90 );
		anime->GetActionData( 2 )->SetMotionData( 4,14, 3, 90, 90 );
		anime->CreateAction( 3, 5 );
		anime->GetActionData( 3 )->SetMotionData( 0, 15, 3, 90, 90 );
		anime->GetActionData( 3 )->SetMotionData( 1, 16, 3, 90, 90 );
		anime->GetActionData( 3 )->SetMotionData( 2, 17, 3, 90, 90 );
		anime->GetActionData( 3 )->SetMotionData( 3, 18, 3, 90, 90 );
		anime->GetActionData( 3 )->SetMotionData( 4, 19, 3, 90, 90 );
		anime->CreateAction( 4, 5 );
		anime->GetActionData( 4 )->SetMotionData( 0, 20, 3, 90, 90 );
		anime->GetActionData( 4 )->SetMotionData( 1, 21, 3, 90, 90 );
		anime->GetActionData( 4 )->SetMotionData( 2, 22, 3, 90, 90 );
		anime->GetActionData( 4 )->SetMotionData( 3, 23, 3, 90, 90 );
		anime->GetActionData( 4 )->SetMotionData( 4, 24, 3, 90, 90 );
		anime->CreateAction( 5, 5 );
		anime->GetActionData( 5 )->SetMotionData( 0, 25, 3, 90, 90 );
		anime->GetActionData( 5 )->SetMotionData( 1, 26, 3, 90, 90 );
		anime->GetActionData( 5 )->SetMotionData( 2, 27, 3, 90, 90 );
		anime->GetActionData( 5 )->SetMotionData( 3, 28, 3, 90, 90 );
		anime->GetActionData( 5 )->SetMotionData( 4, 29, 3, 90, 90 );
		anime->CreateAction( 6,2 );
		anime->GetActionData( 6 )->SetMotionData( 0, 30, 0,	0, 0 );
		anime->GetActionData( 6 )->SetMotionData( 1, 31, 0,	0, 0 );
		break;

	case ANIME_NO_EFF_HIT_001:
		anime->CreateAction( 0, 6 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 250, 45 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 5, 280, 207 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 5, 280, 207 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 5, 280, 207 );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 5, 280, 207 );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 5, 280, 207 );
		break;

	case ANIME_NO_SYS_SCN_COMBO_INFO:
		anime->CreateAction( 0, 11 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 7, 7, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 8, 8, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 9, 9, 0, 64, 64 );
		anime->GetActionData( 0 )->SetMotionData( 10, 10, 0, 64, 32 );
		break;

	case ANIME_NO_SYS_ENDAN:
		anime->CreateAction( 0, 6 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 3, 200, 45 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 3, 200, 45 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 3, 200, 45 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 3, 200, 45 );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 3, 200, 45 );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 3, 200, 45 );
		anime->GetActionData( 0 )->SetAttackDataAbs(0, 0, 160, 35, 235, 50, 1 ); 
		anime->GetActionData( 0 )->SetAttackDataAbs(1, 0, 160, 35, 235, 50, 1 ); 
		anime->GetActionData( 0 )->SetAttackDataAbs(2, 0, 160, 35, 235, 50, 1 ); 
		anime->GetActionData( 0 )->SetAttackDataAbs(3, 0, 160, 35, 235, 50, 1 ); 
		anime->GetActionData( 0 )->SetAttackDataAbs(4, 0, 160, 35, 235, 50, 1 ); 
		anime->GetActionData( 0 )->SetAttackDataAbs(5, 0, 160, 35, 235, 50, 1 ); 
		anime->GetActionData( 0 )->SetAttackSpec(0, 400, 0, 0);
		break;

	case ANIME_NO_EFF_HIT_002:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 84, 84 );
		break;

	case ANIME_NO_EFF_HIT_003:
	case ANIME_NO_EFF_X:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 1, 1 );
		break;

	case ANIME_NO_EFF_HIT_004_1:
	case ANIME_NO_EFF_HIT_004_2:
		tmpx = 48;
		tmpy = 90;
		anime->CreateAction( 0, 8 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 2, 4+tmpx, 86+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 3, 12+tmpx, 182+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 4, 31+tmpx, 244+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 3, 13+tmpx, 210+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 2, 13+tmpx, 155+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 2, 11+tmpx, 153+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 2, 15+tmpx, 143+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 7, 7, 3, 14+tmpx, 140+tmpy );
		tmpx = 48;
		anime->CreateAction( 1, 8 );
		anime->GetActionData( 1 )->SetMotionData( 0, 10, 2, 8+tmpx, 107+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 1, 11, 3, 5+tmpx, 114+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 2, 12, 4, 5+tmpx, 153+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 3, 13, 3, 6+tmpx, 88+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 4, 14, 2, 7+tmpx, 84+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 5, 15, 2, 8+tmpx, 84+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 6, 16, 2, 9+tmpx, 86+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 7, 17, 3, 4+tmpx, 90+tmpy );
		break;

	case ANIME_NO_EFF_HIT_005:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 75, 75);
		break;

	case ANIME_NO_EFF_GUARD_001:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 50, 80);
		break;

	case ANIME_NO_EFF_HIT_006:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 70, 85);
		break;

	case ANIME_NO_EFF_HIT_007_1:
	case ANIME_NO_EFF_HIT_007_2:
		tmpx = 48;
		tmpy = 90;
		anime->CreateAction( 0, 14 );
//		anime->GetActionData( 0 )->SetMotionData( 0, 0, 1, 12+tmpx, 90+tmpy );
//		anime->GetActionData( 0 )->SetMotionData( 1, 1, 1, 10+tmpx, 170+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 0, 2, 2, 28+tmpx, 231+tmpy );
//		anime->GetActionData( 0 )->SetMotionData( 3, 3, 1, 12+tmpx, 190+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 1, 4, 2, 10+tmpx, 159+tmpy );
//		anime->GetActionData( 0 )->SetMotionData( 1, 5, 2, 8+tmpx, 86+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 2, 6, 2, 10+tmpx, 65+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 3, 7, 3, 8+tmpx, 23+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 4, 8, 3, 10+tmpx, 14+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 5, 9, 3, 9+tmpx, 11+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 6, 10, 3, 11+tmpx, 11+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 7, 11, 3, 9+tmpx, 10+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 8, 12, 3, 8+tmpx, 10+tmpy );
		anime->GetActionData( 0 )->SetMotionData( 9, 13, 0, 7+tmpx, 8+tmpy );
		tmpx = 48;
		anime->CreateAction( 1, 14 );
//		anime->GetActionData( 1 )->SetMotionData( 0, 15, 1, 9+tmpx, 96+tmpy );
//		anime->GetActionData( 1 )->SetMotionData( 1, 16, 1, 10+tmpx, 110+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 0, 17, 2, 10+tmpx, 148+tmpy );
//		anime->GetActionData( 1 )->SetMotionData( 3, 18, 1, 10+tmpx, 75+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 1, 19, 2, 10+tmpx, 69+tmpy );
//		anime->GetActionData( 1 )->SetMotionData( 1, 20, 2, 11+tmpx, 33+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 2, 21, 2, 12+tmpx, 35+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 3, 22, 3, 9+tmpx, 23+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 4, 23, 3, 9+tmpx, 12+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 5, 24, 3, 9+tmpx, 10+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 6, 25, 3, 11+tmpx, 11+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 7, 26, 3, 12+tmpx, 10+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 8, 27, 3, 13+tmpx, 12+tmpy );
		anime->GetActionData( 1 )->SetMotionData( 9, 28, 0, 16+tmpx, 19+tmpy );
		break;

	case ANIME_NO_EFF_ACTION_02_1:
	case ANIME_NO_EFF_ACTION_02_2:
	case ANIME_NO_EFF_HIT_004_3:
	case ANIME_NO_EFF_HIT_004_4:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 22, 128);
		anime->CreateAction( 1, 1 );
		anime->GetActionData( 1 )->SetMotionData( 0, 1, 0, 15, 102);
		break;

	case ANIME_NO_EFF_ATTACK_001:
		anime->CreateAction( 0, 7 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 3, 62, 120);
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 3, 62, 120);
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 3, 62, 120);
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 3, 62, 120);
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 3, 62, 120);
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 3, 62, 120);
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 0, 62, 120);
		break;

	case ANIME_NO_EFF_ACTION_01:
		anime->CreateAction( 0, 11 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 7, 7, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 8, 8, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData( 9, 9, 1, 120, 17);
		anime->GetActionData( 0 )->SetMotionData(10,10, 0, 120, 17);
		break;

	case ANIME_NO_EFF_HIT_008:
		anime->CreateAction( 0, 30 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 7, 7, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 8, 8, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 9, 9, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 10, 10, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 11, 11, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 12, 12, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 13, 13, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 14, 14, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 15, 15, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 16, 16, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 17, 17, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 18, 18, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 19, 19, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 20, 20, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 21, 21, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 22, 22, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 23, 23, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 24, 24, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 25, 25, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 26, 26, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 27, 27, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 28, 28, 1, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 29, 29, 1, 100, 100);
		break;

	case ANIME_NO_EFF_ACTION_003:
		anime->CreateAction( 0, 4 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 2, 100, 75);
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 2, 100, 75);
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 2, 100, 75);
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 0, 100, 75);
		break;

	case ANIME_NO_EFF_HIT_009:
	case ANIME_NO_EFF_HIT_010:
		anime->CreateAction( 0, 6 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 2, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 2, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 2, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 2, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 2, 100, 100);
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 2, 100, 100);
		break;

	case ANIME_NO_EFF_HIT_011:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 5, 0);
		break;

	// タイトル画面
	case ANIME_NO_SYS_TITLE:
	case ANIME_NO_SYS_ATTACK_AREA:
		anime->CreateAction( 0, 1 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 400, 300 );
	break;

	case ANIME_NO_SYS_TITLE_ROD:
		anime->CreateAction( 0, 20 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 7, 7, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 8, 8, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 9, 9, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 10, 10, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 11, 11, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 12, 12, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 13, 13, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 14, 14, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 15, 15, 2, 205, 240 );
		anime->GetActionData( 0 )->SetMotionData( 16, 16, 0, 400, 300 );
		anime->GetActionData( 0 )->SetMotionData( 17, 17, 0, 380, 157 );
		anime->GetActionData( 0 )->SetMotionData( 18, 18, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 19, 19, 0, 280, 118 );
	break;

	case ANIME_NO_SYS_TITLE_FLASH:
	case ANIME_NO_SYS_TITLE_LOGO:
	case ANIME_NO_SYS_TITLE_PART_B:
		anime->CreateAction( 0, 3 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 294, 294 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 286, 118 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 0, 400, 300 );
	break;

	case ANIME_NO_SYS_TITLE_MENU:
		anime->CreateAction( 0, 13 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 7, 7, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 8, 8, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 9, 9, 0, 77, 16 );
		anime->GetActionData( 0 )->SetMotionData( 10, 10, 0, 168, 0 );
		anime->GetActionData( 0 )->SetMotionData( 11, 11, 0, 21, 6 );
		anime->GetActionData( 0 )->SetMotionData( 12, 12, 0, 0, 0 );
	break;

	case ANIME_NO_SYS_TITLE_MODEL:
		anime->CreateAction( 0, 2 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 190, 190 );
	break;

	case ANIME_NO_CHARA_SELECT_MENU:
		anime->CreateAction( 0, 2 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 0, 0 );
	break;

	case ANIME_NO_CHARA_SELECT_BACK:
		anime->CreateAction( 0, 2 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 1, 0, 0, 190, 190 );
	break;

	case ANIME_NO_CHARA_SELECT_CUTIN:
		anime->CreateAction( 0, 2 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 0, 0 );
	break;

	case ANIME_NO_CHARA_SELECT_PUCHI:
		// shana
		anime->CreateAction( 0, 7 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 6, 34, 124 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 6, 34, 124 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 6, 34, 124 );
		anime->GetActionData( 0 )->SetMotionData( 3, 3, 6, 34, 124 );
		anime->GetActionData( 0 )->SetMotionData( 4, 4, 6, 34, 124 );
		anime->GetActionData( 0 )->SetMotionData( 5, 5, 6, 34, 124 );
		anime->GetActionData( 0 )->SetMotionData( 6, 6, 6, 34, 124 );
		// will
		anime->CreateAction( 1, 8 );
		anime->GetActionData( 1 )->SetMotionData( 0, 10, 6, 90, 109 );
		anime->GetActionData( 1 )->SetMotionData( 1, 11, 6, 90, 109 );
		anime->GetActionData( 1 )->SetMotionData( 2, 12, 6, 90, 109 );
		anime->GetActionData( 1 )->SetMotionData( 3, 13, 6, 90, 109 );
		anime->GetActionData( 1 )->SetMotionData( 4, 14, 6, 90, 109 );
		anime->GetActionData( 1 )->SetMotionData( 5, 15, 6, 90, 109 );
		anime->GetActionData( 1 )->SetMotionData( 6, 16, 6, 90, 109 );
		anime->GetActionData( 1 )->SetMotionData( 7, 17, 6, 90, 109 );
	break;

	case ANIME_NO_SYS_BATTLE_MENU:
	default:
		anime->CreateAction( 0, 50 );
		anime->GetActionData( 0 )->SetMotionData( 0, 0, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 1, 1, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 2, 2, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 3, 4, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 4, 5, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 5, 6, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 6, 7, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 7, 8, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 8, 9, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 9, 10, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 11, 11, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 12, 12, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 13, 13, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 14, 14, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 15, 15, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 21, 21, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 22, 22, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 23, 23, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 31, 31, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 32, 32, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 33, 33, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 41, 41, 0, 0, 0 );
		anime->GetActionData( 0 )->SetMotionData( 42, 42, 0, 0, 0 );
		break;
	}
}
