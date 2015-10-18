#include "UTL_SoundManager.h"
#include "ShanaProt.h"
#include "DsoundMain.h"

void CSoundManager::Play( int status, int flame )
{
	switch(status){

	//�K�[�h
	case ENUM_TESTCHAR_STATE_GUARD:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_GUARD].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_GUARD].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_GUARD].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�_�E��
	case ENUM_TESTCHAR_STATE_DOWN:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_DOWN].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_DOWN].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_DOWN].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�n��_�b�V��
	case ENUM_TESTCHAR_STATE_DUSH_FORWARD:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_FORWARD].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_FORWARD].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_FORWARD].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�n��o�b�N�_�b�V��
	case ENUM_TESTCHAR_STATE_DUSH_BACK:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_BACK].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_BACK].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_DUSH_BACK].SB_lpDSB->Play(0,0,0);
		}
		break;
	//������U��
	case ENUM_TESTCHAR_STATE_ATTACK_LOW:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_LOW].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
		}
		break;

	//�������U��
	case ENUM_TESTCHAR_STATE_ATTACK_MID:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_MID].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_MID].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_MID].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�������U��
	case ENUM_TESTCHAR_STATE_ATTACK_HIGH:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_HIGH].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_HIGH].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_HIGH].SB_lpDSB->Play(0,0,0);
		}
		break;
	//��������U��
	case ENUM_TESTCHAR_STATE_ATTACK_EX:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_EX].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_EX].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_ATTACK_EX].SB_lpDSB->Play(0,0,0);
		}
		break;
	//���Ⴊ�ݎ�U��
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
		}
		break;
	//���Ⴊ�ݒ��U��
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_MID].SB_lpDSB->Play(0,0,0);
		}
		break;
	//���Ⴊ�݋��U��
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_HIGH].SB_lpDSB->Play(0,0,0);
		}
		break;
	//���Ⴊ�ݓ���U��
	case ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_CROUCH_ATTACK_EX].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�W�����v��U��
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_LOW].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�W�����v���U��
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_MID].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�W�����v���U��
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_HIGH].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�W�����v����U��
	case ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_ATTACK_EX].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�K�E�Z�P
	case ENUM_TESTCHAR_STATE_SPECIAL_1:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_1].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_1].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_1].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�K�E�Z�Q
	case ENUM_TESTCHAR_STATE_SPECIAL_2:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_2].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_2].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_SPECIAL_2].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�K�E�Z�R
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
	//�󒆃_�b�V��
	case ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_FORWARD].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�󒆃o�b�N�_�b�V��
	case ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_DUSH_BACK].SB_lpDSB->Play(0,0,0);
		}
		break;
	//�ǌ���
	case ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND:
		if( flame == 0 ){
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND].SB_lpDSB->Stop();
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND].SB_lpDSB->SetCurrentPosition(0);
			SBArr[_ENUM_TESTCHAR_STATE_JUMP_WALL_BOUND].SB_lpDSB->Play(0,0,0);
		}
		break;
	}

}

