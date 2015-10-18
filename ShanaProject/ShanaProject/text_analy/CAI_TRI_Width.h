
#include "CAI_CommandShana.h"

class CResBattle;
class CNpcAIShana;
class CTRIWidth : public CAINumberShana
{
private:
	int m_Value;
public:
	CTRIWidth( CNpcAIShana* target );
	int GetValue( );
};
