#ifndef	__SHANAPROT
#define	__SHANAPROT

// 前方参照
class CInput;
class CResBattle;
class C3DDraw;

#include "CLIB_Sprite.h"
#include "ShanaCommand.h"

//#include "CLIB_Element.h"
//#include "CLIB_DispObj.h"
//#include "CLIB_Anime.h"
//#include "CLIB_Texture.h"
//#include "CLIB_Sprite.h"
//#include "game.h"


enum ENUM_TESTCHAR_STATE{
	ENUM_TESTCHAR_STATE_INIT			= 0x00000000 ,
	ENUM_TESTCHAR_STATE_NONE			= 0x00000000 ,
	ENUM_TESTCHAR_GROUND				= 0x00010000 ,
	ENUM_TESTCHAR_STATE_NEUTRAL			,
	ENUM_TESTCHAR_STATE_WALK_FORWARD	,
	ENUM_TESTCHAR_STATE_WALK_BACK		,
	ENUM_TESTCHAR_STATE_ATTACK_LOW		,
	ENUM_TESTCHAR_STATE_ATTACK_MID		,
	ENUM_TESTCHAR_STATE_ATTACK_HIGH		,
	ENUM_TESTCHAR_STATE_ATTACK_EX		,
	ENUM_TESTCHAR_STATE_DAMAGE			,
	ENUM_TESTCHAR_STATE_BIG_DAMAGE		,
	ENUM_TESTCHAR_STATE_GUARD			,
	ENUM_TESTCHAR_STATE_CROUCH_DAMAGE	,
	ENUM_TESTCHAR_STATE_CROUCH			= 0x00020000,
	ENUM_TESTCHAR_STATE_CROUCH_FORWARD	,
	ENUM_TESTCHAR_STATE_CROUCH_BACK		,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_START,
	ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_END,
	ENUM_TESTCHAR_STATE_CROUCH_GUARD	,
	ENUM_TESTCHAR_STATE_JUMP_SETUP		,

	ENUM_TESTCHAR_STATE_DUSH_FORWARD	,
	ENUM_TESTCHAR_STATE_DUSH_FORWARD_END,
	ENUM_TESTCHAR_STATE_DUSH_BACK		,

	ENUM_TESTCHAR_STATE_JUMP			= 0x00040000 ,
	ENUM_TESTCHAR_STATE_JUMP_NORMAL		,
	ENUM_TESTCHAR_STATE_JUMP_FORWARD	,
	ENUM_TESTCHAR_STATE_JUMP_BACK		,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID,
	ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX,
	ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD,
	ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK	,
	ENUM_TESTCHAR_STATE_JUMP_DUSH_END	,
	ENUM_TESTCHAR_STATE_JUMP_DAMAGE,
	ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE,
	ENUM_TESTCHAR_STATE_JUMP_BLOW_DOWN	,
	ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND	,
	ENUM_TESTCHAR_STATE_JUMP_GUARD		,
	ENUM_TESTCHAR_STATE_JUMP_RECOVER	,

	ENUM_TESTCHAR_STATE_DOWN			= 0x00080000 ,
	ENUM_TESTCHAR_STATE_GETUP			,			

	ENUM_TESTCHAR_STATE_THROW_STANDBY	= 0x00100000 ,
	ENUM_TESTCHAR_STATE_THROW			,
	ENUM_TESTCHAR_STATE_MISS_THROW		,
	ENUM_TESTCHAR_STATE_DAMAGE_THROW	,

	ENUM_TESTCHAR_STATE_SPECIAL_1		= 0x00200000 ,
	ENUM_TESTCHAR_STATE_SPECIAL_1_END	,
	ENUM_TESTCHAR_STATE_SPECIAL_2		,
	ENUM_TESTCHAR_STATE_SPECIAL_3		,
	ENUM_TESTCHAR_STATE_SPECIAL_3_2		,

	ENUM_TESTCHAR_STATE_FREEZE			= 0x00400000 ,

// 今のところ使わない方向で・・・・
	ENUM_TESTCHAR_FLAG_NOT_DIR			= 0x01000000,
	ENUM_TESTCHAR_MASK_EXCEPT_FLAG		= 0x00FFFFFF		// マスク　除くフラグを

};

enum ENUM_TESTCHAR_SUB_STATE{
	ENUM_TESTCHAR_SUB_STATE_STAND	,
	ENUM_TESTCHAR_SUB_STATE_CROUCH	,
	ENUM_TESTCHAR_SUB_STATE_JUMP	,
	ENUM_TESTCHAR_SUB_STATE_DAMAGE	,
	ENUM_TESTCHAR_SUB_STATE_DOWN
};

enum ENUM_VECTOR{
	ENUM_VECTOR_UP = 0	,
	ENUM_VECTOR_DOWN	,
	ENUM_VECTOR_FWD		,
	ENUM_VECTOR_BACK
};

enum ENUM_DIRECTION{
	ENUM_DIR_RIGHT	= 1 ,
	ENUM_DIR_LEFT	= -1
};

enum ENUM_TESTCHAR_GUARD_INPUT{
	ENUM_TESTCHAR_GUARD_OFF,
	ENUM_TESTCHAR_GUARD_STAND,
	ENUM_TESTCHAR_GUARD_CROUCH,
	ENUM_TESTCHAR_GUARD_JUMP,
	ENUM_TESTCHAR_GUARD_ALL
};

enum ENUM_ACTION_ENABLE{
	ENUM_ACTION_ENABLE_MOVE		= 0x00000001,
	ENUM_ACTION_ENABLE_ATTACK	= 0x00000002,
	ENUM_ACTION_ENABLE_ALL		= 0xFFFFFFF
};

typedef struct CHARACTER_PARAM{
	int m_HpGauge;			// ヒットポイント量
	int m_SpGauge;			// ＳＰゲージ
}ST_CHARACTER_PARAM;

typedef struct CHARACTER_SPEC{
	int		MAX_HP					;	// HPゲージ
	int		MAX_SP					;	// SPゲージ
	int		SPEED_FORWARD			;	// 前進速度
	int		SPPED_BACK				;	// 後退速度
	int		SPEED_JUMP				;	// ジャンプ速度
	int		SPEED_JUMP_FORWARD		;	// 前ジャンプ速度
	int		SPEED_JUMP_BACK			;	// 後ジャンプ速度
	float	DEFENSE					;	// 防御力
	float	WEIGHT					;	// 重さ
	int		FAINT					;	// 気絶値
	float	SPIRIT					;	// 根性値
	int		TIME_JUMP_STANBY		;	// ジャンプ準備時間
	int		RANGE_THROW				;	// 投げ範囲
	int		RANGE_JUMP_THROW		;	// ジャンプ投げ範囲
	int		MAX_JUMP_STEP			;	// 多段ジャンプ回数
	int		MAX_JUMP_DUSH_STEP		;	// 空中ダッシュ回数
	int		SPEED_DUSH_FORWARD		;	// 前進ダッシュ速度
	int		SPEED_DUSH_BACK			;	// 後退ダッシュ速度
	int		SPEED_JUMP_DUSH_FORWARD	;	// 前進ダッシュ速度
	int		SPEED_JUMP_DUSH_BACK	;	// 後退ダッシュ速度
	int		SPEED_JUMP_FALL			;	// ジャンプ降下補正値
	int		TIME_DOWN				;	// ダウン時間
}ST_CHARACTER_SPEC;

class CHARACTER_COMMON_PARAMETER{
public:
	static const float AERIAL_DAMAGE_VECTOR;
	static const float AERIAL_DAMAGE_GRAVITY;
	static const float AIR_DAMAGE_VECTOR;
	static const float AIR_DAMAGE_GRAVITY;
	static const float AIR_GUARD_VECTOR;
	static const float AIR_GUARD_GRAVITY;
};

// サブ状態構造体
typedef struct CHARACTER_CONDITION{
	int		IDLE ;
	int		ATTACK;
}ST_CHARACTER_CONDITION;

// 攻撃喰らい中の情報
typedef struct CHARACTER_DAMAGE_INFO{
	int		m_ComboCount;
}ST_CHARACTER_DAMAGE_INFO;

// 行動可否に関する情報
class CCharacterActionEnableSpec{
private:
	int		m_FullActionEnabled;	// 常に行動可能
	int		m_NotCancelTime;		// キャンセル不可能時間
	int		m_HitCancelTime;		// ヒットしたらキャンセル可能時間
	int		m_EveryCancelTime;		// ヒットしなくてもキャンセル可能時間
	bool	m_Hited;

public:
	void	SetSpec( int full_action_enabled, int not_chancel, int hit_chancel, int every_chancel );
	int		CanCancel( int flame, int hitted );
	void	HitAttack( );
};

class CShanaProt : public CSprite , public CCommandRefer{
protected:
	CInput				*m_Input;		// インプットクラス
	CCommandManager		*m_Command;
	CCommandManager		m_PlayerCommand;
	CResBattle			*m_ResBattle;

	int	m_Blend;

	char m_player;

	// 対戦相手セット
	virtual void SetTarget( CShanaProt* target );

	// 状態遷移
	virtual void ChangeState( int state );
	virtual void ChangeAnime( int animeNo , int animeFlame );
	// アニメーション
//	virtual void Animetion();
	// 移動
   	virtual void Transfer();

	// 移動制御
	virtual void StartAir( float vec_x, float vec_y, int op1 , float gravity = 0.5f );
	virtual void EndAir( );
	virtual void DoAir();
	virtual char CanJump();
	virtual void IncreaseJump();
	virtual void ClearJump();
	virtual char CanJumpDush();
	virtual void IncreaseJumpDush();
	virtual void ClearJumpDush();

	// 攻撃ヒット
	virtual void HitAttack();

	// 投げヒット
	virtual void DecideThrow( int isThrow );

	// キャラクターの向き判定
	virtual void UpdateCharaDir();

	ST_CHARACTER_SPEC	m_Spec;

	// キャラクターデータ
	int m_FieldY;
//	int m_HpGauge;			// ヒットポイント量
//	int m_SpGauge;			// ＳＰゲージ
	CHARACTER_PARAM		m_Parameter;

//	int	m_Dir;				// 向き
	RECT m_Body;			// キャラの本体矩形

	int m_SubStatus;		// サブ状態
	int	m_Condition;		// 状態その２（用途未定）
	int m_GuardInput;		// 防御状態
	int m_FlagActionEnabled;// 行動可否フラグ。移動可否、攻撃可否、防御可否　など
	int m_HittedAttack;		// 攻撃ヒットフラグ

	float m_Vector[2];		// [0]:左右　[1]:上下
	float m_KnockBackVector[2];// ノックバックベクトル[0]:左右　[1]:上下（上下はないかな…）

	float m_AirBase[2];		// ジャンプ始点座標　[0]:X位置　[1]:Y位置
	float m_AirVector[2];	// ジャンプベクトル　[0]:X方向　[1]:Y方向
	float m_AirGravity;		// 空中重力
	float m_AirIncrease;	// 増減値
	int	m_AirTime;			// 空中滞空時間
	int m_NumJump;			// 多段ジャンプ回数
	int m_NumJumpDush;		// 空中ダッシュ回数

public:
	int	m_StopedMoveCount;	// ヒット時のキャラクタ硬直時間カウンタ
	int m_ReceiveAttackTemplateState;
						// 攻撃を喰らった時の状態。すぐに状態を変えると先勝ちになるから状態を一時退避。
	ST_CHARACTER_DAMAGE_INFO	m_DamageInfo;

//	int	m_Flame;			// フレーム数
	int m_EnableDir;		// 方向転換可否
	int m_FlagStateStep[5];	// 各状態で

	CShanaProt*	m_Target;	// 対戦相手
	CShanaProt*	m_KnockBackChara;	// ダメージもらい元のキャラクタ

public:
	CCharacterActionEnableSpec	m_ActionSpec;

	CShanaProt( CResBattle *game, int x, int y, char player, CShanaProt* target = NULL );
	CShanaProt( CResBattle *game );

	// 他利用関数 
	void SetCommand( CCommandManager * cmd );
	void SetDefaultCommand( );

	/************/
	/* メイン：オーバーライト群
	/************/
	virtual bool Event();							// ユーザー等からの入力（イベント）受付
	virtual bool Move();							// フレーム経過により変化する、移動処理（ジャンプ降下等）
	virtual bool Action();							// 入力（イベント）内容からの動作実施
	virtual bool ActionFinalize();					// 入力（イベント）内容からの動作実施
	virtual bool Interfere();						// 判定動作　ヒット確認判定など
	virtual bool InterfereFinalize();				// 最終結果　ヒット時の状態変化など、最後の処理を行う
	virtual bool Draw( CD3DDraw *draw );			// 描画処理メイン　基本こちらを呼ぶ
	virtual bool DrawFinalize();					// 描画処理後処理　Drawの後に呼ぶ
//	virtual bool Draw();					// 描画処理

	virtual bool SetSpec();

	/******************* 他オブジェクトから呼ばれる関数郡 *************************/
	int	GetSpGauge();							// SPゲージを返す
	int GetHpGauge();							// HPゲージを返す
	CShanaProt* GetTarget();
	void NotifyPlayer( CShanaProt* m_Target );	// 相手先をもらう
	void GetVector( int *x, int *y );			// 現在の移動量を返す
	void SetVector( int x, int y );				// 移動量をセットする
	void AddVector( int x, int y );				// 現在の移動量を増減させる
	int	IsCollisioned( CSprite* target );	// 相手の攻撃を喰らってるか調べる（戻り値：ヒット・防御・ミス）
	int IsThrown( CShanaProt* target );			// 相手の投げを喰らってるかどぅか調べる（戻り値：YES/NO）
	virtual int ReceiveAttack( CSprite* target, CAnime *anime );	// 相手からの攻撃を受ける（戻り値：ヒット・防御・ミス）
	int ReceiveThrown( CShanaProt* target );	// 相手からの投げを受ける
	int IsActionEnaled( );						// 行動可否のを返す
	ST_CHARACTER_DAMAGE_INFO*	GetDamageInfo();// 自分の喰らい情報を返す

	/******************* 多重継承宣言 *********************************************/
	char getDir();		// CommandReferからの純粋仮想関数
	char GetDir();		// CSpriteからの仮想関数

protected:
	virtual ~CShanaProt();
	void Initialize( CResBattle *game, int x, int y, char player, CShanaProt* target );
	
};

#endif	// 
