#pragma once
#include "CAI_Command.h"

class CTRIUnder : public CAIOperator
{
public:
	CTRIUnder( );
	CTRIUnder( CAIEquation * param1, CAIEquation * param2 );
	int GetValue();
};

