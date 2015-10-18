#ifndef	__WILPROT
#define	__WILPROT

// 前方参照
class CInput;
class CResBattle;
class C3DDraw;

#include "CLIB_Sprite.h"
#include "ShanaProt.h"
#include "ShanaCommand.h"

class CWilProt : public CShanaProt {
public:

	CWilProt( CResBattle *game, int x, int y, char player, CShanaProt* target = NULL );
	CWilProt( CResBattle *game );
	virtual ~CWilProt();

protected:
	// 対戦相手セット
//	virtual void SetTarget( CShanaProt* target );

	// 状態遷移
	virtual void ChangeState( int state );
//	virtual void ChangeAnime( int animeNo , int animeFlame );
	// アニメーション
//	virtual void Animetion();
	// 移動
// 	virtual void Transfer();

	// 移動制御
//	virtual void StartAir( float vec_x, float vec_y, int op1 , float gravity = 0.5f );
	virtual void EndAir( );
	virtual void DoAir();
//	virtual char CanJump();
//	virtual void IncreaseJump();
//	virtual void ClearJump();
//	virtual char CanJumpDush();
//	virtual void IncreaseJumpDush();
//	virtual void ClearJumpDush();

	// 攻撃ヒット
	virtual void HitAttack();

	// 投げヒット
//	virtual void DecideThrow( int isThrow );

	// キャラクターの向き判定
//	virtual void UpdateCharaDir();

public:
	/************/
	/* メイン：オーバーライト群
	/************/
//	virtual bool Event();							// ユーザー等からの入力（イベント）受付
	virtual bool Move();							// フレーム経過により変化する、移動処理（ジャンプ降下等）
	virtual bool Action();							// 入力（イベント）内容からの動作実施
//	virtual bool ActionFinalize();					// 入力（イベント）内容からの動作実施
//	virtual bool Interfere();						// 判定動作　ヒット確認判定など
//	virtual bool InterfereFinalize();				// 最終結果　ヒット時の状態変化など、最後の処理を行う
//	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
//	virtual bool DrawFinalize();					// 描画処理後処理　Drawの後に呼ぶ
//	virtual bool Draw();					// 描画処理

	virtual bool SetSpec();

	/******************* 他オブジェクトから呼ばれる関数郡 *************************/
	virtual int ReceiveAttack( CSprite* target, CAnime *anime );	// 相手からの攻撃を受ける（戻り値：ヒット・防御・ミス）

	void Initialize( CResBattle *game, int x, int y, char player, CShanaProt* target );
};

#endif	// 
