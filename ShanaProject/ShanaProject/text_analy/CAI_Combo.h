#pragma once
/////////////////////////////
// アクション コマンド
/////////////////////////////
class CAICombo
{
public:
	CAICombo();
	~CAICombo();

	char  m_Type;
	short m_Time[10];
	int	  m_Command[10];
	char m_Name[32];

	int GetAction();
	void Add( char * );
	void Analyze();
	void Strip( char * );

//	virtual CAIAction* MakeAction( char * );
//	virtual void SetParam( int paraNo, char* param );
//	virtual int Run();
//	virtual void SetTarget( CNpcAIShana * target );
};
