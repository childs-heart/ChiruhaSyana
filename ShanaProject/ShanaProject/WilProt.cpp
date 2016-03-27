#include <d3dx9tex.h>
#include "WilProt.h"

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

/*
const float CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_GRAVITY(0.2f);
const float CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_VECTOR(10.0f);
const float CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_GRAVITY(0.5f);
const float CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_VECTOR(15.0f);
const float CHARACTER_COMMON_PARAMETER::AIR_GUARD_GRAVITY(0.4f);
const float CHARACTER_COMMON_PARAMETER::AIR_GUARD_VECTOR(1.0f);
*/

CWilProt::CWilProt( CResBattle *game ):CShanaProt( game )
{
	
	Initialize( game , 0, 0, 0 , NULL );
}

CWilProt::CWilProt( CResBattle *game, int x, int y, char player, CShanaProt* target ):CShanaProt( game )
{
	Initialize( game, x, y, player ,target );
}

// 初期化
void CWilProt::Initialize( CResBattle *game, int x, int y, char player, CShanaProt* target )
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

CWilProt::~CWilProt( )
{
}

// 性能セットアップ
bool CWilProt::SetSpec()
{
	m_Spec.MAX_HP				= 10000;
	m_Spec.MAX_SP				= 1000;
	m_Spec.DEFENSE				= 0 ;
	m_Spec.FAINT				= 0 ;
	m_Spec.MAX_JUMP_DUSH_STEP	= 1 ;
	m_Spec.MAX_JUMP_STEP		= 2 ;
	m_Spec.RANGE_JUMP_THROW		= 0 ;
	m_Spec.RANGE_THROW			= 10 ;
	m_Spec.SPEED_DUSH_BACK		= 8 ;
	m_Spec.SPEED_DUSH_FORWARD	= 6 ;
	m_Spec.SPEED_JUMP_DUSH_BACK		= 8 ;
	m_Spec.SPEED_JUMP_DUSH_FORWARD	= 7 ;
	m_Spec.SPEED_FORWARD		= 4 ;
	m_Spec.SPEED_JUMP			= 20 ;
	m_Spec.SPEED_JUMP_FORWARD	= 4 ;
	m_Spec.SPEED_JUMP_BACK		= 4 ;
	m_Spec.SPEED_JUMP_FALL		= 5 ;
	m_Spec.SPIRIT				= 5 ;
	m_Spec.SPPED_BACK			= 3 ;
	m_Spec.TIME_DOWN			= 10 ;
	m_Spec.TIME_JUMP_STANBY		= 3 ;
	m_Spec.WEIGHT				= 3 ;

	return TRUE;
}

// Move
// イベント関係なく動く動作
// Actionの前に実行される
bool CWilProt::Move()
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
				ChangeAnime( DOT_WILL_ANIME_JUMP + 2 , 0 ) ;
			}
			else if( ( m_AirIncrease <= 0.0f ) &&
				( m_Anime.GetCurrentActionNo() != DOT_WILL_ANIME_JUMP + 3 )){
				ChangeAnime( DOT_WILL_ANIME_JUMP + 3 , 0 ) ;
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
				ChangeAnime( DOT_WILL_ANIME_BACK_JUMP + 2 , 0 ) ;
			}
			else if( ( m_AirIncrease <= 0.0f ) &&
				( m_Anime.GetCurrentActionNo() != DOT_WILL_ANIME_BACK_JUMP + 3 )){
				ChangeAnime( DOT_WILL_ANIME_BACK_JUMP + 3 , 0 ) ;
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
				ChangeAnime( DOT_WILL_ANIME_JUMP + 2 , 0 ) ;
			}
			else if( ( m_AirIncrease <= 0.0f ) &&
				( m_Anime.GetCurrentActionNo() != DOT_WILL_ANIME_JUMP + 3 )){
				ChangeAnime( DOT_WILL_ANIME_JUMP + 3 , 0 ) ;
			}

			if( m_Y > m_FieldY ){
				m_Y = m_FieldY ;
				EndAir();
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
//			m_Vector[1] = 0;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
			if( m_Flame == 23 ){
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
			if( m_Flame == 9 ){
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
			break;

		case ENUM_TESTCHAR_STATE_DUSH_BACK:
			if( m_Flame > 11 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
			if( m_Flame == 3 ){
				ChangeAnime( DOT_WILL_ANIME_JUMP_DUSH_FORWARD1 , 0 ) ;
			}
			if( m_Flame == 20 ){
				ChangeAnime( DOT_WILL_ANIME_JUMP + 2 , 0 ) ;
				ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH_END);
			}
//			if( m_Flame > 4 ){
//				ChangeState( ENUM_TESTCHAR_STATE_JUMP_DUSH);
//			}
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
//			if( m_Flame > 20)

			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_EX:
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH_FOR:
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

//		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
//			if( m_Flame > 5 ){
//				ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX_START );
//			}
//			break;

//		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
//			if (m_Flame > 5) {
//				ChangeState(ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH_START);
//			}
//			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH_START:
			if( m_Flame <= 20 ){
				AddVector( ((20-m_Flame)/2 + 2) * m_Dir , 0 ) ;
			}
			else{
//				AddVector( m_Dir * 58, 0 ) ;
				AddVector( m_Dir * 40, 0 ) ;
				ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH_END );
			}
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH_END:
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
//TBD				ChangeAnime( 25 , 0 ) ;
			}
			if( ( m_AirIncrease <= 1.0f ) &&
				( m_AirIncrease > 0.0f ) ){
//TBD				ChangeAnime( 25 , 0 ) ;
			}
			if( ( m_AirIncrease <= -2.0f ) &&
				( m_AirIncrease > -4.0f ) ){
//TBD				ChangeAnime( 27 , 0 ) ;
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
//TBD				ChangeAnime( 57 , 0 ) ;
			}
			if( ( m_AirIncrease <= -2.0f ) &&
				( m_AirIncrease > -4.0f ) ){
//TBD				ChangeAnime( 58 , 0 ) ;
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
//TBD				ChangeAnime( 51, 0 ) ;
			}
			if( m_Flame == 35 ){
				new(m_ResBattle->m_CommonEffectFront) CEffHit001( m_ResBattle, m_Target );
				new(m_ResBattle->m_CommonEffectFront) CEffHit005( m_ResBattle, m_Target );
				m_Target->m_ReceiveAttackTemplateState = ENUM_TESTCHAR_STATE_BIG_DAMAGE;
			}
			if( m_Flame == 60 ){
//TBD				ChangeAnime( 52, 0 ) ;
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
//TBD					ChangeAnime( 8 , 0 ) ;
				}
				else if( ( m_AirIncrease <= 0.0f ) &&
					( m_Anime.GetCurrentActionNo() != 9 )){
//TBD					ChangeAnime( 9 , 0 ) ;
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
bool CWilProt::Action()
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
				else if( standard & COMMAND_FORWARD ){
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH_FOR );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
				}
			}
//			else if( standard & COMMAND_ATTACK_EX ){
//				ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
//			}

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
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH_FOR );
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
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH_FOR );
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
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH_FOR );
				}
				else{
					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
				}
			}
//			else if( standard & COMMAND_ATTACK_EX ){
//				if( standard & COMMAND_DOWN ){
//					ChangeState( ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX );
//				}
//				else if( standard & COMMAND_FORWARD ){
//					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_EX );
//				}
//				else{
//					ChangeState( ENUM_TESTCHAR_STATE_ATTACK_HIGH );
//				}
//			}

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
//			else if( standard & COMMAND_ATTACK_EX ){
//				ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX );
//			}

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
			if( m_Flame > 20 ){
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

			if( m_Flame > 20 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH_FOR:
			// キャンセル判定
			if( m_ActionSpec.CanCancel( m_Flame, m_HittedAttack ) ){
				if( special == 4 ){
					ChangeState( ENUM_TESTCHAR_STATE_SPECIAL_2 );
				}
			}
			if( m_Flame > 53 ){
				ChangeState( ENUM_TESTCHAR_STATE_NEUTRAL );
			}
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
//				else if( standard & COMMAND_ATTACK_EX ){
//					ChangeState( ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX );
//				}

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
			if( !(standard & COMMAND_FORWARD) ){
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
			m_Vector[0] += m_Spec.SPEED_DUSH_FORWARD * m_Dir;
			break;

		case ENUM_TESTCHAR_STATE_DUSH_BACK:
			m_Vector[0] -= m_Spec.SPEED_DUSH_BACK * m_Dir;
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
			if( m_Flame > 3 ){
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
void CWilProt::ChangeState( int state )
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
			ChangeAnime( DOT_WILL_ANIME_NUTRAL , 0 ) ;
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;
		
		case ENUM_TESTCHAR_STATE_WALK_FORWARD:
			ChangeAnime( DOT_WILL_ANIME_WALK_FORWARD , 0 ) ;
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_WALK_BACK:
			ChangeAnime( DOT_WILL_ANIME_WALK_BACK , 0 ) ;
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_LOW:
//	SBArr[ENUM_SE_BATTLE_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
//	SBArr[ENUM_SE_BATTLE_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
			m_Parameter.m_SpGauge+=10;
			ChangeAnime( DOT_WILL_ANIME_ATTACK_LOW , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 6, 6, 8 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_MID:
			m_Parameter.m_SpGauge+=20;
			ChangeAnime( DOT_WILL_ANIME_ATTACK_MID , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 6, 6, 0 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
			m_Parameter.m_SpGauge+=25;
			ChangeAnime( DOT_WILL_ANIME_ATTACK_HIGH , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 30, 30, 0 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_EX:
			m_Parameter.m_SpGauge+=25;
//			StartAir( (float)5 * m_Dir ,(float)1.0f, 0 );
			ChangeAnime( DOT_WILL_ANIME_ATTACK_EX , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 20, 20, 0 );
			break;

		case ENUM_TESTCHAR_STATE_ATTACK_HIGH_FOR:
			m_Parameter.m_SpGauge += 25;
			//			StartAir( (float)5 * m_Dir ,(float)1.0f, 0 );
			ChangeAnime(DOT_WILL_ANIME_ATTACK_HIGH_FOR, 0);
			m_EnableDir = FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec(false, 20, 20, 0);
			break;

		case ENUM_TESTCHAR_STATE_JUMP_SETUP:
			IncreaseJump();
			ChangeAnime( DOT_WILL_ANIME_JUMP , 0 ) ;
//			m_EnableDir		= FALSE;
			m_EnableDir		= TRUE;
			sub = before_sub;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_FORWARD:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_SETUP ){
                StartAir( (float)m_Spec.SPEED_JUMP_FORWARD * m_Dir , (float)m_Spec.SPEED_JUMP, 0 );
				ChangeAnime( DOT_WILL_ANIME_JUMP + 1 , 0 ) ;
			}
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_BACK:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_SETUP ){
                StartAir( -(float)m_Spec.SPEED_JUMP_BACK * m_Dir , (float)m_Spec.SPEED_JUMP, 0 );
				ChangeAnime( DOT_WILL_ANIME_BACK_JUMP  + 1 , 0 ) ;
			}
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_NORMAL:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_SETUP ){
                StartAir( 0.0f , (float)m_Spec.SPEED_JUMP, 0 );
				ChangeAnime( DOT_WILL_ANIME_JUMP + 1 , 0 ) ;
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
				ChangeAnime( DOT_WILL_ANIME_CROUCH, 3 );
			}
			else{
				ChangeAnime( DOT_WILL_ANIME_CROUCH , 0 ) ;
			}
			m_EnableDir		= TRUE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( true, 0, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW:
			ChangeAnime( DOT_WILL_ANIME_CROUCH_ATTACK_LOW , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID:
			ChangeAnime( DOT_WILL_ANIME_CROUCH_ATTACK_MID , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10, 10, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
//TBD			ChangeAnime( DOT_WILL_ANIME_CROUCH_ATTACK_HIGH , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 30, 30, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH_START:
//TBD			ChangeAnime( 67 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH_END:
//TBD			ChangeAnime( 68 , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
			ChangeAnime( DOT_WILL_ANIME_DUSH_FORWARD , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DUSH_BACK:
			ChangeAnime( DOT_WILL_ANIME_DUSH_BACK , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW:
			ChangeAnime( DOT_WILL_ANIME_JUMP_ATTACK_LOW , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID:
			ChangeAnime( DOT_WILL_ANIME_JUMP_ATTACK_MID , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
			ChangeAnime( DOT_WILL_ANIME_JUMP_ATTACK_HIGH , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX:
//TBD			ChangeAnime( 55, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX ;
			m_ActionSpec.SetSpec( false, 1, 1, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
			IncreaseJumpDush();
			ChangeAnime( DOT_WILL_ANIME_JUMP_DUSH_FORWARD , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK:
			IncreaseJumpDush();
			new(m_ResBattle->m_CommonEffectFront) CEffAction02( m_ResBattle, this );
			ChangeAnime( DOT_WILL_ANIME_JUMP_DUSH_BACK , 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DUSH_END:
			if( m_State == ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD ){
				StartAir( (float)m_Spec.SPEED_JUMP_FORWARD * m_Dir ,0.0f, 0 );
				ChangeAnime( DOT_WILL_ANIME_JUMP4 , 0 ) ;
				state = ENUM_TESTCHAR_STATE_JUMP_FORWARD;
			}
			else if( m_State == ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK ){
				StartAir( -((float)m_Spec.SPEED_JUMP_DUSH_BACK-2) * m_Dir ,0.0f, 0 );
				ChangeAnime( DOT_WILL_ANIME_BACK_JUMP+1 , 0 ) ;
				state = ENUM_TESTCHAR_STATE_JUMP_BACK;
			}

			//if( ( m_Vector[1] <= 1.0f ) &&
			//	( m_Vector[1] > 0.0f ) ){
			//	ChangeAnime( 8 , 0 ) ;
			//}
			//if( m_Vector[1] == 0.0f ){
			//	ChangeAnime( 9 , 0 ) ;
			//}
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );

			break;

		case ENUM_TESTCHAR_STATE_DAMAGE:
			ChangeAnime( DOT_WILL_ANIME_DAMAGE, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_DAMAGE:
//TBD			ChangeAnime( 19, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_AERIAL_DAMAGE:
			StartAir( 1.0f * -m_Dir, CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_VECTOR
						 , 0, (float)CHARACTER_COMMON_PARAMETER::AERIAL_DAMAGE_GRAVITY );
			ChangeAnime( DOT_WILL_ANIME_DAMAGE_AERIAL_DOWN, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_BIG_DAMAGE:
			StartAir( 7.0f * -m_Dir, 7.0f , 0, 0.3f );
//TBD			ChangeAnime( 56, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DOWN:
//TBD			ChangeAnime( 28, 0 ) ;
			m_EnableDir				= FALSE;
//			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_DOWN;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_GETUP:
//TBD			ChangeAnime( 36, 0 ) ;
			m_EnableDir				= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_DOWN;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_GUARD:
			ChangeAnime( DOT_WILL_ANIME_GUARD, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_CROUCH_GUARD:
//TBD			ChangeAnime( 32, 0 ) ;
			m_EnableDir				= FALSE;
			m_KnockBackVector[0]	= 5 * -m_Dir;
			sub = ENUM_TESTCHAR_SUB_STATE_CROUCH;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_DAMAGE:
			StartAir( 5.0f * -m_Dir, CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_VECTOR
						 , 0, (float)CHARACTER_COMMON_PARAMETER::AIR_DAMAGE_GRAVITY );
//TBD			ChangeAnime( 33, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_GUARD:
			StartAir( 5.0f * -m_Dir, CHARACTER_COMMON_PARAMETER::AIR_GUARD_VECTOR
						 , 0, (float)CHARACTER_COMMON_PARAMETER::AIR_GUARD_GRAVITY );
//TBD			ChangeAnime( 34, 0 ) ;
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
//TBD			ChangeAnime( 50, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_DAMAGE_THROW:
//TBD			ChangeAnime( 18, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_MISS_THROW:
//TBD			ChangeAnime( 53, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_1:
			ChangeAnime(DOT_WILL_ANIME_SPECIAL1, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_1_END:
//TBD			ChangeAnime( 61, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_2:
//TBD			ChangeAnime( 1, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_SPECIAL_3:
			StartAir( 1.0f * -m_Dir * -1 , 20.0f , 0, 0.5f );
//TBD			ChangeAnime( 65, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_STAND;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_BLOW_DOWN:
			ChangeAnime( DOT_WILL_ANIME_DAMAGE_BLOW_DOWN, 0 );
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND:
			StartAir( 7.0f * -m_Dir, 7.0f , 0, 0.3f );
			ChangeAnime( DOT_WILL_ANIME_DAMAGE_WALL, 0 ) ;
			m_EnableDir		= FALSE;
			sub = ENUM_TESTCHAR_SUB_STATE_JUMP;
			m_ActionSpec.SetSpec( false, 10000, 0, 0 );
			break;

		case ENUM_TESTCHAR_STATE_JUMP_RECOVER:
			StartAir( 2.0f * -m_Dir, 7.0f , 0, 0.3f );
//TBD			ChangeAnime( 42, 0 ) ;
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

// ジャンプ着地
void CWilProt::EndAir()
{
	ClearJump();
	ClearJumpDush();
	m_AirVector[0]	= 0;
	m_AirVector[1]	= 0;
}

// 空中動作
void CWilProt::DoAir()
{
	m_AirTime++ ;
	m_Y = m_AirBase[1] - ( m_AirVector[1] * m_AirTime - ( m_AirGravity * ( m_AirTime * m_AirTime) ) );// m_Vector[ENUM_VECTOR_UP];
	m_AirIncrease = m_AirVector[1] - m_AirGravity * 2 * m_AirTime;
	m_Vector[0] += m_AirVector[0];
}

// 攻撃を喰らったの処理
// 防御・ヒット等の判定を行う
// さらに状態変化
int CWilProt::ReceiveAttack( CSprite* target, CAnime* anime )
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
void CWilProt::HitAttack()
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

