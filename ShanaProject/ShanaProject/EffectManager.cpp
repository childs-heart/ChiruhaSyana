/************************/
/* エフェクトマネージャ	*/
/************************/

#include "EffectManager.h"
#include "CLIB_Element.h"

#include "EffHit001.h"
#include "EffHit002.h"
#include "EffHit003.h"
#include "EffHit004.h"
#include "EffHit005.h"
#include "EffHit006.h"
#include "EffHit007.h"
#include "EffHit008.h"

#include "EffAction01.h"
#include "EffAction02.h"
#include "EffAttack001.h"
#include "EffGuard001.h"

#include "EffShanaOpt.h"

void CEffectManager::CreateEffect( CCommonData *common, ENUM_EFFECT_LIST effectNo, CResBattle * res
								   , void* target, void* param1, void* param2, void* param3 )
{
	switch( effectNo ){
	case ENUM_EFFECT_HIT001:
		new( common )CEffHit001( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_HIT002:
		new( common )CEffHit002( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_HIT003:
		new( common )CEffHit003( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_HIT004:
		new( common )CEffHit004( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_HIT005:
		new( common )CEffHit005( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_HIT006:
		new( common )CEffHit006( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_HIT007:
		new( common )CEffHit007( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_HIT008:
		new( common )CEffHit008( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_ACTION001:
		new( common )CEffAction01( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_ACTION002:
		new( common )CEffAction02( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_ATTACK001:
		new( common )CEffAttack001( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_GUARD001:
		new( common )CEffGuard001( res, (CShanaProt*)target );
	break;

	case ENUM_EFFECT_SHANA_OPT:
		new( common )CEffShanaOpt( res, (CSprite*)target );
	break;
	}
}
