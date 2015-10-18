// Input�֌W
#include "stdafx.h"
#include "CLIB_Input.h"
#include <dinput.h>		//�C���v�b�g�p

#ifdef CONFIG_TOOL

#pragma comment( lib, "dinput.lib" )
#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

#endif

   #define KEYDOWN(name, key) (name[key] & 0x80) 

//-----------------------------------------------------------------------------------------
// DirectInput�@�ڑ��p�b�h�������߂�
//-----------------------------------------------------------------------------------------
BOOL CALLBACK EnumNumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext)
{
	(*(int*)pContext)++;
	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------------------
// DirectInput�@�p�b�h��F������
//-----------------------------------------------------------------------------------------
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,VOID* pContext)
{
	HRESULT result;
	CInput	*tmp;
	static	int num = 0;

	tmp = (CInput *)pContext;

	if FAILED( result = tmp->m_DI->CreateDevice(pdidInstance->guidInstance,
												&tmp->m_DIPadDevice[num], NULL) )
		return DIENUM_STOP;

	num++;
	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------------------
// DirectInput�@�F�������p�b�h���g����悤�ɂ���
//-----------------------------------------------------------------------------------------
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi,LPVOID pvRef)
{
	HRESULT hr;
	DIPROPRANGE diprg;
	LPDIRECTINPUTDEVICE8 didev;

	didev = (LPDIRECTINPUTDEVICE8)pvRef;

	diprg.diph.dwSize		= sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow		= DIPH_BYID;
	diprg.diph.dwObj		= lpddoi->dwType;
	diprg.lMin				= -DINPUT_RANGE_MAX;			//DInputMax * -1
	diprg.lMax				= DINPUT_RANGE_MAX;
	hr = didev->SetProperty( DIPROP_RANGE, &diprg.diph );
	if FAILED( hr )
		return DIENUM_STOP;
	return DIENUM_CONTINUE;
}

//-----------------------------------------------------------------------------------------
// DirectInput�p�b�h�f�o�C�X�쐬
//-----------------------------------------------------------------------------------------
HRESULT CInput::DISetJoystick( HWND win_hwnd )
{
	HRESULT hr;
	DIDEVCAPS dindcaps;
	DIPROPDWORD diprop;

	int i;

// �ڑ��p�b�h���擾
	hr = m_DI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumNumJoysticksCallback, &m_UsePad, DIEDFL_ATTACHEDONLY);
	if FAILED( hr)
		return hr;

// �ڑ��p�b�h���ɉ����ăf�o�C�X�쐬
	if( m_UsePad != 0 ){
		if( m_DIPadDevice != NULL )
		{
			LPDIRECTINPUTDEVICE8 pDevice = *m_DIPadDevice;
			if( pDevice )
			{
				delete pDevice;
				pDevice = NULL;
			}
			delete m_DIPadDevice;
			m_DIPadDevice = NULL;
		}

		m_DIPadDevice = new LPDIRECTINPUTDEVICE8[m_UsePad];
		m_DIJoyPad = new DIJOYSTATE2[m_UsePad];
		for( int i=0 ; i<m_UsePad ; i++ )
		{
			m_DIPadDevice[i] = NULL;
		}
	}

	// �ڑ��p�b�h�擾
	i = 0 ;
	hr = m_DI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, this, DIEDFL_ATTACHEDONLY);
	if FAILED( hr )
		return hr;

	for ( i = 0 ; i < m_UsePad ; i++ ){
		if ( m_DIPadDevice[i]==NULL )
			return hr;

		hr = m_DIPadDevice[i]->SetDataFormat( &c_dfDIJoystick2 );
		if FAILED( hr )
			return hr;

		//�p�b�h�̋������[�h
		//�r���I�ɂ���Ƃ��@�@����r���ŁA�o�b�O�O���E���h�ł�����
		hr = m_DIPadDevice[i]->SetCooperativeLevel( win_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND );
		if FAILED( hr )
			return hr;

		dindcaps.dwSize=sizeof( DIDEVCAPS );
		hr = m_DIPadDevice[i]->GetCapabilities( &dindcaps );
		if FAILED( hr )
			return hr;

		diprop.diph.dwSize		 = sizeof(DIPROPDWORD);
		diprop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprop.diph.dwObj		 = 0;
		diprop.diph.dwHow		 = DIPH_DEVICE;
		diprop.dwData			 = DIPROPAXISMODE_ABS;

		hr = m_DIPadDevice[i]->SetProperty( DIPROP_AXISMODE, &diprop.diph );
		if FAILED( hr )
			return hr;

		hr = m_DIPadDevice[i]->EnumObjects( EnumAxesCallback, m_DIPadDevice[i], DIDFT_AXIS);
		if FAILED( hr )
			return hr;

/*		hr = lpDIPadDevice[i]->SetProperty( DIPROP_BUFFERSIZE, &diprop.diph ) ;
		diprop.dwData=0;
		if FAILED( hr )
			return hr;
*/
	}
	//�p�b�h�g�p�J�n
	for ( i = 0 ; i < m_UsePad ; i++ ){
		hr = m_DIPadDevice[i]->Acquire() ;
			if FAILED( hr )
			return hr;
	}

	return hr;
}

//-----------------------------------------------------------------------------------------
// DirectInput �L�[�{�[�h�@���͒��̃{�^���擾
//-----------------------------------------------------------------------------------------
void CInput::UpDateState_Key( )
{
	if(m_DIkeyDevice!=NULL)
		m_DIkeyDevice->GetDeviceState( sizeof(m_KeyData), (LPVOID)&m_KeyData );
}

//-----------------------------------------------------------------------------------------
// DirectInput �p�b�h�@�{�^�����͎擾�P�@�ύX�\��
//-----------------------------------------------------------------------------------------
void CInput::UpDateState_Pad( )
{
	int i;
	HRESULT  hr; 

	// �p�b�h����
	if( m_DIPadDevice != NULL ){
		for ( i = 0 ; i < m_UsePad ; i++ ){
			if( m_DIPadDevice[i] != NULL ){
				m_DIPadDevice[i]->Poll();
				m_DIPadDevice[i]->GetDeviceState( sizeof(DIJOYSTATE2), &m_DIJoyPad[i]);
			}
		}
		Convert();
	}
}

void CInput::Convert()
{
	int i;
	for( i = 0 ; i<m_Player ;i++ ){
		if( i < m_UsePad ){
			m_PadData[i].m_Right= PADRIGHT( m_DIJoyPad[i].lX );
			m_PadData[i].m_Left	= PADLEFT( m_DIJoyPad[i].lX );
			m_PadData[i].m_Up	= PADUP( m_DIJoyPad[i].lY );
			m_PadData[i].m_Down	= PADDOWN( m_DIJoyPad[i].lY );
			memcpy( m_PadData[i].m_Buttom, m_DIJoyPad[i].rgbButtons,
									sizeof( m_PadData[i].m_Buttom ) );
		}
		else{
			memset( &m_PadData[i], 0 , sizeof( m_PadData[i] )-4 );
		}
	}
}

//-----------------------------------------------------------------------------------------
// DirectInput ���͒��̃{�^���i�L�[�{�[�h�ƃp�b�h�j�擾
//-----------------------------------------------------------------------------------------
void CInput::UpDateState( )
{
	UpDateState_Key();
	UpDateState_Pad();

	MergeConfig();
}


unsigned long CInput::IsRight( char num )
{
	return m_PadData[num].m_Right;
}

unsigned long CInput::IsLeft( char num )
{
	return m_PadData[num].m_Left;
}

unsigned long CInput::IsUp( char num )
{
	return m_PadData[num].m_Up;
}

unsigned long CInput::IsDown( char num )
{
	return m_PadData[num].m_Down;
}

unsigned long CInput::IsButtom( char num, char buttom )
{
	return m_PadData[num].m_Buttom[buttom];
}

void CInput::SetConfigData( int player, unsigned long *data )
{
	// �R���t�B�O�f�[�^�ϊ�
	// ����
	for( int i = 0 ; i < 4 ; i++ ){
		if( data[i] == 0xFFFFFFFF ){
			m_ConfigData[player].m_PadNo[i] = player;
			m_ConfigData[player].m_Data[i] = 1 << i ;
		}
		else{
			m_ConfigData[player].m_PadNo[i] = ( data[i] % 0x1000 ) / 0x100;
			m_ConfigData[player].m_Data[i] = data[i] % 0x100 ;
		}
	}
	// �{�^��
	for( int i = 4 ; i < 11 ; i++ ){
		if( data[i] == 0xFFFFFFFF ){
			m_ConfigData[player].m_PadNo[i] = player;
			m_ConfigData[player].m_Data[i] = i ;
		}
		else{
			m_ConfigData[player].m_PadNo[i] = ( data[i] % 0x1000 ) / 0x100;
			m_ConfigData[player].m_Data[i] = data[i] % 0x100 ;
		}
	}
//	memcpy( m_ConfigData, data, sizeof( StConfigData ) * num );
}


void CInput::Merge()
{
	unsigned long back ;
	int i;

	// �p�b�h�f�[�^
	for( i = 0 ; i < m_Player ; i++ ){
		back = m_PadData[i].m_MergeData;
		m_PadData[i].m_MergeData = 0;

		if( PADPUT( m_PadData[i].m_Buttom[0] )){
			if( back & PAD_BUTTON1 )
				m_PadData[i].m_MergeData |= PAD_BUTTON1;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON1_ON;
		}

		if( PADPUT( m_PadData[i].m_Buttom[1] )){
			if( back & PAD_BUTTON2 )
				m_PadData[i].m_MergeData |= PAD_BUTTON2;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON2_ON;
		}

		if( PADPUT( m_PadData[i].m_Buttom[2] )){
			if( back & PAD_BUTTON3 )
				m_PadData[i].m_MergeData |= PAD_BUTTON3;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON3_ON;
		}

		if( PADPUT( m_PadData[i].m_Buttom[3] )){
			if( back & PAD_BUTTON4 )
				m_PadData[i].m_MergeData |= PAD_BUTTON4;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON4_ON;
		}

		if( PADPUT( m_PadData[i].m_Buttom[4] )){
			if( back & PAD_BUTTON5 )
				m_PadData[i].m_MergeData |= PAD_BUTTON5;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON5_ON;
		}

		if( PADPUT( m_PadData[i].m_Buttom[5] )){
			if( back & PAD_BUTTON6 )
				m_PadData[i].m_MergeData |= PAD_BUTTON6;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON6_ON;
		}

		if( PADPUT( m_PadData[i].m_Buttom[6] )){
			if( back & PAD_BUTTON7 )
				m_PadData[i].m_MergeData |= PAD_BUTTON7;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON7_ON;
		}

		if( PADPUT( m_PadData[i].m_Buttom[7] )){
			if( back & PAD_BUTTON8 )
				m_PadData[i].m_MergeData |= PAD_BUTTON8;
			else
				m_PadData[i].m_MergeData |= PAD_BUTTON8_ON;
		}

	/*
		if( PADPUT(0,8)	){
			mPadData[0] |= PAD_BUTTON9;
		}
		if( PADPUT(0,9)	){
			mPadData[0] |= PAD_BUTTON10;
		}
		if( PADPUT(0,10) ){
			mPadData[0] |= PAD_BUTTON11;
		}
		if( PADPUT(0,11) ){
			mPadData[0] |= PAD_BUTTON12;
		}
	*/
		if( m_PadData[i].m_Up ){
			if( back & PAD_UP )
				m_PadData[i].m_MergeData |= PAD_UP;
			else
				m_PadData[i].m_MergeData |= PAD_UP_ON;
		}

		if( m_PadData[i].m_Down ){
			if( back & PAD_DOWN )
				m_PadData[i].m_MergeData |= PAD_DOWN;
			else
				m_PadData[i].m_MergeData |= PAD_DOWN_ON;
		}

		if( m_PadData[i].m_Left ){
			if( back & PAD_LEFT )
				m_PadData[i].m_MergeData |= PAD_LEFT;
			else
				m_PadData[i].m_MergeData |= PAD_LEFT_ON;
		}

		if( m_PadData[i].m_Right ){
			if( back & PAD_RIGHT )
				m_PadData[i].m_MergeData |= PAD_RIGHT;
			else
				m_PadData[i].m_MergeData |= PAD_RIGHT_ON;
		}
	}

	// �L�[����
	int k = 1;
	back = m_PadData[k].m_MergeData;
	m_PadData[k].m_MergeData = 0;
	if( KEYDOWN( m_KeyData, DIK_UP ) ){
		if( back & PAD_UP )
			m_PadData[k].m_MergeData |= PAD_UP;
		else
			m_PadData[k].m_MergeData |= PAD_UP_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_DOWN ) ){
		if( back & PAD_DOWN )
			m_PadData[k].m_MergeData |= PAD_DOWN;
		else
			m_PadData[k].m_MergeData |= PAD_DOWN_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_LEFT ) ){
		if( back & PAD_LEFT )
			m_PadData[k].m_MergeData |= PAD_LEFT;
		else
			m_PadData[k].m_MergeData |= PAD_LEFT_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_RIGHT ) ){
		if( back & PAD_RIGHT )
			m_PadData[k].m_MergeData |= PAD_RIGHT;
		else
			m_PadData[k].m_MergeData |= PAD_RIGHT_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_A )){
		if( back & PAD_BUTTON1 )
			m_PadData[k].m_MergeData |= PAD_BUTTON1;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON1_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_S )){
		if( back & PAD_BUTTON2 )
			m_PadData[k].m_MergeData |= PAD_BUTTON2;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON2_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_D )){
		if( back & PAD_BUTTON3 )
			m_PadData[k].m_MergeData |= PAD_BUTTON3;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON3_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_F )){
		if( back & PAD_BUTTON4 )
			m_PadData[k].m_MergeData |= PAD_BUTTON4;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON4_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_Z )){
		if( back & PAD_BUTTON5 )
			m_PadData[k].m_MergeData |= PAD_BUTTON5;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON5_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_X )){
		if( back & PAD_BUTTON6 )
			m_PadData[k].m_MergeData |= PAD_BUTTON6;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON6_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_C )){
		if( back & PAD_BUTTON7 )
			m_PadData[k].m_MergeData |= PAD_BUTTON7;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON7_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_V )){
		if( back & PAD_BUTTON8 )
			m_PadData[k].m_MergeData |= PAD_BUTTON8;
		else
			m_PadData[k].m_MergeData |= PAD_BUTTON8_ON;
	}

}


void CInput::MergeConfig()
{
	unsigned long back,key_back ;
	unsigned long dir[2];
	int i;

	// �����L�[�ϊ�
	for( i = 0 ; i < m_Player ; i++ ){
		dir[i] = 0;
		if( m_PadData[i].m_Up ){
			dir[i]|=1;
		}
		if( m_PadData[i].m_Down ){
			dir[i]|=2;
		}
		if( m_PadData[i].m_Left ){
			dir[i]|=8;
		}
		if( m_PadData[i].m_Right ){
			dir[i]|=4;
		}
	}

	// �p�b�h�f�[�^
	key_back = m_PadData[1].m_MergeData;
	for( i = 0 ; i < m_Player ; i++ ){
		back = m_PadData[i].m_MergeData;
		m_PadData[i].m_MergeData = 0;

		if( m_ConfigData[i].m_PadNo[4] < m_UsePad ){
			if( PADPUT( m_PadData[m_ConfigData[i].m_PadNo[4]].m_Buttom[m_ConfigData[i].m_Data[4]] )){
				if( back & PAD_BUTTON1 )
					m_PadData[i].m_MergeData |= PAD_BUTTON1;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON1_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[5] < m_UsePad ){
			if( PADPUT( m_PadData[m_ConfigData[i].m_PadNo[5]].m_Buttom[m_ConfigData[i].m_Data[5]] )){
				if( back & PAD_BUTTON2 )
					m_PadData[i].m_MergeData |= PAD_BUTTON2;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON2_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[6] < m_UsePad ){
			if( PADPUT( m_PadData[m_ConfigData[i].m_PadNo[6]].m_Buttom[m_ConfigData[i].m_Data[6]] )){
				if( back & PAD_BUTTON3 )
					m_PadData[i].m_MergeData |= PAD_BUTTON3;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON3_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[7] < m_UsePad ){
			if( PADPUT( m_PadData[m_ConfigData[i].m_PadNo[7]].m_Buttom[m_ConfigData[i].m_Data[7]] )){
				if( back & PAD_BUTTON4 )
					m_PadData[i].m_MergeData |= PAD_BUTTON4;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON4_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[8] < m_UsePad ){
			if( PADPUT( m_PadData[m_ConfigData[i].m_PadNo[8]].m_Buttom[m_ConfigData[i].m_Data[8]] )){
				if( back & PAD_BUTTON5 )
					m_PadData[i].m_MergeData |= PAD_BUTTON5;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON5_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[9] < m_UsePad ){
			if( PADPUT( m_PadData[m_ConfigData[i].m_PadNo[9]].m_Buttom[m_ConfigData[i].m_Data[9]] )){
				if( back & PAD_BUTTON1 )
					m_PadData[i].m_MergeData |= PAD_BUTTON1;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON1_ON;

				if( back & PAD_BUTTON2 )
					m_PadData[i].m_MergeData |= PAD_BUTTON2;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON2_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[10] < m_UsePad ){
			if( PADPUT( m_PadData[m_ConfigData[i].m_PadNo[10]].m_Buttom[m_ConfigData[i].m_Data[10]] )){
//			if( PADPUT( m_PadData[i].m_Buttom[7] )){
				if( back & PAD_BUTTON3 )
					m_PadData[i].m_MergeData |= PAD_BUTTON3;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON3_ON;

				if( back & PAD_BUTTON4 )
					m_PadData[i].m_MergeData |= PAD_BUTTON4;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON4_ON;
			}
		}

		if( i < m_UsePad ){
//			if( PADPUT( m_PadData[padNo[i][11]].m_Buttom[m_ConfigData[i].m_Button[7] % 0x100 ] )){
			if( PADPUT( m_PadData[i].m_Buttom[6] )){
				if( back & PAD_BUTTON8 )
					m_PadData[i].m_MergeData |= PAD_BUTTON8;
				else
					m_PadData[i].m_MergeData |= PAD_BUTTON8_ON;
			}
		}

	/*
		if( PADPUT(0,8)	){
			mPadData[0] |= PAD_BUTTON9;
		}
		if( PADPUT(0,9)	){
			mPadData[0] |= PAD_BUTTON10;
		}
		if( PADPUT(0,10) ){
			mPadData[0] |= PAD_BUTTON11;
		}
		if( PADPUT(0,11) ){
			mPadData[0] |= PAD_BUTTON12;
		}
	*/
		if( m_ConfigData[i].m_PadNo[0] < m_UsePad ){
			if( dir[m_ConfigData[i].m_PadNo[0]] & m_ConfigData[i].m_Data[0]){
				if( back & PAD_UP )
					m_PadData[i].m_MergeData |= PAD_UP;
				else
					m_PadData[i].m_MergeData |= PAD_UP_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[1] < m_UsePad ){
			if( dir[m_ConfigData[i].m_PadNo[1]] & m_ConfigData[i].m_Data[1]){
				if( back & PAD_DOWN )
					m_PadData[i].m_MergeData |= PAD_DOWN;
				else
					m_PadData[i].m_MergeData |= PAD_DOWN_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[2] < m_UsePad ){
			if( dir[m_ConfigData[i].m_PadNo[2]] & m_ConfigData[i].m_Data[2]){
				if( back & PAD_LEFT )
					m_PadData[i].m_MergeData |= PAD_LEFT;
				else
					m_PadData[i].m_MergeData |= PAD_LEFT_ON;
			}
		}

		if( m_ConfigData[i].m_PadNo[3] < m_UsePad ){
			if( dir[m_ConfigData[i].m_PadNo[3]] & m_ConfigData[i].m_Data[3]){
				if( back & PAD_RIGHT )
					m_PadData[i].m_MergeData |= PAD_RIGHT;
				else
					m_PadData[i].m_MergeData |= PAD_RIGHT_ON;
			}
		}
	}

	// �L�[����
	back = key_back ;
//	m_PadData[1].m_MergeData = 0;
	if( KEYDOWN( m_KeyData, DIK_UP ) ){
		if( back & PAD_UP )
			m_PadData[1].m_MergeData |= PAD_UP;
		else
			m_PadData[1].m_MergeData |= PAD_UP_ON;
	}

	else if( KEYDOWN( m_KeyData, DIK_DOWN ) ){
		if( back & PAD_DOWN )
			m_PadData[1].m_MergeData |= PAD_DOWN;
		else
			m_PadData[1].m_MergeData |= PAD_DOWN_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_LEFT ) ){
		if( back & PAD_LEFT )
			m_PadData[1].m_MergeData |= PAD_LEFT;
		else
			m_PadData[1].m_MergeData |= PAD_LEFT_ON;
	}

	else if( KEYDOWN( m_KeyData, DIK_RIGHT ) ){
		if( back & PAD_RIGHT )
			m_PadData[1].m_MergeData |= PAD_RIGHT;
		else
			m_PadData[1].m_MergeData |= PAD_RIGHT_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_A )){
		if( back & PAD_BUTTON1 )
			m_PadData[1].m_MergeData |= PAD_BUTTON1;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON1_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_S )){
		if( back & PAD_BUTTON2 )
			m_PadData[1].m_MergeData |= PAD_BUTTON2;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON2_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_D )){
		if( back & PAD_BUTTON3 )
			m_PadData[1].m_MergeData |= PAD_BUTTON3;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON3_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_F )){
		if( back & PAD_BUTTON4 )
			m_PadData[1].m_MergeData |= PAD_BUTTON4;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON4_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_Z )){
		if( back & PAD_BUTTON5 )
			m_PadData[1].m_MergeData |= PAD_BUTTON5;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON5_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_X )){
		if( back & PAD_BUTTON6 )
			m_PadData[1].m_MergeData |= PAD_BUTTON6;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON6_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_C )){
		if( back & PAD_BUTTON7 )
			m_PadData[1].m_MergeData |= PAD_BUTTON7;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON7_ON;
	}

	if( KEYDOWN( m_KeyData, DIK_V )){
		if( back & PAD_BUTTON8 )
			m_PadData[1].m_MergeData |= PAD_BUTTON8;
		else
			m_PadData[1].m_MergeData |= PAD_BUTTON8_ON;
	}

}

unsigned long CInput::GetPadData( int player )
{
	return m_PadData[player].m_MergeData ;
}

void CInput::SetPadData( int player, unsigned long pad_data )
{
	m_PadData[player].m_MergeData = pad_data ;
}

//-----------------------------------------------------------------------------------------
// DirectInput����@�f�X�g���N�^
//-----------------------------------------------------------------------------------------
CInput::~CInput(){

	int		i;

    if (m_DI)
    {
		for ( i = 0 ; i < m_UsePad ; i++ ){
			if(m_DIPadDevice[i] != NULL){
				m_DIPadDevice[i]->Unacquire();
				RELEASE(m_DIPadDevice[i]);
			}
		}

        if (m_DIkeyDevice)
        {
        // Release() ���Ăяo���O�͏�Ƀf�o�C�X���������B
            m_DIkeyDevice->Unacquire();
			RELEASE(m_DIkeyDevice);	
		}
     RELEASE(m_DI);
    }
	
	if( m_DIPadDevice != NULL )
	{
		LPDIRECTINPUTDEVICE8 pDevice = *m_DIPadDevice;
		if( pDevice )
		{
			delete pDevice;
			pDevice = NULL;
		}
		delete m_DIPadDevice;
		m_DIPadDevice = NULL;
	}

	if( m_PadData )
	{
		delete m_PadData;
		m_PadData = NULL;
	}

	if( m_DIJoyPad )
	{
		delete m_DIJoyPad;
		m_DIJoyPad = NULL;
	}
}

//-----------------------------------------------------------------------------------------
// DirectInput�f�o�C�X(�L�[�{�[�h)������
//-----------------------------------------------------------------------------------------
CInput::CInput( HINSTANCE hinst, HWND win_hwnd, int player ){

	// ������
	m_UsePad = 0;
	m_PadData = NULL;
	m_Player = player;

	m_DIPadDevice = 0;
	m_DIJoyPad = 0;

	//DirectInput�f�o�C�X�쐬
	HRESULT hr;
	hr = DirectInput8Create( hinst, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&m_DI, NULL);

	if FAILED(hr){
		MessageBox(NULL,"DirectInput�f�o�C�X�̍쐬�Ɏ��s���܂����B","DirectInput",MB_OK | MB_ICONSTOP);
		return;
	}

	// DirectInput�p�b�h�f�o�C�X�쐬
	hr = DISetJoystick( win_hwnd );

	if FAILED(hr){
		DI_Term();		//DirectInput�f�o�C�X�I���֐�
		return;
	}

	hr = m_DI->CreateDevice(GUID_SysKeyboard,&m_DIkeyDevice,NULL);
	if FAILED(hr){
		DI_Term();		//DirectInput�f�o�C�X�I���֐�
		return;
	}


    // IDirectInputDevice8 �C���^�[�t�F�C�X��ێ����āA
    // �g�p�������������Ƃ���ł���B

    // �L�[�{�[�h�p DirectInput �I�u�W�F�N�g�����A���O��`���ꂽ
    // �L�[�{�[�h �f�[�^�`����p���āA�f�[�^�`����ݒ肷��B


	hr = m_DIkeyDevice->SetDataFormat(&c_dfDIKeyboard);

	if FAILED(hr) {
			DI_Term();
			return;
	}


	// �������x����ݒ肷��B
	hr = m_DIkeyDevice->SetCooperativeLevel(win_hwnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	hr = m_DIkeyDevice->SetCooperativeLevel(win_hwnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	if FAILED(hr){
			DI_Term();
			return;
	}

/*************************************************************/
// 2003/12/08 t.shimizu�@�ǉ��@�v���C���[���ɉ�����PadData�쐬
/*************************************************************/
	if( m_PadData )
	{
		delete m_PadData;
		m_PadData = NULL;
	}

	m_PadData = new StPadData[player];
	for( int i = 0 ; i < player ; i++ ){
		memset( &m_PadData[i], 0, sizeof(m_PadData[i]) );
	}

	if (m_DIkeyDevice) m_DIkeyDevice->Acquire();	//�L�[�{�[�h�ɋ��\��
	
	return;

}

//-----------------------------------------------------------------------------------------
// DirectInput���
//-----------------------------------------------------------------------------------------
void WINAPI CInput::DI_Term(){

	int		i;

    if (m_DI)
    {
		for ( i = 0 ; i < m_UsePad ; i++ ){
			if(m_DIPadDevice[i] != NULL){
				m_DIPadDevice[i]->Unacquire();
				RELEASE(m_DIPadDevice[i]);
			}
		}

        if (m_DIkeyDevice)
        {
        // Release() ���Ăяo���O�͏�Ƀf�o�C�X���������B
            m_DIkeyDevice->Unacquire();
			RELEASE(m_DIkeyDevice);	
		}
     RELEASE(m_DI);
    }

	if( m_DIPadDevice != NULL )
	{
		LPDIRECTINPUTDEVICE8 pDevice = *m_DIPadDevice;
		if( pDevice )
		{
			delete pDevice ;
			pDevice = NULL;
		}
	}

	if( m_PadData )
	{
		delete m_PadData ;
		m_PadData = NULL;
	}

//	DELETE(lpDIPadDevice);
}

//-----------------------------------------------------------------------------------------
// DirectInput�f�o�C�X(�L�[�{�[�h)������
//-----------------------------------------------------------------------------------------
bool CInput::DIinit( HINSTANCE hinst, HWND win_hwnd, int player ){

	// ������
	m_UsePad = 0;

	//DirectInput�f�o�C�X�쐬
	HRESULT hr;
	hr = DirectInput8Create( hinst, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&m_DI, NULL);

	if FAILED(hr){
		MessageBox(NULL,"DirectInput�f�o�C�X�̍쐬�Ɏ��s���܂����B","DirectInput",MB_OK | MB_ICONSTOP);
		return false;
	}

	// DirectInput�p�b�h�f�o�C�X�쐬
	hr = DISetJoystick( win_hwnd );

	if FAILED(hr){
		DI_Term();		//DirectInput�f�o�C�X�I���֐�
		return false;
	}

	hr = m_DI->CreateDevice(GUID_SysKeyboard,&m_DIkeyDevice,NULL);
	if FAILED(hr){
		DI_Term();		//DirectInput�f�o�C�X�I���֐�
		return false;
	}


    // IDirectInputDevice8 �C���^�[�t�F�C�X��ێ����āA
    // �g�p�������������Ƃ���ł���B

    // �L�[�{�[�h�p DirectInput �I�u�W�F�N�g�����A���O��`���ꂽ
    // �L�[�{�[�h �f�[�^�`����p���āA�f�[�^�`����ݒ肷��B


	hr = m_DIkeyDevice->SetDataFormat(&c_dfDIKeyboard);

	if FAILED(hr) {
			DI_Term();
			return false;
	}


	// �������x����ݒ肷��B
	hr = m_DIkeyDevice->SetCooperativeLevel(win_hwnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	if FAILED(hr){
			DI_Term();
			return false;
	}

/*************************************************************/
// 2003/12/08 t.shimizu�@�ǉ��@�v���C���[���ɉ�����PadData�쐬
/*************************************************************/
	if( m_PadData )
	{
		delete m_PadData;
		m_PadData = NULL;
	}

	m_PadData = new StPadData[player];
	for( int i = 0 ; i < player ; i++ ){
		memset( &m_PadData[i], 0, sizeof(m_PadData[i]) );
	}

	if (m_DIkeyDevice) m_DIkeyDevice->Acquire();	//�L�[�{�[�h�ɋ��\��
	
	return S_OK;

}

//-----------------------------------------------------------------------------------------
// Input�Ǘ��֐�
//-----------------------------------------------------------------------------------------


bool WINAPI CInput::ProcessKBInput()

{

    #define KEYDOWN(name, key) (name[key] & 0x80)

    char     buffer[256];
    HRESULT  hr;

    hr = m_DIkeyDevice->GetDeviceState(sizeof(char)*256,buffer);
    if FAILED(hr)
    {
        DI_Term();
		return false;
	}

	return true;
}
