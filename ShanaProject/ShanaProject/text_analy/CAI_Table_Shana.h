#pragma once
/////////////////////////////
// AIÉeÅ[ÉuÉã
/////////////////////////////

#include "CAI_Table.h"
class CNpcAIShana;
class CAITableShana : public CAITable
{
public:
	CNpcAIShana* m_Target;
private:
	int	m_ConditionCurrentIndex;

public:
	CAITableShana();
	virtual ~CAITableShana();

	virtual void SetUp( );
	void SetTarget( CNpcAIShana* target );
	void Judge();
};
