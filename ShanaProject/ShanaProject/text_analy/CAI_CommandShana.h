#pragma once
#include "CAI_Command.h"
class CNpcAIShana;
class CAINumberShana : public CAINumber
{
protected:

public:
	CAINumberShana( CNpcAIShana * );
	CNpcAIShana*	m_Target;
	void SetTarget( CNpcAIShana* m_Target );
};
