#pragma once
//#include <atlmisc.h>

class CFileSave
{
public:
	CFileSave(void);
	~CFileSave(void);

	//CString m_strFilePath;
	char m_strFilePath[100];

	// �I�[�v���A�N���[�Y 
	HRESULT Open( LPTSTR pszFilePath );
	void Close();
	HRESULT Delete();

	HRESULT MakeSection( const LPTSTR pszSection );
	HRESULT WriteMember( const LPTSTR pszSection, const LPTSTR pszMemberHeader, const LPTSTR pszMemberValue );
	HRESULT ReadMember( const LPTSTR pszSection, const LPTSTR pszMemberHeader, LPTSTR pszMemberValue, const DWORD dwSize );
	HRESULT ReadMember( const LPTSTR pszSection, const LPTSTR pszMemberHeader, DWORD* pdwMemberValue );
};
