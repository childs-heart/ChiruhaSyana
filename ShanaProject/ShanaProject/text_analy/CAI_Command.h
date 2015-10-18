
#pragma once

/////////////////////////////
// �g���K�[�v�Z�̊e�v�f������
// �X�[�p�[�N���X
/////////////////////////////
class CAIEquation{
private:
public:
	virtual int GetValue() = 0;
};

/////////////////////////////
// �g���K�[�v�Z�̐����i�����j������
// AIEquation�̃T�u�N���X
/////////////////////////////
class CAINumber : public CAIEquation
{
private:
public:
	virtual int GetValue() = 0;
};

/////////////////////////////
// �g���K�[�v�Z�̉��Z��������
// AIEquation�̃T�u�N���X
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

