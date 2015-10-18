#include "CAI_Command.h"

class CTRIAnd : public CAIOperator
{
public:
	CTRIAnd( );
	CTRIAnd( CAIEquation * param1, CAIEquation * param2 );
	int GetValue();
};

