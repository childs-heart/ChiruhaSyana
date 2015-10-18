#pragma once
#include <windows.h>

// 画像表示パラメータ
typedef struct ST_IMAGE_DATA{
	DWORD	m_TextureNo;		// 表示する画像ファイル（テクスチャー番号）
	DWORD	m_Left , m_Top , m_Right , m_Bottom ;
	long	m_BaseX, m_BaseY;	// 表示中点　地面の真ん中を指定する
	DWORD	m_Flag;
}StImageData;

// 表示エフェクト
typedef struct ST_ADD_EFFECT_DATA{
	DWORD	m_AnimationNo;
	int		m_Param1;		// 未使用
	int		m_Param2;		// 未使用
}StAddEffectData;

// 鳴動効果音
typedef struct ST_ADD_SOUND_DATA{
	DWORD	m_SoundNo;
	int		m_Param1;		// 未使用
}StAddSoundData;

// 攻撃判定パラメータ
typedef struct ST_ATTACK_DATA{
	DWORD	m_NumHit;			// 当たり判定数
	RECT	m_HitArea[10];		// 当たり判定
	int		m_Property;			// 属性	(上段、下段、中段）
	int		m_HitTargetAction;	// ダメージを食らわした時の、相手の状態（ダウン、吹っ飛びなど）
	int		m_BaseDamage;		// 基本ダメージ
	int		m_DamageSupply;		// ダメージ補正
	int		m_HitSpValue;		// SPゲージ増加量（ヒット時）
	int		m_MissSpValue;		// SPゲージ増加量（空振り時）
	int		m_HitStopedTime;	// 攻撃ヒット時の自キャラクタ硬直時間
	int		m_GuardStopedTime;	// 攻撃防御時の自キャラクタ硬直時間
	int		m_HitTargetStopedTime;	// 攻撃ヒット時の相手キャラクタ硬直時間
	int		m_GuardTargetStopedTime;// 攻撃防御時の相手キャラクタ硬直時間
	StAddEffectData	m_HitEffect[10];// 攻撃ヒット時表示エフェクト
	StAddSoundData	m_HitSound[10];	// 攻撃ヒット時鳴動効果音
	StAddEffectData	m_GuardEffect[10];	// 攻撃防御時表示エフェクト
	StAddSoundData	m_GuardSound[10];	// 攻撃防御時鳴動効果音
	DWORD	m_Type;				// タイプ　判定新規・判定継続とか・・・
}StAttackData;

// 喰らい判定パラメータ
typedef struct ST_WOUND_DATA{
	DWORD	m_NumHit;			// 当たり判定数
	RECT	m_HitArea[10];		// 喰らい判定
//	int		
}StWoundData;

// モーションパラメータ
typedef struct ST_MOTION_DATA{
	DWORD			m_Flame;	// 滞在時間（フレーム）0 は無限滞在
	StImageData		m_Image;	// 表示する画像（画像表示パラメータ構造体）
	StAttackData	m_Attack;	// 当たり判定追加
	StWoundData		m_Wound;	// 喰らい判定追加
	StAddEffectData	m_Effect[10];	// 同時表示エフェクト
	StAddSoundData	m_Sound[10];	// 同時鳴動効果音
	//　ほか、いろいろ追加
}StMotionData;

// キャンセル・振り向き可否・その他、設定パラメータ
typedef struct ST_ACTION_SPEC{
	int		m_EnableDir;			// 向き反転可能（アクション開始０フレーム時に反転実施）
	int		m_CancelEnabled;		// 行動（キャンセル）可能
	int		m_NotCancelTime;		// キャンセル不可能時間
	int		m_HitCancelTime;		// 以降ヒットしたらキャンセル可能時間
	int		m_EveryCancelTime;		// 以降ヒットしなくてもキャンセル可能時間
}StActoinSpecl;

// 攻撃属性
enum{
	ENUM_ATTACK_PROPERTY_LOW	= 0x00000001,
	ENUM_ATTACK_PROPERTY_MIDDLE	= 0x00000002,
	ENUM_ATTACK_PROPERTY_HIGH	= 0x00000004,
	ENUM_ATTACK_PROPERTY_JUMP	= 0x00000008,
	ENUM_ATTACK_PROPERTY_RESET	= 0x00000010
};

// 攻撃オプション
enum{
	ENUM_ATTACK_TYPE_RESET		= 0x00000001
};

// キャラクターアクションクラス
// ※アクション⇒「歩き」「屈み」単位
// ※モーション⇒１アクションに含まれるコマ
// 
class CAction{
public:
	// 登録
	void SetMotionData( DWORD motion_num, DWORD tex_no, DWORD flame, DWORD baseX, DWORD baseY );
	void SetAttackData( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom );
	void SetAttackData( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom, int property = 1 );
	void SetAttackDataAbs( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom, int property = 1 );
	void SetAttackSpec( DWORD motion_num, int base_damage, int damage_supply, int type );
	void SetWoundData( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom );
	void SetWoundDataAbs( DWORD motion_num, DWORD arg_num, int left, int top, int right, int bottom );

	void SetEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 = 0, int param2 = 0 );		// 同時表示エフェクト
	void SetHitEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 = 0, int param2 = 0 );	// 攻撃ヒット時表示エフェクト
	void SettGuardEffectData( DWORD motion_num, DWORD arg_num, DWORD animation_no, int param1 = 0, int param2 = 0 );	// 攻撃防御時表示エフェクト
	void SetSoundtData( DWORD motion_num, DWORD arg_num, DWORD sound_no, int param1 = 0 );		// 同時鳴動効果音
	void SetHitSoundData( DWORD motion_num, DWORD arg_num, DWORD sound_no, int param1 = 00 );	// 攻撃ヒット時鳴動効果音
	void SettGuardSoundData( DWORD motion_num, DWORD arg_num, DWORD sound_no, int param1 = 0 );	// 攻撃防御時鳴動効果音
//	void SetAnimeData( DWORD index, DWORD tex_no, DWORD flame, DWORD left, DWORD top, DWORD right, DWORD bottom, DWORD baseX, DWORD baseY );

	// コンストラクタ＆デストラクタ
	CAction( );
	CAction( int num_motion );
	virtual ~CAction();

	// アニメーションデータ読み込み
	void LoadMotionData( );

	// １アクション分のモーション作成
	void CreateMotion( int num_motion );

	StMotionData*	GetMotionData( DWORD moion_num );
	DWORD			GetMotionFlame( DWORD motion_num );
	bool			Collision( StMotionData* );

	// １アクション分のモーションすべてをいれる
	StMotionData*	m_MotionData;
	// １アクション分の数
	DWORD	m_NumMotion;
	// 各モーションの開始番号(仮）
//	DWORD	*m_StartMotion;

private:
	// モーション数
};
