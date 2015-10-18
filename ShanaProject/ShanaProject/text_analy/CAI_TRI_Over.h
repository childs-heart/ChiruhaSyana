#pragma once
#include "CAI_Command.h"

class CTRIOver : public CAIOperator
{
public:
	CTRIOver( );
	CTRIOver( CAIEquation * param1, CAIEquation * param2 );
	int GetValue();
};

