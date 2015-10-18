#include "ShanaCommand.h"

class CNpcCommand : public CCommandManager
{
public:
	virtual void updateInput( char playerNo );
	virtual void setSpecial( unsigned int spe );
	virtual void setStandard( unsigned int Standard );
};
