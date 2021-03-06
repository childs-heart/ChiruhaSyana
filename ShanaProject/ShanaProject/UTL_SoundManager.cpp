#include "UTL_SoundManager.h"
#include "ShanaProt.h"
#include "DsoundMain.h"

void CSoundManager::Play( int status, int flame )
{
	switch(status){

	//ガード
	case ENUM_TESTCHAR_STATE_GUARD:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_GUARD].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_GUARD].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_GUARD].SB_lpDSB->Play(0,0,0);
		}
		break;
	//ダウン
	case ENUM_TESTCHAR_STATE_DOWN:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_DOWN].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_DOWN].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_DOWN].SB_lpDSB->Play(0,0,0);
		}
		break;
	//地上ダッシュ
	case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_FORWARD].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_FORWARD].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_FORWARD].SB_lpDSB->Play(0,0,0);
		}
		break;
	//地上バックダッシュ
	case ENUM_TESTCHAR_STATE_DUSH_BACK:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_BACK].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_BACK].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_BACK].SB_lpDSB->Play(0,0,0);
		}
		break;
	//立ち弱攻撃
	case ENUM_TESTCHAR_STATE_ATTACK_LOW:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_LOW].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
		}
		break;

	//立ち中攻撃
	case ENUM_TESTCHAR_STATE_ATTACK_MID:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_MID].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_MID].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_MID].SB_lpDSB->Play(0,0,0);
		}
		break;
	//立ち強攻撃
	case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_HIGH].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_HIGH].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_HIGH].SB_lpDSB->Play(0,0,0);
		}
		break;
	//立ち特殊攻撃
	case ENUM_TESTCHAR_STATE_ATTACK_EX:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_EX].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_EX].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_EX].SB_lpDSB->Play(0,0,0);
		}
		break;
	//しゃがみ弱攻撃
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
		}
		break;
	//しゃがみ中攻撃
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID].SB_lpDSB->Play(0,0,0);
		}
		break;
	//しゃがみ強攻撃
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH].SB_lpDSB->Play(0,0,0);
		}
		break;
	//しゃがみ特殊攻撃
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX].SB_lpDSB->Play(0,0,0);
		}
		break;
	//ジャンプ弱攻撃
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
		}
		break;
	//ジャンプ中攻撃
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID].SB_lpDSB->Play(0,0,0);
		}
		break;
	//ジャンプ強攻撃
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH].SB_lpDSB->Play(0,0,0);
		}
		break;
	//ジャンプ特殊攻撃
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX].SB_lpDSB->Play(0,0,0);
		}
		break;
	//必殺技１
	case ENUM_TESTCHAR_STATE_SPECIAL_1:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_1].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_1].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_1].SB_lpDSB->Play(0,0,0);
		}
		break;
	//必殺技２
	case ENUM_TESTCHAR_STATE_SPECIAL_2:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_2].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_2].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_2].SB_lpDSB->Play(0,0,0);
		}
		break;
	//必殺技３
	case ENUM_TESTCHAR_STATE_SPECIAL_3:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_3_1].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_3_1].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_3_2].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_3_2].SB_lpDSB->SetCurrentPosition(0);

			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_3_1].SB_lpDSB->Play(0,0,0);
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_3_2].SB_lpDSB->Play(0,0,0);
		}
		break;
	//空中ダッシュ
	case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD].SB_lpDSB->Play(0,0,0);
		}
		break;
	//空中バックダッシュ
	case ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK].SB_lpDSB->Play(0,0,0);
		}
		break;
	//壁激突
	case ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND].SB_lpDSB->Play(0,0,0);
		}
		break;
	}

}

