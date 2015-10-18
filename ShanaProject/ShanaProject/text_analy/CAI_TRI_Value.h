#include "CAI_Command.h"

class CTRIValue : public CAINumber
{
private:
	int m_Value;
public:
	CTRIValue( int value );
	int GetValue();
};
