#include "CAI_Trigger.h"

/////////////////////////////
// ÉgÉäÉKÅ[
/////////////////////////////
class CAIEquation ;
class CAIOperator;
class CNpcAIShana;
class CAITriggerShana : public CAITrigger
{
private:
	CNpcAIShana* m_Target;

public:
	CAITriggerShana( );
	CAITriggerShana( CNpcAIShana* target );
	~CAITriggerShana();

	void SetTarget( CNpcAIShana* target );

	virtual bool MakeEquation( char* data, CAIEquation** temp );
};
