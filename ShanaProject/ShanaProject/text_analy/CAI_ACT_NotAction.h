#pragma once
#include "CAI_Action.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
class CNpcAIShana;

class CACTNotAction:public CAIAction
{
protected:
	int m_WaitTime;
public:
	CACTNotAction();

//	void Add( char * );

	virtual int Run();
	virtual void SetParam( int paraNo, char* param );
//	int GetAction();
};
