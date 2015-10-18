#pragma once
#include "CLIB_DispObj.h"
#include "CLIB_D3DDraw.h"
#include <d3d9.h>
#include <d3d9types.h>

//==============================================================
// •`‰æƒNƒ‰ƒX
//==============================================================
class CD3DDraw2:public CD3DDraw{
private:
public:
	bool Draw2( CDispObj* disp , int param1 );
};
