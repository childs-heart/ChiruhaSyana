
#pragma once

/////////////////////////////
// トリガー計算の各要素を示す
// スーパークラス
/////////////////////////////
class CAIEquation{
private:
public:
	virtual int GetValue() = 0;
};

/////////////////////////////
// トリガー計算の数字（文字）を示す
// AIEquationのサブクラス
/////////////////////////////
class CAINumber : public CAIEquation
{
private:
public:
	virtual int GetValue() = 0;
};

/////////////////////////////
// トリガー計算の演算式を示す
// AIEquationのサブクラス
/////////////////////////////
class CAIOperator : public CAIEquation
{
public:
	CAIEquation * m_Param1;
	CAIEquation * m_Param2;
public:
	CAIOperator( );
	CAIOperator( CAIEquation * param1, CAIEquation * param2 );
	void SetEquation( CAIEquation * param1, CAIEquation * param2 );
	virtual int GetValue() = 0 ;
};

