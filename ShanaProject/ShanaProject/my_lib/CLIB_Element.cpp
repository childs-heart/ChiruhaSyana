
#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include "CLIB_Element.h"

//=============================================================
// �^�X�N���X�g�̏�����
CCommonData::CCommonData(int max_task_size, int max_num_task)
{
	m_MaxTaskSize	= max_task_size ;
	m_MaxNumTask	= max_num_task ; 
	m_NumFreeTask	= max_num_task ;

	// �^�X�N�p�������̊m��
	m_Buf = new char[ max_task_size * (max_num_task + 2) ];

	// �A�N�e�B�u�^�X�N���X�g�̏�����
	m_ActiveTask = (CElement*)(m_Buf + max_task_size * 0);
	m_ActiveTask->m_Prev = m_ActiveTask->m_Next = m_ActiveTask ;

	// �t���[�^�X�N���X�g�̏�����
	m_FreeTask = (CElement*)(m_Buf + max_task_size * 1);
	for( int i=1 ; i<max_num_task+1 ; i++ ){
		((CElement*)(m_Buf + max_task_size * (i)))->m_Next =
			((CElement*)(m_Buf + max_task_size * (i+1))) ;
	}
	((CElement*)(m_Buf + max_task_size * (max_num_task+1)))->m_Next = m_FreeTask ;
}

CCommonData::~CCommonData(){
	DeleteTask();
	delete[] m_Buf;
}

void CCommonData::DeleteTask()
{
	CElement *cEle;
	CElement *cEleNext;
	cEle = m_ActiveTask->m_Next;
	while( cEle->m_Next != m_ActiveTask->m_Next ){
		cEleNext = cEle->m_Next ;
		delete cEle;
		cEle = cEleNext ;
	}
}

//=============================================================
// �^�X�N�̐���
// ����������new�ƃR���X�g���N�^�ɕ�������B
// �폜���������l�Ƀf�X�g���N�^��delete�ɕ�������B

// �ꎞ�I�ɕۑ�����^�X�N���X�g�ւ̃|�C���^
static CCommonData* TmpTaskList;

// new�̏���
void* CElement::operator_new(size_t t, CCommonData* common_data )
{

	// �N���X�T�C�Y���ő�T�C�Y�𒴂�����G���[
	assert(t<=(size_t)common_data->m_MaxTaskSize);

	// �t���[�^�X�N���Ȃ��Ƃ���NULL��Ԃ�
	if( common_data->m_NumFreeTask <= 0 ){
		return NULL;
	}

	// �t���[�^�X�N��1���o��
	CElement* task = common_data->m_FreeTask->m_Next ;
	common_data->m_FreeTask->m_Next = task->m_Next ;
	common_data->m_NumFreeTask-- ;
////
	if( common_data->m_NumFreeTask > 400 ){
		char a[200];
		sprintf(a,"�G�t�F�N�gnew�A[%d]free-%d [%d]max-%d",
			&common_data->m_NumFreeTask, common_data->m_NumFreeTask,&common_data->m_MaxNumTask, common_data->m_MaxNumTask);
//		MessageBox(NULL,a,"assert",MB_OK);
	}
////	
	// �R���X�g���N�^��
	TmpTaskList = common_data ;
	return task ;
}

// �R���X�g���N�^
CElement::CElement() {

	// �^�X�N���X�g
	m_CommonData = TmpTaskList ;

	// �^�X�N���A�N�e�B�u�^�X�N���X�g�ɑ}������
	m_Prev = m_CommonData->m_ActiveTask->m_Prev ;
	m_Next = m_CommonData->m_ActiveTask ;
	m_Prev->m_Next = m_Next->m_Prev = this;
}


//=============================================================
// �^�X�N�̍폜

// �f�X�g���N�^
CElement::~CElement() {

	// �^�X�N���A�N�e�B�u�^�X�N���X�g����폜����
	m_Prev->m_Next = m_Next ;
	m_Next->m_Prev = m_Prev ;

	// delete��
	TmpTaskList = m_CommonData;
}

// new���Z�q
void* CElement::operator new( size_t t, CCommonData *task_list ){
	return operator_new( t, task_list );
}

// delete���Z�q
void CElement::operator delete(void* p)
{
	// �^�X�N�A�^�X�N���X�g
	CElement*	 task		= (CElement*)p ;
	CCommonData* task_list	= TmpTaskList ;

	// �^�X�N���t���[�^�X�N���X�g�ɑ}������
	task->m_Next = task_list->m_FreeTask->m_Next ;
	task_list->m_FreeTask->m_Next = task ;
	task_list->m_NumFreeTask++ ;

	// �t���[�^�X�N�����ő�^�X�N���𒴂�����G���[
	// �idelete�̏d���Ăяo���Ȃǁj
	if( task_list->m_NumFreeTask > 400 ){
		char a[200];
		sprintf(a,"�G�t�F�N�gdelete�A[%d]free-%d [%d]max-%d",
			&task_list->m_NumFreeTask, task_list->m_NumFreeTask,&task_list->m_MaxNumTask,task_list->m_MaxNumTask);
//		MessageBox(NULL,a,"assert",MB_OK);
	}
	if( task_list->m_NumFreeTask > task_list->m_MaxNumTask ){
		char a[200];
		sprintf(a,"�����[�Ƃ�����Afree-%d max-%d",task_list->m_NumFreeTask,task_list->m_MaxNumTask);
		MessageBox(NULL,a,"assert",MB_OK);
	}
	assert(task_list->m_NumFreeTask <= task_list->m_MaxNumTask) ;
}

// delete���Z�q
void CElement::operator delete(void* p,CCommonData *task_list )
{
//�@new���s���ɌĂ΂��֐��i�R���p�C�����������t�j�B�J�������͂Ȃ��i���Ԃ�j
	// �^�X�N�A�^�X�N���X�g
	CElement*	 task		= (CElement*)p ;
//	CCommonData* task_list	= TmpTaskList ;

	// �^�X�N���t���[�^�X�N���X�g�ɑ}������
	task->m_Next = task_list->m_FreeTask->m_Next ;
	task_list->m_FreeTask->m_Next = task ;
	task_list->m_NumFreeTask++ ;

	// �t���[�^�X�N�����ő�^�X�N���𒴂�����G���[
	// �idelete�̏d���Ăяo���Ȃǁj
	assert(task_list->m_NumFreeTask <= task_list->m_MaxNumTask) ;

}

bool CElement::Move()
{

	return FALSE;
}

bool CElement::Draw()
{

	return FALSE;
}

bool CElement::Draw( CD3DDraw *draw )
{

	return FALSE;
}

bool CElement::Interfere()
{

	return FALSE;
}

bool CElement::InterfereFinalize()
{

	return FALSE;
}

bool CElement::Action( )
{

	return FALSE;
}

bool CElement::ActionFinalize()
{
	return FALSE;
}

bool CElement::Event()
{

	return FALSE;
}

bool CElement::DrawFinalize()
{
	return FALSE;
}
