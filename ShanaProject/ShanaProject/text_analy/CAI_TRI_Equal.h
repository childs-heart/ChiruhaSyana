#include "CAI_Command.h"

class CTRIEqual : public CAIOperator
{
public:
	CTRIEqual( );
	CTRIEqual( CAIEquation * param1, CAIEquation * param2 );
	int GetValue();
};

