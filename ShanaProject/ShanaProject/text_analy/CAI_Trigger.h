/////////////////////////////
// ÉgÉäÉKÅ[
/////////////////////////////
class CAIEquation ;
class CAIOperator;

class CAITrigger
{
protected:
	const int MAX_SIZE ;
	CAIEquation * m_EquationTable[100];
	CAIEquation * m_Value1;
	CAIEquation * m_Value2;
	CAIOperator * m_Operation;
	CAIOperator * m_LastOperation;

	int m_Term;		// ç≈å„îˆ
	char*	m_Data[100];
	int m_Size;		//

	void AddEquation( CAIEquation * equ );

public:
	CAITrigger();
	~CAITrigger();

	void Add( char * );
	void Analyze( );
	void Analyze_( char * data );
	int Indent( int start, CAIEquation** term );
	int Judge();
	virtual bool MakeEquation( char* data, CAIEquation** temp );

};
