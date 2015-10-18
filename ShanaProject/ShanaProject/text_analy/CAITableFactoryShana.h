#pragma once
#include <stdio.h>
#include "CAI_Command.h"
#include "CAITableFactory.h"

class CAITableFactoryShana : public CAITableFactory
{
private:

public:
	void ReadText();
	void ReadText( CAITable* table );
};
