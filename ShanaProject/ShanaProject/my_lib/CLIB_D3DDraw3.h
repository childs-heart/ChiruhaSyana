#pragma once
#include "CLIB_DispObj.h"
#include "CLIB_D3DDraw.h"
#include <d3d9.h>
#include <d3d9types.h>

//==============================================================
// •`‰æƒNƒ‰ƒX
//==============================================================
class CD3DDraw3:public CD3DDraw{
private:
public:
	bool Draw3( CDispObj* disp, float x, float y, float z );
};
