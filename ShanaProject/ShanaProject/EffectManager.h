#pragma once

enum ENUM_EFFECT_LIST{
	ENUM_EFFECT_HIT001 = 0,
	ENUM_EFFECT_HIT002,
	ENUM_EFFECT_HIT003,
	ENUM_EFFECT_HIT004,
	ENUM_EFFECT_HIT005,
	ENUM_EFFECT_HIT006,
	ENUM_EFFECT_HIT007,
	ENUM_EFFECT_HIT008,

	ENUM_EFFECT_ACTION001,
	ENUM_EFFECT_ACTION002,
	ENUM_EFFECT_ATTACK001,
	ENUM_EFFECT_GUARD001,

	ENUM_EFFECT_SHANA_OPT
};

// ëOï˚éQè∆
class CResBattle;
class CShanaProt;

#include "CLIB_Sprite.h"

class CEffectManager{
public:
	static void CreateEffect( CCommonData *common, ENUM_EFFECT_LIST effectNo, CResBattle * res
							, void* target, void* param1=NULL, void* param2=NULL, void* param3=NULL );	
};
