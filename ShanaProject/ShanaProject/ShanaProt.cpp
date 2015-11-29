#include <d3dx9tex.h>
#include "ShanaProt.h"

#include "EffShanaOptParts.h"
#include "ResBattle.h"

#include "CLIB_DispObj.h"
#include "CLIB_Anime.h"
#include "CLIB_Texture.h"
#include "CLIB_Util.h"
#include "UTL_SoundManager.h"

//#include "title.h"
#include "EffTest.h"
#include "EffShanaOpt.h"
#include "EffHit001.h"
#include "EffHit002.h"
#include "EffHit003.h"
#include "EffHit004.h"
#include "EffHit005.h"
#include "EffHit006.h"
#include "EffHit007.h"
#include "EffHit009.h"
#include "EffGuard001.h"
#include "EffAction01.h"
#include "EffAction02.h"
#include "EffAction003.h"

#include "CChaEndan.h"
#include "EffAttack001.h"

#include "DsoundMain.h"

const float CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_GRAVITY(0.2f);
const float CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_VECTOR(10.0f);
const float CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_GRAVITY(0.5f);
const float CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_VECTOR(15.0f);
const float CHARACTER_COMMON_PARAMETER::AIR_GUARD_GRAVITY(0.4f);
const float CHARACTER_COMMON_PARAMETER::AIR_GUARD_VECTOR(1.0f);

CShanaProt::CShanaProt( CResBattle *game ):CSprite( game ),CCommandRefer()
{
	
	Initialize( game , 0, 0, 0 , NULL );
}

CShanaProt::CShanaProt( CResBattle *game, int x, int y, char player, CShanaProt* target ):CSprite( game )
{
	Initialize( game, x, y, player ,target );
}

// 初期化
void CShanaProt::Initialize( CResBattle *game, int x, int y, char player, CShanaProt* target )
{
	// 資源調達
	m_ResBattle = game ;
	m_Input = game->m_Input ;			// m_Inputいらないかも
	m_Command = &m_PlayerCommand;
	m_Command->setInput( m_Input );
	m_Command->setRefer( this );
	m_Command->SetCommandSequence(0);

	m_Anime.m_AnimeSpec		= game->m_AnimationManager->GetAnimation( player );
	m_Tex					= game->m_TextureManager->GetTextureGroup( player );
	m_DispObjGroup			= m_Game->m_DispObjGroup;
	m_DispObj				= m_DispObjGroup->GetDispObj();

	m_player = player ;
	m_Target = NULL;

	m_FlagActionEnabled = ENUM_ACTION_ENABLE_ALL ;

	// 初期状態
	ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );

	m_X				= x;
	m_Y				= y;
	m_FieldY		= y;
	m_Dir			= ENUM_DIR_RIGHT ;
	m_EnableDir		= TRUE;

	m_Vector[0]	= 0;
	m_Vector[1]	= 0;
	m_Vector[2]	= 0;
	m_Vector[3]	= 0;
	m_AirVector[0] = 0;
	m_AirVector[1] = 0;
	m_NumJump		= 0;

	m_StopedMoveCount = 0;

	// 対戦相手に自分を教える
	if( target != NULL ){
		target->NotifyPlayer( this );
		SetTarget( target );
	}

	m_KnockBackVector[0] = 0;
	m_KnockBackVector[1] = 0;

	// パラメータ関係
	SetSpec();
	
	m_Parameter.m_HpGauge = m_Spec.MAX_HP ;
	m_Parameter.m_SpGauge = 0 ;

	// いまんところ使ってなかったりします
	m_Body.left = -30;
	m_Body.right = 30;
	m_Body.top = -30;
	m_Body.bottom = -30;

	m_DamageInfo.m_ComboCount = 0;
//	new(m_ResBattle->m_CommonEffect) CEffShanaOpt( m_ResBattle, this );
}

CShanaProt::~CShanaProt( )
{
}

// 性能セットアップ
bool CShanaProt::SetSpec()
{
	m_Spec.MAX_HP				= 10000;
	m_Spec.MAX_SP				= 1000;
	m_Spec.DEFENSE				= 0 ;
	m_Spec.FAINT				= 0 ;
	m_Spec.MAX_JUMP_DUSH_STEP	= 1 ;
	m_Spec.MAX_JUMP_STEP		= 2 ;
	m_Spec.RANGE_JUMP_THROW		= 0 ;
	m_Spec.RANGE_THROW			= 10 ;
	m_Spec.SPEED_DUSH_BACK		= 10 ;
	m_Spec.SPEED_DUSH_FORWARD	= 10 ;
	m_Spec.SPEED_JUMP_DUSH_BACK		= 10 ;
	m_Spec.SPEED_JUMP_DUSH_FORWARD	= 13 ;
	m_Spec.SPEED_FORWARD		= 5 ;
	m_Spec.SPEED_JUMP			= 20 ;
	m_Spec.SPEED_JUMP_FORWARD	= 5 ;
	m_Spec.SPEED_JUMP_BACK		= 4 ;
	m_Spec.SPEED_JUMP_FALL		= 5 ;
	m_Spec.SPIRIT				= 5 ;
	m_Spec.SPPED_BACK			= 4 ;
	m_Spec.TIME_DOWN			= 10 ;
	m_Spec.TIME_JUMP_STANBY		= 3 ;
	m_Spec.WEIGHT				= 3 ;

	return TRUE;
}

// 対戦相手セット
void CShanaProt::SetTarget( CShanaProt *target )
{
	m_Target = target;

	int x,y ;
	m_Target->GetPosition( &x , &y );

	if( x + m_player > m_X ){
		m_Dir = ENUM_DIR_RIGHT ;
	}
	else{
		m_Dir = ENUM_DIR_LEFT ;
	}
}

// イベント受付（ボタン入力実施）
bool CShanaProt::Event()
{
	// パラメータリセット
	m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_NONE;

	if( m_StopedMoveCount > 0 ){
		return TRUE;
	}
//	m_Command.updateInput( m_player );

	return TRUE;
}

// Move
// イベント関係なく動く動作
// Actionの前に実行される
bool CShanaProt::Move()
{
	////////////////////////////////////
	// キャラクター移動					
	////////////////////////////////////
	m_Vector[0] = 0;
	m_Vector[1] = 0;
	int x,y;
	m_ResBattle->GetScreenPosition( &x, &y );

	m_GuardInput = ENUM_TESTCHAR_GUARD_OFF;

	if( m_StopedMoveCount != 0 ){
		return TRUE;
	}

	m_Flame++;
	switch( m_State ){
		case ENUM_TESTCHAR_STATE_JUMP_SETUP:

			break;

		case ENUM_TESTCHAR_STATE_JUMP_FORWARD:
			DoAir();

			if( ( m_AirIncrease <= 1.0f ) &&
				( m_AirIncrease > 0.0f ) ){
				ChangeAnime( 8 , 0 ) ;
			}
			else if( ( m_AirIncrease <= 0.0f ) &&
				( m_Anime.GetCurrentActionNo() != 9 )){
				ChangeAnime( 9 , 0 ) ;
			}

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}

//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_BACK:
/*			m_Vector[ENUM_VECTOR_UP] -= 0.5f;
			y -= m_Vector[ENUM_VECTOR_UP];
			if( ( m_Vector[ENUM_VECTOR_UP] <= 3.0f ) &&
				( m_Vector[ENUM_VECTOR_UP] > 0.0f ) ){
				m_AnimeNo = 8;
			}
			if( m_Vector[ENUM_VECTOR_UP] == 0.0f ){
				m_AnimeNo = 9;
			}
			if( y > 300 ){
				y = 300 ;
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
*/
			DoAir();

			if( ( m_AirIncrease <= 1.0f ) &&
				( m_AirIncrease > 0.0f ) ){
				ChangeAnime( 8 , 0 ) ;
			}
			else if( ( m_AirIncrease <= 0.0f ) &&
				( m_Anime.GetCurrentActionNo() != 9 )){
				ChangeAnime( 9 , 0 ) ;
			}

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}

//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_NORMAL:
			DoAir();

			if( ( m_AirIncrease <= 1.0f ) &&
				( m_AirIncrease > 0.0f ) ){
				ChangeAnime( 8 , 0 ) ;
			}
			else if( ( m_AirIncrease <= 0.0f ) &&
				( m_Anime.GetCurrentActionNo() != 9 )){
				ChangeAnime( 9 , 0 ) ;
			}

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
			if( m_Flame == 34 ){
				ChangeAnime( 9 , 0 ) ;
			}
			DoAir();

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW:
			if( m_Flame == 20 ){
				ChangeAnime( 9 , 0 ) ;
			}
			DoAir();

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID:
			if( m_Flame == 24 ){
				ChangeAnime( 9 , 0 ) ;
			}
			DoAir();

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX:
//			if( m_Flame == 6 ){
//				ChangeAnime( 9 , 0 ) ;
//			}
			DoAir();

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
			if( m_Flame == 6 ){
				ChangeAnime( 45, 0 );
			}
			if( m_Flame > 60 ){
				ChangeState( ENUM_TESTCHAR_STATE_DUSH_FORWARD_END );
			}
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD_END:
//			DoAir();
			if( m_Flame > 3 ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_NORMAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_DUSH_BACK:
			if( m_Flame > 11 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
			if( m_Flame > 27 ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_END);
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK:
			if( m_Flame > 10 ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_END);
			}
			break;

		case ENUM_TESTCHAR_STATE_NEUTRAL:
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_LOW:
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_MID:
//			if( m_Flame == 34)
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_EX:
//			DoAir();
			if( m_Flame == 12 ){
				new(m_ResBattle->m_CommonEffectFront)CEffAttack001(m_ResBattle, this);
			}
			else if( m_Flame < 32 ){
				AddVector( (32-m_Flame)/4 * m_Dir + 1 , 
							abs( (m_Flame-15)/4 )*( (m_Flame-15)/4) ) ;
			}
			else{
				m_Y = m_FieldY ;
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW:
			if( m_Flame == 6 ){
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID:
			if( m_Flame > 20 ){
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
			if( m_Flame > 53 ){
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
			if( m_Flame > 5 ){
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_START );
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_START:
			if( m_Flame <= 20 ){
				AddVector( ((20-m_Flame)/2 + 2) * m_Dir , 0 ) ;
			}
			else{
//				AddVector( m_Dir * 58, 0 ) ;
				AddVector( m_Dir * 40, 0 ) ;
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_END );
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_END:
			if( m_Flame > 5 ){
//				AddVector( m_Dir * 26, 0 ) ;
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
			}
			break;

		case ENUM_TESTCHAR_STATE_DAMAGE:
			if( m_Flame > 15 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			else if( m_Flame == 9 ){
				
				m_KnockBackVector[0] = 0;
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_DAMAGE:
			if( m_Flame > 15 ){
//				m_KnockBackVector[0] = 5;
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
			}
			else if( m_Flame == 9 ){
				m_KnockBackVector[0] = 0;
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE:
			DoAir();

			if( ( m_AirIncrease <= 2.0f ) &&
				( m_AirIncrease > 1.0f ) ){
				ChangeAnime( 25 , 0 ) ;
			}
			if( ( m_AirIncrease <= 1.0f ) &&
				( m_AirIncrease > 0.0f ) ){
				ChangeAnime( 25 , 0 ) ;
			}
			if( ( m_AirIncrease <= -2.0f ) &&
				( m_AirIncrease > -4.0f ) ){
				ChangeAnime( 27 , 0 ) ;
			}

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				m_Vector[0] = m_AirVector[0];
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_DOWN );
			}

//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_BIG_DAMAGE:
			DoAir();

			if( ( m_AirIncrease <= 1.0f ) &&
				( m_AirIncrease > 0.0f ) ){
				ChangeAnime( 57 , 0 ) ;
			}
			if( ( m_AirIncrease <= -2.0f ) &&
				( m_AirIncrease > -4.0f ) ){
				ChangeAnime( 58 , 0 ) ;
			}

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				m_Vector[0] = m_AirVector[0];
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_DOWN );
			}

//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DAMAGE:
			DoAir();
			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				m_Vector[0] = m_AirVector[0];
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_DOWN );
			}

//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_GUARD:
			DoAir();
			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				m_Vector[0] = m_AirVector[0];
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}

//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_DOWN:
			if( m_Flame == 60 ){
				ChangeState( ENUM_TESTCHAR_STATE_GETUP );
			}
			break;

		case ENUM_TESTCHAR_STATE_GETUP:
			if( m_Flame == 10 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

 		case ENUM_TESTCHAR_STATE_GUARD:
			if( m_Flame > 10 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			else if( m_Flame == 9 ){
				
				m_KnockBackVector[0] = 0;
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_GUARD:
			if( m_Flame > 10 ){
//				m_KnockBackVector[0] = 5;
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
			}
			else if( m_Flame == 9 ){
				m_KnockBackVector[0] = 0;
			}
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_1:
			if( m_Flame == 10 ){
				new(m_ResBattle->m_CommonEffectFront) CEffHit006(m_ResBattle, this );
			}
			if( m_Flame >= 10 ){
				int y;
				y = 30;
				if( m_Y + y > m_FieldY ){
					AddVector( 30*m_Dir , 0 ) ;
					m_Y = m_FieldY ;
					EndAir();
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_1_END );
				}
				else{
					AddVector( 30*m_Dir , y ) ;
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_1_END:
			if( m_Flame < 30 ){
				AddVector( (30-m_Flame)/10 * m_Dir , 0 ) ;
			}
			else{
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_2:
			if( m_Flame == 10 ){
				new(m_ResBattle->m_CommonChara[m_player])CChaEndan( m_ResBattle, this, m_ResBattle->m_CommonChara[m_player] );
			}
			if( m_Flame == 60 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_3:
			DoAir();

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				m_Vector[0] = m_AirVector[0];
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}

//			m_Vector[0] += m_AirVector[0];
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_THROW:
			if( m_Flame == 20 ){
				ChangeAnime( 51, 0 ) ;
			}
			if( m_Flame == 35 ){
				new(m_ResBattle->m_CommonEffectFront) CEffHit001( m_ResBattle, m_Target );
				new(m_ResBattle->m_CommonEffectFront) CEffHit005( m_ResBattle, m_Target );
				m_Target->m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_BIG_DAMAGE;
			}
			if( m_Flame == 60 ){
				ChangeAnime( 52, 0 ) ;
			}
			if( m_Flame > 68 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_MISS_THROW:
			if( m_Flame == 20 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_BLOW_DOWN:
			if( m_X + m_Dir * -15 < -400 + x ){
				m_X = -400 + x ;
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND );
			}
			else if( m_X + m_Dir * -15 > 400 + x ){
				m_X = 400 + x ;
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND );
			}
			else{
				AddVector( m_Dir * -15 , 0 );
			}

			break;

		case ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND:
			DoAir();

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				m_Vector[0] = m_AirVector[0];
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_DOWN );
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_RECOVER:
			DoAir();

//			if( m_Y > m_FieldY ){
//				m_Y = m_FieldY ;
//				m_Vector[0] = m_AirVector[0];
//				EndAir();
			if( m_Flame == 15 ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_NORMAL );
				if( ( m_AirIncrease <= 1.0f ) &&
					( m_AirIncrease > 0.0f ) ){
					ChangeAnime( 8 , 0 ) ;
				}
				else if( ( m_AirIncrease <= 0.0f ) &&
					( m_Anime.GetCurrentActionNo() != 9 )){
					ChangeAnime( 9 , 0 ) ;
				}
			}
			break;
	}


/***余計な追加***********************/
	if( m_Target == NULL ){
		return true;
	}

//	int x,y ;
	m_Target->GetPosition( &x , &y );

	if( m_EnableDir ){
		if( x + m_player > m_X ){
			m_Dir = ENUM_DIR_RIGHT ;
		}
		else{
			m_Dir = ENUM_DIR_LEFT ;
		}
	}
/**************************/

	return TRUE;
}

// Action
// イベント結果から動作実行
bool CShanaProt::Action()
{
	unsigned long	standard;
	unsigned long	special;

	if( m_StopedMoveCount != 0 ){
		return TRUE;
	}

	m_Command->updateInput( m_player );
	standard = m_Command->getStandardAction();
	special = m_Command->getSpecialAction();

//	if( special == 16 ){
//		ChangeState( ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE );
//	}
	switch( m_State & ENUM_TESTCHAR_MASK_EXCEPT_FLAG ){
		case ENUM_TESTCHAR_STATE_NEUTRAL:
			if( special == 1 ){
				ChangeState( ENUM_TESTCHAR_STATE_DUSH_FORWARD );
			}
			else if( special == 2 ){
				ChangeState( ENUM_TESTCHAR_STATE_DUSH_BACK );
			}
			else if( special == 8 ){
				ChangeState( ENUM_TESTCHAR_STATE_THROW_STANDBY );
			}
			else if( special == 4 ){
				ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
			}
			else if( special == 16 ){
				ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_3 );
			}

			else if( standard & COMMAND_ATTACK_LOW ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_LOW );
				}
			}
			else if( standard & COMMAND_ATTACK_MID ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_MID );
				}
			}
			else if( standard & COMMAND_ATTACK_HIGH ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH );
				}
//				else if( standard & COMMAND_FORWARD ){
//					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
//				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
				}
			}
			else if( standard & COMMAND_ATTACK_EX ){
				ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
			}

			else if( standard & COMMAND_UP ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
			}
			else if( standard & COMMAND_DOWN ){
				if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_FORWARD );
				}
				else if( standard & COMMAND_BACK ){
					m_GuardInput = ENUM_TESTCHAR_GUARD_CROUCH;
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_BACK );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
				}
			}
			else if( standard & COMMAND_FORWARD ){
				ChangeState( ENUM_TESTCHAR_STATE_WALK_FORWARD );
			}
			else if( standard & COMMAND_BACK ){
				m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
				ChangeState( ENUM_TESTCHAR_STATE_WALK_BACK );
			}
			
			break;

		case ENUM_TESTCHAR_STATE_WALK_FORWARD:
			if( special == 1 ){
				ChangeState( ENUM_TESTCHAR_STATE_DUSH_FORWARD );
			}
			else if( special == 4 ){
				ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
			}
			else if( special == 8 ){
				ChangeState( ENUM_TESTCHAR_STATE_THROW_STANDBY );
			}
			else if( special == 16 ){
				ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_3 );
			}
			else if( standard & COMMAND_ATTACK_LOW ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_LOW );
				}
			}
			else if( standard & COMMAND_ATTACK_MID ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_MID );
				}
			}
			else if( standard & COMMAND_ATTACK_HIGH ){
				if( standard & COMMAND_NONE_DIR ){
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
				}
				else if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
				}
			}

			else if( standard & COMMAND_NONE_DIR ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			else if( standard & COMMAND_UP ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
			}
			else if( standard & COMMAND_DOWN ){
				if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_FORWARD );
				}
				else if( standard & COMMAND_BACK ){
					m_GuardInput = ENUM_TESTCHAR_GUARD_CROUCH;
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_BACK );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
				}
			}
			else if( standard & COMMAND_BACK ){
				m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
				ChangeState( ENUM_TESTCHAR_STATE_WALK_BACK );
			}

			break;

		case ENUM_TESTCHAR_STATE_WALK_BACK:
			if( special == 1 ){
				ChangeState( ENUM_TESTCHAR_STATE_DUSH_FORWARD );
			}
			else if( special == 4 ){
				ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
			}
			else if( special == 8 ){
				ChangeState( ENUM_TESTCHAR_STATE_THROW_STANDBY );
			}
			else if( standard & COMMAND_ATTACK_LOW ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_LOW );
				}
			}
			else if( standard & COMMAND_ATTACK_MID ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_MID );
				}
			}
			else if( standard & COMMAND_ATTACK_HIGH ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH );
				}
				else if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
				}
			}

			else if( standard & COMMAND_NONE_DIR ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			else if( standard & COMMAND_UP ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
			}
			else if( standard & COMMAND_DOWN ){
				if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_FORWARD );
				}
				else if( standard & COMMAND_BACK ){
					m_GuardInput = ENUM_TESTCHAR_GUARD_CROUCH;
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_BACK );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH );
				}
			}
			else if( standard & COMMAND_FORWARD ){
				ChangeState( ENUM_TESTCHAR_STATE_WALK_FORWARD );
			}
			else{
				m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH:
		case ENUM_TESTCHAR_STATE_CROUCH_FORWARD:
		case ENUM_TESTCHAR_STATE_CROUCH_BACK:
			if( special == 16 ){
				ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_3 );
			}
			else if( standard & COMMAND_ATTACK_LOW ){
				if( standard & COMMAND_NONE_DIR ){
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_LOW );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW );
				}
			}
			else if( standard & COMMAND_ATTACK_MID ){
				if( standard & COMMAND_NONE_DIR ){
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_MID );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID );
				}
			}
			else if( standard & COMMAND_ATTACK_HIGH ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH );
				}
				else if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
				}
			}
			else if( standard & COMMAND_ATTACK_EX ){
				if( standard & COMMAND_DOWN ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX );
				}
//				else if( standard & COMMAND_FORWARD ){
//					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
//				}
//				else{
//					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
//				}
			}

			else if( standard & COMMAND_NONE_DIR ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			else if( standard & COMMAND_UP ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
			}
			else if( standard & COMMAND_DOWN ){
				if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_FORWARD );
				}
				else if( standard & COMMAND_BACK ){
					m_GuardInput = ENUM_TESTCHAR_GUARD_CROUCH;
					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_BACK );
				}
			}
			else if( standard & COMMAND_FORWARD ){
				ChangeState( ENUM_TESTCHAR_STATE_WALK_FORWARD );
			}
			else if( standard & COMMAND_BACK ){
				m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
				ChangeState( ENUM_TESTCHAR_STATE_WALK_BACK );
			}

			break;

		case ENUM_TESTCHAR_STATE_JUMP_SETUP:
			if( m_Flame > m_Spec.TIME_JUMP_STANBY ){
				if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_FORWARD );
				}
				else if( standard & COMMAND_BACK ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_BACK );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_NORMAL );
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_NORMAL:
		case ENUM_TESTCHAR_STATE_JUMP_BACK:
		case ENUM_TESTCHAR_STATE_JUMP_FORWARD:
			if( special == 1 ){
				if( CanJumpDush() ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD );
				}
			}
			else if( special == 2 ){
				if( CanJumpDush() ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK );
				}
			}
			else if( special == 4 ){
				ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_1 );
			}

			else if( standard & COMMAND_ATTACK_HIGH ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH );
			}
			else if( standard & COMMAND_ATTACK_LOW ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW );
			}
			else if( standard & COMMAND_ATTACK_MID ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID );
			}
			else if( standard & COMMAND_ATTACK_EX ){
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX );
			}

			else if( standard & COMMAND_MAKE_UP ){
				if( CanJump() ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
				}
			}
			else if( standard & COMMAND_BACK ){
				m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
			}
//			if( pad & PAD_UP ){
//				ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
//			}
//			if( special == 1 ){
//				ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD );
//			}
//			if( special == 2 ){
//				ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK );
//			}
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_LOW:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( standard & COMMAND_ATTACK_LOW ){
					if( standard & COMMAND_DOWN ){
						ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW );
					}
					else{
						ChangeState( ENUM_TESTCHAR_STATE_ATTACK_LOW );
					}
				}
				else if( standard & COMMAND_ATTACK_MID ){
					if( standard & COMMAND_DOWN ){
						ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID );
					}
					else{
						ChangeState( ENUM_TESTCHAR_STATE_ATTACK_MID );
					}
				}
				else if( standard & COMMAND_ATTACK_HIGH ){
					if( standard & COMMAND_DOWN ){
						ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH );
					}
					else{
						ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
					}
				}
			}

			if( m_Flame > 12 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_MID:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
				}
				else if( standard & COMMAND_ATTACK_HIGH ){
					if( standard & COMMAND_DOWN ){
						ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH );
					}
					else{
						ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
					}
				}
			}
			if( m_Flame > 34 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DAMAGE:
			if( m_Flame > 15 ){
//				ChangeState( ENUM_TESTCHAR_STATE_JUMP_RECOVER );
			}
			else if( m_Flame > 15 ){
				if( standard & COMMAND_ATTACK_LOW ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_RECOVER );
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 1 ){
					ChangeState( ENUM_TESTCHAR_STATE_DUSH_FORWARD );
				}
			}

			if( m_Flame > 55 ){
				m_Vector[0] += 44 * m_Dir;
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_EX:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
				}
			}
//			if( m_Flame > 32 ){
//				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
//			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 1 ){
					if( CanJumpDush() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD );
					}
				}
				else if( special == 2 ){
					if( CanJumpDush() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK );
					}
				}
				else if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_1 );
				}

				else if( standard & COMMAND_ATTACK_HIGH ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH );
				}
				else if( standard & COMMAND_ATTACK_LOW ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW );
				}
				else if( standard & COMMAND_ATTACK_MID ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID );
				}
				else if( standard & COMMAND_ATTACK_EX ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX );
				}

				else if( standard & COMMAND_MAKE_UP ){
					if( CanJump() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
					}
				}
				else if( standard & COMMAND_BACK ){
					m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 1 ){
					if( CanJumpDush() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD );
					}
				}
				else if( special == 2 ){
					if( CanJumpDush() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK );
					}
				}
				else if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_1 );
				}

				else if( standard & COMMAND_ATTACK_HIGH ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH );
				}
				else if( standard & COMMAND_ATTACK_LOW ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW );
				}
				else if( standard & COMMAND_ATTACK_MID ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID );
				}
				else if( standard & COMMAND_ATTACK_EX ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX );
				}

				else if( standard & COMMAND_MAKE_UP ){
					if( CanJump() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
					}
				}
				else if( standard & COMMAND_BACK ){
					m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 1 ){
					if( CanJumpDush() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD );
					}
				}
				else if( special == 2 ){
					if( CanJumpDush() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK );
					}
				}
				else if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_1 );
				}

				else if( standard & COMMAND_ATTACK_HIGH ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH );
				}
				else if( standard & COMMAND_ATTACK_LOW ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW );
				}
				else if( standard & COMMAND_ATTACK_MID ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID );
				}
				else if( standard & COMMAND_ATTACK_EX ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX );
				}

				else if( standard & COMMAND_MAKE_UP ){
					if( CanJump() ){
						ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
					}
				}
				else if( standard & COMMAND_BACK ){
					m_GuardInput = ENUM_TESTCHAR_GUARD_STAND;
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
				}
				else if( standard & COMMAND_UP ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
				}
				else if( standard & COMMAND_UP ){
					ChangeState( ENUM_TESTCHAR_STATE_JUMP_SETUP );
				}
			}
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
			if( m_Flame > 20 ){
				if( !(standard & COMMAND_FORWARD) ){
					ChangeState( ENUM_TESTCHAR_STATE_DUSH_FORWARD_END );
				}
			}
			break;


	}
	// エフェクト表示アクション
	if( standard & COMMAND_ATTACK_OPT1 ){
//		new(m_Game->m_CommonEffect) CEffTest( m_Game, this );
	}
	// エフェクト表示アクション
	if( standard & COMMAND_OPT2 ){
//		new(m_Game->m_CommonEffect) CEffTest( m_Game, this );
	}

	////////////////////////////////////
	// キャラクター移動					
	////////////////////////////////////

	switch( m_State ){
		case ENUM_TESTCHAR_STATE_WALK_FORWARD:
			m_Vector[0] += m_Spec.SPEED_FORWARD * m_Dir;
			break;

		case ENUM_TESTCHAR_STATE_WALK_BACK:
			m_Vector[0] -= m_Spec.SPPED_BACK * m_Dir;
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
			if( m_Flame < 6 ){
//				m_Vector[0] += 4 * m_Dir;
			}
			else{
				m_Vector[0] += m_Spec.SPEED_DUSH_FORWARD * m_Dir;
				m_Vector[1] -= 3 ;
			}
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD_END:
			DoAir();
			break;

		case ENUM_TESTCHAR_STATE_DUSH_BACK:
			m_Vector[0] -= m_Spec.SPEED_DUSH_BACK * m_Dir;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
			if( m_Flame > 10 ){
				m_Vector[0] += m_Spec.SPEED_JUMP_DUSH_FORWARD * m_Dir;
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK:
			m_Vector[0] -= m_Spec.SPEED_JUMP_DUSH_BACK * m_Dir;
			break;
	}

	// サウンド処理
	CSoundManager::Play( m_State, m_Flame );

	return TRUE;
}

// ChangeState
// 状態変化処理
void CShanaProt::ChangeState( int state )
{
	m_Flame		= 0;
	
	int flag	= 0x0;
	int sub		= 0;
	int before_sub= 0;

	before_sub = m_SubStatus ;
	m_HittedAttack	= 0;

	// 状態退状アクション
	switch( m_State )
	{
		case ENUM_TESTCHAR_STATE_DAMAGE:
		case ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE:
		case ENUM_TESTCHAR_STATE_CROUCH_DAMAGE:
		case ENUM_TESTCHAR_STATE_JUMP_DAMAGE:
		case ENUM_TESTCHAR_STATE_BIG_DAMAGE:
		case ENUM_TESTCHAR_STATE_DOWN:
			m_KnockBackVector[0] = 0;
			m_KnockBackVector[1] = 0;
			// コンボ数クリア判定（ここかな・・・）
			switch( state )
			{
				case ENUM_TESTCHAR_STATE_DAMAGE:
				case ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE:
				case ENUM_TESTCHAR_STATE_CROUCH_DAMAGE:
				case ENUM_TESTCHAR_STATE_JUMP_DAMAGE:
				case ENUM_TESTCHAR_STATE_BIG_DAMAGE:
				case ENUM_TESTCHAR_STATE_JUMP_BLOW_DOWN:
				break;

				default:
					m_DamageInfo.m_ComboCount = 0 ;	// コンボ数クリア
				break;
			}

		break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
			StartAir( 5 * m_Dir , 3.0f , 0 );
		break;

/*		case ENUM_TESTCHAR_STATE_JUMP_SETUP:
			switch( state )
			{
				case ENUM_TESTCHAR_STATE_JUMP_BACK:
				case ENUM_TESTCHAR_STATE_JUMP_NORMAL:
				case ENUM_TESTCHAR_STATE_JUMP_FORWARD:
				new(m_ResBattle->m_CommonEffect) CEffAction01( m_ResBattle, this );
			}
		break;
*/
	}

	// 状態入状アクション
	switch( state ){
		case ENUM_TESTCHAR_STATE_NEUTRAL:
			ChangeAnime( 0 , 0 ) ;
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;
		
		case ENUM_TESTCHAR_STATE_WALK_FORWARD:
			ChangeAnime( 1 , 0 ) ;
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_WALK_BACK:
			ChangeAnime( 2 , 0 ) ;
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_LOW:
//	SBArr[ENUM_SE_BATTLE_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
//	SBArr[ENUM_SE_BATTLE_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
			m_Parameter.m_SpGauge+=10;
			ChangeAnime( 3 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 6, 6, 8 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_MID:
			m_Parameter.m_SpGauge+=20;
			ChangeAnime( 20 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 6, 6, 0 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
			m_Parameter.m_SpGauge+=25;
			ChangeAnime( 4 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 30, 30, 0 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_EX:
			m_Parameter.m_SpGauge+=25;
//			StartAir( (float)5 * m_Dir ,(float)1.0f, 0 );
			ChangeAnime( 5 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 20, 20, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_SETUP:
			IncreaseJump();
			ChangeAnime( 6 , 0 ) ;
//			m_EnableDir		= FALSE;
			m_EnableDir		= TRUE;
			sub = before_sub;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_FORWARD:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_SETUP ){
                StartAir( (float)m_Spec.SPEED_JUMP_FORWARD * m_Dir , (float)m_Spec.SPEED_JUMP, 0 );
				ChangeAnime( 7 , 0 ) ;
			}
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_BACK:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_SETUP ){
                StartAir( -(float)m_Spec.SPEED_JUMP_BACK * m_Dir , (float)m_Spec.SPEED_JUMP, 0 );
				ChangeAnime( 7 , 0 ) ;
			}
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_NORMAL:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_SETUP ){
                StartAir( 0.0f , (float)m_Spec.SPEED_JUMP, 0 );
				ChangeAnime( 7 , 0 ) ;
			}
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH:
		case ENUM_TESTCHAR_STATE_CROUCH_FORWARD:
		case ENUM_TESTCHAR_STATE_CROUCH_BACK:
			// すでにしゃがみ状態だったら、しゃがみアニメーション省略
			if( ( m_State == ENUM_TESTCHAR_STATE_CROUCH )
				|| ( m_State == ENUM_TESTCHAR_STATE_CROUCH_FORWARD )
				|| ( m_State == ENUM_TESTCHAR_STATE_CROUCH_BACK )){
			}
			else if( m_SubStatus == ENUM_TESTCHAR_SUB_STATE_CROUCH ){
				ChangeAnime( 11, 3 );
			}
			else{
				ChangeAnime( 11 , 0 ) ;
			}
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW:
			ChangeAnime( 14 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID:
			ChangeAnime( 21 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10, 10, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
			ChangeAnime( 29 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 30, 30, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
			ChangeAnime( 66 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_START:
			ChangeAnime( 67 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_END:
			ChangeAnime( 68 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
			new(m_ResBattle->m_CommonEffectFront) CEffHit007( m_ResBattle, this );
			new(m_ResBattle->m_CommonEffectFront) CEffAction003( m_ResBattle, this );
			ChangeAnime( 12 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD_END:
			ChangeAnime( 46 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DUSH_BACK:
			ChangeAnime( 13 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW:
			ChangeAnime( 22 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID:
			ChangeAnime( 23 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
			ChangeAnime( 15 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX:
			ChangeAnime( 55, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX ;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
			IncreaseJumpDush();
			new(m_ResBattle->m_CommonEffectFront) CEffHit004( m_ResBattle, this );
			ChangeAnime( 16 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK:
			IncreaseJumpDush();
			new(m_ResBattle->m_CommonEffectFront) CEffAction02( m_ResBattle, this );
			ChangeAnime( 17 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_END:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD ){
				StartAir( (float)m_Spec.SPEED_JUMP_FORWARD * m_Dir ,0.0f, 0 );
				ChangeAnime( 7 , 0 ) ;
				state = ENUM_TESTCHAR_STATE_JUMP_FORWARD;
			}
			else if( m_State == ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK ){
				StartAir( -((float)m_Spec.SPEED_JUMP_DUSH_BACK-2) * m_Dir ,0.0f, 0 );
				ChangeAnime( 7 , 0 ) ;
				state = ENUM_TESTCHAR_STATE_JUMP_BACK;
			}

			if( ( m_Vector[1] <= 1.0f ) &&
				( m_Vector[1] > 0.0f ) ){
				ChangeAnime( 8 , 0 ) ;
			}
			if( m_Vector[1] == 0.0f ){
				ChangeAnime( 9 , 0 ) ;
			}
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );

			break;

		case ENUM_TESTCHAR_STATE_DAMAGE:
			ChangeAnime( 18, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_DAMAGE:
			ChangeAnime( 19, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE:
			StartAir( 1.0f * -m_Dir, CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_VECTOR
						 , 0, (float)CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_GRAVITY );
			ChangeAnime( 24, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_BIG_DAMAGE:
			StartAir( 7.0f * -m_Dir, 7.0f , 0, 0.3f );
			ChangeAnime( 56, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DOWN:
			ChangeAnime( 28, 0 ) ;
			m_EnableDir				= FALSE;
//			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_DOWN;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_GETUP:
			ChangeAnime( 36, 0 ) ;
			m_EnableDir				= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_DOWN;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_GUARD:
			ChangeAnime( 30, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_GUARD:
			ChangeAnime( 32, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DAMAGE:
			StartAir( 5.0f * -m_Dir, CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_VECTOR
						 , 0, (float)CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_GRAVITY );
			ChangeAnime( 33, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_GUARD:
			StartAir( 5.0f * -m_Dir, CHARACTER_COMMON_PARAMETER::AIR_GUARD_VECTOR
						 , 0, (float)CHARACTER_COMMON_PARAMETER::AIR_GUARD_GRAVITY );
			ChangeAnime( 34, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_THROW_STANDBY:
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_THROW:
			ChangeAnime( 50, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DAMAGE_THROW:
			ChangeAnime( 18, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_MISS_THROW:
			ChangeAnime( 53, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_1:
			ChangeAnime( 60, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_1_END:
			ChangeAnime( 61, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_2:
			ChangeAnime( 63, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_3:
			StartAir( 1.0f * -m_Dir * -1 , 20.0f , 0, 0.5f );
			ChangeAnime( 65, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_BLOW_DOWN:
			ChangeAnime( 40, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND:
			StartAir( 7.0f * -m_Dir, 7.0f , 0, 0.3f );
			ChangeAnime( 41, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_RECOVER:
			StartAir( 2.0f * -m_Dir, 7.0f , 0, 0.3f );
			ChangeAnime( 42, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;
	}
	// ジャンプしたときのエフェクト処理
/*	if( ( before_sub == ENUM_TESTCHAR_SUB_STATE_STAND )
		||( before_sub == ENUM_TESTCHAR_SUB_STATE_CROUCH ) ){
		if( sub == ENUM_TESTCHAR_SUB_STATE_JUMP ){
			new(m_ResBattle->m_CommonEffect) CEffAction01( m_ResBattle, this );
		}
	}
*/	if( ( before_sub == ENUM_TESTCHAR_SUB_STATE_JUMP )
		&&( sub == ENUM_TESTCHAR_SUB_STATE_STAND ) ){
		new(m_ResBattle->m_CommonEffect) CEffAction01( m_ResBattle, this );
	}

	m_State = state | flag ;
	m_SubStatus = sub ;
}

// アニメーション変更
void CShanaProt::ChangeAnime( int animeNo , int motionNo )
{
	m_Anime.ChangeAction( animeNo , motionNo );
/*
m_AnimeNo		= animeNo;
//	m_AnimeFlame	= 0;
	m_AnimeImage	= 0;// 旧　m_Anime->m_StartAction[m_AnimeNo] ;

	while( animeFlame > 0 ){
        // アニメーションのフレーム数が０の場合　アニメーションなし
		if( m_Anime.GetCurrentMotion()->m_Flame == 0 ){
// 旧	if( m_Anime->m_AnimeData[m_AnimeImage].m_Flame == 0 ){
			break;
		}
		animeFlame -= m_Anime.GetCurrentMotion()->m_Flame;
// 旧	m_Anime->m_AnimeData[m_AnimeImage].m_Flame ;
		if( animeFlame >= 0 ){
			m_AnimeImage++;
		}
		if( m_AnimeImage >= ( m_Anime.GetCurrentAction()->m_NumMotion ) ){
// 旧	if( m_AnimeImage >= ( m_Anime->m_StartAction[m_AnimeNo] + m_Anime->m_NumAction[m_AnimeNo] ) ){
			m_AnimeImage = 0;// 旧　m_Anime->m_StartAction[m_AnimeNo] ;
		}
	}
*/
}

// ジャンプ開始
void CShanaProt::StartAir( float vec_x, float vec_y, int op1, float gravity )
{
	m_AirVector[0]	= vec_x;
	m_AirVector[1]	= vec_y;
	m_AirBase[0]	= m_X;
	m_AirBase[1]	= m_Y;
	m_AirTime		= op1;
	m_AirGravity	= gravity;
}

// ジャンプ着地
void CShanaProt::EndAir()
{
	ClearJump();
	ClearJumpDush();
	m_AirVector[0]	= 0;
	m_AirVector[1]	= 0;
}

// 空中動作
void CShanaProt::DoAir()
{
	m_AirTime++ ;
	m_Y = m_AirBase[1] - ( m_AirVector[1] * m_AirTime - ( m_AirGravity * ( m_AirTime * m_AirTime) ) );// m_Vector[ENUM_VECTOR_UP];
	m_AirIncrease = m_AirVector[1] - m_AirGravity * 2 * m_AirTime;
	m_Vector[0] += m_AirVector[0];
}

// Action()コール後の後処理
bool CShanaProt::ActionFinalize()
{
	if( m_StopedMoveCount != 0 ){
		return true;
	}

	int x,y;
	m_ResBattle->GetScreenPosition(&x, &y);
	x -= 400;
	x = m_X - x ;

	// ノックバック対象者が本体じゃなかったから、相手のベクトルを増やすことはしない
	if( m_KnockBackChara == m_Target ){
		if( x + m_Vector[0] + m_KnockBackVector[0] < 0 ){
			if( m_KnockBackVector[0] < 0 ){
				if( x + m_Vector[0] < 0 ){
					// 相手のベクトルを増やす
					m_KnockBackChara->AddVector( -m_KnockBackVector[0], 0 );
				}
				else{
					// 相手のベクトルを増やす
					m_KnockBackChara->AddVector( x + m_Vector[0] - m_KnockBackVector[0], 0 );
				}
			}
		}
		if( x + m_Vector[0] + m_KnockBackVector[0] > 800 ){
			if( m_KnockBackVector[0] > 0 ){
				if( x + m_Vector[0] > 800 ){
					// 相手のベクトルを増やす
					m_KnockBackChara->AddVector( -m_KnockBackVector[0], 0 );
				}
				else{
					// 相手のベクトルを増やす
					m_KnockBackChara->AddVector( 800 - x - m_Vector[0] - m_KnockBackVector[0], 0 );
				}
			}
		}
	}

	// ノックバック移動
	m_Vector[0] += m_KnockBackVector[0];
	m_Vector[1] += m_KnockBackVector[1];
	// キャラクター移動
//	Transfer();

}

// Interfer
// 衝突、判定処理
bool CShanaProt::Interfere()
{
	// キャラクター移動
	Transfer();

	if( m_StopedMoveCount != 0 ){
		return true;
	}

	// 相手がいる場合の処理がここから開始
	////////////////////
	if( m_Target == NULL ){
		return true;
	}

//	m_KnockBackChara = NULL;
	// 当たり判定
	if( m_Anime.IsAttackEnabled() && m_Target->IsCollisioned( this ) ){	// 相手に攻撃あたってる？
		HitAttack();
	}

	// 投げ判定
	if( m_State == ENUM_TESTCHAR_STATE_THROW_STANDBY ){
		DecideThrow( m_Target->IsThrown( this ) );
	}

	if( m_StopedMoveCount == 0 ){
		if( m_EnableDir ){
			UpdateCharaDir();
		}
	}

	return true;
}

// 最終的な自キャラの座標計算
void CShanaProt::Transfer()
{
	// キャラクター移動
	m_X += m_Vector[0];
	m_Y += m_Vector[1];

	// 衝突判定
	int x1(0);
	int x2(0);
	if( abs( m_Y - m_Target->m_Y ) < 100 ){ 
		if( ( m_X < m_Target->m_X ) && ( m_X + 50 > m_Target->m_X ) ){
			x1 = (m_Target->m_X - m_X - 51) >> 1 ;
			x2 = (m_X - m_Target->m_X + 51) >> 1 ;
		}
		// X軸がぴったり一致した場合
		else if( m_X == m_Target->m_X ){
			x1 = m_Y > m_Target->m_Y?m_Dir:0;
		}
		this->AddPosition( x1 , 0 );
		m_Target->AddPosition( x2 , 0 );
	}
//	if( ( m_X < m_Target->m_X ) && ( m_X + 30 > m_Target->m_X ) ){
//		this->AddPosition( (m_X - m_Target->m_X) >> 1, 0 ) ;
//		m_Target->AddPosition( (m_Target->m_X - m_X) >> 1, 0 ) ;
//	}
//	m_X += m_AirVector[0];
//	m_Y += m_AirVector[1];

	int x,y;
	m_ResBattle->GetScreenPosition(&x, &y);
	x -= 400;
	x = m_X - x ;
	if( x < 0 ){
		m_X -= x;
	}
	if( x > 800 ){
		m_X -= x - 800;
	}

}

/*
bool CShanaProt::Draw()
{
	return true;
}
*/

// 衝突、判定の後処理
bool CShanaProt::InterfereFinalize( )
{
	// 最終
/*	switch( m_ReceiveAttackTemplateState ){
		case ENUM_TESTCHAR_STATE_DAMAGE :
//			m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_CROUCH_DAMAGE ;
			ChangeState( ENUM_TESTCHAR_STATE_DAMAGE );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_DAMAGE :
//			m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_CROUCH_DAMAGE ;
			ChangeState( ENUM_TESTCHAR_STATE_CROUCH_DAMAGE );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE:
			ChangeState( ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE );
			break;
	}
*/
	// 投げ喰らったけど、同時に攻撃があたっていたら、投げられ無効
	if( m_ReceiveAttackTemplateState == ENUM_TESTCHAR_STATE_DAMAGE_THROW ){
		if( m_Target->m_ReceiveAttackTemplateState != ENUM_TESTCHAR_STATE_NONE ){
			m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_NONE;
		}
		else{
			int x,y;
			m_Target->GetPosition(&x, &y);
			m_X = x - 40 * m_Dir;
		}
	}
	if( m_ReceiveAttackTemplateState != ENUM_TESTCHAR_STATE_NONE ){

		// 動作完全ストップ
		m_StopedMoveCount = 5;

		// キャラクター向き反映（ここか？）
		UpdateCharaDir();

		ChangeState( m_ReceiveAttackTemplateState );
	}

	//////////////////////
	// アニメーション実行
	//////////////////////
//	if( m_StopedMoveCount != 0 ){
//		m_StopedMoveCount--;
//	}
//	else{
//		CSprite::InterfereFinalize();
//	}

	return 0;
}

// 描画処理
bool CShanaProt::Draw( CD3DDraw *draw )
{
	CTexture	*tex;
	D3DXIMAGE_INFO	texInfo;

	CSprite::Draw();

	// 描画
	// 画像表示基準点
	StImageData *anime ;
	anime = &m_Anime.GetCurrentMotion()->m_Image ;

	tex = m_Tex->GetTexture( anime->m_TextureNo ) ;
	tex->GetTextureInfo( &texInfo ) ;

	// 描画（影）
	m_DispObj->SetBlendColor( D3DCOLOR_ARGB(200,0,0,0) );
	m_DispObj->SetRotation( 1,-90,0,0, 0, 0);
	m_DispObj->SetTexture( tex );
/*	m_DispObj->SetDestRect( m_X + ( -anime->m_BaseX ) * 2 * m_Dir * -1 ,
										( m_FieldY * 2 - m_Y ) + ( (long)-texInfo.Height / 2 * 2 ),
										m_X + ( (long)texInfo.Width - anime->m_BaseX ) * 2 * m_Dir * -1 ,
										( m_FieldY * 2 - m_Y ) + ( (long)texInfo.Height / 2 * 2 ),
										- anime->m_BaseY - ( m_FieldY - m_Y ) );
*/
	m_DispObj->SetDestRect( m_X + ( -anime->m_BaseX ) * 2 * m_Dir * -1 ,
										m_FieldY + ( (long)-texInfo.Height / 2 * 2 ),
										m_X + ( (long)texInfo.Width - anime->m_BaseX ) * 2 * m_Dir * -1 ,
										m_FieldY + ( (long)texInfo.Height / 2 * 2 ),
										- anime->m_BaseY );

	draw->Draw( m_DispObj );

	// 描画（人物）
	m_DispObj->SetBlendColor( 0xffffffff );
	m_DispObj->SetRotation( 1,0,0,0, 0, 0);
	m_DispObj->SetTexture( tex );
	m_DispObj->SetDestRect( m_X + ( -anime->m_BaseX ) * 2 * m_Dir * -1 ,
										m_Y + ( -anime->m_BaseY ) * 2,
										m_X + ( (long)texInfo.Width - anime->m_BaseX ) * 2 * m_Dir * -1 ,
										m_Y + ( (long)texInfo.Height - anime->m_BaseY ) * 2 ,0);

	draw->Draw( m_DispObj );

	return TRUE;
}

bool CShanaProt::DrawFinalize()
{
	//////////////////////
	// アニメーション実行
	//////////////////////
	if( m_StopedMoveCount != 0 ){
		m_StopedMoveCount--;
	}
	else{
		CSprite::DrawFinalize();
	}
	return TRUE;
}

// SPゲージ取得
int CShanaProt::GetSpGauge(){
	return m_Parameter.m_SpGauge;
}

// HPゲージ取得
int CShanaProt::GetHpGauge(){
	return m_Parameter.m_HpGauge;
}

// キャラの向き取得
char CShanaProt::getDir( ){

	return (m_Dir == ENUM_DIR_RIGHT ? DIRECTION_RIGHT : DIRECTION_LEFT) ;

}

// キャラの向き取得
char CShanaProt::GetDir( ){

	return m_Dir;

}

// 自分の存在を教えてあげる
void CShanaProt::NotifyPlayer( CShanaProt *target )
{
	SetTarget( target );
}

// 移動方向量取得
void CShanaProt::GetVector( int *x, int *y )
{
	*x = m_Vector[0];
	*y = m_Vector[1];
}

// ターゲット取得
CShanaProt* CShanaProt::GetTarget()
{
	return m_Target;
}

// 移動方向量セット
void CShanaProt::SetVector( int x, int y )
{
	m_Vector[0] = x;
	m_Vector[1] = y;
}

// 移動方向量加算
void CShanaProt::AddVector( int x, int y )
{
	m_Vector[0] += x;
	m_Vector[1] += y;
}

// ダメージ情報取得
ST_CHARACTER_DAMAGE_INFO* CShanaProt::GetDamageInfo( )
{
	return &m_DamageInfo ;
}

// 喰らい判定
int CShanaProt::IsCollisioned( CSprite *target )
{
	RECT	myrect;
	RECT	destrect;
	RECT	hitrect;
	int		mybaseX, mybaseY, destbaseX, destbaseY ;

	StMotionData	*attack;
	StMotionData	*wound;

	attack = target->GetAnime()->GetCurrentMotion();

	// TBD　アニメ全部実装されるまで。
	if (attack == 0) {
		return 0;
	}

	wound = m_Anime.GetCurrentMotion();

	target->GetPosition( &destbaseX, &destbaseY);//
	//destbaseX = target->m_X;// + attack->m_Image.m_BaseX * 2 * target->m_Dir * -1 ;
	//destbaseY = target->m_Y;// + attack->m_Image.m_BaseY * 2 ;
	mybaseX = m_X;// + wound->m_Image.m_BaseX * 2 * m_Dir * -1 ;
	mybaseY = m_Y;// + wound->m_Image.m_BaseY * 2 ;

	int i;
	int j;
	for( j = 0 ; j < attack->m_Attack.m_NumHit ; j++ ){
		int dir;
		dir = target->GetDir();
		SetRect( &destrect, destbaseX + attack->m_Attack.m_HitArea[j].left * 2 * dir * -1,
							destbaseY + attack->m_Attack.m_HitArea[j].top * 2 ,
							destbaseX + attack->m_Attack.m_HitArea[j].right * 2 * dir * -1,
							destbaseY + attack->m_Attack.m_HitArea[j].bottom * 2 );
		for( i = 0 ; i < wound->m_Wound.m_NumHit ; i++ ){
			SetRect(&myrect,mybaseX + wound->m_Wound.m_HitArea[i].left * 2 * m_Dir * -1,
							mybaseY + wound->m_Wound.m_HitArea[i].top * 2 ,
							mybaseX + wound->m_Wound.m_HitArea[i].right * 2 * m_Dir * -1,
							mybaseY + wound->m_Wound.m_HitArea[i].bottom * 2 );

			if( myrect.left > myrect.right ){
				int tmp = myrect.left;
				myrect.left = myrect.right ;
				myrect.right = tmp;
			}
			if( myrect.top > myrect.bottom ){
				int tmp = myrect.bottom;
				myrect.bottom = myrect.top ;
				myrect.top = tmp;
			}

			if( destrect.left > destrect.right ){
				int tmp = destrect.left;
				destrect.left = destrect.right ;
				destrect.right = tmp;
			}
			if( destrect.top > destrect.bottom ){
				int tmp = destrect.bottom;
				destrect.bottom = destrect.top ;
				destrect.top = tmp;
			}

			// 判定
			if( IntersectRect( &hitrect, &myrect, &destrect ) != 0 ){
				return 1;
			}
		}
	}

	return 0;
}

// 攻撃を喰らったの処理
// 防御・ヒット等の判定を行う
// さらに状態変化
int CShanaProt::ReceiveAttack( CSprite* target, CAnime* anime )
{
	// 防御・ヒット等の判定を行う
	//////////////////////////////
	// 表示優先順位変更
	m_ResBattle->NotifyReceivedAttack( this->m_player );

	// 防御中
	m_KnockBackChara = m_Target ;
	if( m_Target != target ){
		m_KnockBackChara = NULL;
	}
	int ret = 0;
	if( m_GuardInput != ENUM_TESTCHAR_GUARD_OFF ){
		switch( anime->GetCurrentMotion()->m_Attack.m_Property ){
			case ENUM_ATTACK_PROPERTY_HIGH:
				ret = 1 ;
			break;

			case ENUM_ATTACK_PROPERTY_LOW:
				if( ( m_SubStatus == ENUM_TESTCHAR_SUB_STATE_CROUCH )
					|| ( m_SubStatus == ENUM_TESTCHAR_SUB_STATE_JUMP ) ){
					ret = 1 ;
				}
			break;

			case ENUM_ATTACK_PROPERTY_MIDDLE:
				if( ( m_SubStatus == ENUM_TESTCHAR_SUB_STATE_STAND )
					|| ( m_SubStatus == ENUM_TESTCHAR_SUB_STATE_JUMP ) ){
					ret = 1 ;
				}
			break;
		}
	}
	if( ret == 1 ){
		switch( m_SubStatus ){
			case ENUM_TESTCHAR_SUB_STATE_STAND :
				m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_GUARD ;
				break;

			case ENUM_TESTCHAR_SUB_STATE_CROUCH :
				m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_CROUCH_GUARD ;
				break;

			case ENUM_TESTCHAR_SUB_STATE_JUMP :
				m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_JUMP_GUARD ;
				break;
		}
		return 1;
	}

	// 喰らい情報更新
	m_DamageInfo.m_ComboCount++ ;	// コンボ数インクリメント

	// HPを減らす
	m_Parameter.m_HpGauge -= m_ResBattle->GetDamage(
								anime->GetCurrentMotion()->m_Attack.m_BaseDamage,
								m_DamageInfo.m_ComboCount) ;
	if( m_Parameter.m_HpGauge < 0 ){
		m_Parameter.m_HpGauge = 0;
	}

    // 状態変化
	/////////////
	// 喰らった攻撃の威力を確認
	if( anime->GetCurrentMotion()->m_Attack.m_Type ){
	}

	if( target->GetState() == ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH ){
		m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE ;
	}
	else if( target->GetState() == ENUM_TESTCHAR_STATE_ATTACK_HIGH ){
		m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_JUMP_BLOW_DOWN ;
	}
	else{
		switch( m_SubStatus ){
			case ENUM_TESTCHAR_SUB_STATE_STAND :
	//			m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_AERIAL_DAMAGE ;
				m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_DAMAGE ;
				break;

			case ENUM_TESTCHAR_SUB_STATE_CROUCH :
				m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_CROUCH_DAMAGE ;
				break;

			case ENUM_TESTCHAR_SUB_STATE_DAMAGE :
				m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_CROUCH_DAMAGE ;
				break;

			case ENUM_TESTCHAR_SUB_STATE_JUMP:
				m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_JUMP_DAMAGE ;
				break;
		}
	}			
	return 0;
}

// 攻撃が当たった時の処理
// さらに状態変化
void CShanaProt::HitAttack()
{
	m_StopedMoveCount = 5;
	m_HittedAttack	= 1;
	m_Anime.AttackHit();		// 名前変えよう・・・

	if( m_Target->ReceiveAttack( this , &m_Anime ) == 0 ){
		// 攻撃がヒットしたことを通知
		m_ResBattle->NotifyHittedAttack( m_State );

		////////////
		// エフェクト処理
		// 上段・打撃限定
		switch( m_State ){
			case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW:
			case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
			case ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW:
			case ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID:
				new(m_ResBattle->m_CommonEffectFront) CEffHit009( m_ResBattle, m_Target );
				break;

			default:
				if( GetAnime()->GetCurrentMotion()->m_Attack.m_Property == ENUM_ATTACK_PROPERTY_HIGH ){
				new(m_ResBattle->m_CommonEffectFront) CEffHit009( m_ResBattle, m_Target );
			break;
		}

		}

		// そのた
		switch( m_State ){
			case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
				new(m_ResBattle->m_CommonEffectFront) CEffTest( m_ResBattle, m_Target );
			break;

			case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
				for( int i = 0 ; i < 20 ; i++)
				new(m_ResBattle->m_CommonEffectFront) CEffHit003( m_ResBattle, m_Target );
			break;

			default:
				new(m_ResBattle->m_CommonEffectFront) CEffHit005( m_ResBattle, m_Target );
			break;
		}
		switch( m_State ){
			case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
			case ENUM_TESTCHAR_STATE_ATTACK_MID:
			case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID:
			case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
			case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
			case ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX:
				new(m_ResBattle->m_CommonEffectFront) CEffHit001( m_ResBattle, m_Target );
				break;
		}

	}
	else{
		////////////
		// エフェクト処理
//		switch( m_State ){
//			case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
				new(m_ResBattle->m_CommonEffectFront) CEffGuard001( m_ResBattle, m_Target );
//			break;
//		}
	}
}

int CShanaProt::IsActionEnaled()
{
	return m_FlagActionEnabled;
}

int CShanaProt::IsThrown( CShanaProt *target )
{
	int x,dx,y;
	if( ( m_SubStatus == ENUM_TESTCHAR_SUB_STATE_STAND ) ||
		( m_SubStatus == ENUM_TESTCHAR_SUB_STATE_CROUCH ) ){
		target->GetPosition( &x, &y );
		dx = ( m_X > x )? m_X - x : x - m_X; 
		if( dx < 80 ){
			return true;
		}
	}
	return false;
}

void CShanaProt::DecideThrow( int isThrow )
{
	if( isThrow ){
		m_Target->ReceiveThrown( this );
		ChangeState( ENUM_TESTCHAR_STATE_THROW );
	}
	else{
		ChangeState( ENUM_TESTCHAR_STATE_MISS_THROW );
	}
}

int CShanaProt::ReceiveThrown( CShanaProt* target )
{
	// 表示優先順位変更
	m_ResBattle->NotifyReceivedAttack( this->m_player );

	m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_DAMAGE_THROW ;
	return true;
}

char CShanaProt::CanJump()
{
	return ( m_Spec.MAX_JUMP_STEP > m_NumJump );
}
void CShanaProt::IncreaseJump()
{
	m_NumJump++;
}
void CShanaProt::ClearJump()
{
	m_NumJump = 0;
}

char CShanaProt::CanJumpDush()
{
	return ( m_Spec.MAX_JUMP_DUSH_STEP > m_NumJumpDush );
}
void CShanaProt::IncreaseJumpDush()
{
	m_NumJumpDush++;
}
void CShanaProt::ClearJumpDush()
{
	m_NumJumpDush = 0;
}

void CShanaProt::UpdateCharaDir()
{
	int x,y ;
	m_Target->GetPosition( &x , &y );

	if( x + m_player > m_X ){
		m_Dir = ENUM_DIR_RIGHT ;
	}
	else{
		m_Dir = ENUM_DIR_LEFT ;
	}
}

void CShanaProt::SetCommand( CCommandManager *cmd )
{
	m_Command = cmd;
}

void CShanaProt::SetDefaultCommand( )
{
	m_Command = &m_PlayerCommand;
}

/////////////////////////////////////////////////////////////////////////
// CCharacterActionEnableSpec
/////////////////////////////////////////////////////////////////////////
void CCharacterActionEnableSpec::SetSpec(int action_enabled, int not, int hit, int every)
{
	m_FullActionEnabled = action_enabled;
	m_NotCancelTime = not;
	m_HitCancelTime = hit;
	m_EveryCancelTime = every;
	m_Hited = false;
}

int CCharacterActionEnableSpec::CanCancel( int flame, int hitted )
{
	if( m_FullActionEnabled ){
		return true;
	}
	else if( m_NotCancelTime >= flame ){
		return false;
	}
	else if( m_HitCancelTime <= flame ){
		if( hitted == true ){
			return true;
		}
	}
	if( m_EveryCancelTime == 0 ){
		return false;
	}
	else if( m_EveryCancelTime <= flame ){
		return true;
	}
	return 0;
}

void CCharacterActionEnableSpec::HitAttack( )
{
	m_Hited = true;
}
