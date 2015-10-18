#pragma once
#include <stdio.h>
#include "CAI_Command.h"

class CAITable;
class CAITableFactory
{
protected:
	FILE	*m_File;

	CAITable *m_Table;

public:
	void ReadText();
	void ReadText( CAITable* table );
	void AnalyzeWord( char *word );
	void AnalyzeRow( char *row );
	int GetWord( char *data , char *store_word );
	CAITable * GetTable();
};
