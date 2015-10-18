#pragma once
#include "CAI_Action.h"

/////////////////////////////
// ƒAƒNƒVƒ‡ƒ“
/////////////////////////////
class CNpcAIShana;
class CShanaProt;
class CAICombo;
class CAIActionShana : public CAIAction
{
public:
//	CNpcAIShana* m_Target;

	CAIActionShana( );
	CAIActionShana( CNpcAIShana* target );
	~CAIActionShana();

	virtual CAIAction* MakeAction( char *, CAICombo* combo );

	virtual void SetParam( int paraNo, char* param );
	virtual void SetTarget( CNpcAIShana * target );

};
