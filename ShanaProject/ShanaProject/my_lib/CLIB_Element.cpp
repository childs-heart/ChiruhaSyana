
#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include "CLIB_Element.h"

//=============================================================
// タスクリストの初期化
CCommonData::CCommonData(int max_task_size, int max_num_task)
{
	m_MaxTaskSize	= max_task_size ;
	m_MaxNumTask	= max_num_task ; 
	m_NumFreeTask	= max_num_task ;

	// タスク用メモリの確保
	m_Buf = new char[ max_task_size * (max_num_task + 2) ];

	// アクティブタスクリストの初期化
	m_ActiveTask = (CElement*)(m_Buf + max_task_size * 0);
	m_ActiveTask->m_Prev = m_ActiveTask->m_Next = m_ActiveTask ;

	// フリータスクリストの初期化
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
// タスクの生成
// 生成処理をnewとコンストラクタに分割する。
// 削除処理も同様にデストラクタとdeleteに分割する。

// 一時的に保存するタスクリストへのポインタ
static CCommonData* TmpTaskList;

// newの処理
void* CElement::operator_new(size_t t, CCommonData* common_data )
{

	// クラスサイズが最大サイズを超えたらエラー
	assert(t<=(size_t)common_data->m_MaxTaskSize);

	// フリータスクがないときはNULLを返す
	if( common_data->m_NumFreeTask <= 0 ){
		return NULL;
	}

	// フリータスクを1個取り出す
	CElement* task = common_data->m_FreeTask->m_Next ;
	common_data->m_FreeTask->m_Next = task->m_Next ;
	common_data->m_NumFreeTask-- ;
////
	if( common_data->m_NumFreeTask > 400 ){
		char a[200];
		sprintf(a,"エフェクトnew、[%d]free-%d [%d]max-%d",
			&common_data->m_NumFreeTask, common_data->m_NumFreeTask,&common_data->m_MaxNumTask, common_data->m_MaxNumTask);
//		MessageBox(NULL,a,"assert",MB_OK);
	}
////	
	// コンストラクタへ
	TmpTaskList = common_data ;
	return task ;
}

// コンストラクタ
CElement::CElement() {

	// タスクリスト
	m_CommonData = TmpTaskList ;

	// タスクをアクティブタスクリストに挿入する
	m_Prev = m_CommonData->m_ActiveTask->m_Prev ;
	m_Next = m_CommonData->m_ActiveTask ;
	m_Prev->m_Next = m_Next->m_Prev = this;
}


//=============================================================
// タスクの削除

// デストラクタ
CElement::~CElement() {

	// タスクをアクティブタスクリストから削除する
	m_Prev->m_Next = m_Next ;
	m_Next->m_Prev = m_Prev ;

	// deleteへ
	TmpTaskList = m_CommonData;
}

// new演算子
void* CElement::operator new( size_t t, CCommonData *task_list ){
	return operator_new( t, task_list );
}

// delete演算子
void CElement::operator delete(void* p)
{
	// タスク、タスクリスト
	CElement*	 task		= (CElement*)p ;
	CCommonData* task_list	= TmpTaskList ;

	// タスクをフリータスクリストに挿入する
	task->m_Next = task_list->m_FreeTask->m_Next ;
	task_list->m_FreeTask->m_Next = task ;
	task_list->m_NumFreeTask++ ;

	// フリータスク数が最大タスク数を超えたらエラー
	// （deleteの重複呼び出しなど）
	if( task_list->m_NumFreeTask > 400 ){
		char a[200];
		sprintf(a,"エフェクトdelete、[%d]free-%d [%d]max-%d",
			&task_list->m_NumFreeTask, task_list->m_NumFreeTask,&task_list->m_MaxNumTask,task_list->m_MaxNumTask);
//		MessageBox(NULL,a,"assert",MB_OK);
	}
	if( task_list->m_NumFreeTask > task_list->m_MaxNumTask ){
		char a[200];
		sprintf(a,"あさーとおきる、free-%d max-%d",task_list->m_NumFreeTask,task_list->m_MaxNumTask);
		MessageBox(NULL,a,"assert",MB_OK);
	}
	assert(task_list->m_NumFreeTask <= task_list->m_MaxNumTask) ;
}

// delete演算子
void CElement::operator delete(void* p,CCommonData *task_list )
{
//　new失敗時に呼ばれる関数（コンパイラが自動割付）。開放処理はない（たぶん）
	// タスク、タスクリスト
	CElement*	 task		= (CElement*)p ;
//	CCommonData* task_list	= TmpTaskList ;

	// タスクをフリータスクリストに挿入する
	task->m_Next = task_list->m_FreeTask->m_Next ;
	task_list->m_FreeTask->m_Next = task ;
	task_list->m_NumFreeTask++ ;

	// フリータスク数が最大タスク数を超えたらエラー
	// （deleteの重複呼び出しなど）
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
