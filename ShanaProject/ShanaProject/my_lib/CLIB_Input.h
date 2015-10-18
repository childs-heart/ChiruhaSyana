#include <dinput.h>		//�C���v�b�g�p

// 2003/12/04 T.Shimizu�@
#ifndef __DI_INPUT
#define	__DI_INPUT

//-----------------------------------------------------------------------------------------
// �C���v�b�g�N���X�����g�p��p �萔
//-----------------------------------------------------------------------------------------
// �_�C���N�g�C���v�b�g
// �p�b�h���͊֌W
#define PADPUT(a)	(a !=  0 )
#define PADUP(a)	(a <= -200)
#define PADDOWN(a)	(a >=  200)
#define PADLEFT(a)	(a <= -200)
#define PADRIGHT(a)	(a >=  200)
#define NOPAD(a)	(a  >  -200 && a < 200 && a > -200 && a < 200)

// �R�}���h�֌W
#define CMD_BUF_MAX				100				// �R�}���h�o�b�t�@�}�b�N�X
#define DINPUT_RANGE_MAX		1000			// �p�b�h�͈�

//-----------------------------------------------------------------------------------------
// �}�N��
//-----------------------------------------------------------------------------------------

#define		RELEASE(x)	{if(x){x->Release();x=NULL;}}			// ���

// �C���v�b�g�N���X
// �p�b�h���͊֌W
// 12/08 t.shimizu enum���ǉ��@�]����define����Input.h�Ɉړ�
enum{
	PAD_NONE		= 0x00000000,
	PAD_MASK_DIR	= 0x000000FF,
	PAD_UP			= 0x00000001,
	PAD_DOWN		= 0x00000002,
	PAD_RIGHT		= 0x00000004,
	PAD_LEFT		= 0x00000008,
	PAD_UP_ON		= 0x00000011,
	PAD_DOWN_ON		= 0x00000022,
	PAD_RIGHT_ON	= 0x00000044,
	PAD_LEFT_ON		= 0x00000088,
	PAD_MASK_BUTTON	= 0x00FFFF00,
	PAD_BUTTON1		= 0x00000100,
	PAD_BUTTON2		= 0x00000200,
	PAD_BUTTON3		= 0x00000400,
	PAD_BUTTON4		= 0x00000800,
	PAD_BUTTON5		= 0x00001000,
	PAD_BUTTON6		= 0x00002000,
	PAD_BUTTON7		= 0x00004000,
	PAD_BUTTON8		= 0x00008000,
	PAD_BUTTON1_ON	= 0x00010100,
	PAD_BUTTON2_ON	= 0x00020200,
	PAD_BUTTON3_ON	= 0x00040400,
	PAD_BUTTON4_ON	= 0x00080800,
	PAD_BUTTON5_ON	= 0x00101000,
	PAD_BUTTON6_ON	= 0x00202000,
	PAD_BUTTON7_ON	= 0x00404000,
	PAD_BUTTON8_ON	= 0x00808000,

	PAD_OR			= 0x01000000,
	PAD_AND			= 0x02000000,

	PAD_END			= 0xF0000000,
	PAD_ERROR		= 0xF0000000,

	PAD_ETC			= 0x80000000
};

typedef struct ST_PAD_DATA{
	long m_Left;
	long m_Right;
	long m_Up;
	long m_Down;
	BYTE m_Buttom[256];
	unsigned long m_MergeData;
}StPadData;

typedef struct st_config_data
{
	unsigned char	m_PadNo[20];
	unsigned long	m_Data[20];
}StConfigData;

//-----------------------------------------------------------------------------------------
// �C���v�b�g�N���X
//-----------------------------------------------------------------------------------------
class CInput{
public:
	// �ϐ�
	LPDIRECTINPUT8				m_DI;					// DirectInput�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8		m_DIkeyDevice;			// �L�[�{�[�h�f�o�C�X
	LPDIRECTINPUTDEVICE8*		m_DIPadDevice;			// �p�b�h�f�o�C�X

	// �֐�
	~CInput();
	CInput( HINSTANCE hinst, HWND hwnd, int player_num = 4 );
	void UpDateState( );
	void UpDateState_Key( );
	void UpDateState_Pad( );
	bool DIinit( HINSTANCE hinst, HWND win_hwnd, int player );		// ������ (��������v���C���[��)

	unsigned long  IsLeft( char num );
	unsigned long  IsRight( char num );
	unsigned long  IsUp( char num );
	unsigned long  IsDown( char num );
	unsigned long  IsButtom( char num , char buttom );
	unsigned long GetPadData( int player );

	void	SetPadData( int player, unsigned long pad_data );

	char* GetKeyData(){ return m_KeyData; };
	StPadData* GetPadData(){ return m_PadData; };
	int GetUsePad(){ return m_UsePad; };

	void SetConfigData( int player, unsigned long *data );

private:
	// �ϐ�
	int				m_UsePad;			// �F�������p�b�h��
	int				m_Player;			// �v���C���[��
	DIJOYSTATE2		m_DIKeyborad;		
	DIJOYSTATE2		*m_DIJoyPad;			
	StPadData		*m_PadData;			// �p�b�h�f�[�^ (�z�� �v���C���[���Ԃ�)
	char			m_KeyData[256];
	StConfigData	m_ConfigData[2];

	// �֐�
	HRESULT	DISetJoystick( HWND hwnd );
	void WINAPI DI_Term();
	bool WINAPI ProcessKBInput();
	void Convert();
	void Merge();
	void MergeConfig();

};

#endif
