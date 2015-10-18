#pragma once

#include "CLIB_D3DDraw.h"

class CCHARACTER{
public:
	int type;
	int state;
	int frame;
};

//==============================================================
// タスククラス
//==============================================================
class CElement{
friend class CCommonData;

public:
	// タスクリストへのポインタ
	CCommonData* m_CommonData;

	// 前後のタスクへのポインタ
	CElement	*m_Prev;
	CElement	*m_Next;

	// タスクリストを指定しないnewを無効にする
	void* operator new(size_t t) {}

protected:
	// newの処理：
	// new演算子内でコールされる。
	static void* operator_new(size_t t, CCommonData* task_list);

public:
	int m_iObjectType;

	// コンストラクタ＆デストラクタ
	CElement();
	virtual ~CElement();

	// 引数つきnew演算子
	void* operator new( size_t t, CCommonData *task_list );
	// delete演算子のオーバーロード
	void operator delete( void* p );
	// 引数付きのnew演算子でエラーが発生すると自動的によばれる。
	// もし、コールされたらプログラムの終了してもいいかも。
	void operator delete( void* p, CCommonData *task_list );

	/************/
	/* オーバーライト群
	/************/
	virtual bool Event();							// ユーザー等からの入力（イベント）受付
	virtual bool Move();							// 移動処理
	virtual bool Action();							// 入力（イベント）内容からの動作実施
	virtual bool ActionFinalize();
	virtual bool Interfere();						// 判定動作　ヒット確認など
	virtual bool InterfereFinalize();				// 最終結果　ヒット時の状態変化など、最後の処理を行う
//	virtual bool Result();							// 判定動作　ヒット確認など
//	virtual bool FlameResult();						// 最終結果　ヒット時の状態変化など、最後の処理を行う
	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
	virtual bool Draw();							// 描画処理
	virtual bool DrawFinalize();					// 描画処理後処理　Drawの後に呼ぶ

//	void SetSelfPointer(CElement** pElement);		// 己のポインタ返し
//	void SetCommonDataPointer(CCommonData *pCommonData);		// 現在のCCommonDataの位置取得
//	virtual BOOL GetTexRect(TEXRECT *spTexRect); 			// 描画部分関数

#if 0
	int m_iAttackPower, m_iDurability;
	TEXRECT m_TexRect;			// 描画用の構造体
	ANIDATA m_AniData;
	RECT m_sHitRect;			// 衝突判定用短形
	CCommonData* m_pCommonData;
	CElement** m_ppSelf;
	UINT m_iAttackAtr, m_iDefenceAtr;

	virtual void Collision(int iObjectType, int iDamage);		// 衝突処理
#endif

};


//==============================================================
// タスクリストクラス
//==============================================================
class CCommonData{
friend class CElement;

public:
	// アクティブタスクリスト、フリータスクリスト
	CElement	*m_ActiveTask;
	CElement	*m_FreeTask;

	// タスクの最大サイズ、タスクの最大数
	int m_MaxTaskSize;
	int	m_MaxNumTask;
	
	// フリータスクの数
	volatile int m_NumFreeTask;

	// 確保したメモリ番地
	char *m_Buf;

public:
	// コンストラクタ＆デストラクタ
	CCommonData( int max_task_size, int max_num_task );
	virtual ~CCommonData();
	
	// タスクの数
	int GetNumFreeTask();// { return NumFreeTask; }
	int GetNumActiveTask();// { return MaxNumTask-NumFreeTask; }

	// 全タスクの消去
	void DeleteTask();
};
