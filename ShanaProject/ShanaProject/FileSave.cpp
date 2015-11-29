//#include "StdAfx.h"
//#include "Stdafx.h"
#include ".\filesave.h"
#include "common.h"
#include "tchar.h"

#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )

CFileSave::CFileSave(void)
{
	// 初期化 
//	m_strFilePath.Empty();
	memset(m_strFilePath, 0, sizeof(m_strFilePath));
}

CFileSave::~CFileSave(void)
{
	// キレイサッパリ 
//	m_strFilePath.Empty();
	memset(m_strFilePath, 0, sizeof(m_strFilePath));
}

HRESULT CFileSave::Open( LPTSTR pszFilePath )
{
	if( pszFilePath == NULL )
	{
		return E_FAIL;
	}

	memcpy( m_strFilePath , pszFilePath , sizeof(m_strFilePath ));

	return S_OK;
}

HRESULT CFileSave::Delete()
{
//	if( m_strFilePath.IsEmpty() )
	if (strlen(m_strFilePath) == 0)
	{
		return E_FAIL;
	}

	// ファイルが存在したら削除する 
	if( ::PathFileExists( m_strFilePath ) )
	{
		::SetFileAttributes( m_strFilePath, FILE_ATTRIBUTE_NORMAL );
		BOOL bRet = DeleteFile( m_strFilePath );

		if( bRet != TRUE )
			return E_FAIL;	// 削除できない 
	}

	return S_OK;
}

void CFileSave::Close()
{
	// キレイサッパリ 
//	m_strFilePath.Empty();
	memset(m_strFilePath, 0, sizeof(m_strFilePath));
}

HRESULT CFileSave::MakeSection( const LPTSTR pszSection )
{	
	if ((strlen(m_strFilePath) == 0) || (pszSection == NULL) )
		return E_FAIL;

	BOOL bRet = WritePrivateProfileSection( pszSection, TEXT(""), m_strFilePath );

	if( bRet != TRUE )
		return E_FAIL;

	return S_OK;
}

HRESULT CFileSave::WriteMember( const LPTSTR pszSection, const LPTSTR pszMemberHeader, const LPTSTR pszMemberValue )
{
	if ((strlen(m_strFilePath) == 0) || (pszSection == NULL) || (pszMemberHeader == NULL) || (pszMemberValue == NULL))
		return E_FAIL;

	BOOL bRet = WritePrivateProfileString( pszSection, pszMemberHeader, pszMemberValue, m_strFilePath );
	
	if( bRet != TRUE )
		return E_FAIL;

	return S_OK;
}

HRESULT CFileSave::ReadMember( const LPTSTR pszSection, const LPTSTR pszMemberHeader, LPTSTR pszMemberValue, const DWORD dwSize )
{
	if ((strlen(m_strFilePath) == 0) || (pszSection == NULL) || (pszMemberHeader == NULL) || (pszMemberValue == NULL))
		return E_FAIL;

	// 読み込み 
	BOOL bRet = GetPrivateProfileString( pszSection, pszMemberHeader, PRIVATE_PROFILE_DEFAULT_STRING, 
										 pszMemberValue, dwSize, m_strFilePath  );
	
	if( _tcscmp( pszMemberValue, PRIVATE_PROFILE_DEFAULT_STRING ) == 0 )
		return E_FAIL;

	return S_OK;
}

HRESULT CFileSave::ReadMember( const LPTSTR pszSection, const LPTSTR pszMemberHeader, DWORD* pdwMemberValue )
{
	if( (strlen(m_strFilePath)==0) || (pszSection == NULL) || (pszMemberHeader == NULL) || (pdwMemberValue == NULL) )
		return E_FAIL;

	// 読み込み 
	TCHAR szMemberValue[MAX_PATH];
	BOOL bRet = GetPrivateProfileString( pszSection, pszMemberHeader, PRIVATE_PROFILE_DEFAULT_STRING, 
										 szMemberValue, MAX_PATH, m_strFilePath  );
	
	if( _tcscmp( szMemberValue, PRIVATE_PROFILE_DEFAULT_STRING ) == 0 )
		return E_FAIL;

	DWORD dwValue = _tcstol( szMemberValue, NULL, 16 );
	if( (dwValue & 0x0000FFFF) == 0x0000FFFF )
	{
		*pdwMemberValue = 0xFFFFFFFF;
	}
	else
	{
		*pdwMemberValue = dwValue;
	}

	return S_OK;
}